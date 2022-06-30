#include "leaderboard.h"
Leaderboard::Leaderboard(sf::Vector2f centrePos)
{
    HeaderBody.setFillColor(sf::Color(LEADERBOARD_HEADER_COLOR));
    HeaderBody.setSize(sf::Vector2f((float)LEADERBOARD_WIDTH, (float)LEADERBOARD_ROW_HEIGHT));
    HeaderBody.setPosition(centrePos + sf::Vector2f(-(float)LEADERBOARD_WIDTH / 2, -3 * (float)LEADERBOARD_ROW_HEIGHT));

    MainBody.setFillColor(sf::Color(LEADERBOARD_BODY_COLOR));
    MainBody.setSize(sf::Vector2f((float)LEADERBOARD_WIDTH, 5 * (float)LEADERBOARD_ROW_HEIGHT + 10));
    MainBody.setPosition(centrePos + sf::Vector2f(-(float)LEADERBOARD_WIDTH / 2, -2 * (float)LEADERBOARD_ROW_HEIGHT));

    HeaderText.setString("Leader Board");
    HeaderText.setFont(gameData->getFontHolder().get(FontID::TextFont));
    HeaderText.setCharacterSize(LEADERBORAD_CHAR_SIZE);
    HeaderText.setOrigin(HeaderText.getLocalBounds().width / 2, HeaderText.getLocalBounds().height / 2);
    HeaderText.setPosition(centrePos + sf::Vector2f(0.f, -2.7 * (float)LEADERBOARD_ROW_HEIGHT));

    position = centrePos;
    update();
}

void Leaderboard::update()
{

    auto ranks = FileHandler::getPlayerInfo();

    sort(ranks.begin(), ranks.end(),
         [](std::pair<std::string, unsigned> a,
            std::pair<std::string, unsigned> b)
         { return a.second > b.second; });

    LeaderNames.resize(MAX_LEADERS);
    LeaderScores.resize(MAX_LEADERS);

    int rank_size=ranks.size();


    for (int i = 0; i < std::min((int)MAX_LEADERS, rank_size); i++)
    {
        LeaderNames[i].setString(ranks[i].first);
        LeaderScores[i].setString(std::to_string(ranks[i].second));
    }
    for (int i = ranks.size(); i < MAX_LEADERS; i++)
    {
        LeaderNames[i].setString("-----");
        LeaderScores[i].setString("---");
    }
    for (int i = 0; i < MAX_LEADERS; i++)
    {
        LeaderNames[i].setFont(gameData->getFontHolder().get(FontID::TextFont));
        LeaderNames[i].setCharacterSize(LEADERBORAD_CHAR_SIZE);

        LeaderNames[i].setOrigin(0.f, LeaderNames[i].getLocalBounds().height / 2);
        LeaderNames[i].setPosition(position + sf::Vector2f(-(float)LEADERBOARD_WIDTH / 2 + 10, (0.5 + i - 2) * (float)LEADERBOARD_ROW_HEIGHT));

        LeaderScores[i].setFont(gameData->getFontHolder().get(FontID::TextFont));
        LeaderScores[i].setCharacterSize(LEADERBORAD_CHAR_SIZE);
        LeaderScores[i].setOrigin(LeaderScores[i].getLocalBounds().width, LeaderScores[i].getLocalBounds().height / 2);
        LeaderScores[i].setPosition(position + sf::Vector2f(+(float)LEADERBOARD_WIDTH / 2 - 20, (0.5 + i - 2) * (float)LEADERBOARD_ROW_HEIGHT));
    }
}

void Leaderboard::draw()
{
    auto window = gameData->getWindow();

    window->draw(HeaderBody);
    window->draw(HeaderText);

    window->draw(MainBody);
    for (int i = 0; i < MAX_LEADERS; i++)
    {
        window->draw(LeaderNames[i]);
        window->draw(LeaderScores[i]);
    }
}

void Leaderboard::addPlayer(std::string name, unsigned score)
{
    auto ranks = FileHandler::getPlayerInfo();

    auto curPlayer = std::make_pair(name, score);
    bool flag = false;
    for (auto &i : ranks)
    {
        if (i.first == curPlayer.first)
        {
            i.second = std::max(curPlayer.second, i.second);
            flag = true;
            break;
        }
    }
    if (!flag)
    {
        ranks.emplace_back(std::move(curPlayer));
    }
    
    FileHandler::savePlayerInfo(ranks);
}