#ifndef FIREBALL_H
#define FIREBALL_H

#include "ball.h"

/**
 * @brief ball will have a very high damage
 * 
 */
class FireBall : public Ball
{
public:
    FireBall() = delete;
    /** Constructor for the Ball
     * @param pos the initial position of the ball
     * @param vel the initial velocity of the ball
     * */
    FireBall(sf::Vector2f pos, sf::Vector2f vel);
};

#endif