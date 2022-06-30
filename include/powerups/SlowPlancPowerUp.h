#ifndef SLOW_PLANC_POWER_UP
#define SLOW_PLANC_POWER_UP

#include "powerup.h"

/**
 * @brief menmbers of this class decreases planc speed
 * 
 */

class SlowPlancPowerUp : public Powerup
{
public:
/**
 *  Construct a new Slow Planc Power Up object
 * 
 * @param pos posiion of broken block
 */
    SlowPlancPowerUp(sf::Vector2f pos);
    void handleCollision(Planc &Planc);
};
#endif