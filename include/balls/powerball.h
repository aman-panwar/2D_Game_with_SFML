#ifndef POWERBALL_H
#define POWERBALL_H

#include"ball.h"

class PowerBall:public Ball
{
public:
    PowerBall()=delete;
    /** Constructor for the Ball
     * @param pos the initial position of the ball
     * @param vel the initial velocity of the ball
     * */
    PowerBall(sf::Vector2f pos, sf::Vector2f vel);
};

#endif