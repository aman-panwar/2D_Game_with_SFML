#include "MainMenuScreen.h"
#include <iostream>

MainMenuScreen::MainMenuScreen()
{
    initBackground();
    initLogo();
    initText();
}
void MainMenuScreen::initText()
{
    PlancButtonText.setString("Planc Style:");
    PlancButtonText.setFont(gameData->getFontHolder().get(FontID::TextFont));
    PlancButtonText.setPosition(sf::Vector2f(550.f, 880.f));
}
void MainMenuScreen::renderText()
{
    auto mywindow = gameData->getWindow();

    mywindow->draw(PlancButtonText);
}
void MainMenuScreen::render()
{

    auto mywindow = gameData->getWindow();

    mywindow->clear();

    mywindow->draw(Background);
    mywindow->draw(Logo);

    renderText();
    renderButtons();
    leaderboard.draw();
    UserNameTextbox.draw();

    mywindow->display();
}
void MainMenuScreen::update(sf::Time deltaTime)
{
    updateButtons();
    UserNameTextbox.update();
    leaderboard.update();
}
void MainMenuScreen::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    UserNameTextbox.handleInput(key, isPressed);
    // switch (key)
    // {
    // case sf::Keyboard::Escape:
    //     if (!isPressed)
    //     {
    //         ScreenManager::GetManager()->goToScreen(Screen::QuitScreen);
    //     }
    //     break;
    // }
    if(key==sf::Keyboard::Escape)
    {
        if (!isPressed)
        {
            ScreenManager::GetManager()->goToScreen(Screen::QuitScreen);
        }
    }
}
void MainMenuScreen::updateButtons()
{
    //PLAY BUTTON
    PlayButton.update();
    SoundButton.update();
    PlancButton.update();
    CustomLevelButton.update();
    InfinityPlayButton.update();


    if (PlayButton.isClicked())
    {
        ScreenManager::GetManager()->goToScreen(Screen::LevelScreen);
    }

    if (PlancButton.isClicked())
    {
        switch (gameData->getPlancStyle())
        {
        case PlancStyle::Style1:
            gameData->setPlancStyle(PlancStyle::Style2);
            PlancButton.updateTexture(gameData->getTextureHolder().get(TextureID::Planc2));
            break;
        case PlancStyle::Style2:
            gameData->setPlancStyle(PlancStyle::Style1);
            PlancButton.updateTexture(gameData->getTextureHolder().get(TextureID::Planc1));
            break;
        }
    }

    if (SoundButton.isClicked())
    {
        gameData->setSoundState(!gameData->isSoundOn());
        if (gameData->isSoundOn())
        {
            SoundButton.updateTexture(gameData->getTextureHolder().get(TextureID::SoundOn));
        }
        else
        {
            SoundButton.updateTexture(gameData->getTextureHolder().get(TextureID::SoundOff));
        }
    }
    if (CustomLevelButton.isClicked())
    {
        ScreenManager::GetManager()->goToScreen(Screen::CustomLevelScreen);
    }
    if (InfinityPlayButton.isClicked())
    {
        ScreenManager::GetManager()->goToScreen(Screen::InfinityPlayScreen);
    }
}
void MainMenuScreen::initLogo()
{
    Logo.setTexture(gameData->getTextureHolder().get(TextureID::Logo));
    Logo.setOrigin(Logo.getLocalBounds().width / 2, Logo.getLocalBounds().height / 2);
    Logo.setPosition(float(gameData->getWindow()->getSize().x) / 2, 100.f);
}
void MainMenuScreen::initBackground()
{
    auto window = gameData->getWindow();
    Background.setTexture(gameData->getTextureHolder().get(TextureID::MenuBackground));
    Background.setScale(window->getSize().x / Background.getLocalBounds().width,
                        window->getSize().y / Background.getLocalBounds().height);
    Background.setOrigin(Background.getLocalBounds().width / 2,
                         Background.getLocalBounds().height / 2);
    Background.setPosition(window->getSize().x / 2.f, window->getSize().y / 2.f);
}
void MainMenuScreen::renderButtons()
{
    PlayButton.draw();
    SoundButton.draw();
    PlancButton.draw();
    CustomLevelButton.draw();
    InfinityPlayButton.draw();
}