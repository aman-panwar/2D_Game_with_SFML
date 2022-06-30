#include "LevelScreen.h"
LevelScreen::LevelScreen()
{
    cur_page_number = 1;
    max_page_number = ((FileHandler::getLevelCount() + GRID_COLS - 1) / GRID_COLS + GRID_ROWS - 1) / GRID_ROWS;
    initBackground();
    initButtons();
}
void LevelScreen::render()
{
    auto window = gameData->getWindow();
    window->clear();

    window->draw(Background);
    window->draw(BoundaryBox);
    window->draw(HeaderBox);
    window->draw(Header);
    renderButtons();
    window->display();
}
void LevelScreen::update(sf::Time deltaTime)
{
    updateButtons();
    manageButtonClick();
}
void LevelScreen::manageButtonClick()
{
    //checks close button
    if (CloseButton.isClicked())
    {
        ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
    }
    //checks level buttons
    for (unsigned i = (cur_page_number - 1) * (GRID_COLS * GRID_ROWS);
         i < std::min((cur_page_number - 1) * (GRID_COLS * GRID_ROWS) + GRID_COLS * GRID_ROWS, unsigned(levelButtons.size()));
         i++)
    {
        if (levelButtons[i].isClicked())
        {
            gameData->setLevelIndex(i+1);
            gameData->setLevelInfo(FileHandler::getLevelInfo(i + 1));
            ScreenManager::GetManager()->goToScreen(Screen::StandardPlayScreen);
        }
    }
    //checks delete buttons
    for (unsigned i = (cur_page_number - 1) * (GRID_COLS * GRID_ROWS);
         i < std::min((cur_page_number - 1) * (GRID_COLS * GRID_ROWS) + GRID_COLS * GRID_ROWS, unsigned(levelButtons.size()));
         i++)
    {
        if (deleteButtons[i].isClicked())
        {
            FileHandler::deleteLevelInfo(i + 1);
            max_page_number = ((FileHandler::getLevelCount() + GRID_COLS - 1) / GRID_COLS + GRID_ROWS - 1) / GRID_ROWS;
            initButtons();
        }
    }
    //next button
    if (NextPageButton.isClicked())
    {
        cur_page_number = std::min(cur_page_number + 1, max_page_number);
        updatePageButtonTexture();
    }
    //prev page button
    if (PrevPageButton.isClicked())
    {
        cur_page_number = std::max(unsigned(1), cur_page_number - 1);
        updatePageButtonTexture();
    }
}
void LevelScreen::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    // switch (key)
    // {
    // case sf::Keyboard::Escape:
    //     if (!isPressed)
    //         ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
    //     break;
    // }
    if(key==sf::Keyboard::Escape)
    {
        if (!isPressed)
            ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
    }
}
void LevelScreen::initBackground()
{
    auto window = gameData->getWindow();

    Background.setTexture(gameData->getTextureHolder().get(TextureID::MenuBackground));
    Background.setScale(window->getSize().x / Background.getLocalBounds().width,
                        window->getSize().y / Background.getLocalBounds().height);
    Background.setOrigin(Background.getLocalBounds().width / 2,
                         Background.getLocalBounds().height / 2);
    Background.setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f);

    //initialising boundary box
    BoundaryBox.setOutlineThickness(5);
    BoundaryBox.setOutlineColor(sf::Color(255, 255, 255, 255));
    BoundaryBox.setFillColor(sf::Color(0, 0, 0, 100));
    BoundaryBox.setSize(sf::Vector2f(window->getSize().x - 160, window->getSize().y - 160));
    BoundaryBox.setOrigin(BoundaryBox.getLocalBounds().width / 2,
                          BoundaryBox.getLocalBounds().height / 2);
    BoundaryBox.setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f);

    //headerBox
    HeaderBox.setOutlineThickness(5);
    HeaderBox.setOutlineColor(sf::Color(255, 255, 255, 255));
    HeaderBox.setFillColor(sf::Color(0, 0, 0, 100));
    HeaderBox.setSize(sf::Vector2f(window->getSize().x - 160, 80));
    HeaderBox.setOrigin(BoundaryBox.getLocalBounds().width / 2, 0);
    HeaderBox.setPosition(window->getSize().x / 2.f, 75);

    //init Text
    Header.setString("Level");
    Header.setFillColor(sf::Color(255, 255, 255, 255));
    Header.setCharacterSize(50);
    Header.setFont(gameData->getFontHolder().get(FontID::TextFont));
    Header.setOrigin(Header.getLocalBounds().width / 2, 0.f);
    Header.setPosition(sf::Vector2f(window->getSize().x / 2, 90));
}
void LevelScreen::renderButtons()
{
    CloseButton.draw();
    NextPageButton.draw();
    PrevPageButton.draw();
    //level grid buttons
    for (unsigned i = (cur_page_number - 1) * (GRID_COLS * GRID_ROWS);
         i < std::min((cur_page_number - 1) * (GRID_COLS * GRID_ROWS) + GRID_COLS * GRID_ROWS, unsigned(levelButtons.size()));
         i++)
    {
        levelButtons[i].draw();
        deleteButtons[i].draw();
    }
}
void LevelScreen::updateButtons()
{
    CloseButton.update();
    NextPageButton.update();
    PrevPageButton.update();
    //updating level grid buttons
    for (unsigned i = (cur_page_number - 1) * (GRID_COLS * GRID_ROWS);
         i < std::min((cur_page_number - 1) * (GRID_COLS * GRID_ROWS) + GRID_COLS * GRID_ROWS, unsigned(levelButtons.size()));
         i++)
    {
        levelButtons[i].update();
        deleteButtons[i].update();
    }
}
void LevelScreen::updatePageButtonTexture()
{
    if (cur_page_number == max_page_number)
    {
        NextPageButton.updateTexture(gameData->getTextureHolder().get(TextureID::PageButtonDeactivated));
    }
    else
    {
        NextPageButton.updateTexture(gameData->getTextureHolder().get(TextureID::PageButton));
    }

    if (cur_page_number <= 1)
    {
        PrevPageButton.updateTexture(gameData->getTextureHolder().get(TextureID::PageButtonDeactivated));
    }
    else
    {
        PrevPageButton.updateTexture(gameData->getTextureHolder().get(TextureID::PageButton));
    }
}
void LevelScreen::initButtons()
{
    //level and delete buttons
    levelButtons.clear();
    deleteButtons.clear();

    unsigned level_count = FileHandler::getLevelCount();
    float box_width = (BoundaryBox.getLocalBounds().width - (GRID_COLS + 1) * LEVEL_MARGIN) / GRID_COLS,
          box_height = (BoundaryBox.getLocalBounds().height - HeaderBox.getLocalBounds().height - (GRID_ROWS + 1) * (LEVEL_MARGIN + LEVEL_DELETE_BUTTON_HEIGHT)) / GRID_ROWS;

    sf::Vector2f index00pos = sf::Vector2f(gameData->getWindow()->getSize().x / 2 - (GRID_COLS / 2.0 - 0.5) * box_width - ((GRID_COLS - 1) / 2.0) * LEVEL_MARGIN,
                                           255 + LEVEL_MARGIN);
    for (unsigned i = 0; i < level_count; i++)
    {
        unsigned col, row;
        col = i % GRID_COLS;
        row = (i / GRID_COLS) % GRID_ROWS;
        sf::Vector2f position = index00pos + sf::Vector2f(col * (box_width + LEVEL_MARGIN), row * (box_height + LEVEL_MARGIN + LEVEL_DELETE_BUTTON_HEIGHT));
        levelButtons.emplace_back(TextButton(std::to_string(i + 1),
                                             position,
                                             box_width,
                                             box_height));
        deleteButtons.emplace_back(SpriteButton(gameData->getTextureHolder().get(TextureID::LevelDeleteButton),
                                                position + sf::Vector2f(0.f, (LEVEL_DELETE_BUTTON_HEIGHT + box_height) / 2.0),
                                                box_width,
                                                float(LEVEL_DELETE_BUTTON_HEIGHT)));
    }

    PrevPageButton.setRotation(180);
    updatePageButtonTexture();
}