#ifndef LONG_PLANC_POWER_UP
#define LONG_PLANC_POWER_UP

#include "powerup.h"
/**
 * @brief menmbers of this class increase planc length
 * 
 */
class LongPlancPowerUp : public Powerup
{
public:
/**
 *  Construct a new Long Planc Power Up object
 * 
 * @param pos set position of sprite at broken block
 */
    LongPlancPowerUp(sf::Vector2f pos);
    /**
     *  if cllided then will initiate game logic
     * 
     * @param Planc 
     */
    void handleCollision(Planc &Planc);
};
#endif