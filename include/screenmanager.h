#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <stack>
#include <memory>

#include "defines.h"

#include "MainMenuScreen.h"
#include "StandardPlayScreen.h"
#include "LevelScreen.h"
#include "InfinityPlayScreen.h"
#include "CustomLevelScreen.h"
#include "QuitScreen.h"
#include "WinScreen.h"
#include "LostScreen.h"
#include "pauseScreen.h"
#include "InfinityWinScreen.h"

enum class Screen
{
    MainMenuScreen,
    LevelScreen,
    StandardPlayScreen,
    InfinityPlayScreen,
    CustomLevelScreen,
    QuitScreen,
    QuitGame,
    WinScreen,
    LoseScreen,
    PauseScreen,
    InfinityWinScreen
};

/** @brief This is a sigleton Class which changes the screeen currenntly in use
 * */
class ScreenManager
{
private:
    ScreenManager() {}
    ScreenManager(ScreenManager const &) {}
    ScreenManager &operator=(ScreenManager const &) = delete;
    static ScreenManager *instance;

    ///Stores the Screens of the Game
    std::stack<std::shared_ptr<GameScreen>> ScreenStack;

    ///Store the name of the current screen
    Screen curScreenName;

public:
    /// lazy initialises the ScreenManager and sets the initial screen of the gmae
    static ScreenManager *GetManager();

    /** tries to go to a target screen
     * @param screenName target screen to visit
     * @return true if the target screen was valid and put in use  otherwise false
     * */
    bool goToScreen(Screen screenName);

    /** return the pointer to the current screen in use
     * @return pointer to the current screen in use
     * */
    std::optional<std::shared_ptr<GameScreen>> curScreen();
};

#endif