#pragma once

#include "GameManager.h"
#include "GameObjectStruct.h"

struct PacmanStruct : GameObjectStruct {
    PacmanStruct(int xPos, int yPos, Direction direction) : GameObjectStruct{ xPos, yPos, PACMAN, direction } {}

    PacmanStruct(Point2D position, Direction direction) : GameObjectStruct{ position.x, position.y, PACMAN, direction } {}

    /// <summary>
    /// Allows pacman to eat / not eat the ghosts
    /// </summary>
    /// <param name="toggle">true for eating, false for no eating</param>
    void ToggleGhostEating(bool toggle) {
        _canEatGhosts = toggle;
    }

    void Eat() {
        auto& manager = GameManager::Get(); 

        auto currentPos = Point2D(x, y);

        // Eat the dot if there is one at the current position
        if (manager.GetValueAt(currentPos) == Dot) {
            manager.SetValueAt(currentPos, 0);
        }

        // Eat the Energizer
        if (manager.GetValueAt(currentPos) == Energizer) {
            manager.SetValueAt(currentPos, 0);
        }

        // Eat the Energizer
        if (manager.GetValueAt(currentPos) == Fruit) {
            manager.SetValueAt(currentPos, 0);
        }

        // Eat the ghost
        if (_canEatGhosts) {
            manager.TryEatGhost(currentPos);
        }

    }
protected: 
    bool _canEatGhosts{ false };
};