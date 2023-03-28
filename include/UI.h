/**
 * \file
 * Description of UI.h file.
 */

/*
 *  Created on: Jan 29, 2015
 *      Author: frits
 *       Group: TA's
 */

#ifndef SRC_UI_H_
#define SRC_UI_H_

#include "GameObjectStruct.h"
#include "Collidable.h"

#include <SDL2/SDL.h>

#include <map>
#include <vector>
#include <string>

/**
 * Description of UI class
 */
class UI
{
  public:
    /// Constructor initializes the UI fully.
    ///
    /// Creates a main (SDL) window for rendering, and loads the sprites from a
    /// bitmap on disk.
    ///
    /// \param map the map of the board
    UI(std::vector<std::vector<short>> map);

    // UI objects should not be copied or moved.
    UI(const UI&) = delete;
    UI(const UI&&) = delete;
    UI &operator=(const UI &) = delete;

    /// Destructor fully de-initializes the UI, including closing the main window.
    ~UI();

    void SetBoard(std::vector<std::vector<short>> _map) {
        map = _map;
    }

    /// Setter for the score.
    ///
    /// \param score score
    void setScore(int score);

    void PrintMap();

    /// Setter for the lives.
    /// @param lives lives
    void setLives(int lives);

    /// Update the screen
    /// - Draw the background
    /// - Draw the score
    /// - Draw the remaining lives
    /// - Draw the objects (last)
    ///
    /// \param objects Objects that are drawn last.
    void update(std::vector<GameObjectStruct> objects);

  private:
    void init();

    /// Loads the sprite sheet.
    void loadTextures();

    /// Load the maps that contains all the clipping masks.
    ///
    /// The clipping masks are stored in #clips. Usage is:
    /// `clips[<type>][<direction>]`.
    void loadMaps();

    /// Draws walls onto the screen according to \p map
    /// \param map A 2-by-2 grid indicating which grid locations are walls.
    void drawBackground(std::vector<std::vector<short>> &map);

    /// Draws the score onto the screen.
    void drawScore();

    /// Draws the lives onto the screen.
    void drawLives();

    /// Loads an image into a texture on the rendering device
    /// \param file The image file to load
    /// \return the loaded texture, or nullptr if something went wrong.
    SDL_Texture *loadTexture(const std::string &file);

  private:
    /// Total score.
    int score = 0;

    /// Pacman lives.
    int lives = 3;

    /// Main game UI window.
    SDL_Window *window;
    /// SDL Renderer to draw items onto #window.
    SDL_Renderer *renderer;
    /// Loaded SDL texture with all sprite bitmaps.
    SDL_Texture *sheet;

    /// 2d array containing the map, a 1 is a wall.
    std::vector<std::vector<short>> map;

    /// Map containing all the game objects.
    ///
    /// Stores the clipping masks related to UI::sheet. Usage is:
    /// `clips[<type>][<direction>]`.
    /// \see Type
    /// \see Direction
    std::map<Type, std::map<Direction, SDL_Rect>> clips;

    enum { TILESIZE = 24 };
};

#endif /* SRC_UI_H_ */
