#pragma once
#include<iostream>
#include<vector>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<array>
constexpr unsigned char CELL_SIZE = 16;//the size of a CELL

constexpr unsigned short SCREEN_WIDTH = 272;//the width of screen
constexpr unsigned short SCREEN_HEIGHT = 240;

constexpr float MAX_VERTICAL_SPEED = 1.8;
constexpr float GRAVITY = 0.1;

constexpr float MAX_RIGHT_SPEED = 0.9;//max right speed as it said
constexpr float MAX_LEFT_SPEED = -MAX_RIGHT_SPEED;

constexpr unsigned char JUMP_TIMER = 50;//which is used to make Mario jump higher when you press longer
constexpr float POWER = 0.05;//acceleration of Mario
constexpr float FRICTION = 0.02;//friction of the floor
constexpr float JUMP_SPEED = -2;

enum Cell {
	Empty,
	Wall,
	Brick,
	Coin,
	Pipe1,
	Pipe2,
	Pipe3,
	Pipe4,
	QuestionBlock,
	QuestionBlockChanged,
	FlagPole,
	Flag
};

typedef std::vector<std::vector<Cell>> Map;
