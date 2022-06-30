#include "block.h"
Block::Block(BlockStyle blockStyle,
             sf::Vector2f size,
             sf::Vector2f pos)
{
    myblockstyle = blockStyle;
    switch (blockStyle)
    {
    case BlockStyle::Style1:
        health = BLOCK1_HEALTH;
        object.setTexture(gameData->getTextureHolder().get(TextureID::Block1));
        break;
    case BlockStyle::Style2:
        health = BLOCK2_HEALTH;
        object.setTexture(gameData->getTextureHolder().get(TextureID::Block2));
        break;
    case BlockStyle::Style3:
        health = BLOCK3_HEALTH;
        object.setTexture(gameData->getTextureHolder().get(TextureID::Block3));
        break;
        break;
    case BlockStyle::Style4:
        health = BLOCK4_HEALTH;
        object.setTexture(gameData->getTextureHolder().get(TextureID::Block4));
        break;
    default:
        object.setTexture(gameData->getTextureHolder().get(TextureID::Block1));
        break;
    }
    object.setPosition(pos);
    object.setScale(size.x / object.getLocalBounds().width,
                    size.y / object.getLocalBounds().height);
    switch (myblockstyle)
    {
    case BlockStyle::Style1:
        ifpower = (rand() % 100 < BLOCK1_POWERUP_PROB);
        break;

    case BlockStyle::Style2:
        ifpower = (rand() % 100 < BLOCK2_POWERUP_PROB);
        break;

    case BlockStyle::Style3:
        ifpower = (rand() % 100 < BLOCK3_POWERUP_PROB);
        break;

    case BlockStyle::Style4:
        ifpower = (rand() % 100 < BLOCK4_POWERUP_PROB);
        break;
    }
    if (ifpower)
    {
        powerUpMarker.setTexture(gameData->getTextureHolder().get(TextureID::BlockHasPowerUp));
        powerUpMarker.setScale(sf::Vector2f(POWERUPMARKERSIZE / powerUpMarker.getGlobalBounds().width,
                                            POWERUPMARKERSIZE / powerUpMarker.getGlobalBounds().height));
        powerUpMarker.setOrigin(sf::Vector2f(powerUpMarker.getGlobalBounds().width / 2,
                                             powerUpMarker.getGlobalBounds().height / 2));
        powerUpMarker.setPosition(sf::Vector2f(object.getGlobalBounds().left + object.getGlobalBounds().width / 2,
                                               object.getGlobalBounds().top + object.getGlobalBounds().height / 2));
    }
}
sf::FloatRect Block::getBounds()
{
    return object.getGlobalBounds();
}
BlockStyle Block::getBlockStyle()
{
    return myblockstyle;
}
void Block::draw()
{
    auto window = gameData->getWindow();
    window->draw(object);
    if (ifpower)
    {
        window->draw(powerUpMarker);
    }
}
unsigned Block::gethealth()
{
    return health;
}
void Block::takeDamage(unsigned damage)
{
    health = std::max(int(0), int(health) - int(damage));
}
PowerUp Block::dropPowerUp()
{
    PowerUp mypowerup = PowerUp::NoPowerUp;
    if (ifpower && health == 0)
    {
        int powerupindex = rand() % 12;
        switch (powerupindex)
        {
        case 0:
            mypowerup = PowerUp::Momentum;
            break;
        case 1:
            mypowerup = PowerUp::IncreasePlancLength;
            break;
        case 2:
            mypowerup = PowerUp::DecreadePlancLength;
            break;
        case 3:
            mypowerup = PowerUp::IncreasePlancSpeed;
            break;
        case 4:
            mypowerup = PowerUp::DecreasePlancSpeed;
            break;
        case 5:
            mypowerup = PowerUp::TenBalls;
            break;
        case 6:
            mypowerup = PowerUp::TenBalls;
            break;
        case 7:
            mypowerup = PowerUp::ExtraLife;
            break;
        case 8:
            mypowerup = PowerUp::SlowDownBalls;
            break;
        case 9:
            mypowerup = PowerUp::SpeedUpBalls;
            break;
        case 10:
            mypowerup = PowerUp::FireBall;
            break;
        case 11:
            mypowerup = PowerUp::CrazyBall;
            break;
        default:
            break;
        }
    }
    return mypowerup;
}