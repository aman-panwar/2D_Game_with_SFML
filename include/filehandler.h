#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <fstream>
#include <string>
#include <vector>
#include <list>
#include "block.h"
#include "defines.h"
/** @brief Manages the file io for the game
 * 
 * Saves and retrieves the information to/from files
 * 
 * The class is intended to be used as such:
 * 
 * To retrieve player name and highscore, use getPlaerInfo()
 * To save information pass a vector of pair conating the name and high score to savePlayerInfo()
 * */
class FileHandler
{
public:
    ///return the information saved in the file as a vector of pair containing the name and score
    static std::vector<std::pair<std::string, unsigned>> getPlayerInfo();
    /**saves the provided information into the file.
     * Takes the input as a vector of pair containing the name and score
     **/
    static void savePlayerInfo(std::vector<std::pair<std::string, unsigned>>);
    /** retrieves level information from file
     * return the block information
     * @param index the index of the level to be returned 
     * */
    static std::list<Block> getLevelInfo(unsigned index);
    /** deletes level information from file
     * return the block information
     * @param index the index of the level to be deleted 
     * @return true if and only if deletion was successful
     * */
    static bool deleteLevelInfo(unsigned index);
    /** saves the level information on the file
     * @param blocks the information of the level
     * */
    static void saveLevelInfo(std::list<Block> &blocks);
    /** return the number of levels stored in the file
     * 
    */
    static unsigned getLevelCount();
};

#endif