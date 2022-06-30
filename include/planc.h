#ifndef PLANC_H
#define PLANC_H

#include <SFML/Graphics.hpp>
#include "defines.h"
#include "GameData.h"
/**
 * @brief class holding all info of planc
 * 
 */
class Planc
{
private:
    sf::Sprite object;
    sf::Time momentumEndTime = sf::Time::Zero;
    sf::Vector2f velocity;
    float cur_speed = DEFAULT_PLANC_SPEED;
    sf::Clock myClock;
    float last_dir = 0;

public:
    enum class Dir
    {
        Left,
        Right
    };
    Planc();
    void activateMomentum();         ///activates the momentum property
    void update(sf::Time deltaTime); ///updates the planc
    void draw();
    void move(Dir direction, bool isPressed); ///moves the block left or right
    void increaseSpeed();//increaseSpeed
    void decreaseSpeed();//decreases speed
    void increaseLength();//increase length
    void decreaseLength();//decrease length
    sf::Vector2f getVelocity(); ///return the current speed of the planc
    sf::FloatRect getBounds();
};
#endif