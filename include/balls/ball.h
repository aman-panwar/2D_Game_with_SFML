#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <math.h>
#include "defines.h"
#include "GameData.h"

/** @brief The base class for all the balls in the game
 * 
 * */
class Ball
{
protected:
    sf::Vector2f postion;  ///position of the ball
    sf::Vector2f velocity; ///velocity of the ball
    sf::Sprite object;     ///the actual sprite of the ball
    unsigned damage;       ///the damage the ball causes
    sf::Sound bounceSound; ///Holds the bouncing Sound

    /** Sets a new position of the ball
     * @param newPos the new position of the ball to be set
     **/
    void setPosition(sf::Vector2f newPos); //we might not have to use this

    /** Returns the current positon of the ball
     *  @return radius of the ball
     **/
    float getRadius();

    /** Bounces the ball off an object
     *  @param obstacle the smallest sf::FloatRect encapsulating the object
     * */
    virtual void bounceOff(sf::FloatRect);

public:
    Ball() = delete;
    /** Constructor for the Ball
     * @param pos the initial position of the ball
     * @param vel the initial velocity of the ball
     * */
    Ball(sf::Vector2f pos, sf::Vector2f vel);

    /** Returns the current positon of the centre of the ball
     *  @return current centre position of the ball
     **/
    sf::Vector2f getCentrePosition();

    /** Handles the collision with a sf::FloatRect
     * @param obstacle is the smallest sf::FloatRect encapsulating the object
     * @param deltaTime is the delta time
     * @return true if there is collision, false otherwise
     * */
    virtual bool handleCollision(sf::FloatRect obstacle, sf::Time deltaTime);

    virtual void increaseSpeed();
    virtual void decreaseSpeed();

    // /** Return reference to the bounceSound from GameData
    //  * @return reference to the sf::Sound containing the ball's bounce sound
    //  * */
    // sf::Sound &getBounceSound();
    void update(sf::Time deltaTime);
    virtual void draw();
    bool isInBounds();
    unsigned getDamage();
    void addToVelocity(sf::Vector2f velocity_addition);
};
#endif
