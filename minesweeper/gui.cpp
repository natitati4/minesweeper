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

void setupMenu(sf::Font& font, sf::RectangleShape& menuBackground, sf::Text& resetButton, sf::Text& difficultyText, sf::Text& flagsText, sf::Text& gameButton,
                std::vector<sf::Text>& dropdownOptions, sf::RectangleShape& dropdownBackground, std::vector<sf::Text>& customChoices,
                sf::RectangleShape& customBackground)
{
    // Menu background
    menuBackground.setFillColor(sf::Color(200, 200, 200));
    menuBackground.setSize(sf::Vector2f(windowWidth, MENU_HEIGHT));

    // Reset button
    resetButton.setPosition(5, 0);

    // Flags left text
    flagsText.setPosition(5 , resetButton.getGlobalBounds().height + 5);

    // Diifculty text
    difficultyText.setPosition(5, flagsText.getGlobalBounds().top + flagsText.getGlobalBounds().height);

    // Game button
    gameButton.setPosition(windowWidth - gameButton.getGlobalBounds().width - 5, 0);

    // Dropdown background
    dropdownBackground.setPosition(windowWidth - dropdownOptions[1].getGlobalBounds().width,
                                    gameButton.getGlobalBounds().top + gameButton.getGlobalBounds().height);
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

    // Custom background
    customBackground.setPosition(windowWidth - dropdownOptions[1].getGlobalBounds().width * 2,
                                    dropdownBackground.getPosition().y);
    customBackground.setFillColor(sf::Color::White);
    customBackground.setOutlineThickness(1);
    customBackground.setOutlineColor(sf::Color::Black);

    // Custom choices input
    for (int i = 0; i < customChoices.size(); i++)
    {
        customChoices[i].setFillColor(DARK_GREEN);
        customChoices[i].setPosition(customBackground.getGlobalBounds().left,
                                        customBackground.getGlobalBounds().top + customChoices[0].getGlobalBounds().height * i);
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
    sf::Text resetButton("Reset", font, 20);
    sf::Text gameButton("Game", font, 20);
    sf::Text difficultyText("Difficulty on reset: " + currDifficulty, font, 16);
    difficultyText.setFillColor(BLACK);
    sf::Text flagsText("Flags: " + std::to_string(numMines) , font, 16);
    flagsText.setFillColor(sf::Color::Red);
    std::vector<sf::Text> dropdownOptions;
    dropdownOptions.emplace_back("Beginner", font, 16);
    dropdownOptions.emplace_back("Intermediate", font, 16);
    dropdownOptions.emplace_back("Expert", font, 16);
    dropdownOptions.emplace_back("Custom", font, 16);
    sf::RectangleShape dropdownBackground(sf::Vector2f(dropdownOptions[1].getGlobalBounds().width,
                                            dropdownOptions[0].getGlobalBounds().height * dropdownOptions.size()));

    // Choices for custom dialog
    std::vector<sf::Text> customChoices;
    customChoices.emplace_back("Width: " + std::to_string(numRows), font, 16);
    customChoices.emplace_back("Height: " + std::to_string(numCols), font, 16);
    customChoices.emplace_back("Mines: " + std::to_string(numMines), font, 16);

    sf::RectangleShape customBackground(sf::Vector2f(customChoices[1].getGlobalBounds().width + 38,
        customChoices[0].getGlobalBounds().height * customChoices.size() + 10));

    setupMenu(font, menuBackground, resetButton, difficultyText, flagsText, gameButton,
                dropdownOptions, dropdownBackground, customChoices, customBackground);

    bool gameWon = false;
    bool gameLost = false;
    bool isDropdownOpen = false;
    bool isCustomOpen = false;
    bool isClearingAnimationFinished = false;

    bool isCursorVisible = true;
    sf::Clock cursorClock;
    int chosenInput = 0;

    std::vector<std::string> inputStates(3);
    for (int i = 0; i < 3; i++)
        inputStates[i] = customChoices[i].getString();

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

                // If pressed the menu bar or the tiny pixel row at the bottom, or if out of X bounds, ignore.
                if (mousePositionF.y < MENU_HEIGHT || windowHeight - 1 < mousePositionF.y || mousePositionF.y < 0 || windowWidth < mousePositionF.x)
                {
                    // If pressed somewhere else in menu and not pressed game button, close menu
                    if (mousePosition.y < MENU_HEIGHT && !gameButton.getGlobalBounds().contains(mousePositionF))
                        isDropdownOpen = false;

                    // If pressed somewhere else in menu and not pressed game button or custom button, close custom
                    if (mousePosition.y < MENU_HEIGHT && !dropdownOptions[3].getGlobalBounds().contains(mousePositionF)
                                                        && !customBackground.getGlobalBounds().contains(mousePositionF))
                        isCustomOpen = false;

                    continue;
                }

                if (event.mouseButton.button == sf::Mouse::Left && !gameLost && !gameWon)
                {
                    // Calculate the grid indices based on the mouse position
                    int row = mousePositionF.x / CELL_SIZE;
                    int col = mousePositionF.y / CELL_SIZE - (float)MENU_HEIGHT / CELL_SIZE;

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
                    int col = mousePositionF.y / CELL_SIZE - (float)MENU_HEIGHT / CELL_SIZE;

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

            // Check for keyboard events
            if (event.type == sf::Event::TextEntered)
            {
                // Check if the selected input is editable, if the custom dialog is open, and if the length hasn't exceeded the custom dialog
                if (0 <= chosenInput && chosenInput < customChoices.size() && isCustomOpen && inputStates[chosenInput].length() < 13)
                {
                    // Check if the entered character is a digit
                    if (std::isdigit(static_cast<char>(event.text.unicode)))
                    {
                        // Append the character to the selected input's text
                        char enteredChar = static_cast<char>(event.text.unicode);
                        inputStates[chosenInput] += enteredChar;
                        customChoices[chosenInput].setString(inputStates[chosenInput]);
                    }
                }
            }

            else if (event.type == sf::Event::KeyPressed)
            {
                // Check if Backspace key is pressed
                if (event.key.code == sf::Keyboard::Backspace)
                {
                    // Remove the last character from the selected input's text
                    if (0 <= chosenInput && chosenInput < customChoices.size())
                    {
                        std::string& selectedText = inputStates[chosenInput];
                        if (!selectedText.empty())
                        {
                            // Check if the last character is a space
                            if (selectedText.back() != ' ')
                            {
                                selectedText.pop_back();
                                customChoices[chosenInput].setString(selectedText);
                            }
                        }
                    }
                }

                // Check if Enter key is pressed
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    // If a space, means deleted all numbers
                    if (!(inputStates[0].back() == ' ') && !(inputStates[1].back() == ' ') && !(inputStates[2].back() == ' '))
                    {
                        // Convert the input strings to integers
                        int tempNumRows = std::stoi(inputStates[0].substr(inputStates[0].find(' ') + 1));
                        int tempNumCols = std::stoi(inputStates[1].substr(inputStates[1].find(' ') + 1));
                        int tempNumMines = std::stoi(inputStates[2].substr(inputStates[2].find(' ') + 1));

                        // If not mines are equal or more than squares num
                        if (tempNumRows * tempNumCols >= tempNumMines && (8 <= tempNumRows && tempNumRows <= 65) && (0 < tempNumCols && tempNumCols <= 35))
                        {
                            numRows = tempNumRows;
                            numCols = tempNumCols;
                            numMines = tempNumMines;
                            isCustomOpen = false; // Close custom dialog
                        }
                    }
                }
            }
        }

        if (checkButtonPressed(window, resetButton))
        {
            if (currDifficulty != "Custom")
            {
                numRows = difficultyMap[currDifficulty][0];
                numCols = difficultyMap[currDifficulty][1];
                numMines = difficultyMap[currDifficulty][2];
            }

            windowWidth = CELL_SIZE * numRows;
            windowHeight = CELL_SIZE * numCols + MENU_HEIGHT;

            window.setSize(sf::Vector2u(windowWidth, windowHeight));
            window.setView(sf::View(sf::Vector2f(windowWidth / 2, windowHeight / 2), sf::Vector2f(windowWidth, windowHeight)));
            gameGrid = initGameGrid(numRows, numCols, numMines);
            guiGrid = initGuiGrid();
            flagsText.setString("Flags: " + std::to_string(numMines));
            setupMenu(font, menuBackground, resetButton, difficultyText, flagsText, gameButton,
                        dropdownOptions, dropdownBackground, customChoices, customBackground);

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

        // Draw all
        window.clear(sf::Color::White);
        drawGrid(window, guiGrid);
        window.draw(menuBackground);
        window.draw(gameButton);
        window.draw(difficultyText);
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
                    difficultyText.setString("Difficulty on reset: " + currDifficulty);

                    if (currDifficulty == "Custom")
                        isCustomOpen = true;
                }
            }
        }

        // In case custom dialog is open, do stuff related to it
        if (isCustomOpen)
        {
            // Draw background
            window.draw(customBackground);


            // Draw choices
            for (int i = 0; i < customChoices.size(); ++i)
            {
                auto& input = customChoices[i];
                window.draw(input);

                if (checkButtonPressed(window, input))
                {
                    customChoices[chosenInput].setString(inputStates[chosenInput]); // Remove pipe from previous chosen
                    chosenInput = i;
                }
            }

            // Handle cursor blinking
            if (cursorClock.getElapsedTime().asSeconds() >= 0.5f)
            {
                isCursorVisible = !isCursorVisible;
                cursorClock.restart();
            }

            if (isCursorVisible)
                customChoices[chosenInput].setString(inputStates[chosenInput] + "|");

            else
                customChoices[chosenInput].setString(inputStates[chosenInput]);
        }


        window.draw(resetButton);
        window.draw(clearingDeviceSprite);
        window.display();
    }
}

