#ifndef FAST_PLANC_POWER_UP
#define FAST_PLANC_POWER_UP

#include "powerup.h"
/**
 * @brief menmbers of this class increase planc speed
 * 
 */
class FastPlancPowerUp : public Powerup
{
public:
    /**
     * Construct a new Fast Planc Power Up object
     * 
     * @param pos takes position of block having the powerup
     */
    FastPlancPowerUp(sf::Vector2f pos);
    /**
     *if collided implements the powerup logic
     * 
     * @param Planc takes planc to check if collided
     */
    void handleCollision(Planc &Planc);
};
#endif