#include "gui.hpp"

sf::Texture unrevealedEmptyTexture;
sf::Texture revealedEmptyTexture;
sf::Texture pressedMineTexture;
sf::Texture unpressedMineTexture;
sf::Texture flagTexture;
sf::Texture num1Texture;
sf::Texture num2Texture;
sf::Texture num3Texture;
sf::Texture num4Texture;
sf::Texture num5Texture;
sf::Texture num6Texture;
sf::Texture num7Texture;
sf::Texture num8Texture;

bool initTextures()
{
    if (!unrevealedEmptyTexture.loadFromFile("Images/unrevealed_empty.png"))
        return false;
    
    if (!revealedEmptyTexture.loadFromFile("Images/revealed_empty.png"))
        return false;

    if (!pressedMineTexture.loadFromFile("Images/pressedMine.png"))
        return false;

    if (!unpressedMineTexture.loadFromFile("Images/unpressedMine.png"))
        return false;

    if (!flagTexture.loadFromFile("Images/flag.png"))
        return false;

    if (!num1Texture.loadFromFile("Images/1.png"))
        return false;

    if (!num2Texture.loadFromFile("Images/2.png"))
        return false;

    if (!num3Texture.loadFromFile("Images/3.png"))
        return false;

    if (!num4Texture.loadFromFile("Images/4.png"))
        return false;

    if (!num5Texture.loadFromFile("Images/5.png"))
        return false;

    if (!num6Texture.loadFromFile("Images/6.png"))
        return false;

    if (!num7Texture.loadFromFile("Images/7.png"))
        return false;

    if (!num8Texture.loadFromFile("Images/8.png"))
        return false;

    
    // Everything fine, return true
    return true;
}

bool checkResetButtonPressed(sf::RenderWindow& window, sf::Text& resetButton)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (resetButton.getGlobalBounds().contains(mousePositionF))
    {
        resetButton.setFillColor(RESET_BUTTON_COLOR_HOVER);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            resetButton.setFillColor(RESET_BUTTON_COLOR_PRESSED);
            return true;
        }
    }

    else
        resetButton.setFillColor(RESET_BUTTON_COLOR_IDLE);

    return false;
}

void drawGrid(sf::RenderWindow& window, const std::vector<std::vector<sf::Sprite>>& grid)
{
    for (int i = 0; i < grid.size(); i++)
    {
        for (int j = 0; j < grid[0].size(); j++)
        {
            window.draw(grid[i][j]);
        }
    }
}

std::vector<std::vector<sf::Sprite>> initGuiGrid()
{
    std::vector<std::vector<sf::Sprite>> guiGrid(DEFAULT_ROWS_NUM, std::vector<sf::Sprite>(DEFAULT_COLS_NUM));

    // Set the position and scale of each sprite
    for (int i = 0; i < DEFAULT_ROWS_NUM; i++)
    {
        for (int j = 0; j < DEFAULT_COLS_NUM; j++)
        {
            guiGrid[i][j].setTexture(unrevealedEmptyTexture);
            guiGrid[i][j].setPosition(i * CELL_SIZE, MENU_HEIGHT + j * CELL_SIZE);

            // Rescale to CELL_SIZE (multiply by CELL_SIZE / IMAGE_DIMENSION, for both x and y) 
            guiGrid[i][j].setScale((float)CELL_SIZE / unrevealedEmptyTexture.getSize().x, (float)CELL_SIZE / unrevealedEmptyTexture.getSize().y);
        }
    }

    return guiGrid;
}

void setAppropriateTexture(std::vector<std::vector<sf::Sprite>>& guiGrid, int row, int col, sf::Texture& texture)
{
    guiGrid[row][col].setTexture(texture);
    guiGrid[row][col].setPosition(row * CELL_SIZE, MENU_HEIGHT + col * CELL_SIZE);
    guiGrid[row][col].setScale((float)CELL_SIZE / texture.getSize().x, (float)CELL_SIZE / texture.getSize().y);
}

void textureForSquare(std::vector<std::vector<sf::Sprite>>& guiGrid, std::vector<std::vector<char>>& gameGrid, int row, int col)
{
    int ch = gameGrid[row][col];

    switch (ch)
    {
        case UNREVEALED_EMPTY:
        {
            setAppropriateTexture(guiGrid, row, col, unrevealedEmptyTexture);
            break;
        }

        case UNREVEALED_MINE:
        {
            setAppropriateTexture(guiGrid, row, col, unrevealedEmptyTexture);
            break;
        }

        case REVEALED_EMPTY:
        {
            setAppropriateTexture(guiGrid, row, col, revealedEmptyTexture);
            break;
        }

        case 1:
        {
            setAppropriateTexture(guiGrid, row, col, num1Texture);
            break;
        }

        case 2:
        {
            setAppropriateTexture(guiGrid, row, col, num2Texture);
            break;
        }

        case 3:
        {
            setAppropriateTexture(guiGrid, row, col, num3Texture);
            break;
        }

        case 4:
        {
            setAppropriateTexture(guiGrid, row, col, num4Texture);
            break;
        }

        case 5:
        {
            setAppropriateTexture(guiGrid, row, col, num5Texture);
            break;
        }

        case 6:
        {
            setAppropriateTexture(guiGrid, row, col, num6Texture);
            break;
        }

        case 7:
        {
            setAppropriateTexture(guiGrid, row, col, num7Texture);
            break;
        }

        case 8:
        {
            setAppropriateTexture(guiGrid, row, col, num8Texture);
            break;
        }

        default:
            std::cout << ch << std::endl;

    }
}

