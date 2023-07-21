#include "application.h"

#include "const/state_identifiers.h"
#include "states/state.h"
#include "states/game_state.h"
#include <iostream>


const sf::Time Application::TimePerFrame = sf::seconds(1.f/60.f);
const int Application::SCREEN_WIDTH = 768;
const int Application::SCREEN_HEIGHT = 700;

Application::Application()
: mWindow(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Look At Cursor SFML", sf::Style::Close)
, mTextures()
, mStateStack(State::Context(mWindow, mTextures))
{
    mWindow.setKeyRepeatEnabled(false);

//    mFonts.load(Fonts::Main, 	"res/font/minecraft.ttf");

//    mTextures.load(Textures::Buttons,		"res/sprite/buttons.png");


    registerStates();
    mStateStack.pushState(States::Game);
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
    mStateStack.registerState<GameState>(States::Game);
}
