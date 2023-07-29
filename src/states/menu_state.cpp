#include "menu_state.h"
#include "../GUI/button.h"
#include "../application.h"
#include <SFML/Graphics/RenderWindow.hpp>

MenuState::MenuState(StateStack &stack, Context context)
    : State(stack, context)
{
    mTitleLabel.setString("Star Pusher");
    mTitleLabel.setFont(context.fonts->get(Fonts::Main));
    mTitleLabel.setCharacterSize(74);
    mTitleLabel.setFillColor(sf::Color::White);
    mTitleLabel.setOrigin(mTitleLabel.getGlobalBounds().width/2, mTitleLabel.getGlobalBounds().height/2);
    mTitleLabel.setPosition(Application::HALF_WIDTH, 120);

    auto playButton = std::make_shared<GUI::Button>(context);
    //playButton->setCenterOrigin();
    playButton->setPosition(Application::HALF_WIDTH-200, 300);
    playButton->setText("Play");
    playButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::Game);
    });

    auto optionsButton = std::make_shared<GUI::Button>(context);
    optionsButton->setPosition(Application::HALF_WIDTH-200, 400);
    optionsButton->setText("Options");
    optionsButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::Options);
    });

    auto quitButton = std::make_shared<GUI::Button>(context);
    quitButton->setPosition(Application::HALF_WIDTH-200, 500);
    quitButton->setText("Quit");
    quitButton->setCallback([this] ()
    {
        requestStackPop();
    });

    mGUIContainer.pack(playButton);
    mGUIContainer.pack(optionsButton);
    mGUIContainer.pack(quitButton);
}

void MenuState::draw()
{
    sf::RenderWindow& window = *getContext().window;


    window.setView(window.getDefaultView());

    window.draw(mTitleLabel);

    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time)
{
    return true;
}

bool MenuState::handleEvent(const sf::Event &event)
{
    mGUIContainer.handleEvent(event);
    return false;
}
