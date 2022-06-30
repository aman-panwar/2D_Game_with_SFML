#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "defines.h"
#include <fstream>
#include<algorithm>

/**
 * @brief class which holds all the info about the current player
 * 
 */
class Player
{
private:
    std::string alias = "Unknown";
    unsigned max_score = 0;
    unsigned cur_score = 0;
    unsigned lives = DEFAULT_INITIAL_LIVES;

public:
    /** returns the alias of the player 
     * @return alias of the player
     * */
    std::string getAlias();

    /** sets the alias of the player
     * @param newAlias the new alias of the player
     * */
    void setAlias(std::string newAlias);

    /** returns the current score
     * @return current score
     * */
    unsigned getCurScore();

    /** returns the max score
     * @return max score
     * */
    unsigned getMaxScore();

    /** increases the cur_score
     * @param score the value by which the score must be increased
     * */
    void addToCurScore(unsigned score);

    /**increases the number of lives. Pass negative value to decrease lives
     * @param lives no of lices to be added
     * */
    void addToLives(int add_to_lives);
    
    /** return the number of lives
     * */
    unsigned getLives();
    /** sets the curscore to 0 and lives to their default value
     * */
    void reset();
};

#endif