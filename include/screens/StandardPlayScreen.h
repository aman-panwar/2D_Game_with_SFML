#ifndef STANDARDPLAYSCREEN_H
#define STANDARDPLAYSCREEN_H

#include "GameScreen.h"
#include "GameData.h"
#include "screenmanager.h"
#include "level.h"

/**
 * @brief Class for creating the play screen
 */
class StandardPlayScreen : public GameScreen
{
private:
    Level myLevel;
    void handleInput(sf::Keyboard::Key key, bool isPressed);

public:
    StandardPlayScreen();
    /**
     *  updates all the buttons on the screen
     * @param deltaTime 
     */
    void update(sf::Time deltaTime);
    /**
     *  displays all buttons and background
     */
    void render();
    /**
     *  pauses game
     */
    void pause();
};
#endif