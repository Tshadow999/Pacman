#include "GameManager.h"
#include "Pacman.h"
#include "GameObjectStruct.h"
#include "Ghost.h"
#include "UI.h"
#include <SDL2/SDL.h>
#include <vector>
#include <thread>

Uint32 gameUpdate(Uint32 interval, void* /*param*/)
{
    // Do game loop update here
    return interval;
}

int main(int /*argc*/, char** /*argv*/)
{
    GameManager& manager = GameManager::Get();

    // Give the UI a location in memory rather than the board itself,
    // So it updates automatically
    UI ui(manager.GetBoard());

    // Start timer for game update, call this function every 100 ms.
    SDL_TimerID timer_id = SDL_AddTimer(100, gameUpdate, static_cast<void*>(nullptr));

    // Initialize pacman
    PacmanStruct pacman{13, 11, UP};
    manager.SetPacman(&pacman);

    // Create the ghosts
    ClydeGhost clyde{ 12,13 };
    InkyGhost inky{ 13,13 };
    BlinkyGhost blinky{ 14,13 };
    PinkyGhost pinky{ 15,13 };

    manager.AddGhost(&clyde);
    manager.AddGhost(&inky);
    manager.AddGhost(&blinky);
    manager.AddGhost(&pinky);

    bool quit = false;

    while (!quit) {
        // set timeout to limit frame rate
        Uint32 timeout = SDL_GetTicks() + 100;

        // Handle the input
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            // Quit button.
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            // All keydown events
            if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                case SDLK_LEFT:
                    pacman.dir = LEFT;
                    break;
                case SDLK_RIGHT:
                    pacman.dir = RIGHT;
                    break;
                case SDLK_UP:
                    pacman.dir = UP;
                    break;
                case SDLK_DOWN:
                    pacman.dir = DOWN;
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
                case SDLK_r:
                    // Reset the game
                    manager.Reset();
                    break;
                }
            }
        }

        if (manager.IsLevelCompleted()) continue;

        Point2D pacmanNextPos = pacman.GetNextPosition();

        if (manager.CanMove(pacmanNextPos)) {
            pacman.x = pacmanNextPos.x;
            pacman.y = pacmanNextPos.y;
            pacman.Eat();
        }

        // move the ghosts
        inky.Tick();
        clyde.Tick();
        pinky.Tick();
        blinky.Tick();

        if (manager.GetScore() >= 100) {
            manager.ToggleGhostMovement(true);
        }

        // Set the score
        ui.setScore(manager.GetScore());

        // Set the amount of lives
        ui.setLives(manager.GetLives());

        std::vector<GameObjectStruct> objects = { pacman, clyde, inky, blinky, pinky };

        // Update the sprites
        ui.update(objects);

        while (!SDL_TICKS_PASSED(SDL_GetTicks(), timeout)) {}
    }

    SDL_RemoveTimer(timer_id);

    return 0;
}
