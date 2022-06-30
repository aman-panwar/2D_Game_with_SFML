#include "WinScreen.h"

WinScreen::WinScreen()
{
    Text.setString("Game Won!!!");
    Text.setFont(gameData->getFontHolder().get(FontID::TextFont));
    Text.setCharacterSize(60);
    Text.setOrigin(Text.getGlobalBounds().width / 2, Text.getGlobalBounds().height);
    Text.setPosition(gameData->getWindow()->getSize().x / 2,
                     gameData->getWindow()->getSize().y / 2 - WINSCREEN_BUTTON_HEIGHT / 2.0 - WINSCREEN_MARGIN);

    Background.setTexture(gameData->getTextureHolder().get(TextureID::MenuBackground));
    Background.setPosition(sf::Vector2f(0.0, 0.0));
    Background.setScale(gameData->getWindow()->getSize().x / Background.getGlobalBounds().width,
                        gameData->getWindow()->getSize().y / Background.getGlobalBounds().height);

    Container.setFillColor(sf::Color(0, 0, 0, 100));
    Container.setOutlineThickness(5);
    Container.setOutlineColor(sf::Color(255, 255, 255, 255));
    Container.setSize(sf::Vector2f(3 * WINSCREEN_BUTTON_WIDTH + 4 * WINSCREEN_MARGIN,
                                   Text.getGlobalBounds().height + 2 * WINSCREEN_BUTTON_HEIGHT + 3 * WINSCREEN_MARGIN));
    Container.setOrigin(Container.getGlobalBounds().width / 2,
                        Container.getGlobalBounds().height / 2);
    Container.setPosition(sf::Vector2f(gameData->getWindow()->getSize().x / 2,
                                       gameData->getWindow()->getSize().y / 2));
}

void WinScreen::update(sf::Time deltatime)
{
    ReplayButton.update();
    NextButton.update();
    HomeButton.update();
    if (ReplayButton.isClicked())
    {
        ScreenManager::GetManager()->goToScreen(Screen::StandardPlayScreen);
    }
    if (NextButton.isClicked())
    {
        if (FileHandler::getLevelCount() > gameData->getLevelIndex())
        {
            gameData->setLevelInfo(FileHandler::getLevelInfo(gameData->getLevelIndex() + 1));
            gameData->setLevelIndex(gameData->getLevelIndex() + 1);
            ScreenManager::GetManager()->goToScreen(Screen::StandardPlayScreen);
        }
        else
        {
            ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
        }
    }
    if (HomeButton.isClicked())
    {
        ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
    }
}
void WinScreen::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if (!isPressed)
    {
        switch (key)
        {
        case sf::Keyboard::Escape:
            ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
            break;

        default:
            break;
        }
    }
}
void WinScreen::render()
{
    auto window = gameData->getWindow();
    window->clear();

    window->draw(Background);
    window->draw(Container);
    window->draw(Text);
    ReplayButton.draw();
    NextButton.draw();
    HomeButton.draw();

    window->display();
}