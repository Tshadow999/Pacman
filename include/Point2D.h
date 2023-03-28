#pragma once

// Create a container for an (x,y) point.
struct Point2D {
    int x;
    int y;

    // Add in a constructor
    Point2D(int x, int y) : x{ x }, y{ y } {}

    bool operator == (Point2D other) {
        return (other.x == x && other.y == y);
    }

    bool operator != (Point2D other) {
        return !operator==(other);
    }

    int GetDistanceTo(Point2D other) {
        if (x > other.x) {
            return (x - other.x) * (x - other.x) + (y - other.y) * (y - other.y);
        }
        return (other.x - x) * (other.x - x) + (other.y - y) * (other.y - y);

    }
};