#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>
#include <iostream>
#include "defines.h"
#include "GameData.h"

/** @brief class for textbox 
 * 
 * 
 * creates a textbox which activates when clicked on
 * */
class Textbox
{
private:
    sf::RectangleShape box;
    sf::Text myText;
    sf::Sound errorTypeSound;
    sf::Sound typeSound;
    bool isSelected = false;

public:
    Textbox() = delete;
    /** constructor 
     *  @param centerPos centre position of the textbox
     * @param width width of the textbox
     * @param initText the default text of the textbox
     **/
    Textbox(sf::Vector2f centrePos, float width, std::string initText);
    /** takes the input and does the appropriate action
     * @param key the key whose state changes
     * @param isPressed is the key was pressed or not i.e released
     */
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    ///updates the textbox
    void update();
    ///render the textbox
    void draw();
};
#endif