#include "textbox.h"

Textbox::Textbox(sf::Vector2f centrePos, float width, std::string initText)
{
    box.setSize(sf::Vector2f(width, float(TEXTBOX_HEIGHT)));
    box.setOrigin(box.getLocalBounds().width / 2, box.getLocalBounds().height / 2);
    box.setPosition(centrePos);
    box.setFillColor(sf::Color(TEXTBOX_BACKGROUND_COLOR));
    box.setOutlineThickness(5);
    box.setOutlineColor(sf::Color(TEXTBOX_UNSELECTED_BORDER_COLOR));

    myText.setFont(gameData->getFontHolder().get(FontID::TextFont));
    myText.setString(initText);
    myText.setFillColor(sf::Color(TEXTBOX_TEXT_COLOR));
    myText.setCharacterSize(TEXTBOX_HEIGHT);
    myText.setScale(0.5 * box.getLocalBounds().height / myText.getLocalBounds().height,
                    0.5 * box.getLocalBounds().height / myText.getLocalBounds().height);
    myText.setOrigin(0, myText.getLocalBounds().height / 2);
    myText.setPosition(centrePos + sf::Vector2f(-width / 2 + 5, 0));

    errorTypeSound.setBuffer(gameData->getSoundHolder().get(SoundID::TextboxError));
    typeSound.setBuffer(gameData->getSoundHolder().get(SoundID::TextboxType));
}
void Textbox::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if (!isSelected)
        return;
    if (!isPressed)
    {
        if (key == sf::Keyboard::BackSpace)
        {
            std::string curString = myText.getString();
            if (curString.size() == 0)
            {
                if (gameData->isSoundOn())
                {
                    errorTypeSound.play();
                }
            }
            else
            {
                curString.pop_back();
                if (gameData->isSoundOn())
                {
                    typeSound.play();
                }
            }
            myText.setString(sf::String(curString));
        }
        else
        {
            char inputChar = (key - sf::Keyboard::A) + 'A';
            if ((inputChar >= 'A') && (inputChar <= 'Z'))
            {
                if (myText.getString().getSize() <= MAX_USERNAME_LENGTH)
                {
                    if (gameData->isSoundOn())
                    {
                        typeSound.play();
                    }
                    myText.setString(myText.getString() + sf::String(inputChar));
                }
                else
                {
                    if (gameData->isSoundOn())
                    {
                        errorTypeSound.play();
                    }
                }
            }
        }
    }
    std::string Alias = myText.getString();
    if (Alias == "")
        Alias = "UNKNOWN";
    gameData->getCurPlayer().setAlias(Alias);
}
void Textbox::update()
{
    sf::Vector2f mousepos = (sf::Vector2f)sf::Mouse::getPosition(*(gameData->getWindow()));

    //setting colour of the textbox and setting selected state;
    sf::Color newCol = sf::Color(TEXTBOX_UNSELECTED_BORDER_COLOR);
    if (box.getGlobalBounds().contains(mousepos))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isSelected = true;
            newCol = sf::Color(TEXTBOX_SELECTED_BORDER_COLOR);
        }
        else
        {
            newCol = sf::Color(TEXTBOX_HOVER_BORDER_COLOR);
        }
    }
    else
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            isSelected = false;
        }
    }
    if (isSelected)
    {
        newCol = sf::Color(TEXTBOX_SELECTED_BORDER_COLOR);
    }
    box.setOutlineColor(newCol);
}
void Textbox::draw()
{
    auto window = gameData->getWindow();
    window->draw(box);
    window->draw(myText);
}