#ifndef GAMEDATA_H
#define GAMEDATA_H

#include <iostream>
#include <SFML/Graphics.hpp>
#include <list>
#include <queue>
#include <optional>
#include "defines.h"
#include "resourceholder.hpp"
#include "player.h"
#include "block.h"

#define gameData GameData::GetData()

/** @brief This is a singleton class which hold encapsulates the main renderwindow
 * the player info, the instructions for navigation, resources
 * 
 * This class provides a convinient way to pass around the necessary information
 * easily between the Screens of the Game.
 */
class GameData
{

public:
    /// Return the pointer to the class object
    static GameData *GetData();

    /// @return The pointer to the window set by setWindow()
    /// @see setWindow()
    sf::RenderWindow *getWindow();

    /** stores the sf::RenderWindow of the game but only once, once it is stored it does not update the window
     * @param Window the pointer to game window
     * @return if the pointer to the render window was changed
     * */
    bool setWindow(sf::RenderWindow *Window);

    /** returns is Sound is on or off
     * */
    bool isSoundOn();
    /** sets if sound is on of off
     * */
    void setSoundState(bool SoundState);
    ///returns the planc style
    PlancStyle getPlancStyle();
    ///saves the planc style
    void setPlancStyle(PlancStyle newPlanc);

    ///return refrence to the player
    Player &getCurPlayer();
    ///save the level info
    void setLevelInfo(std::list<Block>);
    ///returns the level info
    std::list<Block> getLevelInfo();
    void setLevelIndex(unsigned index);
    unsigned getLevelIndex();

    void setInfinityModeDifficulty(unsigned);
    unsigned getInfinityModeDifficulty();

    ///return reference to main texture holder
    TextureHolder &getTextureHolder();
    ///return reference to main font holder
    FontHolder &getFontHolder();
    ///return reference to main sound holder
    SoundHolder &getSoundHolder();
    ///return reference to main music holder
    MusicHolder &getMusicHolder();

    bool isStandardPlay();
    void setIfStandardPlay(bool);

private:
    GameData() {}
    GameData(GameData const &) {}
    GameData &operator=(GameData const &) = delete;
    static GameData *instance; ///pointer ot the single instance

    sf::RenderWindow *window; ///Stores the pointer to the game window

    bool CurSoundState;    ///saves if game sounds are on or off
    PlancStyle plancstyle; ///saves the plac style
    Player curPlayer;      ///the the player info
    unsigned level_index = 0;
    unsigned difficulty = 0;
    bool isstanadardplay = true;
    std::list<Block> level_info; ///saves the level info

    TextureHolder Textures; ///saves the textures
    FontHolder Fonts;       ///saves the fonts
    SoundHolder Sounds;     ///saves the sounds
    MusicHolder Musics;     ///saves the music
};
#endif