#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "defines.h"
#include "player.h"
#include "filehandler.h"
#include "GameData.h"
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>

#include <iostream>

/** @brief Encapsulates the working of leaderboard
 * 
 * The class creates a gui object which shows the leaderboard
 * The class is intended to be used as such:
 * 
 * create a object to use it as a gui element
 * 
 * use static function addPlayer(name of the player, score of the player) to 
 * add a new player to the list of player or to update the maxscore of an old user
 * */
class Leaderboard
{
private:
    sf::RectangleShape HeaderBody;
    sf::RectangleShape MainBody;
    sf::Vector2f position;
    sf::Text HeaderText;
    std::vector<sf::Text> LeaderNames;
    std::vector<sf::Text> LeaderScores;

public:
    Leaderboard() = delete;
    ///takes the centre postion of the leaderboard
    Leaderboard(sf::Vector2f centrePos);

    ///add/updates the name and maxscore of a player to the list
    static void addPlayer(std::string name, unsigned score);
    ///updates the leaderboard
    void update();
    ///renders the leaerboard
    void draw();
};
#endif