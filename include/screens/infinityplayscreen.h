#ifndef INFINITYPLAYSCREEN_H
#define INFINITYPLAYSCREEN_H

#include "GameScreen.h"
#include "GameData.h"
#include "screenmanager.h"
#include "level.h"

/**
 * @brief class for making endless play mode
 * 
 */
class InfinityPlayScreen : public GameScreen
{
private:
    Level myLevel;
    unsigned difficulty = 0;
    /** Takes upropriate action for each key
     * @param key 
     * @param isPressed 
     */
    void handleInput(sf::Keyboard::Key key, bool isPressed);
public:
    InfinityPlayScreen();
    void update(sf::Time deltaTime);
    void render(); /// renders the game
    void pause();
};
#endif