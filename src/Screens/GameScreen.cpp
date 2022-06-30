#include "GameScreen.h"

void GameScreen::processEvents()
{
    sf::Event event;
    while (gameData->getWindow()->pollEvent(event))
    {
        if (gameData->getWindow()->hasFocus())
        {
            switch (event.type)
            {
            case sf::Event::KeyPressed:
                handleInput(event.key.code, true);
                break;
            case sf::Event::KeyReleased:
                handleInput(event.key.code, false);
                break;
            case sf::Event::Closed:
                gameData->getWindow()->close();
                break;
            case sf::Event::LostFocus:
                break;
            case sf::Event::GainedFocus:
                break;
            case sf::Event::TextEntered:
                break;
            case sf::Event::MouseWheelMoved:
                break;
            case sf::Event::MouseWheelScrolled:
                break;
            case sf::Event::MouseButtonPressed:
                break;
            case sf::Event::MouseButtonReleased:
                break;
            case sf::Event::MouseMoved:
                break;
            case sf::Event::MouseEntered:
                break;
            case sf::Event::MouseLeft:
                break;
            case sf::Event::JoystickButtonPressed:
                break;
            case sf::Event::JoystickButtonReleased:
                break;
            case sf::Event::JoystickMoved:
                break;
            case sf::Event::JoystickConnected:
                break;
            case sf::Event::JoystickDisconnected:
                break;
            case sf::Event::TouchBegan:
                break;
            case sf::Event::TouchMoved:
                break;
            case sf::Event::TouchEnded:
                break;
            case sf::Event::SensorChanged:
                break;
            case sf::Event::Count:
                break;
            case sf::Event::Resized:
                break;
            }
        }
        else
        {
            pause();
        }
    }
}