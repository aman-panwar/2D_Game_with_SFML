#include "SlowPlancPowerUp.h"
SlowPlancPowerUp::SlowPlancPowerUp(sf::Vector2f pos) : Powerup(pos)
{
    object.setTexture(gameData->getTextureHolder().get(TextureID::FastPlancPowerUp));
    object.setScale(POWER_UP_SIZE / object.getGlobalBounds().width,
                    POWER_UP_SIZE / object.getGlobalBounds().height);
}
void SlowPlancPowerUp::handleCollision(Planc &planc)
{
    if (planc.getBounds().intersects(object.getGlobalBounds()))
    {
        is_Alive=false;
        if (gameData->isSoundOn())
        {
            CollisionSound.play();
        }
        planc.decreaseSpeed();
    }
}
