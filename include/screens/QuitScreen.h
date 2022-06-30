#ifndef QUITSCREEN_H
#define QUITSCREEN_H

#include "GameScreen.h"
#include "GameData.h"
#include "screenmanager.h"
#include "textbutton.h"

/**
 * @brief Class for creating quit screen
 * 
 */
class QuitScreen: public GameScreen
{
private:
    TextButton YesButton = TextButton("YES",
                                      sf::Vector2f(gameData->getWindow()->getSize().x / 2 - QUITSCREEN_BUTTON_WIDTH/2.0 - QUITSCREEN_MARGIN / 2.0,
                                                   gameData->getWindow()->getSize().y / 2),
                                      QUITSCREEN_BUTTON_WIDTH,
                                      QUITSCREEN_BUTTON_HEIGHT);

    TextButton NoButton = TextButton("NO",
                                      sf::Vector2f(gameData->getWindow()->getSize().x / 2 + QUITSCREEN_BUTTON_WIDTH/2.0 + QUITSCREEN_MARGIN / 2.0,
                                                   gameData->getWindow()->getSize().y / 2),
                                      QUITSCREEN_BUTTON_WIDTH,
                                      QUITSCREEN_BUTTON_HEIGHT);
    sf::Sprite Background;
    sf::RectangleShape Container;
    sf::Text Text;
public:
    QuitScreen();
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