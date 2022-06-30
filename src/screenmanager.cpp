#include "screenmanager.h"
//just to debug code easy
std::string ScreenToString(Screen myScreen)
{
    std::string str = "";
    switch (myScreen)
    {
    case Screen::MainMenuScreen:
        str = "mainmenu";
        break;
    case Screen::LevelScreen:
        str = "levelscreen";
        break;
    case Screen::StandardPlayScreen:
        str = "stand play";
        break;

    case Screen::InfinityPlayScreen:
        str = "infi play";
        break;
    case Screen::CustomLevelScreen:
        str = "cust level";
        break;
    case Screen::QuitScreen:
        str = "quit scr";
        break;
    case Screen::WinScreen:
        str = "win scr";
        break;
    case Screen::LoseScreen:
        str = "lose scr";
        break;
    case Screen::PauseScreen:
        str = "pause scr";
        break;
    case Screen::InfinityWinScreen:
        str = "infi win scr";
        break;

    default:
        break;
    }
    return str;
}

ScreenManager *ScreenManager::GetManager()
{
    if (!instance)
    {
        instance = new ScreenManager();
        ///setting initial screen for the game
        ScreenManager::GetManager()->ScreenStack.push(std::unique_ptr<GameScreen>(new MainMenuScreen));
        ScreenManager::GetManager()->curScreenName = Screen::MainMenuScreen;
    }
    return instance;
}
bool ScreenManager::goToScreen(Screen screenName)
{
    //try to use a tree like strcuture to define the screen hierarchy.
    //that will make it easier to add new screens
    bool isSuccess = false;

    //std::cout<<"===\ncur: "<<ScreenToString(curScreenName)<<"\ngoing to: "<<ScreenToString(screenName)<<"\n";

    switch (curScreenName)
    {
    case Screen::MainMenuScreen:
        if (screenName == Screen::LevelScreen)
        {
            ScreenStack.push(std::unique_ptr<GameScreen>(new LevelScreen));
            curScreenName = Screen::LevelScreen;
            isSuccess = true;
        }
        else if (screenName == Screen::QuitScreen)
        {
            ScreenStack.push(std::unique_ptr<GameScreen>(new QuitScreen));
            curScreenName = Screen::QuitScreen;
            isSuccess = true;
        }
        else if (screenName == Screen::InfinityPlayScreen)
        {
            ScreenStack.push(std::unique_ptr<GameScreen>(new InfinityPlayScreen));
            curScreenName = Screen::InfinityPlayScreen;
            isSuccess = true;
        }
        else if (screenName == Screen::CustomLevelScreen)
        {
            ScreenStack.push(std::unique_ptr<GameScreen>(new CustomLevelScreen));
            curScreenName = Screen::CustomLevelScreen;
            isSuccess = true;
        }
        break;
    case Screen::LevelScreen:
        if (screenName == Screen::MainMenuScreen)
        {
            ScreenStack.pop();
            curScreenName = Screen::MainMenuScreen;
            isSuccess = true;
        }
        else if (screenName == Screen::StandardPlayScreen)
        {
            ScreenStack.push(std::unique_ptr<GameScreen>(new StandardPlayScreen));
            curScreenName = Screen::StandardPlayScreen;
            isSuccess = true;
        }
        break;
    case Screen::StandardPlayScreen:
        if (screenName == Screen::MainMenuScreen)
        {
            ScreenStack.pop();
            ScreenStack.pop();
            curScreenName = Screen::MainMenuScreen;
            isSuccess = true;
        }
        if (screenName == Screen::PauseScreen)
        {
            ScreenStack.push(std::unique_ptr<GameScreen>(new PauseScreen));
            curScreenName = Screen::PauseScreen;
            isSuccess = true;
        }
        if (screenName == Screen::WinScreen)
        {
            ScreenStack.push(std::unique_ptr<GameScreen>(new WinScreen));
            curScreenName = Screen::WinScreen;
            isSuccess = true;
        }
        if (screenName == Screen::LoseScreen)
        {
            ScreenStack.push(std::unique_ptr<GameScreen>(new LostScreen));
            curScreenName = Screen::LoseScreen;
            isSuccess = true;
        }
        break;
    case Screen::QuitScreen:
        if (screenName == Screen::MainMenuScreen)
        {
            ScreenStack.pop();
            curScreenName = Screen::MainMenuScreen;
            isSuccess = true;
        }
        if (screenName == Screen::QuitGame)
        {
            while (!ScreenStack.empty())
            {
                ScreenStack.pop();
            }
            isSuccess = true;
        }
        break;

    case Screen::PauseScreen:
        if (screenName == Screen::MainMenuScreen)
        {
            while (!ScreenStack.empty())
            {
                ScreenStack.pop();
            }
            ScreenStack.push(std::unique_ptr<GameScreen>(new MainMenuScreen));

            curScreenName = Screen::MainMenuScreen;
            isSuccess = true;
        }
        if (screenName == Screen::StandardPlayScreen)
        {
            ScreenStack.pop();
            curScreenName = Screen::StandardPlayScreen;
            isSuccess = true;
        }
        if (screenName == Screen::InfinityPlayScreen)
        {
            ScreenStack.pop();
            curScreenName = Screen::InfinityPlayScreen;
            isSuccess = true;
        }
        break;
    case Screen::WinScreen:
        if (screenName == Screen::MainMenuScreen)
        {
            ScreenStack.pop();
            ScreenStack.pop();
            ScreenStack.pop();
            curScreenName = Screen::MainMenuScreen;
            isSuccess = true;
        }
        if (screenName == Screen::StandardPlayScreen)
        {
            ScreenStack.pop();
            ScreenStack.pop();
            ScreenStack.push(std::unique_ptr<GameScreen>(new StandardPlayScreen));
            curScreenName = Screen::StandardPlayScreen;
            isSuccess = true;
        }
        break;
    case Screen::LoseScreen:
        if (screenName == Screen::MainMenuScreen)
        {
            while (ScreenStack.size() != 1)
            {
                ScreenStack.pop();
            }
            curScreenName = Screen::MainMenuScreen;
            isSuccess = true;
        }
        if (screenName == Screen::StandardPlayScreen)
        {
            ScreenStack.pop();
            ScreenStack.pop();
            ScreenStack.push(std::unique_ptr<GameScreen>(new StandardPlayScreen));
            curScreenName = Screen::StandardPlayScreen;
            isSuccess = true;
        }
        if (screenName == Screen::InfinityPlayScreen)
        {
            ScreenStack.pop();
            ScreenStack.pop();
            ScreenStack.push(std::unique_ptr<GameScreen>(new InfinityPlayScreen));
            curScreenName = Screen::InfinityPlayScreen;
            isSuccess = true;
        }
        break;
    case Screen::CustomLevelScreen:
        if (screenName == Screen::MainMenuScreen)
        {
            ScreenStack.pop();
            curScreenName = Screen::MainMenuScreen;
            isSuccess = true;
        }
        break;
    case Screen::InfinityPlayScreen:
        if (screenName == Screen::InfinityWinScreen)
        {
            curScreenName = Screen::InfinityWinScreen;
            ScreenStack.push(std::unique_ptr<GameScreen>(new InfinityWinScreen));
            isSuccess = true;
        }
        if (screenName == Screen::PauseScreen)
        {
            curScreenName = Screen::PauseScreen;
            ScreenStack.push(std::unique_ptr<GameScreen>(new PauseScreen));
            isSuccess = true;
        }
        if (screenName == Screen::LoseScreen)
        {
            curScreenName = Screen::LoseScreen;
            ScreenStack.push(std::unique_ptr<GameScreen>(new LostScreen));
            isSuccess = true;
        }
        break;
    case Screen::InfinityWinScreen:
        if (screenName == Screen::MainMenuScreen)
        {
            ScreenStack.pop();
            ScreenStack.pop();
            curScreenName = Screen::MainMenuScreen;
            isSuccess = true;
        }
        if (screenName == Screen::InfinityPlayScreen)
        {
            ScreenStack.pop();
            ScreenStack.pop();
            ScreenStack.push(std::unique_ptr<GameScreen>(new InfinityPlayScreen));
            curScreenName = Screen::InfinityPlayScreen;
            isSuccess = true;
        }
        break;
    case Screen::QuitGame:
        break;
    }
    return isSuccess;
}
std::optional<std::shared_ptr<GameScreen>> ScreenManager::curScreen()
{
    if (!ScreenStack.empty())
    {
        return ScreenStack.top();
    }
    return {};
}
ScreenManager *ScreenManager::instance = NULL;