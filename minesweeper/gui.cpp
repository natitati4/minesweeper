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
sf::Texture clearingDeviceTexture;
sf::Texture gameTextTexture;
sf::Sprite clearingDeviceSprite;

std::unordered_map<std::string, std::vector<int>> difficultyMap{
    {"Beginner", {9, 9, 10}},
    {"Intermediate", {15, 15, 35}},
    {"Expert", {30, 18, 100}}
};

std::string currDifficulty = "Intermediate";
int numRows = difficultyMap[currDifficulty][0];
int numCols = difficultyMap[currDifficulty][1];
int numMines = difficultyMap[currDifficulty][2];
int windowWidth = CELL_SIZE * numRows;
int windowHeight = CELL_SIZE * numCols + MENU_HEIGHT;

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

    if (!clearingDeviceTexture.loadFromFile("Images/cleaningDevice.png"))
        return false;

    // Everything fine, return true
    return true;
}

bool checkButtonPressed(const sf::RenderWindow& window, sf::Text& button)
{
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
    sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

    if (button.getGlobalBounds().contains(mousePositionF))
    {
        button.setFillColor(BUTTON_COLOR_HOVER);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            button.setFillColor(BUTTON_COLOR_PRESSED);
            return true;
        }
    }

    else
    {
        button.setFillColor(BUTTON_COLOR_IDLE);
    }

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
    std::vector<std::vector<sf::Sprite>> guiGrid(numRows, std::vector<sf::Sprite>(numCols));

    // Set the position and scale of each sprite
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            guiGrid[i][j].setTexture(unrevealedEmptyTexture);
            guiGrid[i][j].setPosition(i * CELL_SIZE, MENU_HEIGHT + j * CELL_SIZE);

            // Rescale to CELL_SIZE (multiply by CELL_SIZE / IMAGE_DIMENSION, for both x and y) 
            guiGrid[i][j].setScale((float)CELL_SIZE / unrevealedEmptyTexture.getSize().x, (float)CELL_SIZE / unrevealedEmptyTexture.getSize().y);
        }
    }

    return guiGrid;
}

void setupMenu(sf::Font& font, sf::RectangleShape& menuBackground, sf::Text& resetButton, sf::Text& flagsText, 
                sf::Text& gameButton, std::vector<sf::Text>& dropdownOptions, sf::RectangleShape& dropdownBackground)
{
    // Menu background
    menuBackground.setFillColor(sf::Color(200, 200, 200));
    menuBackground.setSize(sf::Vector2f(windowWidth, MENU_HEIGHT));

    // Reset button
    resetButton.setPosition(10, 0);
    
    // Flags left text
    flagsText.setPosition(10 + resetButton.getGlobalBounds().width, MENU_HEIGHT / 2);

    // Game button
    gameButton.setPosition(windowWidth - gameButton.getGlobalBounds().width - 5, 0);

    // Dropdown background
    dropdownBackground.setPosition(windowWidth - dropdownOptions[1].getGlobalBounds().width,
        gameButton.getPosition().y + gameButton.getGlobalBounds().height);
    dropdownBackground.setFillColor(sf::Color::White);
    dropdownBackground.setOutlineThickness(1);
    dropdownBackground.setOutlineColor(sf::Color::Black);

    // Dropdown options
    for (int i = 0; i < dropdownOptions.size(); i++)
    {
        dropdownOptions[i].setFillColor(sf::Color::Black);
        dropdownOptions[i].setPosition(dropdownBackground.getGlobalBounds().left,
            dropdownBackground.getGlobalBounds().top + dropdownOptions[0].getGlobalBounds().height * i);
    }

    // Cleaning device
    clearingDeviceSprite.setTexture(clearingDeviceTexture);
    clearingDeviceSprite.setPosition(0, -static_cast<float>(clearingDeviceTexture.getSize().y));
    clearingDeviceSprite.setScale(static_cast<float>(windowWidth) / clearingDeviceTexture.getSize().x,
        static_cast<float>(CLEANING_DEVICE_HEIGHT) / clearingDeviceTexture.getSize().y);
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

        case FLAG_EMPTY:
        {
            setAppropriateTexture(guiGrid, row, col, flagTexture);
            break;
        }

        case FLAG_MINE:
        {
            setAppropriateTexture(guiGrid, row, col, flagTexture);
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
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            textureForSquare(guiGrid, gameGrid, i, j);
        }
    }
}

