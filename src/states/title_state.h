#ifndef TITLESTATE_H
#define TITLESTATE_H
#include "state.h"

class TitleState : public State
{
public:
                        TitleState(StateStack& stack, Context context);

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const sf::Event& event);
};

#endif // TITLESTATE_H
