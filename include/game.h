#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <memory>
#include <stack>

#include "defines.h"
#include "screenmanager.h"
#include "resourceholder.hpp"
#include "StandardPlayScreen.h"
#include "MainMenuScreen.h"
#include "GameData.h"

/** @brief Encapsultes all part of the game
 * 
 * This class creates the window for the game, updates the state of the game an renders the state onto the screen
 * */
class Game
{
public:
    ///Constructor. It initialises the game.
    Game();

    /// This contians the game loop.This actually runs the game.
    void run();

private:
    sf::RenderWindow window; ///Main Window
    void initWindow();       ///intialises the window
    void loadTextures();     ///loads the textures
    void loadFonts();        ///loads the fonts
    void loadAudio();        ///loads the audios
};
#endif