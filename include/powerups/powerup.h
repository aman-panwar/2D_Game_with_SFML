#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
#include "planc.h"
#include "ball.h"
#include "crazyball.h"
#include "fireball.h"

/**
 * @brief Base class for all the powerups
 * 
 */
class Powerup
{
protected:
    sf::Sprite object; /// holds texture of powerups
    sf::Sound CollisionSound;/// holds texture colission sound
    Powerup() = delete;
    Powerup(sf::Vector2f pos);/// constructor - loads corresponding texture and set its position to broken brick
    bool is_Alive = true;// tells us if power up is still alive

public:
/**
 * makes the falling effect of powerup
 * 
 * @param deltaTime 
 */
    void update(sf::Time deltaTime);
    virtual void handleCollision(Planc &Planc) = 0; ///check if collides with planc, if yes then makes required change to planc
    /**
     * tells us if powerup is still alive or not
     * 
     * @return true 
     * @return false 
     */
    bool isAlive();
    /**
     *  draw the sprite on screen
     * 
     */
    void draw();
};
#endif
// class longplanc : public Powerup
// {
// private:
// public:
//     void handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc);
// };

// class shortplanc : public Powerup
// {
// private:
// public:
//     void handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc);
// };

// class slowplanc : public Powerup
// {
// private:
// public:
//     void handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc);
// };

// class fastplanc : public Powerup
// {
// private:
// public:
//     void handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc);
// };

// class multiball : public Powerup
// {
// private:
// public:
//     void handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc);
// };

// class plusball : public Powerup
// {
// private:
// public:
//     void handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc);
// };

// class fireball : public Powerup
// {
// private:
// public:
//     void handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc);
// };

// class crazyball : public Powerup
// {
// private:
// public:
//     void handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc);
// };

// class fastball : public Powerup
// {
// private:
// public:
//     void handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc);
// };

// class slowball : public Powerup
// {
// private:
// public:
//     void handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc);
// };