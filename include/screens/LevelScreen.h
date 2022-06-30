#ifndef LEVELSCREEN_H
#define LEVELSCREEN_H

#include "GameScreen.h"
#include "GameData.h"
#include "screenmanager.h"
#include "textbutton.h"
#include "spritebutton.h"

/** @brief this screen displays the diffirent levels available to play
 * 
 * 
 * generates the various level buttons, when the button is pressed 
 * it loads the corresponding level data and takes us to standard play screen
 * */
class LevelScreen : public GameScreen
{
private:
    sf::RectangleShape BoundaryBox; ///boundary for the screen
    sf::RectangleShape HeaderBox;   ///banner for header of the screen
    sf::Sprite Background;          ///background
    sf::Text Header;                ///header text

    unsigned cur_page_number = 1, ///cur page
        max_page_number = 1;      ///total number of pages

    ///takes us back to main menu
    SpriteButton CloseButton = SpriteButton(gameData->getTextureHolder().get(TextureID::CloseButton),
                                            sf::Vector2f(125.f, 125.f),
                                            35.f,
                                            35.f);
    ///shows us the next set of levels
    SpriteButton NextPageButton = SpriteButton(gameData->getTextureHolder().get(TextureID::PageButton),
                                               sf::Vector2f(gameData->getWindow()->getSize().x - 125.f, 125.f),
                                               35.f,
                                               35.f);
    ///shows us the prev set of levels
    SpriteButton PrevPageButton = SpriteButton(gameData->getTextureHolder().get(TextureID::PageButtonDeactivated),
                                               sf::Vector2f(gameData->getWindow()->getSize().x - 125.f - 45.f, 125.f),
                                               35.f,
                                               35.f);

    std::vector<TextButton> levelButtons;    ///level butttons
    std::vector<SpriteButton> deleteButtons; ///delete buttons
    ///inititalise the background
    void initBackground();
    /** manages what to do with the events
     * @param key the key whose state changes
     * @param isPressed is the key was pressed or not i.e released
     */
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    ///initialises the buttons
    void initButtons();
    ///renders the button
    void renderButtons();
    ///updates the buttons
    void updateButtons();
    ///does the required aciton on button clicks
    void manageButtonClick();
    ///activates or deactivates the textures for nextpage and prev page buttons
    void updatePageButtonTexture();

public:
    LevelScreen();
    ///updates all the elements in the screen
    void update(sf::Time deltaTime);
    ///renders all the elements on in the screen
    void render();
};
#endif