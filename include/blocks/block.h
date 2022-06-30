#include "GameData.h"
#ifndef BLOCK_H
#define BLOCK_H

#include <SFML/Graphics.hpp>
#include "defines.h"
/** @brief The base class for all the blocks in the game
 * 
 **/
class Block
{
private:
    sf::Sprite object; //sprite for the block
    sf::Sprite powerUpMarker;
    unsigned health; //health of the block
    BlockStyle myblockstyle;
    bool ifpower = false;

public:
    /** creates a new block 
     * @param blockStyle the style of the block to be constructed
     * @param Pos place in grid where block is to be set
     * @param size size of the block
     **/
    Block(BlockStyle blockStyle, sf::Vector2f size, sf::Vector2f pos);

    /**check if ball collided the given block
     * @param ballpos takes ball position and compare it with block pos
     * */
    bool CheckColission(sf::FloatRect ballpos);

    /**
     * updates texture based on health
     * */
    void updatetexture();

    /**
     * displays block
     */
    void draw();

    /**
     * @return block health
     */
    unsigned gethealth();

    /**
     * take damage value from block and remove it from health of block
     */
    void takeDamage(unsigned damage);
    
    /**
     * return the kind of power up the block has. Returns the power up only when the health is 0
     * @return the power up type
     * */
    PowerUp dropPowerUp();

    /// returns global bounds of block
    /**
     * @return bounds of block 
     */
    sf::FloatRect getBounds();
    /**
     *Get the Block Style object
     * 
     * @return BlockStyle 
     */
    BlockStyle getBlockStyle();
    /**
     * 
     * @param myblock 
     * @return bool 
     */
    friend bool isBlockDead(const Block &myblock);
};
#endif