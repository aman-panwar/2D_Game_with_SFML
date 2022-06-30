#include "level.h"
bool isBlockDead(const Block &myblock)
{
    return myblock.health == 0;
}
bool isBallDead(const std::unique_ptr<Ball> &myball)
{
    return !(myball->isInBounds());
}
bool isPowerUpDead(const std::unique_ptr<Powerup> &mypowerup)
{
    return !(mypowerup->isAlive());
}
Level::Level()
{
    gameData->getCurPlayer().reset();
    initScore();
    initAudio();
    initBackground();
    intiLives();
    intiBalls();
    initStartLevelText();
}
void Level::Load(std::list<Block> info)
{
    blocks = info;
}
void Level::GenerateRandom(unsigned difficulty)
{
    blocks.clear();
    float block_size = MIN_BLOCK_DIMENSION + 200 * pow(1.2, -int(difficulty) - 1);
    float level_width = LEVEL_WIDTH;
    float level_height = gameData->getWindow()->getSize().y - 350 - TOP_MARGIN;
    int rowCount = level_width / block_size;
    int colCount = rand() % (int(level_height / block_size)) + 1;

    float mid_x = gameData->getWindow()->getSize().x / 2;
    //float top_y = gameData->getWindow()->getSize().y - TOP_MARGIN - 50;

    for (int col = 0; col < colCount; col++)
    {
        int this_row_count = std::max(rowCount - rand() % 10, 1);
        for (int row = 0; row < this_row_count; row++)
        {
            int blocktype = rand() % 4 + 1;
            BlockStyle blockstyle;
            switch (blocktype)
            {
            case 1:
                blockstyle = BlockStyle::Style1;
                break;
            case 2:
                blockstyle = BlockStyle::Style2;
                break;
            case 3:
                blockstyle = BlockStyle::Style3;
                break;
            case 4:
                blockstyle = BlockStyle::Style4;
                break;
            default:
                blockstyle = BlockStyle::Style1;
                break;
            }
            sf::Vector2f pos = sf::Vector2f(mid_x - block_size * this_row_count / 2.0 + row * block_size,
                                            TOP_MARGIN + 50 + col * block_size);
            blocks.emplace_back(Block(blockstyle, sf::Vector2f(block_size, block_size), pos));
        }
    }
}
bool Level::updateStartState()
{
    if (!level_started)
    {
        StartLevelTextOpacity += 1;
        StartLevelTextOpacity %= 256;
        StartLevelText.setFillColor(sf::Color(255, 255, 255, StartLevelTextOpacity));
    }
    return level_started;
}
void Level::updateLiveText()
{
    LiveText.setString(std::to_string(lives));
}
void Level::updateBalls(sf::Time deltaTime)
{
    for (auto &curBall : balls)
    {
        for (auto &curBlock : blocks)
        {
            if (curBall->handleCollision(curBlock.getBounds(), deltaTime))
            {
                curBlock.takeDamage(curBall->getDamage());
                score += BLOCK_COLLIDE_SCORE;
                managePowerUps(curBlock.dropPowerUp(), curBall, curBlock);
            }
        }
        if (curBall->handleCollision(planc.getBounds(), deltaTime))
        {
            curBall->addToVelocity(0.3f * planc.getVelocity());
        }
        curBall->update(deltaTime);
    }
}
void Level::removeDeadBlocks()
{
    for (auto &block : blocks)
    {
        if (block.gethealth() == 0)
        {
            score += BLOCK_BREAK_SCORE;
        }
    }
}
void Level::update(sf::Time deltaTime)
{
    if (!updateStartState())
    {
        return;
    }
    planc.update(deltaTime);
    updateBalls(deltaTime);
    removeDeadBlocks();
    updateWinLossState();
    updatePowerUps(deltaTime);
    updateLiveText();
    updateScoreText();
}
void Level::updatePowerUps(sf::Time deltaTime)
{
    for (auto &curPowerup : powerups)
    {
        curPowerup->update(deltaTime);
        curPowerup->handleCollision(planc);
    }
    powerups.remove_if(isPowerUpDead);
}
void Level::updateWinLossState()
{
    //updating lives
    unsigned lives_lost = balls.size();
    blocks.remove_if(isBlockDead);
    balls.remove_if(isBallDead);
    lives_lost -= balls.size();

    //checking for ball reset
    if (balls.size() == 0 && lives > 0)
    {
        sf::Vector2f ball_pos = sf::Vector2f(planc.getBounds().left + planc.getBounds().width / 2, planc.getBounds().top - 80),
                     ball_vel = sf::Vector2f(((rand() % 2 * 2 - 1)) * BALL_DEFAULT_SPEED, -BALL_DEFAULT_SPEED);
        balls.emplace_back(std::unique_ptr<Ball>(new Ball(ball_pos, ball_vel)));

        if (gameData->isSoundOn())
        {
            NewBallSound.play();
        }
    }
    //checking win
    if (blocks.size() == 0)
    {
        ///win
        if (gameData->isStandardPlay())
        {
            gameData->getCurPlayer().addToCurScore(score);
            auto player_vec = FileHandler::getPlayerInfo();
            player_vec.emplace_back(std::make_pair(gameData->getCurPlayer().getAlias(),
                                                   gameData->getCurPlayer().getCurScore()));
            FileHandler::savePlayerInfo(player_vec);
            ScreenManager::GetManager()->goToScreen(Screen::WinScreen);
        }
        else
        {
            gameData->getCurPlayer().addToCurScore(score);
            ScreenManager::GetManager()->goToScreen(Screen::InfinityWinScreen);
        }
    }

    //checking loss
    if (lives_lost > 0)
    {
        if (gameData->isSoundOn())
        {
            LiveLostSound.play();
        }
    }
    lives = std::max(0, int(lives) - int(lives_lost));
    if (lives == 0)
    {
        ///game lost
        ScreenManager::GetManager()->goToScreen(Screen::LoseScreen);
    }
}
void Level::updateScoreText()
{
    ScoreText.setString("Score: " + std::to_string(score));
}
void Level::draw()
{
    auto window = gameData->getWindow();
    window->clear();

    window->draw(Background);

    for (auto &cur_ball : balls)
    {
        cur_ball->draw();
    }
    for (auto &cur_block : blocks)
    {
        cur_block.draw();
    }
    for (auto &cur_powerup : powerups)
    {
        cur_powerup->draw();
    }

    planc.draw();

    window->draw(UpperWall);
    window->draw(LeftWall);
    window->draw(RightWall);

    if (!level_started)
    {
        window->draw(StartLevelText);
    }
    window->draw(HeartShape);
    window->draw(LiveText);

    window->draw(ScoreText);
    window->display();
}
void Level::StartLevel()
{
    level_started = true;
}
void Level::MoveLeft(bool isPressed)
{
    planc.move(Planc::Dir::Left, isPressed);
}
void Level::MoveRight(bool isPressed)
{
    planc.move(Planc::Dir::Right, isPressed);
}
void Level::initScore()
{
    if (!(gameData->isStandardPlay()))
    {
        score = gameData->getCurPlayer().getCurScore();
    }
    ScoreText.setString("Score: " + std::to_string(score));
    ScoreText.setFont(gameData->getFontHolder().get(FontID::TextFont));
    ScoreText.setOrigin(sf::Vector2f(0, ScoreText.getLocalBounds().height / 2));
    ScoreText.setPosition(sf::Vector2f(SCORE_TEXT_POS));
}
void Level::initAudio()
{
    LiveLostSound.setBuffer(gameData->getSoundHolder().get(SoundID::LiveLost));
    NewBallSound.setBuffer(gameData->getSoundHolder().get(SoundID::NewBall));
}
void Level::initBackground()
{
    auto window_width = gameData->getWindow()->getSize().x,
         window_height = gameData->getWindow()->getSize().y;

    Background.setTexture(gameData->getTextureHolder().get(TextureID::LevelBackground));
    //init walls
    gameData->getTextureHolder().get(TextureID::Wall).setRepeated(true);
    UpperWall.setTexture(gameData->getTextureHolder().get(TextureID::Wall));
    LeftWall.setTexture(gameData->getTextureHolder().get(TextureID::Wall));
    RightWall.setTexture(gameData->getTextureHolder().get(TextureID::Wall));

    UpperWall.setPosition(sf::Vector2f((window_width - LEVEL_WIDTH) / 2.0, 0.0));
    LeftWall.setPosition(sf::Vector2f(0.0, 0.0));
    RightWall.setPosition((window_width + LEVEL_WIDTH) / 2.0, 0.0);

    UpperWall.setTextureRect(sf::IntRect(0, 0, LEVEL_WIDTH, TOP_MARGIN));
    LeftWall.setTextureRect(sf::IntRect(0, 0, (window_width - LEVEL_WIDTH) / 2, window_height));
    RightWall.setTextureRect(sf::IntRect(0, 0, (window_width - LEVEL_WIDTH) / 2, window_height));
}
void Level::intiLives()
{
    HeartShape.setTexture(gameData->getTextureHolder().get(TextureID::Lives));
    HeartShape.setScale(LIVES_SIZE / HeartShape.getGlobalBounds().width,
                        LIVES_SIZE / HeartShape.getGlobalBounds().height);
    HeartShape.setOrigin(HeartShape.getGlobalBounds().width / 2,
                         HeartShape.getGlobalBounds().height / 2);
    HeartShape.setPosition(sf::Vector2f(gameData->getWindow()->getSize().x - LIVES_SIZE,
                                        ScoreText.getPosition().y));

    LiveText.setFont(gameData->getFontHolder().get(FontID::TextFont));
    LiveText.setCharacterSize(40);
    LiveText.setString(std::to_string(lives));
    LiveText.setOrigin(LiveText.getGlobalBounds().width / 2,
                       LiveText.getGlobalBounds().height / 2);
    LiveText.setPosition(sf::Vector2f(gameData->getWindow()->getSize().x - LIVES_SIZE,
                                      ScoreText.getPosition().y) +
                         sf::Vector2f(20.f, 10.f));
}
void Level::intiBalls()
{
    sf::Vector2f ball_pos = sf::Vector2f(planc.getBounds().left + planc.getBounds().width / 2, planc.getBounds().top - 80),
                 ball_vel = sf::Vector2f(((rand() % 2 * 2 - 1)) * BALL_DEFAULT_SPEED, -BALL_DEFAULT_SPEED);

    balls.emplace_back(std::unique_ptr<Ball>(new Ball(ball_pos, ball_vel)));
}
void Level::initStartLevelText()
{
    auto window_width = gameData->getWindow()->getSize().x,
         window_height = gameData->getWindow()->getSize().y;

    StartLevelText.setString("Press Spacebar to start");
    StartLevelText.setFont(gameData->getFontHolder().get(FontID::TextFont));
    StartLevelText.setOrigin(sf::Vector2f(StartLevelText.getLocalBounds().width / 2, StartLevelText.getLocalBounds().height / 2));
    StartLevelText.setPosition(sf::Vector2f(window_width / 2, window_height / 2));
}
void Level::managePowerUps(PowerUp mypower, std::unique_ptr<Ball> &ball, Block &block)
{
    ////std::cout<< << "managae power up\n";
    if (mypower == PowerUp::NoPowerUp)
    {
        return;
    }

    // sf::Vector2f blockpos = sf::Vector2f(block.getBounds().left + block.getBounds().width / 2,
    //                                      block.getBounds().top + block.getBounds().height / 2);
    sf::Vector2f ballvel, ballpos = ball->getCentrePosition();
    double angle;
    switch (mypower)
    {
    case PowerUp::NoPowerUp:
        break;
    case PowerUp::Momentum:
        //std::cout<< << "momentum\n";
        powerups.emplace_back(
            std::unique_ptr<Powerup>(new MomentumPowerUp(sf::Vector2f(block.getBounds().left + block.getBounds().width / 2,
                                                                      block.getBounds().top + block.getBounds().height / 2))));
        planc.activateMomentum();
        break;
    case PowerUp::IncreasePlancLength:
        //std::cout<< << "pad+\n";
        powerups.emplace_back(
            std::unique_ptr<Powerup>(new LongPlancPowerUp(sf::Vector2f(block.getBounds().left + block.getBounds().width / 2,
                                                                       block.getBounds().top + block.getBounds().height / 2))));
        break;
    case PowerUp::DecreadePlancLength:
        //std::cout<< << "pad-\n";
        powerups.emplace_back(
            std::unique_ptr<Powerup>(new ShortPlancPowerUp(sf::Vector2f(block.getBounds().left + block.getBounds().width / 2,
                                                                        block.getBounds().top + block.getBounds().height / 2))));
        break;
    case PowerUp::IncreasePlancSpeed:
        //std::cout<< << "pad fast\n";
        powerups.emplace_back(
            std::unique_ptr<Powerup>(new FastPlancPowerUp(sf::Vector2f(block.getBounds().left + block.getBounds().width / 2,
                                                                       block.getBounds().top + block.getBounds().height / 2))));
        break;
    case PowerUp::DecreasePlancSpeed:
        //std::cout<< << "pad slow\n";
        powerups.emplace_back(
            std::unique_ptr<Powerup>(new LongPlancPowerUp(sf::Vector2f(block.getBounds().left + block.getBounds().width / 2,
                                                                       block.getBounds().top + block.getBounds().height / 2))));
        break;
    case PowerUp::TenBalls:
        //std::cout<< << "ten\n";
        for (int i = 0; i < 10; i++)
        {
            double angle = 2 * 3.14159 * (rand() % 360) / 360;
            ballvel.x = cos(angle) * BALL_DEFAULT_SPEED;
            ballvel.y = sin(angle) * BALL_DEFAULT_SPEED;
            balls.emplace_back(std::unique_ptr<Ball>(new Ball(ballpos, ballvel)));
        }
        lives += 10;
        break;
    case PowerUp::TwoBalls:
        //std::cout<< << "two\n";
        for (int i = 0; i < 2; i++)
        {
            angle = 2 * 3.14159 * (rand() % 360) / 360;
            ballvel.x = cos(angle) * BALL_DEFAULT_SPEED;
            ballvel.y = sin(angle) * BALL_DEFAULT_SPEED;
            balls.emplace_back(std::unique_ptr<Ball>(new Ball(ballpos, ballvel)));
        }
        lives += 2;
        break;
    case PowerUp::ExtraLife:
        //std::cout<< << "extra life\n";
        lives += 1;
        break;
    case PowerUp::SlowDownBalls:
        //std::cout<< << "slow down balls\n";
        for (auto &i : balls)
        {
            i->decreaseSpeed();
        }
        break;
    case PowerUp::SpeedUpBalls:
        //std::cout<< << "fast balls \n";
        for (auto &i : balls)
        {
            i->increaseSpeed();
        }
        break;
    case PowerUp::FireBall:
        //std::cout<< << "fire ball\n";
        angle = 2 * 3.14159 * (rand() % 360) / 360;
        ballvel.x = cos(angle) * BALL_DEFAULT_SPEED;
        ballvel.y = sin(angle) * BALL_DEFAULT_SPEED;
        balls.emplace_back(std::unique_ptr<Ball>(new FireBall(ballpos, ballvel)));
        break;
    case PowerUp::CrazyBall:
        //std::cout<< << "crazy\n";
        angle = 2 * 3.14159 * (rand() % 360) / 360;
        ballvel.x = cos(angle) * BALL_DEFAULT_SPEED;
        ballvel.y = sin(angle) * BALL_DEFAULT_SPEED;
        balls.emplace_back(std::unique_ptr<Ball>(new CrazyBall(ballpos, ballvel)));
        break;
    }
    if (gameData->isSoundOn())
    {
        NewBallSound.play();
    }
    ////std::cout<< << "managae power up over\n";
}