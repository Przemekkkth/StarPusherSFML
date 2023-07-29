#include "title_state.h"
#include "../utils/resource_holder.h"
#include "../application.h"

TitleState::TitleState(StateStack &stack, Context context)
    : State(stack, context),
      m_showText(false), m_textEffectTime(sf::Time::Zero)
{
    m_sfmlLogo.setTexture(getContext().textures->get(Textures::SFML_LOGO));
    m_sfmlLogo.setOrigin( m_sfmlLogo.getGlobalBounds().width/2.0f, m_sfmlLogo.getGlobalBounds().height/2.0f);
    m_sfmlLogo.setPosition(Application::HALF_WIDTH, 100);

    m_text0.setFont(getContext().fonts->get(Fonts::Main));
    m_text0.setString("Bondrusiek\'s game");
    m_text0.setCharacterSize(35);
    m_text0.setOrigin(m_text0.getGlobalBounds().width/2.0f,
                        m_text0.getGlobalBounds().height/2.0f);
    m_text0.setPosition(Application::HALF_WIDTH, 250);

    m_avatarLogo.setTexture(getContext().textures->get(Textures::AvatorLogo));
    m_avatarLogo.setOrigin( m_avatarLogo.getGlobalBounds().width/2.0f, m_avatarLogo.getGlobalBounds().height/2.0f);
    m_avatarLogo.setPosition(Application::HALF_WIDTH, 450);

    m_text1.setFont(getContext().fonts->get(Fonts::Main));
    m_text1.setString("Press any key to continue...");
    m_text1.setCharacterSize(25);
    m_text1.setOrigin(m_text1.getGlobalBounds().width/2.0f,
                        m_text1.getGlobalBounds().height/2.0f);
    m_text1.setPosition(Application::HALF_WIDTH, 600);
}

void TitleState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.draw(m_sfmlLogo);
    window.draw(m_text0);
    window.draw(m_avatarLogo);
    if(m_showText)
        window.draw(m_text1);
}

bool TitleState::update(sf::Time dt)
{
    m_textEffectTime += dt;

    if (m_textEffectTime >= sf::seconds(0.5f))
    {
        m_showText = !m_showText;
        m_textEffectTime = sf::Time::Zero;
    }
    return true;
}

bool TitleState::handleEvent(const sf::Event &event)
{
    // If any key is pressed, trigger the next screen
    if (event.type == sf::Event::KeyReleased)
    {
        //requestStackPop();

       // requestStackPush(States::Game);
    }
    return true;
}
