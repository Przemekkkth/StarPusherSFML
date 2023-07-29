#ifndef MENUSTATE_H
#define MENUSTATE_H
#include "state.h"
#include "../GUI/container.h"
#include "../GUI/label.h"

class MenuState : public State
{
public:
                        MenuState(StateStack& stack, Context context);

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const sf::Event& event);
private:
    GUI::Container			mGUIContainer;
    sf::Text                mTitleLabel;
};

#endif // MENUSTATE_H
