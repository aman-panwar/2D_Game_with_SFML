#ifndef SPRITEBUTTON_H
#define SPRITEBUTTON_H

#include "button.h"
/** @brief class to use image as button
 * 
 * displays an image as a button. Scale the image to desired values.
 *  This class is similar to textbutton
 * */
class SpriteButton : public Button
{
private:
    sf::Sprite object; ///sprite for the button

public:
    SpriteButton() = delete;
    /** constructor for the SpriteButton
     * @param buttonTexture the texture containing the image
     * @param pos the cordinates of the centre of the button
     * @param width the width of the button
     * @param height the height of the button
     */
    SpriteButton(const sf::Texture &buttonTexture,
                 sf::Vector2f pos,
                 float width,
                 float height);

    /** sets a new Texture for the sprite
     * @param newTexture the texture containin the new image
     * */
    void updateTexture(const sf::Texture &newTexture);
    /// renders the button onto the screen
    void draw();
    ///play the approprite sound, changes colour, and changes the clicked state of the button
    void update();
    /// set the rotation of the sprite
    void setRotation(float);
};
#endif
