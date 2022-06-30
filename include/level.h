#include "screenmanager.h"
#ifndef LEVEL_H
#define LEVEL_H

#include <memory>
#include <list>
#include <queue>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "block.h"
#include "ball.h"
#include "planc.h"
#include "powerup.h"
#include "LongPlancPowerUp.h"
#include "ShortPlancPowerUp.h"
#include "FastPlancPowerUp.h"
#include "SlowPlancPowerUp.h"
#include "MomentumPowerUp.h"
/**
 * @brief class for start a level choosen and play
 */
class Level
{
private:
    std::list<std::unique_ptr<Ball>> balls;
    std::list<Block> blocks;
    std::list<std::unique_ptr<Powerup>> powerups;
    Planc planc;
    sf::Sound LiveLostSound;
    sf::Sound NewBallSound;

    unsigned lives = DEFAULT_INITIAL_LIVES;
    bool level_started = 0;
    unsigned score = 0;
    sf::Sprite UpperWall, LeftWall, RightWall;
    sf::Sprite Background;
    sf::Sprite HeartShape;
    sf::Text LiveText;
    sf::Text ScoreText;
    sf::Text StartLevelText;
    unsigned StartLevelTextOpacity = 255;

    void initScore();          /// initialises score text
    void initAudio();          /// initialises all the req audio
    void initBackground();     /// initialises background
    void intiLives();          /// initialises pre set no of lives
    void intiBalls();          /// initialises defaults no of starting balls
    void initStartLevelText(); /// initialises start level text (press space to start)

    bool updateStartState(); /// checks if spacebar is pressed
    void updateLiveText();
    /**
     *  updates the balls on screen
     * 
     * @param deltaTime 
     */
    void updateBalls(sf::Time deltaTime);
    /**
     *  removes all dead balls(balls gone out of bounds)
     * 
     */
    void removeDeadBlocks();
    void updateScoreText();                  /// updates score string
    void updatePowerUps(sf::Time deltaTime); /// checks if any power up is alive and updates them
    void updateWinLossState();               /// checks if list having bricks or balls is empty
    void managePowerUps(PowerUp mypower, std::unique_ptr<Ball> &ball, Block &block);

public:
    Level();
    /**
     *  loads info abt the custom made or pre made level
     * 
     * @param info 
     */
    void Load(std::list<Block> info);
    void GenerateRandom(unsigned difficulty);
    /**
     *  updates whole game
     * 
     * @param deltaTime 
     */
    void update(sf::Time deltaTime);
    /**
     *  initialises level
     * 
     */
    void StartLevel();
    /**
     *  renders all which has to be displayed
     * 
     */
    void draw();

    void MoveLeft(bool);
    void MoveRight(bool);
    unsigned getLives();
    void setLives(unsigned newLives); // used mainly for inf play mode
};
#endif