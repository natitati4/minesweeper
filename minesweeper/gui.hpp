#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Windows.h>
#include "minesweeper.hpp"

#define CELL_SIZE 20

#define MENU_HEIGHT 40
#define DROPDOWN_WIDTH 120
#define DROPDOWN_HEIGHT 30

#define RESET_BUTTON_WIDTH 80
#define RESET_BUTTON_HEIGHT 30
#define RESET_BUTTON_COLOR_IDLE sf::Color(0, 255, 0)    // Green color for idle state
#define RESET_BUTTON_COLOR_HOVER sf::Color(255, 255, 0)  // Yellow color for hover state
#define RESET_BUTTON_COLOR_PRESSED sf::Color(255, 0, 0)  // Red color for pressed state

#define CLEANING_DEVICE_HEIGHT 30

#define WINDOW_WIDTH CELL_SIZE * DEFAULT_ROWS_NUM
#define WINDOW_HEIGHT CELL_SIZE * DEFAULT_COLS_NUM + MENU_HEIGHT

void startGame();