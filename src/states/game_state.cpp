#include "game_state.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>


GameState::GameState(StateStack& stack, Context context)
: State(stack, context)
, mWorld(*context.window)
{

}

void GameState::draw()
{
    mWorld.draw();

}

bool GameState::update(sf::Time dt)
{
    mWorld.update(dt);
    return true;
}

bool GameState::handleEvent(const sf::Event& event)
{
    if (event.type == sf::Event::KeyReleased)
    {

    }

    mWorld.processInput(event);
    return true;
}
