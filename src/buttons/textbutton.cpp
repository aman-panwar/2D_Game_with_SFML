#include "textbutton.h"

TextButton::TextButton(std::string buttonText, sf::Vector2f pos, float width, float height)
{
    //box properties
    box.setSize(sf::Vector2f(width - 2*BUTTON_BORDER_THICKNESS, height-2*BUTTON_BORDER_THICKNESS));
    box.setOrigin(box.getLocalBounds().width / 2, box.getLocalBounds().height / 2);
    box.setPosition(pos);
    box.setOutlineColor(sf::Color(DEFAULT_BUTTON_BORDER_COLOR));
    box.setOutlineThickness(BUTTON_BORDER_THICKNESS);
    box.setFillColor(sf::Color(DEFAULT_BUTTON_IDLE_COLOR));

    //text properties
    text.setString(buttonText);
    text.setFont(gameData->getFontHolder().get(FontID::ButtonFont));
    text.setCharacterSize((int)width + 1);
    float textScaleValue = 0.6 * std::min(box.getLocalBounds().height / text.getLocalBounds().height,
                                          box.getLocalBounds().width / text.getLocalBounds().width);
    text.setScale(textScaleValue, textScaleValue);
    text.setOrigin(text.getLocalBounds().width / 2,
                   text.getLocalBounds().height / 2);
    text.setPosition(pos + sf::Vector2f(0.f, -textScaleValue * 20.f));
}
void TextButton::draw()
{
    gameData->getWindow()->draw(box);
    gameData->getWindow()->draw(text);
}
void TextButton::update()
{
    sf::Vector2f mousepos = (sf::Vector2f)sf::Mouse::getPosition(*(gameData->getWindow()));

    //setting colour of the button
    sf::Color newCol = sf::Color(DEFAULT_BUTTON_IDLE_COLOR);
    if (box.getGlobalBounds().contains(mousepos))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            if (!clickSoundMade)
            {
                if (gameData->isSoundOn())
                {
                    clickSound.play();
                }
                clickSoundMade = true;
            }
            newCol = sf::Color(DEFAULT_BUTTON_CLICKED_COLOR);
        }
        else
        {
            if (!hoverSoundMade)
            {
                if (gameData->isSoundOn())
                {
                    hoverOverSound.play();
                }
                hoverSoundMade = true;
            }
            clickSoundMade = false;
            newCol = sf::Color(DEFAULT_BUTTON_HOVER_COLOR);
        }
    }
    else
    {
        clickSoundMade = false;
        hoverSoundMade = false;
    }
    box.setFillColor(newCol);

    updateClickState(box.getGlobalBounds());
}