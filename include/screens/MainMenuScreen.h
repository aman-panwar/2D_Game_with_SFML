#ifndef MAINMENUSCREEN_H
#define MAINMENUSCREEN_H

#include "GameScreen.h"
#include "GameData.h"
#include "screenmanager.h"
#include "textbutton.h"
#include "spritebutton.h"
#include "leaderboard.h"
#include "filehandler.h"
#include "textbox.h"
/** @brief Screen for the Main Menu of the Game
 * 
 * has the various components of the game like the username textbox, play button, sound on/off button, leaderboard, etc
 */
class MainMenuScreen : public GameScreen
{
public:
    MainMenuScreen();
    ///Makes the changes required on the main screen
    void update(sf::Time deltaTime);
    ///Renders the Screen onto the window
    void render();

private:
    sf::Sprite Logo;                                                   ///The logo of the game
    sf::Sprite Background;                                             ///the backgrounf for the screen
    Leaderboard leaderboard = Leaderboard(sf::Vector2f(960.f, 540.f)); ///the leaderboard of the

    /// the play button , takes to level selector screen
    TextButton PlayButton = TextButton(std::string("PLAY"),
                                       sf::Vector2f(960.f, 800.f),
                                       200.f,
                                       80.f);
    TextButton CustomLevelButton = TextButton(std::string("NEW LEVEL"),
                                       sf::Vector2f(1260.f, 800.f),
                                       200.f,
                                       80.f);
    TextButton InfinityPlayButton = TextButton(std::string("ENDLESS PLAY"),
                                       sf::Vector2f(660.f, 800.f),
                                       200.f,
                                       80.f);
    /// the sound on/off button
    SpriteButton SoundButton = SpriteButton(gameData->getTextureHolder().get(TextureID::SoundOn),
                                            sf::Vector2f(1560.f, 800.f),
                                            80.f,
                                            80.f);
    /// selects the planc style
    SpriteButton PlancButton = SpriteButton(gameData->getTextureHolder().get(TextureID::Planc1),
                                            sf::Vector2f(960.f, 900.f),
                                            320.f,
                                            40.f);
    /// Textbox to input the username
    Textbox UserNameTextbox = Textbox(sf::Vector2f(960.f, 1000.f), 320.f, "Unknown");
    /// text to mention planc button
    sf::Text PlancButtonText;

    /** manages what to do with the events
     * @param key the key whose state changes
     * @param isPressed is the key was pressed or not i.e released
     */
    void handleInput(sf::Keyboard::Key key, bool isPressed);
    ///update all the button on the screen
    void updateButtons();
    ///initialises the logo
    void initLogo();
    ///initialises the backround
    void initBackground();
    ///initialises the text
    void initText();
    ///renders the background onto the screen
    void renderButtons();
    ///renders the text onto the screen
    void renderText();
};
#endif