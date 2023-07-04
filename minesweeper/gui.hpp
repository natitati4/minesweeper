#pragma once

#include <iostream>
#include "SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <Windows.h>
#include "minesweeper.hpp"

#define CELL_SIZE 20

#define MENU_HEIGHT 80
#define DROPDOWN_WIDTH 120
#define DROPDOWN_HEIGHT 30

#define RESET_BUTTON_WIDTH 80
#define RESET_BUTTON_HEIGHT 30
#define BUTTON_COLOR_IDLE sf::Color(0x66, 0x99, 0xCC)     // Green color for idle state
#define BUTTON_COLOR_HOVER sf::Color(255, 255, 0)  // Yellow color for hover state
#define BUTTON_COLOR_PRESSED sf::Color(255, 0, 0)  // Red color for pressed state

#define CLEANING_DEVICE_HEIGHT 30

#define GAME_BUTTON_WIDTH 60
#define GAME_BUTTON_HEIGHT MENU_HEIGHT / 2

void startGame();