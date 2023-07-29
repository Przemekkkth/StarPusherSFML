#include "application.h"

#include "const/state_identifiers.h"
#include "states/state.h"
#include "states/game_state.h"
#include "states/title_state.h"
#include <iostream>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);
const int Application::SCREEN_WIDTH  = 1024;
const int Application::SCREEN_HEIGHT = 680;
const int Application::HALF_WIDTH    = SCREEN_WIDTH/2;
const int Application::HALF_HEIGHT   = SCREEN_HEIGHT/2;

Application::Application()
: mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Star Pusher SFML", sf::Style::Close)
, mTextures()
, mStateStack(State::Context(mWindow, mTextures, mFonts))
{
    mWindow.setKeyRepeatEnabled(false);
    registerStates();
    mStateStack.pushState(States::Title);

    mTextures.load(Textures::SFML_LOGO,  "res/sprite/sfml-logo-small.png");
    mTextures.load(Textures::AvatorLogo, "res/sprite/avatar.png");

    mFonts.load(Fonts::Main, "res/fonts/juniory.ttf");
}

void Application::run()
{
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;

    while (mWindow.isOpen())
    {
        sf::Time dt = clock.restart();
        timeSinceLastUpdate += dt;
        while (timeSinceLastUpdate > TimePerFrame)
        {
            timeSinceLastUpdate -= TimePerFrame;

            processInput();
            update(TimePerFrame);

            // Check inside this loop, because stack might be empty before update() call
            if (mStateStack.isEmpty())
                mWindow.close();
        }

        render();
    }
}

void Application::processInput()
{
    sf::Event event;
    while (mWindow.pollEvent(event))
    {
        mStateStack.handleEvent(event);

        if (event.type == sf::Event::Closed)
            mWindow.close();
    }
}

void Application::update(sf::Time dt)
{
    mStateStack.update(dt);
}

void Application::render()
{
    mWindow.clear();
    mStateStack.draw();
    mWindow.setView(mWindow.getDefaultView());
    mWindow.display();
}

void Application::registerStates()
{
    mStateStack.registerState<TitleState>(States::Title);
    mStateStack.registerState<GameState>(States::Game);
}
