#ifndef PAUSESCREEN_H
#define PAUSESCREEN_H

#include "screenmanager.h"
#include "GameScreen.h"
#include "GameData.h"
#include "textbutton.h"

/**
 * @brief Class for creating pause screen
 * 
 */
class PauseScreen:public GameScreen
{
    private:
    TextButton ContinueButton = TextButton("CONTINUE",
                                      sf::Vector2f(gameData->getWindow()->getSize().x / 2 - PAUSESCREEN_BUTTON_WIDTH/2.0 - PAUSESCREEN_MARGIN / 2.0,
                                                   gameData->getWindow()->getSize().y / 2),
                                      PAUSESCREEN_BUTTON_WIDTH,
                                      PAUSESCREEN_BUTTON_HEIGHT);

    TextButton QuitButton = TextButton("QUIT",
                                      sf::Vector2f(gameData->getWindow()->getSize().x / 2 + PAUSESCREEN_BUTTON_WIDTH/2.0 + PAUSESCREEN_MARGIN / 2.0,
                                                   gameData->getWindow()->getSize().y / 2),
                                      PAUSESCREEN_BUTTON_WIDTH,
                                      PAUSESCREEN_BUTTON_HEIGHT);
    sf::Sprite Background;
    sf::RectangleShape Container;
    sf::Text Text;
public:
    PauseScreen();
    /**
     *  updates buttons based on mouse position
     * 
     * @param deltatime 
     */
    void update(sf::Time deltatime);
    /**
     *  handles keyboard events(if spacebar is pressed)
     * 
     * @param key 
     * @param isPressed 
     */
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    void render();
};
#endif