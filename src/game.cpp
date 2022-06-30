#include "game.h"

Game::Game()
{
    initWindow();
    loadTextures();
    loadAudio();
    loadFonts();
}
void Game::run()
{
    sf::Clock clock;
    sf::Time deltaTime = sf::Time::Zero;

    while (window.isOpen())
    {
        deltaTime = clock.restart();
        auto currentScreen = ScreenManager::GetManager()->curScreen();
        if (currentScreen)
        {
            (*currentScreen)->processEvents();

            if (window.hasFocus())
            {
                (*currentScreen)->update(deltaTime);
                (*currentScreen)->render();
            }
        }
        else
        {
            window.close();
        }
    }
}
void Game::initWindow()
{
    window.create(sf::VideoMode::getDesktopMode(), "Brick Breaker", sf::Style::Fullscreen);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(MAX_FPS);
    gameData->setWindow(&window);
}
void Game::loadTextures()
{
    gameData->getTextureHolder().load(TextureID::Logo, "../media/texture/new_logo.png");
    gameData->getTextureHolder().load(TextureID::MenuBackground, "../media/texture/back.png");

    gameData->getTextureHolder().load(TextureID::SoundOn, "../media/texture/unmute.png");
    gameData->getTextureHolder().load(TextureID::SoundOff, "../media/texture/mute.png");

    gameData->getTextureHolder().load(TextureID::Planc1, "../media/texture/normalplanc.png");
    gameData->getTextureHolder().load(TextureID::Planc2, "../media/texture/powerplanc.png");

    gameData->getTextureHolder().load(TextureID::CloseButton, "../media/texture/CloseButton.png");

    gameData->getTextureHolder().load(TextureID::Block1, "../media/texture/01-Breakout-Tiles.png");
    gameData->getTextureHolder().load(TextureID::Block2, "../media/texture/03-Breakout-Tiles.png");
    gameData->getTextureHolder().load(TextureID::Block3, "../media/texture/11-Breakout-Tiles.png");
    gameData->getTextureHolder().load(TextureID::Block4, "../media/texture/09-Breakout-Tiles.png");

    gameData->getTextureHolder().load(TextureID::PageButton, "../media/texture/next_page.png");
    gameData->getTextureHolder().load(TextureID::PageButtonDeactivated, "../media/texture/next_page_unselected.png");
    gameData->getTextureHolder().load(TextureID::LevelDeleteButton, "../media/texture/level_delete_button.png");

    gameData->getTextureHolder().load(TextureID::Ball, "../media/texture/ball.png");
    gameData->getTextureHolder().load(TextureID::FireBall, "../media/texture/fireball.png");
    gameData->getTextureHolder().load(TextureID::CrazyBall, "../media/texture/crazy_ball.png");
    gameData->getTextureHolder().load(TextureID::Wall, "../media/texture/blocks1.jpg");
    gameData->getTextureHolder().load(TextureID::LevelBackground, "../media/texture/back.png");
    gameData->getTextureHolder().load(TextureID::Lives, "../media/texture/Lives.png");
    
    gameData->getTextureHolder().load(TextureID::FastPlancPowerUp, "../media/texture/power_up.png");
    gameData->getTextureHolder().load(TextureID::SlowPlancPowerUp, "../media/texture/power_up.png");
    gameData->getTextureHolder().load(TextureID::LongPlancPowerUp, "../media/texture/power_up.png");
    gameData->getTextureHolder().load(TextureID::ShortPlancPowerUp, "../media/texture/power_up.png");
    gameData->getTextureHolder().load(TextureID::MomentumPowerUp, "../media/texture/power_up.png");
    gameData->getTextureHolder().load(TextureID::BlockHasPowerUp, "../media/texture/blockhaspowerup.png");
}
void Game::loadFonts()
{
    gameData->getFontHolder().load(FontID::ButtonFont, "../media/font/LEMONMILK-Regular.otf");
    gameData->getFontHolder().load(FontID::TextFont, "../media/font/LEMONMILK-Regular.otf");
}
void Game::loadAudio()
{
    gameData->getSoundHolder().load(SoundID::ButtonClicked, "../media/audio/ButtonSound.wav");
    gameData->getSoundHolder().load(SoundID::ButtonHoverOver, "../media/audio/ButtonHover.wav");
    gameData->getSoundHolder().load(SoundID::TextboxError, "../media/audio/ButtonSound.wav");
    gameData->getSoundHolder().load(SoundID::TextboxType, "../media/audio/ButtonHover.wav");
    gameData->getSoundHolder().load(SoundID::BallBounce, "../media/audio/Hit_01.wav");
    gameData->getSoundHolder().load(SoundID::LiveLost, "../media/audio/LiveLostSound.wav");
    gameData->getSoundHolder().load(SoundID::NewBall, "../media/audio/NewBallSound.wav");
}
