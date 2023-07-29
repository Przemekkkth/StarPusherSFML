#ifndef OPTIONSSTATE_H
#define OPTIONSSTATE_H
#include "state.h"
#include <SFML/Graphics/Text.hpp>
#include "../GUI/container.h"

class OptionsState : public State
{
public:
    OptionsState(StateStack& stack, Context context);
    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const sf::Event& event);
private:

    GUI::Container			mGUIContainer;
};

#endif // OPTIONSSTATE_H
