#ifndef TEXTBUTTON_H
#define TEXTBUTTON_H

#include "button.h"
/** @brief class for button that diplays a text
 * 
 * derived from Button class declared in button.h
 *  This class is similar to spritebutton
 * */
class TextButton : public Button
{
private:
    sf::RectangleShape box;
    sf::Text text;

    sf::Color IdleColour;
    sf::Color HoverColour;
    sf::Color ClickedColour;
    sf::Color BorderColour;

public:
    TextButton() = delete;
    /** constructor for the class
     * @param buttonText the text to be displayed
     * @param pos the cordinates of the centre of the button
     * @param width the width of the button
     * @param height the height of the button
     */
    TextButton(std::string buttonText,
               sf::Vector2f pos,
               float width,
               float height);
    /// renders the button onto the screen
    void draw();
    ///play the approprite sound, changes colour, and changes the clicked state of the button
    void update();
};
#endif