void updateGuiGrid(std::vector<std::vector<sf::Sprite>>& guiGrid, std::vector<std::vector<char>>& gameGrid)
{
    // Set the position and scale of each sprite
    for (int i = 0; i < DEFAULT_ROWS_NUM; i++)
    {
        for (int j = 0; j < DEFAULT_COLS_NUM; j++)
        {
            textureForSquare(guiGrid, gameGrid, i, j);
        }
    }
}

void loseScreen(std::vector<std::vector<sf::Sprite>>& guiGrid, std::vector<std::vector<char>>& gameGrid, int pressedMineRow, int pressedMineCol)
{
    // Set the position and scale of each sprite
    for (int i = 0; i < DEFAULT_ROWS_NUM; i++)
    {
        for (int j = 0; j < DEFAULT_COLS_NUM; j++)
        {
            if (gameGrid[i][j] == UNREVEALED_MINE)
                setAppropriateTexture(guiGrid, i, j, unpressedMineTexture);
        }
    }

    setAppropriateTexture(guiGrid, pressedMineRow, pressedMineCol, pressedMineTexture);
}

void startGame()
{
    if (!initTextures())
        return;

    std::vector<std::vector<char>> gameGrid = initGameGrid(DEFAULT_ROWS_NUM, DEFAULT_COLS_NUM, DEFAULT_MINES_NUM);
    std::vector<std::vector<sf::Sprite>> guiGrid = initGuiGrid();

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Minesweeper");
    
    sf::RectangleShape menuBar(sf::Vector2f(window.getSize().x, MENU_HEIGHT));
    menuBar.setFillColor(sf::Color(200, 200, 200));

    sf::Font font;
    if (!font.loadFromFile("ArialFont/arial.ttf"))
        return;

    // Button
    sf::Text resetButton("Reset", font, 20);
    resetButton.setPosition(10, (MENU_HEIGHT - RESET_BUTTON_HEIGHT) / 2);

    // Dropdown
    sf::RectangleShape dropdownButton(sf::Vector2f(DROPDOWN_WIDTH, DROPDOWN_HEIGHT));
    dropdownButton.setPosition(window.getSize().x - DROPDOWN_WIDTH - 10, (MENU_HEIGHT - DROPDOWN_HEIGHT) / 2);
    dropdownButton.setFillColor(sf::Color::White);
    dropdownButton.setOutlineThickness(1);
    dropdownButton.setOutlineColor(sf::Color(100, 100, 100));

    sf::Text dropdownText("Difficulty", font, 16);
    dropdownText.setPosition(window.getSize().x - DROPDOWN_WIDTH - 10 + 10, (MENU_HEIGHT - DROPDOWN_HEIGHT) / 2);

    bool gameEnded = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left && !gameEnded)
                {
                    // Get the mouse position relative to the window
                    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                    // If pressed the menu bar, ignore
                    if (mousePosition.y < MENU_HEIGHT)
                        continue;

                    // Calculate the grid indices based on the mouse position
                    int row = mousePosition.x / CELL_SIZE;
                    int col = mousePosition.y / CELL_SIZE - MENU_HEIGHT / CELL_SIZE;

                    // Pressed a mine
                    if (gameGrid[row][col] == UNREVEALED_MINE)
                    {
                        loseScreen(guiGrid, gameGrid, row, col);
                        gameEnded = true;
                    }
                    
                    // Pressed empty square
                    else if (gameGrid[row][col] == UNREVEALED_EMPTY)
                    {
                        updateGameGrid(gameGrid, row, col);
                        updateGuiGrid(guiGrid, gameGrid);
                    }
                }
            }
        }

        if (checkResetButtonPressed(window, resetButton))
        {
            gameGrid = initGameGrid(DEFAULT_ROWS_NUM, DEFAULT_COLS_NUM, DEFAULT_MINES_NUM);
            guiGrid = initGuiGrid();

            gameEnded = false;
        }

        window.clear(sf::Color::White);
        window.draw(menuBar);
        window.draw(resetButton);
        window.draw(dropdownButton);
        window.draw(dropdownText);
        drawGrid(window, guiGrid);
        window.display();
    }
}

