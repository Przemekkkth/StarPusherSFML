#ifndef LEVEL_H
#define LEVEL_H

#include <list>
#include <QPoint>
#include "game_data.h"
struct Level
{
    int width;
    int height;
    std::vector < std::vector<char> > mapObj;
    std::vector < sf::Vector2i > goals;
    GameData startState;
};



#endif // LEVEL_H
