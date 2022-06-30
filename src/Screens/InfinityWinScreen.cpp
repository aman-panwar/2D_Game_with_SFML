#include "InfinityWinScreen.h"

InfinityWinScreen::InfinityWinScreen()
{

    Background.setTexture(gameData->getTextureHolder().get(TextureID::MenuBackground));
    Background.setPosition(sf::Vector2f(0.0, 0.0));
    Background.setScale(gameData->getWindow()->getSize().x / Background.getGlobalBounds().width,
                        gameData->getWindow()->getSize().y / Background.getGlobalBounds().height);

    Container.setFillColor(sf::Color(0, 0, 0, 100));
    Container.setOutlineThickness(5);
    Container.setOutlineColor(sf::Color(255, 255, 255, 255));
    Container.setSize(sf::Vector2f(2 * QUITSCREEN_BUTTON_WIDTH + 3 * QUITSCREEN_MARGIN,
                                   2 * QUITSCREEN_BUTTON_HEIGHT + 3 * QUITSCREEN_MARGIN));
    Container.setOrigin(Container.getGlobalBounds().width / 2,
                        Container.getGlobalBounds().height / 2);
    Container.setPosition(sf::Vector2f(gameData->getWindow()->getSize().x / 2,
                                       gameData->getWindow()->getSize().y / 2));
}

void InfinityWinScreen::update(sf::Time deltatime)
{
    ContinueButton.update();
    HomeButton.update();
    if (ContinueButton.isClicked())
    {
        gameData->setInfinityModeDifficulty(gameData->getInfinityModeDifficulty() + 1);
        ScreenManager::GetManager()->goToScreen(Screen::InfinityPlayScreen);
    }
    if (HomeButton.isClicked())
    {
        gameData->setInfinityModeDifficulty(0);
        auto player_vec = FileHandler::getPlayerInfo();
        player_vec.emplace_back(std::make_pair(gameData->getCurPlayer().getAlias(),
                                               gameData->getCurPlayer().getCurScore()));
        FileHandler::savePlayerInfo(player_vec);
        ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
    }
}
void InfinityWinScreen::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if (!isPressed)
    {
        switch (key)
        {
        default:
            break;
        }
    }
}
void InfinityWinScreen::render()
{
    auto window = gameData->getWindow();
    window->clear();

    window->draw(Background);
    window->draw(Container);
    ContinueButton.draw();
    HomeButton.draw();

    window->display();
}