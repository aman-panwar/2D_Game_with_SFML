#include "powerup.h"

Powerup::Powerup(sf::Vector2f pos)
{
    object.setPosition(pos);
}

void Powerup::update(sf::Time deltaTime)
{
    object.move(sf::Vector2f( 0,POWERUP_FALL_SPEED));
}

void Powerup::draw()
{
    if (isAlive())
    {
        gameData->getWindow()->draw(object);
    }
}

bool Powerup::isAlive()
{
    
    if (object.getGlobalBounds().top >= gameData->getWindow()->getSize().y)
        is_Alive = false;

    return is_Alive;
}

// void longplanc::handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc)
// {
//     Planc.increaseLength();
// }

// void shortplanc::handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc)
// {
//     Planc.decreaseLength();
// }

// void slowplanc::handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc)
// {
//     Planc.decreaseSpeed();
// }

// void multiball::handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc)
// {
//     sf::Vector2f pos;
//     pos.x = Planc.getbounds().left + Planc.getbounds().width / 2;
//     pos.y = Planc.getbounds().top;
//     sf::Vector2f vel1, vel2;
//     vel1.x = abs(balls.front()->getvelocity().x);
//     vel1.y = -1 * abs(balls.front()->getvelocity().y);
//     vel2 = vel1;
//     vel2.x = -vel1.x;

//     balls.push_back(std::unique_ptr<Ball>(new Ball(pos, vel1)));
//     balls.push_back(std::unique_ptr<Ball>(new Ball(pos, vel2)));
// }

// void plusball::handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc)
// {
//     sf::Vector2f pos;
//     pos.x = Planc.getbounds().left + Planc.getbounds().width / 2;
//     pos.y = Planc.getbounds().top;
//     sf::Vector2f vel;
//     vel.x = abs(balls.front()->getvelocity().x);
//     vel.y = -1 * abs(balls.front()->getvelocity().y);
//     balls.push_back(std::unique_ptr<Ball>(new Ball(pos, vel)));
// }

// void fireball::handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc)
// {
//     sf::Vector2f pos;
//     pos.x = Planc.getbounds().left + Planc.getbounds().width / 2;
//     pos.y = Planc.getbounds().top;
//     sf::Vector2f vel;
//     vel.x = abs(balls.front()->getvelocity().x);
//     vel.y = -1 * abs(balls.front()->getvelocity().y);
//     balls.push_back(std::unique_ptr<Ball>(new FireBall(pos, vel)));
// }

// void crazyball::handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc)
// {
//     sf::Vector2f pos;
//     pos.x = Planc.getbounds().left + Planc.getbounds().width / 2;
//     pos.y = Planc.getbounds().top;
//     sf::Vector2f vel;
//     vel.x = abs(balls.front()->getvelocity().x);
//     vel.y = -1 * abs(balls.front()->getvelocity().y);
//     balls.push_back(std::unique_ptr<Ball>(new CrazyBall(pos, vel)));
// }

// void fastball::handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc)
// {
//     for (auto &cur_ball : balls)
//     {
//         cur_ball->increaseSpeed();
//     }
// }

// void slowball::handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc)
// {
//     for (auto &cur_ball : balls)
//     {
//         cur_ball->decreaseSpeed();
//     }
// }

// void pluslife::handleCollision(std::list<std::unique_ptr<Ball>> &balls, Planc &Planc)
// {
//     // nothing to write as there is no collision
// }
