#ifndef GAME_STATE_H
#define GAME_STATE_H

#include "state.h"
#include "../world.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>


class GameState : public State
{
    public:
                            GameState(StateStack& stack, Context context);

        virtual void		draw();
        virtual bool		update(sf::Time dt);
        virtual bool		handleEvent(const sf::Event& event);
    private:
        World				mWorld;

};
#endif // GAME_STATE_H
