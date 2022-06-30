#include "LostScreen.h"

LostScreen::LostScreen()
{
    gameData->setInfinityModeDifficulty(0);
    Text.setString("Sorry You Lost ");
    Text.setFont(gameData->getFontHolder().get(FontID::TextFont));
    Text.setCharacterSize(60);
    Text.setOrigin(Text.getGlobalBounds().width / 2, Text.getGlobalBounds().height);
    Text.setPosition(gameData->getWindow()->getSize().x / 2,
                     gameData->getWindow()->getSize().y / 2 - LOSTSCREEN_BUTTON_HEIGHT / 2.0 - LOSTSCREEN_MARGIN);

    Background.setTexture(gameData->getTextureHolder().get(TextureID::MenuBackground));
    Background.setPosition(sf::Vector2f(0.0, 0.0));
    Background.setScale(gameData->getWindow()->getSize().x / Background.getGlobalBounds().width,
                        gameData->getWindow()->getSize().y / Background.getGlobalBounds().height);

    Container.setFillColor(sf::Color(0, 0, 0, 100));
    Container.setOutlineThickness(5);
    Container.setOutlineColor(sf::Color(255, 255, 255, 255));
    Container.setSize(sf::Vector2f(2 * LOSTSCREEN_BUTTON_WIDTH + 3 * LOSTSCREEN_MARGIN,
                                   Text.getGlobalBounds().height + 2 * LOSTSCREEN_BUTTON_HEIGHT + 3 * LOSTSCREEN_MARGIN));
    Container.setOrigin(Container.getGlobalBounds().width / 2,
                        Container.getGlobalBounds().height / 2);
    Container.setPosition(sf::Vector2f(gameData->getWindow()->getSize().x / 2,
                                       gameData->getWindow()->getSize().y / 2));
}

void LostScreen::update(sf::Time deltatime)
{
    RetryButton.update();
    HomeButton.update();
    if (RetryButton.isClicked())
    {
        if (gameData->isStandardPlay())
        {
            ScreenManager::GetManager()->goToScreen(Screen::StandardPlayScreen);
        }
        else
        {
            gameData->setInfinityModeDifficulty(0);
            auto player_vec = FileHandler::getPlayerInfo();
            player_vec.emplace_back(std::make_pair(gameData->getCurPlayer().getAlias(),
                                                   gameData->getCurPlayer().getCurScore()));
            FileHandler::savePlayerInfo(player_vec);
            ScreenManager::GetManager()->goToScreen(Screen::InfinityPlayScreen);
        }
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
void LostScreen::handleInput(sf::Keyboard::Key key, bool isPressed)
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
void LostScreen::render()
{
    auto window = gameData->getWindow();
    window->clear();

    window->draw(Background);
    window->draw(Container);
    window->draw(Text);
    RetryButton.draw();
    HomeButton.draw();

    window->display();
}