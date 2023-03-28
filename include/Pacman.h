#pragma once

#include "Collidable.h"
#include "GameManager.h"
#include "GameObjectStruct.h"
#include "Point2D.h"

struct PacmanStruct : GameObjectStruct {
    PacmanStruct(int xPos, int yPos, Direction direction) : GameObjectStruct{ xPos, yPos, PACMAN, direction } {}

    PacmanStruct(Point2D position, Direction direction) : GameObjectStruct{ position.x, position.y, PACMAN, direction } {}

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
    }
};