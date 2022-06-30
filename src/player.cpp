#include"player.h"

std::string Player::getAlias()
{
    return alias;
}
void Player::setAlias(std::string newAlias)
{
    alias=newAlias;
}
unsigned Player::getCurScore()
{
    return cur_score;
}
unsigned Player::getMaxScore()
{
    return max_score;
}
void Player::addToCurScore(unsigned score)
{
    cur_score+=score;
}
void Player::addToLives(int add_to_lives)
{
    lives = std::max(unsigned(0), lives+add_to_lives);
}
void Player::reset()
{
    cur_score=0;
    lives=DEFAULT_INITIAL_LIVES;
}