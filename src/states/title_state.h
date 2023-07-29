#ifndef TITLESTATE_H
#define TITLESTATE_H
#include "state.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class TitleState : public State
{
public:
                        TitleState(StateStack& stack, Context context);

    virtual void		draw();
    virtual bool		update(sf::Time dt);
    virtual bool		handleEvent(const sf::Event& event);

private:
    sf::Sprite m_sfmlLogo, m_avatarLogo;
    sf::Text   m_text0, m_text1;
    bool	   m_showText;
    sf::Time   m_textEffectTime;
};

#endif // TITLESTATE_H
