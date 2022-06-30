#ifndef SHORT_PLANC_POWER_UP
#define SHORT_PLANC_POWER_UP

#include "powerup.h"

/**
 * @brief menmbers of this class decrease planc length
 * 
 */
class ShortPlancPowerUp : public Powerup
{
public:
    /**
     *  Construct a new Short Planc Power Up object
     * 
     * @param pos sets powerup sprite position at broken brick place
     */
    ShortPlancPowerUp(sf::Vector2f pos);
    void handleCollision(Planc &Planc);
};
#endif