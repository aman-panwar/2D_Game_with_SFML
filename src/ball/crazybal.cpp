#include "crazyball.h"
CrazyBall::CrazyBall(sf::Vector2f pos, sf::Vector2f vel) : Ball(pos, vel)
{
    object.setTexture(gameData->getTextureHolder().get(TextureID::CrazyBall));
    // object.setScale(2 * BALL_RADIUS / object.getLocalBounds().width,
    //                 2 * BALL_RADIUS / object.getLocalBounds().height);
    // object.setOrigin(object.getLocalBounds().width / 2,
    //                  object.getLocalBounds().height / 2);
    damage = CRAZYBALL_DAMAMGE;
}
void CrazyBall::bounceOff(sf::FloatRect rect)
{
    sf::Vector2f ball_centre, nearest_corner;
    ball_centre.x = object.getGlobalBounds().left + BALL_RADIUS;
    ball_centre.y = object.getGlobalBounds().top + BALL_RADIUS;
    nearest_corner.x = (ball_centre.x < rect.left) ? rect.left : rect.left + rect.width;
    nearest_corner.y = (ball_centre.y < rect.top) ? rect.top : rect.top + rect.height;

    if ((rect.left <= ball_centre.x) && (ball_centre.x <= rect.left + rect.width))
    {
        velocity.y *= -1;
        velocity.x = (2 * rand() % 2 - 1) * (rand() % 10 + 1) * velocity.x / 10;
    }
    else if (rect.top <= ball_centre.y && ball_centre.y <= rect.top + rect.height)
    {
        velocity.x *= -1;
        velocity.y = (2 * rand() % 2 - 1) * (rand() % 10 + 1) * velocity.y / 10;
    }
    else
    {
        if (abs((nearest_corner - ball_centre).x) <= abs((nearest_corner - ball_centre).y))
        {
            velocity.y *= -1;
            velocity.x = (2 * rand() % 2 - 1) * (rand() % 10 + 1) * velocity.x / 10;
        }
        else if (abs((nearest_corner - ball_centre).x) >= abs((nearest_corner - ball_centre).y))
        {
            velocity.x *= -1;
            velocity.y = (2 * rand() % 2 - 1) * (rand() % 10 + 1) * velocity.y / 10;
        }
    }
}