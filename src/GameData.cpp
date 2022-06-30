#include "GameData.h"

GameData *GameData::GetData()
{
    if (!instance)
    {
        instance = new GameData();
        instance->setSoundState(true);
        instance->setPlancStyle(PlancStyle::Style1);
        GameData::GetData()->window = nullptr;
    }
    return instance;
}

bool GameData::setWindow(sf::RenderWindow *Window)
{
    if (window == nullptr)
    {
        window = Window;
        return true;
    }
    return false;
}

sf::RenderWindow *GameData::getWindow()
{
    return window;
}
Player &GameData::getCurPlayer()
{
    return curPlayer;
}

TextureHolder &GameData::getTextureHolder()
{
    return Textures;
}
FontHolder &GameData::getFontHolder()
{
    return Fonts;
}
SoundHolder &GameData::getSoundHolder()
{
    return Sounds;
}
MusicHolder &GameData::getMusicHolder()
{
    return Musics;
}

bool GameData::isSoundOn()
{
    return CurSoundState;
}
void GameData::setSoundState(bool SoundState)
{
    CurSoundState = SoundState;
}

PlancStyle GameData::getPlancStyle()
{
    return plancstyle;
}
void GameData::setPlancStyle(PlancStyle newPlanc)
{
    plancstyle = newPlanc;
}

void GameData::setLevelInfo(std::list<Block> block_info)
{
    level_info = block_info;
}
std::list<Block> GameData::getLevelInfo()
{
    return level_info;
}
void GameData::setLevelIndex(unsigned index)
{
    level_index=index;
}
unsigned GameData::getLevelIndex()
{
    return level_index;
}
void GameData::setInfinityModeDifficulty(unsigned inp)
{
    difficulty = inp;
}
unsigned GameData::getInfinityModeDifficulty()
{
    return difficulty;
}
bool GameData::isStandardPlay()
{
    return isstanadardplay;
}
void GameData::setIfStandardPlay(bool inp)
{
    isstanadardplay=inp;
}
//Defining the instance of GameData
GameData *GameData::instance = NULL;