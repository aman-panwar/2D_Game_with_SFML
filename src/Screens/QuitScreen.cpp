#include "QuitScreen.h"

QuitScreen::QuitScreen()
{
    Text.setString("Do you want to Quit?");
    Text.setFont(gameData->getFontHolder().get(FontID::TextFont));
    Text.setCharacterSize(60);
    Text.setOrigin(Text.getGlobalBounds().width / 2, Text.getGlobalBounds().height);
    Text.setPosition(gameData->getWindow()->getSize().x / 2,
                     gameData->getWindow()->getSize().y / 2 - QUITSCREEN_BUTTON_HEIGHT / 2.0 - QUITSCREEN_MARGIN);

    Background.setTexture(gameData->getTextureHolder().get(TextureID::MenuBackground));
    Background.setPosition(sf::Vector2f(0.0, 0.0));
    Background.setScale(gameData->getWindow()->getSize().x / Background.getGlobalBounds().width,
                        gameData->getWindow()->getSize().y / Background.getGlobalBounds().height);

    Container.setFillColor(sf::Color(0, 0, 0, 100));
    Container.setOutlineThickness(5);
    Container.setOutlineColor(sf::Color(255, 255, 255, 255));
    Container.setSize(sf::Vector2f(2 * QUITSCREEN_BUTTON_WIDTH + 3 * QUITSCREEN_MARGIN,
                                   Text.getGlobalBounds().height + 2 * QUITSCREEN_BUTTON_HEIGHT + 3 * QUITSCREEN_MARGIN));
    Container.setOrigin(Container.getGlobalBounds().width / 2,
                        Container.getGlobalBounds().height / 2);
    Container.setPosition(sf::Vector2f(gameData->getWindow()->getSize().x / 2,
                                       gameData->getWindow()->getSize().y / 2));
}

void QuitScreen::update(sf::Time deltatime)
{
    YesButton.update();
    NoButton.update();
    if (YesButton.isClicked())
    {
        ScreenManager::GetManager()->goToScreen(Screen::QuitGame);
    }
    if (NoButton.isClicked())
    {
        ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
    }
}
void QuitScreen::handleInput(sf::Keyboard::Key key, bool isPressed)
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
void QuitScreen::render()
{
    auto window=gameData->getWindow();
    window->clear();

    window->draw(Background);
    window->draw(Container);
    window->draw(Text);
    YesButton.draw();
    NoButton.draw();

    window->display();
}