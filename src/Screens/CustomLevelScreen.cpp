#include "CustomLevelScreen.h"
CustomLevelScreen::CustomLevelScreen()
{
    cur_block_shape.setFillColor(sf::Color(255, 255, 255, 100));
    FailSound.setBuffer(gameData->getSoundHolder().get(SoundID::TextboxError));
    PassSound.setBuffer(gameData->getSoundHolder().get(SoundID::TextboxType));

    auto window_width = gameData->getWindow()->getSize().x,
         window_height = gameData->getWindow()->getSize().y;

    ValidArea.left = (window_width - LEVEL_WIDTH) / 2.0;
    ValidArea.top = TOP_MARGIN;
    ValidArea.width = LEVEL_WIDTH;
    ValidArea.height = window_height - 300 - TOP_MARGIN;

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

    PlancArea.setFillColor(sf::Color(100, 0, 0, 100));
    PlancArea.setSize(sf::Vector2f(window_width, 300));
    PlancArea.setPosition(sf::Vector2f(0, window_height - 300));
}
void CustomLevelScreen::render()
{
    auto window = gameData->getWindow();
    window->clear();

    window->draw(Background);
    window->draw(PlancArea);
    window->draw(UpperWall);
    window->draw(LeftWall);
    window->draw(RightWall);

    SaveButton.draw();
    QuitButton.draw();
    BlockButton1.draw();
    BlockButton2.draw();
    BlockButton3.draw();
    BlockButton4.draw();

    for (auto &i : placed_blocks)
    {
        i.draw();
    }
    if (first_placed)
    {
        window->draw(cur_block_shape);
    }

    window->display();
}
void CustomLevelScreen::update(sf::Time deltaTime)
{
    updateButtons();
    updateBlockPlacement();
}
void CustomLevelScreen::handleInput(sf::Keyboard::Key key, bool isPressed)
{
}
void CustomLevelScreen::updateButtons()
{
    SaveButton.update();
    QuitButton.update();
    BlockButton1.update();
    BlockButton2.update();
    BlockButton3.update();
    BlockButton4.update();

    if (SaveButton.isClicked())
    {
        if (placed_blocks.size() != 0)
        {
            FileHandler::saveLevelInfo(placed_blocks);
        }
        ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
    }
    if (QuitButton.isClicked())
    {
        ScreenManager::GetManager()->goToScreen(Screen::MainMenuScreen);
    }
    if (BlockButton1.isClicked())
    {
        cur_block = 1;
    }
    if (BlockButton2.isClicked())
    {
        cur_block = 2;
    }
    if (BlockButton3.isClicked())
    {
        cur_block = 3;
    }
    if (BlockButton4.isClicked())
    {
        cur_block = 4;
    }
}
void CustomLevelScreen::updateBlockPlacement()
{
    if (cur_block == 0)
    {
        return;
    }

    sf::Vector2f mousepos = (sf::Vector2f)sf::Mouse::getPosition(*(gameData->getWindow()));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (ValidArea.contains(mousepos))
        {
            bool isvalid = true;
            for (auto &i : placed_blocks)
            {
                if (i.getBounds().contains(mousepos))
                {
                    isvalid = false;
                    break;
                }
            }

            if (isvalid)
            {

                if (!first_placed)
                {
                    pos1 = mousepos;
                    first_placed = true;
                }
            }
            else
            {
                first_placed = false;
                cur_block = 0;
                if (gameData->isSoundOn())
                {
                    FailSound.play();
                }
            }
        }
        else
        {
            cur_block = 0;
            first_placed = false;
            if (gameData->isSoundOn())
            {
                FailSound.play();
            }
        }
    }
    else
    {
        if (ValidArea.contains(mousepos))
        {
            bool isvalid = true;
            for (auto &i : placed_blocks)
            {
                if (i.getBounds().contains(mousepos))
                {
                    isvalid = false;
                    break;
                }
            }

            if (isvalid)
            {
                if (first_placed)
                {
                    pos2 = mousepos;
                    if (abs((pos2 - pos1).x) >= MIN_BLOCK_DIMENSION &&
                        abs((pos2 - pos1).y) >= MIN_BLOCK_DIMENSION)
                    {
                        BlockStyle blockstyle;
                        switch (cur_block)
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

                        bool if_intersect_with_placed_block = false;
                        Block temp_block(blockstyle, (pos2 - pos1), pos1);
                        for (auto &i : placed_blocks)
                        {
                            if (i.getBounds().intersects(temp_block.getBounds()))
                            {
                                if_intersect_with_placed_block = true;
                                break;
                            }
                        }
                        if (if_intersect_with_placed_block)
                        {
                            first_placed = false;
                            cur_block = 0;
                            if (gameData->isSoundOn())
                            {
                                FailSound.play();
                            }
                        }
                        else
                        {
                            if (gameData->isSoundOn())
                            {
                                PassSound.play();
                            }
                            placed_blocks.emplace_back(temp_block);
                        }

                        //resetsystem
                        cur_block = 0;
                        first_placed = false;
                    }
                    else
                    {
                        first_placed = false;
                        cur_block = 0;
                        if (gameData->isSoundOn())
                        {
                            FailSound.play();
                        }
                    }
                }
            }
            else
            {
                if (first_placed)
                {
                    first_placed = false;
                    cur_block = 0;
                    if (gameData->isSoundOn())
                    {
                        FailSound.play();
                    }
                }
            }
        }
    }

    if (first_placed)
    {
        cur_block_shape.setPosition(pos1);
        cur_block_shape.setSize(mousepos - pos1);
    }
}