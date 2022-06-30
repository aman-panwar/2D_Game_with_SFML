#ifndef CUSTOM_LEVEL_SCREEN_H
#define CUSTOM_LEVEL_SCREEN_H

#include "screenmanager.h"
#include "GameScreen.h"
#include "GameData.h"
#include "textbutton.h"

/**
 * @brief class for custom level designeer screen
 * 
 *  This class allows us to make the levels as we wanted
 * 
 */
class CustomLevelScreen : public GameScreen
{
private:
    TextButton SaveButton = TextButton("SAVE",
                                       sf::Vector2f(CUSTOMLEVEL_BUTTON_WIDTH / 2.0 + 10,
                                                    CUSTOMLEVEL_BUTTON_HEIGHT / 2.0 + 10),
                                       CUSTOMLEVEL_BUTTON_WIDTH,
                                       CUSTOMLEVEL_BUTTON_HEIGHT);

    TextButton QuitButton = TextButton("QUIT",
                                       sf::Vector2f(CUSTOMLEVEL_BUTTON_WIDTH / 2.0 + 10,
                                                    3 * CUSTOMLEVEL_BUTTON_HEIGHT / 2.0 + 20),
                                       CUSTOMLEVEL_BUTTON_WIDTH,
                                       CUSTOMLEVEL_BUTTON_HEIGHT);

    TextButton BlockButton1 = TextButton("Block 1",
                                         sf::Vector2f(CUSTOMLEVEL_BUTTON_WIDTH / 2.0 + 10,
                                                      5 * CUSTOMLEVEL_BUTTON_HEIGHT / 2.0 + 30),
                                         CUSTOMLEVEL_BUTTON_WIDTH,
                                         CUSTOMLEVEL_BUTTON_HEIGHT);
    TextButton BlockButton2 = TextButton("Block 2",
                                         sf::Vector2f(CUSTOMLEVEL_BUTTON_WIDTH / 2.0 + 10,
                                                      7 * CUSTOMLEVEL_BUTTON_HEIGHT / 2.0 + 40),
                                         CUSTOMLEVEL_BUTTON_WIDTH,
                                         CUSTOMLEVEL_BUTTON_HEIGHT);
    TextButton BlockButton3 = TextButton("Block 3",
                                         sf::Vector2f(CUSTOMLEVEL_BUTTON_WIDTH / 2.0 + 10,
                                                      9 * CUSTOMLEVEL_BUTTON_HEIGHT / 2.0 + 50),
                                         CUSTOMLEVEL_BUTTON_WIDTH,
                                         CUSTOMLEVEL_BUTTON_HEIGHT);

    TextButton BlockButton4 = TextButton("Block 4",
                                         sf::Vector2f(CUSTOMLEVEL_BUTTON_WIDTH / 2.0 + 10,
                                                      11 * CUSTOMLEVEL_BUTTON_HEIGHT / 2.0 + 60),
                                         CUSTOMLEVEL_BUTTON_WIDTH,
                                         CUSTOMLEVEL_BUTTON_HEIGHT);
    sf::Sound FailSound, PassSound;

    std::list<Block> placed_blocks;///holds list of blocks created up till the moment
    sf::RectangleShape cur_block_shape;/// holds block shape
    bool first_placed = false;
    unsigned cur_block = 0;
    sf::Vector2f pos1, pos2;

    sf::FloatRect ValidArea;// make sure blocks does not intersect

    sf::RectangleShape PlancArea;// make sure no blocks in planc area
    sf::Sprite UpperWall, LeftWall, RightWall;
    sf::Sprite Background;
    sf::RectangleShape Container;
    sf::Text Text;
    /**
     *  updates all buttons
     * 
     */
    void updateButtons();
    /**
     *  update the block's place
     * 
     */
    void updateBlockPlacement();

public:
    CustomLevelScreen();
    /**
     *  updates all placed blocks, buttons, background and borders
     * 
     * @param deltatime 
     */
    void update(sf::Time deltatime);
    /**
     *  handle quitting by pressing esc
     * 
     * @param key 
     * @param isPressed 
     */
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    /**
     *  renders every thing to be displayed
     * 
     */
    void render();
};
#endif