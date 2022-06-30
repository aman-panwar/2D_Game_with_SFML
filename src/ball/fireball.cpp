#include "fireball.h"
FireBall::FireBall(sf::Vector2f pos, sf::Vector2f vel) : Ball(pos, vel)
{
    object.setTexture(gameData->getTextureHolder().get(TextureID::FireBall));
    // object.setScale(2 * BALL_RADIUS / object.getLocalBounds().width,
    //                 2 * BALL_RADIUS / object.getLocalBounds().height);
    // object.setOrigin(object.getLocalBounds().width / 2,
    //                  object.getLocalBounds().height / 2);
    damage = FIREBALL_DAMAMGE;
}