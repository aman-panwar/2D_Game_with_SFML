#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "GameData.h"
#include "defines.h"
/**
 * @brief base class for buttons
 * 
 * provides the common functionality for sprite button and text button
 * */
class Button
{
public:
    virtual ~Button(){};
    /** checks is the button was clicked, this also resets the button to unclicked
     * @return true if and only if the button was clicked
     * */
    virtual bool isClicked();
    /** make the changes to the state of button based on mouse position
     * */
    virtual void update() = 0;
    /**renders the button onto the window
     * */
    virtual void draw() = 0;

protected:
    Button();
    sf::Sound clickSound;         ///plays the click sound for the button
    sf::Sound hoverOverSound;     ///plays the hover sound for the button
    bool clickSoundMade = false;  ///saves if the click sound has been made once or not
    bool hoverSoundMade = false;  ///saves if the hover sound has been made once or not
    bool isbuttonPressed = false; ///saves if the button was pressed
    bool isMousePressed = false;  ///saves if mouse was pressed over the button
    /** update the buttonPressed to appropriate value
     * @param box the gobal bounds of the object
     * */
    void updateClickState(sf::FloatRect box);
};
#endif