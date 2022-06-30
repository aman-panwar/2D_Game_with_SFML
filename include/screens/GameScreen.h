#ifndef GAMESCREEN_H
#define GAMESCREEN_H

#include "GameData.h"
#include "resourceholder.hpp"
#include <SFML/Graphics.hpp>

/** @brief It's the base class for all Screen in the Game
 * 
 * Define the basic virtual functions for all the screen
 */
class GameScreen
{
protected:
    sf::CircleShape object;

public:
    ~GameScreen(){};
    ///Makes the required changes on the screen
    virtual void update(sf::Time deltaTime) = 0;

    ///Renders the screen onto the window
    virtual void render() = 0;
    /**
     *  handles events of key pressed or mouse clicked
     * 
     */
    void processEvents();
    /**
     *  do necessary work based on key work
     * 
     * @param key 
     * @param isPressed 
     */
    virtual void handleInput(sf::Keyboard::Key key, bool isPressed) = 0;

    virtual void pause(){}
};
#endif