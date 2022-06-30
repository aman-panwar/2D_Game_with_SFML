#ifndef CRAZYBALL_H
#define CRAZYBALL_H

#include "ball.h"
/**
 * @brief Ball bounces in a weird way 
 * 
 */
class CrazyBall : public Ball
{
public:
    CrazyBall() = delete;
    /** Constructor for the Ball
     * @param pos the initial position of the ball
     * @param vel the initial velocity of the ball
     * */
    CrazyBall(sf::Vector2f pos, sf::Vector2f vel);
    /**
     *takes position of object ball cllided with and makes ball bounce of it
     * 
     */
    void bounceOff(sf::FloatRect);
};

#endif