#include "pauseScreen.h"

PauseScreen::PauseScreen()
{
    Text.setString("Game Paused");
    Text.setFont(gameData->getFontHolder().get(FontID::TextFont));
    Text.setCharacterSize(60);
    Text.setOrigin(Text.getGlobalBounds().width / 2, Text.getGlobalBounds().height);
    Text.setPosition(gameData->getWindow()->getSize().x / 2,
                     gameData->getWindow()->getSize().y / 2 - PAUSESCREEN_BUTTON_HEIGHT / 2.0 - PAUSESCREEN_MARGIN);

    Background.setTexture(gameData->getTextureHolder().get(TextureID::MenuBackground));
    Background.setPosition(sf::Vector2f(0.0, 0.0));
    Background.setScale(gameData->getWindow()->getSize().x / Background.getGlobalBounds().width,
                        gameData->getWindow()->getSize().y / Background.getGlobalBounds().height);

    Container.setFillColor(sf::Color(0, 0, 0, 100));
    Container.setOutlineThickness(5);
    Container.setOutlineColor(sf::Color(255, 255, 255, 255));
    Container.setSize(sf::Vector2f(2 * PAUSESCREEN_BUTTON_WIDTH + 3 * PAUSESCREEN_MARGIN,
                                   Text.getGlobalBounds().height + 2 * PAUSESCREEN_BUTTON_HEIGHT + 3 * PAUSESCREEN_MARGIN));
    Container.setOrigin(Container.getGlobalBounds().width / 2,
                        Container.getGlobalBounds().height / 2);
    Container.setPosition(sf::Vector2f(gameData->getWindow()->getSize().x / 2,
                                       gameData->getWindow()->getSize().y / 2));
}

void PauseScreen::update(sf::Time deltatime)
{
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::P))
    {
        std::cout<<"going to infiplayscrene";
        ScreenManager::GetManager()->goToScreen(Screen::InfinityPlayScreen);
    }
    ContinueButton.update();
    QuitButton.update();

    if (ContinueButton.isClicked())
    {
        if (gameData->isStandardPlay())
        {
            std::cout<<"standard play\n";
            ScreenManager::GetManager()->goToScreen(Screen::StandardPlayScreen);
        }
        else
        {
            std::cout<<"infi play\n";
            ScreenManager::GetManager()->goToScreen(Screen::InfinityPlayScreen);
        }
    }
    if (QuitButton.isClicked())
    {
        ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
    }
}
void PauseScreen::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if (!isPressed)
    {
        switch (key)
        {
        case sf::Keyboard::Escape:
            ScreenManager::GetManager()->goToScreen(Screen::StandardPlayScreen);
            break;
        default:
            break;
        }
    }
}
void PauseScreen::render()
{
    auto window = gameData->getWindow();
    window->clear();

    window->draw(Background);
    window->draw(Container);
    window->draw(Text);
    ContinueButton.draw();
    QuitButton.draw();

    window->display();
}