bool checkWin(std::vector<std::vector<char>>& gameGrid)
{
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            // If there's an empty square (either with a flag or not) that wasn't clicked, no win
            if (gameGrid[i][j] == UNREVEALED_EMPTY || gameGrid[i][j] == FLAG_EMPTY)
                return false;
        }
    }

    return true;
}

void loseScreen(std::vector<std::vector<sf::Sprite>>& guiGrid, std::vector<std::vector<char>>& gameGrid, int pressedMineRow, int pressedMineCol)
{
    // Set the position and scale of each sprite
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            if (gameGrid[i][j] == UNREVEALED_MINE)
                setAppropriateTexture(guiGrid, i, j, unpressedMineTexture);
        }
    }

    // Set texture for the pressed mine
    setAppropriateTexture(guiGrid, pressedMineRow, pressedMineCol, pressedMineTexture);
}

void startGame()
{
    if (!initTextures())
        return;

    sf::Font font;
    if (!font.loadFromFile("ArialFont/arial.ttf"))
        return;

    std::vector<std::vector<char>> gameGrid = initGameGrid(numRows, numCols, numMines);
    std::vector<std::vector<sf::Sprite>> guiGrid = initGuiGrid();

    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Minesweeper", sf::Style::Titlebar | sf::Style::Close);
    
    sf::RectangleShape menuBackground(sf::Vector2f(window.getSize().x, MENU_HEIGHT));
    sf::Text resetButton("Reset", font, 18);
    sf::Text gameButton("Game", font, 18);
    sf::Text flagsText("Flags: " + std::to_string(numMines) , font, 18);
    flagsText.setFillColor(sf::Color::Red);
    std::vector<sf::Text> dropdownOptions;
    dropdownOptions.emplace_back("Beginner", font, 16);
    dropdownOptions.emplace_back("Intermediate", font, 16);
    dropdownOptions.emplace_back("Expert", font, 16);
    dropdownOptions.emplace_back("Custom", font, 16);
    sf::RectangleShape dropdownBackground(sf::Vector2f(dropdownOptions[1].getGlobalBounds().width,
                                            dropdownOptions[0].getGlobalBounds().height * dropdownOptions.size()));

    setupMenu(font, menuBackground, resetButton, flagsText, gameButton, dropdownOptions, dropdownBackground);

    bool gameWon = false;
    bool gameLost = false;
    bool isDropdownOpen = false;
    bool isClearingAnimationFinished = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            else if (event.type == sf::Event::MouseButtonReleased)
            {
                // Get the mouse position relative to the window
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousePositionF(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

                std::cout << "Coords" << mousePosition.x << ", " << mousePosition.y << std::endl;

                // If pressed the menu bar or the tiny pixel row at the bottom, or if out of X bounds, ignore.
                if (mousePositionF.y < MENU_HEIGHT || windowHeight - 1 < mousePositionF.y || mousePositionF.y < 0 || windowWidth < mousePositionF.x)
                {
                    // If pressed somewhere else in menu and not pressed game button, close menu
                    if (mousePosition.y < MENU_HEIGHT && !gameButton.getGlobalBounds().contains(mousePositionF))
                        isDropdownOpen = false;

                    continue;
                }

                if (event.mouseButton.button == sf::Mouse::Left && !gameLost && !gameWon)
                {
                    // Calculate the grid indices based on the mouse position
                    int row = mousePositionF.x / CELL_SIZE;
                    int col = mousePositionF.y / CELL_SIZE - MENU_HEIGHT / CELL_SIZE;

                    // Pressed a mine
                    if (gameGrid[row][col] == UNREVEALED_MINE)
                    {
                        loseScreen(guiGrid, gameGrid, row, col);
                        gameLost = true;
                    }
                    
                    // Pressed empty square
                    else if (gameGrid[row][col] == UNREVEALED_EMPTY)
                    {
                        updateGameGrid(gameGrid, row, col);
                        updateGuiGrid(guiGrid, gameGrid);

                        if (checkWin(gameGrid))
                        {
                            gameWon = true;

                            // Start the clearing animation
                            isClearingAnimationFinished = false;
                        }
                    }
                }

                else if (event.mouseButton.button == sf::Mouse::Right && !gameLost && !gameWon)
                {
                    // Calculate the grid indices based on the mouse position
                    int row = mousePositionF.x / CELL_SIZE;
                    int col = mousePositionF.y / CELL_SIZE - MENU_HEIGHT / CELL_SIZE;

                    // Pressed outside
                    if (row == -1)
                        return;

                    switch (gameGrid[row][col])
                    {
                        case UNREVEALED_EMPTY:
                            gameGrid[row][col] = FLAG_EMPTY;
                            numMines--;
                            break;

                        case UNREVEALED_MINE:
                            gameGrid[row][col] = FLAG_MINE;
                            numMines--;
                            break;

                        case FLAG_EMPTY:
                            gameGrid[row][col] = UNREVEALED_EMPTY;
                            numMines++;
                            break;

                        case FLAG_MINE:
                            gameGrid[row][col] = UNREVEALED_MINE;
                            numMines++;
                            break;

                        default:
                            break;
                    }

                    flagsText.setString("Flags: " + std::to_string(numMines));
                    updateGuiGrid(guiGrid, gameGrid);
                }
            }
        }

        if (checkButtonPressed(window, resetButton))
        {
            numRows = difficultyMap[currDifficulty][0];
            numCols = difficultyMap[currDifficulty][1];
            numMines = difficultyMap[currDifficulty][2];
            windowWidth = CELL_SIZE * numRows;
            windowHeight = CELL_SIZE * numCols + MENU_HEIGHT;

            window.setSize(sf::Vector2u(windowWidth, windowHeight));
            window.setView(sf::View(sf::Vector2f(windowWidth / 2, windowHeight / 2), sf::Vector2f(windowWidth, windowHeight)));
            gameGrid = initGameGrid(numRows, numCols, numMines);
            guiGrid = initGuiGrid();
            flagsText.setString("Flags: " + std::to_string(numMines));
            setupMenu(font, menuBackground, resetButton, flagsText, gameButton, dropdownOptions, dropdownBackground);

            gameWon = false;
            gameLost = false;
        }

        if (checkButtonPressed(window, gameButton))
            isDropdownOpen = true;

        // Animation update
        if (gameWon && !isClearingAnimationFinished)
        {
            clearingDeviceSprite.move(0, 0.09); // Move the clearing device downwards

            // Check if the clearing device has reached the bottom of the screen
            if (clearingDeviceSprite.getPosition().y >= windowHeight)
            {
                isClearingAnimationFinished = true;
                MessageBox(NULL, L"You win", L"Congratulations", MB_ICONASTERISK);
            }
        }

        window.clear(sf::Color::White);
        drawGrid(window, guiGrid);
        window.draw(menuBackground);
        window.draw(gameButton);
        window.draw(flagsText);

        // Draw the dropdown options if the dropdown is open
        if (isDropdownOpen)
        {
            window.draw(dropdownBackground);
            for (auto& option : dropdownOptions)
            {
                window.draw(option);
                if (checkButtonPressed(window, option))
                {
                    // Change difficulty
                    currDifficulty = option.getString();
                }
            }
        }

        window.draw(resetButton);
        window.draw(clearingDeviceSprite);
        window.display();
    }
}

