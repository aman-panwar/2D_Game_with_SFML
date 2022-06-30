#ifndef WINSCREEN_H
#define WINSCREEN_H

#include "GameScreen.h"
#include "GameData.h"
#include "screenmanager.h"
#include "textbutton.h"

/**
 * @brief class for creating you won screen
 * 
 */
class WinScreen : public GameScreen
{
private:
    TextButton ReplayButton = TextButton("REPLAY",
                                         sf::Vector2f(gameData->getWindow()->getSize().x / 2 - WINSCREEN_BUTTON_WIDTH - WINSCREEN_MARGIN,
                                                      gameData->getWindow()->getSize().y / 2),
                                         WINSCREEN_BUTTON_WIDTH,
                                         WINSCREEN_BUTTON_HEIGHT);

    TextButton NextButton = TextButton("NEXT LEVEL",
                                       sf::Vector2f(gameData->getWindow()->getSize().x / 2,
                                                    gameData->getWindow()->getSize().y / 2),
                                       WINSCREEN_BUTTON_WIDTH,
                                       WINSCREEN_BUTTON_HEIGHT);
    TextButton HomeButton = TextButton("HOME",
                                       sf::Vector2f(gameData->getWindow()->getSize().x / 2 + WINSCREEN_BUTTON_WIDTH + WINSCREEN_MARGIN,
                                                    gameData->getWindow()->getSize().y / 2),
                                       WINSCREEN_BUTTON_WIDTH,
                                       WINSCREEN_BUTTON_HEIGHT);

    sf::Sprite Background;
    sf::RectangleShape Container;
    sf::Text Text;

public:
    WinScreen();
    /**
     * updates all the buttons
     * 
     * @param deltatime 
     */
    void update(sf::Time deltatime);
    /**
     *  handles keyboard events(if esc is pressed)
     * 
     * @param key 
     * @param isPressed 
     */
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    void render();
};
#endif