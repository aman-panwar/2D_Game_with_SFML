#include "filehandler.h"

std::vector<std::pair<std::string, unsigned>> FileHandler::getPlayerInfo()
{
    std::ifstream filein(PLAYER_INFO_FILE, std::fstream::in);
    if (!filein)
    {
        std::runtime_error("error opening " + std::string(PLAYER_INFO_FILE));
    }

    std::vector<std::pair<std::string, unsigned>> vec;
    size_t vec_size;
    filein >> vec_size;
    //filein.read(reinterpret_cast<char *>(&vec_size), sizeof(vec_size));
    while (vec_size--)
    {
        std::string Alias;
        unsigned score;
        //std::getline(filein, Alias, '\0');
        filein >> Alias >> score;
        vec.emplace_back(std::make_pair(Alias, score));
    }
    filein.close();

    return vec;
}
void FileHandler::savePlayerInfo(std::vector<std::pair<std::string, unsigned>> player_vec)
{
    std::ofstream fileout(PLAYER_INFO_FILE, std::fstream::out | std::fstream::trunc);
    if (!fileout)
    {
        std::runtime_error("error opening " + std::string(PLAYER_INFO_FILE));
    }

    auto vec_size = player_vec.size();
    //fileout.write(reinterpret_cast<char *>(&vec_size), sizeof(vec_size));
    fileout << vec_size << '\n';
    for (auto &player : player_vec)
    {
        fileout << player.first;
        fileout << " ";
        fileout << player.second;
        fileout << '\n';
        // fileout.write(player.first.c_str(),player.first.size());
        // fileout.write(reinterpret_cast<char*>(&player.second),sizeof(player.second));
    }

    fileout.close();
}

void FileHandler::saveLevelInfo(std::list<Block> &blocks)
{
    std::ofstream fileout("temp.dat", std::fstream::out | std::fstream::trunc);
    if (!fileout)
    {
        std::runtime_error("error opening " + std::string("temp.dat"));
    }
    std::ifstream filein(LEVEL_INFO_FILE, std::fstream::in);
    if (!filein)
    {
        std::runtime_error("error opening " + std::string(LEVEL_INFO_FILE));
    }

    unsigned level_count;
    filein >> level_count;
    fileout << level_count + 1 << '\n';
    for (unsigned i = 1; i <= level_count; i++)
    {
        unsigned block_count;
        filein >> block_count;
        fileout << block_count << '\n';
        while (block_count--)
        {
            unsigned block_style;
            float left, top, height, width;

            filein >> block_style >> left >> top >> height >> width;
            fileout << block_style << " "
                    << left << " "
                    << top << " "
                    << height << " "
                    << width << "\n";
        }
    }
    fileout << blocks.size() << '\n';
    for (auto &cur_block : blocks)
    {
        unsigned block_style = 1;
        switch (cur_block.getBlockStyle())
        {
        case BlockStyle::Style1:
            block_style = 1;
            break;
        case BlockStyle::Style2:
            block_style = 2;
            break;
        case BlockStyle::Style3:
            block_style = 3;
            break;
        case BlockStyle::Style4:
            block_style = 4;
            break;
        default:
            block_style = 1;
            break;
        }
        fileout << block_style << " "
                << cur_block.getBounds().left << " "
                << cur_block.getBounds().top << " "
                << cur_block.getBounds().height << " "
                << cur_block.getBounds().width << "\n";
    }
    filein.close();
    fileout.close();
    remove(LEVEL_INFO_FILE);
    rename("temp.dat", LEVEL_INFO_FILE);
}
std::list<Block> FileHandler::getLevelInfo(unsigned index)
{
    std::ifstream filein(LEVEL_INFO_FILE, std::fstream::in);
    if (!filein)
    {
        std::runtime_error("error opening " + std::string(LEVEL_INFO_FILE));
    }

    std::list<Block> level_info;
    unsigned level_count;

    filein >> level_count;
    for (unsigned cur_index = 1; cur_index <= level_count; cur_index++)
    {
        unsigned list_size;
        filein >> list_size;
        for (unsigned i = 0; i < list_size; i++)
        {
            sf::FloatRect tempbounds;
            unsigned blocktype;
            filein >> blocktype >> tempbounds.left >> tempbounds.top >> tempbounds.height >> tempbounds.width;
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
            if (cur_index == index)
            {
                level_info.emplace_back(Block(blockstyle,
                                              sf::Vector2f(tempbounds.width, tempbounds.height),
                                              sf::Vector2f(tempbounds.left, tempbounds.top)));
            }
        }
        if (cur_index == index)
        {
            break;
        }
    }
    filein.close();
    return level_info;
}
unsigned FileHandler::getLevelCount()
{
    std::ifstream filein(LEVEL_INFO_FILE, std::fstream::in);
    if (!filein)
    {
        std::runtime_error("error opening " + std::string(LEVEL_INFO_FILE));
    }

    unsigned level_count;
    filein >> level_count;

    filein.close();

    return level_count;
}
bool FileHandler::deleteLevelInfo(unsigned index)
{
    std::ofstream fileout("temp.dat", std::fstream::out | std::fstream::trunc);
    if (!fileout)
    {
        std::runtime_error("error opening " + std::string("temp.dat"));
    }
    std::ifstream filein(LEVEL_INFO_FILE, std::fstream::in);
    if (!filein)
    {
        std::runtime_error("error opening " + std::string(LEVEL_INFO_FILE));
    }

    unsigned level_count;
    filein >> level_count;
    fileout << level_count - 1 << '\n';
    for (unsigned i = 1; i <= level_count; i++)
    {
        if (i != index)
        {
            unsigned block_count;
            filein >> block_count;
            fileout << block_count << '\n';
            while (block_count--)
            {
                unsigned block_style;
                float left, top, height, width;

                filein >> block_style >> left >> top >> height >> width;
                fileout << block_style << " "
                        << left << " "
                        << top << " "
                        << height << " "
                        << width << "\n";
            }
        }
    }
    filein.close();
    fileout.close();
    remove(LEVEL_INFO_FILE);
    rename("temp.dat", LEVEL_INFO_FILE);
    return (index > 0) && (index <= level_count);
}