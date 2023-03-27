#pragma once

enum Collidable {
	None = 0,
	Wall = 1,
	Ghost = 2,
	Pacman = 4,
	Energizer = 8,
	Fruit = 16,
	Dot = 32
};