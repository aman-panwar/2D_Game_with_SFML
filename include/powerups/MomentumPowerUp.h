#ifndef MOMENTUM_POWER_UP
#define MOMENTUM_POWER_UP

#include "powerup.h"
/** @brief class for momentum power up
 * 
 * class is derived from Powerup and uses 
 * virtual handleCollision to change the 
 * properties of planc passed byt refference
 * */
class MomentumPowerUp : public Powerup
{
public:
    MomentumPowerUp(sf::Vector2f pos);
    void handleCollision(Planc &Planc);
};
#endif