#include "StandardPlayScreen.h"

StandardPlayScreen::StandardPlayScreen()
{
    gameData->setIfStandardPlay(true);
    myLevel.Load(gameData->getLevelInfo());
}
void StandardPlayScreen::render()
{
    myLevel.draw();
}
void StandardPlayScreen::update(sf::Time deltaTime)
{
    processEvents();
    myLevel.update(deltaTime);
}
void StandardPlayScreen::handleInput(sf::Keyboard::Key key, bool isPressed)
{
        // switch (key)
    // {
    // case sf::Keyboard::Space:
    //     myLevel.StartLevel();
    //     break;
    // case sf::Keyboard::Right:
    //     myLevel.MoveRight(isPressed);
    //     break;
    // case sf::Keyboard::Left:
    //     myLevel.MoveLeft(isPressed);
    //     break;
    // case sf::Keyboard::Escape:
    //     if (!isPressed)
    //         ScreenManager::GetManager()->goToScreen(Screen::PauseScreen);
    //     break;
    // }
    if (key == sf::Keyboard::Space)
    {
        myLevel.StartLevel();
    }
    else if (key == sf::Keyboard::Right)
    {
        myLevel.MoveRight(isPressed);
    }
    else if (key == sf::Keyboard::Left)
    {
        myLevel.MoveLeft(isPressed);
    }
    else if (key == sf::Keyboard::Escape)
    {
        if (!isPressed)
            ScreenManager::GetManager()->goToScreen(Screen::PauseScreen);
    }
}
void StandardPlayScreen::pause()
{
    ScreenManager::GetManager()->goToScreen(Screen::PauseScreen);
}