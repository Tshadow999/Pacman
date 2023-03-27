#pragma once

// Create a container for an (x,y) point.
struct Point2D {
    int x;
    int y;

    // Add in a constructor
    Point2D(int x, int y) : x{ x }, y{ y } {}
};