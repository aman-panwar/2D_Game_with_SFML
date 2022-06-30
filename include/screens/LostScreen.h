#ifndef LOSTSCREEN_H
#define LOSTSCREEN_H

#include "GameScreen.h"
#include "GameData.h"
#include "screenmanager.h"
#include "textbutton.h"

/**
 * @brief Class for creating Lost screen
 * 
 */
class LostScreen : public GameScreen
{
private:
    TextButton RetryButton = TextButton("RETRY",
                                        sf::Vector2f(gameData->getWindow()->getSize().x / 2 - LOSTSCREEN_BUTTON_WIDTH / 2.0 - LOSTSCREEN_MARGIN / 2.0,
                                                     gameData->getWindow()->getSize().y / 2),
                                        LOSTSCREEN_BUTTON_WIDTH,
                                        LOSTSCREEN_BUTTON_HEIGHT);

    TextButton HomeButton = TextButton("QUIT",
                                       sf::Vector2f(gameData->getWindow()->getSize().x / 2 + LOSTSCREEN_BUTTON_WIDTH / 2.0 + LOSTSCREEN_MARGIN / 2.0,
                                                    gameData->getWindow()->getSize().y / 2),
                                       LOSTSCREEN_BUTTON_WIDTH,
                                       LOSTSCREEN_BUTTON_HEIGHT);
    sf::Sprite Background;
    sf::RectangleShape Container;
    sf::Text Text;

public:
    LostScreen();
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