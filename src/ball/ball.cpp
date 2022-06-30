#include "ball.h"

Ball::Ball(sf::Vector2f pos, sf::Vector2f vel)
{
    object.setTexture(gameData->getTextureHolder().get(TextureID::Ball));
    object.setScale(2 * BALL_RADIUS / object.getLocalBounds().width,
                    2 * BALL_RADIUS / object.getLocalBounds().height);
    object.setOrigin(object.getLocalBounds().width / 2,
                     object.getLocalBounds().height / 2);
    object.setPosition(pos);

    velocity = vel;
    float cur_speed = sqrtf(pow(velocity.x, 2) + pow(velocity.y, 2));
    velocity *= std::max(float(BALL_MIN_SPEED), cur_speed) / cur_speed;

    damage = BALL_DAMAMGE;

    bounceSound.setBuffer(gameData->getSoundHolder().get(SoundID::BallBounce));
}
void Ball::setPosition(sf::Vector2f newPos)
{
    object.setPosition(newPos);

    bool ifcollision = false;
    //placing the ball back into the bounds
    //top
    if (object.getGlobalBounds().top <= TOP_MARGIN)
    {
        object.setPosition(object.getPosition().x, TOP_MARGIN + BALL_RADIUS);
        velocity.y = abs(velocity.y);
        ifcollision = true;
    }
    //left
    if (object.getGlobalBounds().left <= (gameData->getWindow()->getSize().x - LEVEL_WIDTH) / 2)
    {
        object.setPosition((gameData->getWindow()->getSize().x - LEVEL_WIDTH) / 2 + BALL_RADIUS, object.getPosition().y);
        velocity.x = abs(velocity.x);
        ifcollision = true;
    }
    //right
    if (object.getGlobalBounds().left + 2 * BALL_RADIUS >= (gameData->getWindow()->getSize().x + LEVEL_WIDTH) / 2.0)
    {
        object.setPosition((gameData->getWindow()->getSize().x + LEVEL_WIDTH) / 2.0 - BALL_RADIUS, object.getPosition().y);
        velocity.x = -abs(velocity.x);
        ifcollision = true;
    }
    if (ifcollision)
    {
        if (gameData->isSoundOn())
        {
            bounceSound.play();
        }
    }
}
float Ball::getRadius()
{
    return object.getLocalBounds().width / 2;
}
void Ball::bounceOff(sf::FloatRect rect)
{
    sf::Vector2f ball_centre, nearest_corner;
    ball_centre.x = object.getGlobalBounds().left + BALL_RADIUS;
    ball_centre.y = object.getGlobalBounds().top + BALL_RADIUS;
    nearest_corner.x = (ball_centre.x < rect.left) ? rect.left : rect.left + rect.width;
    nearest_corner.y = (ball_centre.y < rect.top) ? rect.top : rect.top + rect.height;

    if ((rect.left <= ball_centre.x) && (ball_centre.x <= rect.left + rect.width))
    {
        velocity.y *= -1;
    }
    else if (rect.top <= ball_centre.y && ball_centre.y <= rect.top + rect.height)
    {
        velocity.x *= -1;
    }
    else
    {
        if (abs((nearest_corner - ball_centre).x) <= abs((nearest_corner - ball_centre).y))
        {
            velocity.y *= -1;
        }
        else if (abs((nearest_corner - ball_centre).x) >= abs((nearest_corner - ball_centre).y))
        {
            velocity.x *= -1;
        }
    }
}
bool Ball::handleCollision(sf::FloatRect obstacle, sf::Time deltaTime)
{
    auto next_pos = object.getGlobalBounds();
    next_pos.left += velocity.x * deltaTime.asSeconds();
    next_pos.top += velocity.y * deltaTime.asSeconds();

    //checking for collision with next position
    bool ifcollides = next_pos.intersects(obstacle);
    if (ifcollides)
    {
        bounceOff(obstacle);
        if (gameData->isSoundOn())
        {
            bounceSound.play();
        }
    }
    return ifcollides;
}
void Ball::update(sf::Time deltaTime)
{
    sf::Vector2f newPos = object.getPosition() + velocity * deltaTime.asSeconds();
    setPosition(newPos);
}
void Ball::draw()
{
    auto window = gameData->getWindow();
    window->draw(object);
}
bool Ball::isInBounds()
{
    sf::FloatRect window_bounds;
    window_bounds.left = 0;
    window_bounds.top = 0;
    window_bounds.width = gameData->getWindow()->getSize().x;
    window_bounds.height = gameData->getWindow()->getSize().y;

    return window_bounds.intersects(object.getGlobalBounds());
}
void Ball::increaseSpeed()
{
    float cur_speed = sqrtf(pow(velocity.x, 2) + pow(velocity.y, 2));
    velocity *= (cur_speed + BALL_SPEED_CHANGE) / cur_speed;
}
void Ball::decreaseSpeed()
{
    float cur_speed = sqrtf(pow(velocity.x, 2) + pow(velocity.y, 2));
    velocity *= std::max(float(BALL_MIN_SPEED), (cur_speed - BALL_SPEED_CHANGE)) / cur_speed;
}
sf::Vector2f Ball::getCentrePosition()
{
    return object.getPosition();
}
unsigned Ball::getDamage()
{
    return damage;
}
void Ball::addToVelocity(sf::Vector2f velocity_addition)
{
    velocity += velocity_addition;
}