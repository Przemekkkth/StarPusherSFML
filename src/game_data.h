#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <QPoint>
#include <list>
#include <SFML/System/Vector2.hpp>
struct GameData
{
    sf::Vector2i playerPos;
    int stepCounter;
    std::vector<sf::Vector2i> starsPos;
    GameData()
        : stepCounter(0)
    {

    }
};

#endif // GAME_DATA_H
