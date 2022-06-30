#include "spritebutton.h"
SpriteButton::SpriteButton(const sf::Texture &buttonTexture,
                           sf::Vector2f pos,
                           float width,
                           float height)
{
    object.setTexture(buttonTexture);
    object.setScale(width / object.getLocalBounds().width,
                    height / object.getLocalBounds().height);
    object.setOrigin(object.getLocalBounds().width / 2,
                     object.getLocalBounds().height / 2);
    object.setPosition(pos);
}

void SpriteButton::draw()
{
    gameData->getWindow()->draw(object);
}

void SpriteButton::update()
{
    sf::Vector2f mousepos = (sf::Vector2f)sf::Mouse::getPosition(*(gameData->getWindow()));
    //setting colour of the button
    sf::Color newCol = sf::Color(255, 255, 255, 255);
    if (object.getGlobalBounds().contains(mousepos))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            //set color for pressed
            newCol = sf::Color(220, 220, 220, 255);
            if (!clickSoundMade)
            {
                if (gameData->isSoundOn())
                {
                    clickSound.play();
                }
                clickSoundMade = true;
            }
        }
        else
        {
            //set color for hover
            newCol = sf::Color(180, 180, 180, 255);
            if (!hoverSoundMade)
            {
                if (gameData->isSoundOn())
                {
                    hoverOverSound.play();
                }
                hoverSoundMade = true;
            }
            clickSoundMade = false;
        }
    }
    else
    {
        clickSoundMade = false;
        hoverSoundMade = false;
    }
    object.setColor(newCol);
    updateClickState(object.getGlobalBounds());
}
void SpriteButton::updateTexture(const sf::Texture &newTexture)
{
    object.setTexture(newTexture);
}
void SpriteButton::setRotation(float angle)
{
    object.setRotation(angle);
}