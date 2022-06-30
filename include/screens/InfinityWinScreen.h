#ifndef INFINITYWINSCREEN_H
#define INFINITYWINSCREEN_H

#include "GameScreen.h"
#include "GameData.h"
#include "screenmanager.h"
#include "textbutton.h"

/**
 * @brief Class for creating win screen for infinity play
 * 
 */
class InfinityWinScreen : public GameScreen
{
private:
    TextButton ContinueButton = TextButton("CONTINUE",
                                      sf::Vector2f(gameData->getWindow()->getSize().x / 2 - QUITSCREEN_BUTTON_WIDTH / 2.0 - QUITSCREEN_MARGIN / 2.0,
                                                   gameData->getWindow()->getSize().y / 2),
                                      QUITSCREEN_BUTTON_WIDTH,
                                      QUITSCREEN_BUTTON_HEIGHT);

    TextButton HomeButton = TextButton("HOME",
                                     sf::Vector2f(gameData->getWindow()->getSize().x / 2 + QUITSCREEN_BUTTON_WIDTH / 2.0 + QUITSCREEN_MARGIN / 2.0,
                                                  gameData->getWindow()->getSize().y / 2),
                                     QUITSCREEN_BUTTON_WIDTH,
                                     QUITSCREEN_BUTTON_HEIGHT);
    
    sf::Sprite Background;
    sf::RectangleShape Container;

public:
    InfinityWinScreen();
    /**
     *  updates buttons based on mouse position
     * 
     * @param deltatime 
     */
    void update(sf::Time deltatime);
    /**
     *  handles keyboard events(if escape is pressed)
     * 
     * @param key 
     * @param isPressed 
     */
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    void render();
};

#endif