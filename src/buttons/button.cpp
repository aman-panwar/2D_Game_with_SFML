#include "button.h"
Button::Button()
{
    clickSound.setBuffer(gameData->getSoundHolder().get(SoundID::ButtonClicked));
    hoverOverSound.setBuffer(gameData->getSoundHolder().get(SoundID::ButtonHoverOver));
    //clickSound.setVolume(20.f);
    hoverOverSound.setVolume(10.f);
}
void Button::updateClickState(sf::FloatRect box)
{
    sf::Vector2f mousepos = (sf::Vector2f)sf::Mouse::getPosition(*(gameData->getWindow()));

    if (box.contains(mousepos))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isMousePressed = true;
        }
        else
        {
            if (isMousePressed == true)
            {
                isbuttonPressed = true;
                isMousePressed = false;
            }
        }
    }
    else
    {
        isMousePressed = false;
    }
}

bool Button::isClicked()
{
    if (isbuttonPressed == true)
    {
        isbuttonPressed = false;
        return true;
    }
    return false;
}