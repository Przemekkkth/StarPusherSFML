#ifndef UNIT_H
#define UNIT_H
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>

struct Unit
{
    float fHeading;
    sf::Vector2f vPosition;
    sf::Vector2f vTarget;
    sf::Sprite sprite;
};

#endif // UNIT_H
