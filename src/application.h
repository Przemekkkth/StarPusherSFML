#ifndef APPLICATION_H
#define APPLICATION_H

#include "utils/resource_holder.h"
#include "utils/resource_identifiers.h"
#include "states/state_stack.h"

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

class Application
{
    public:
        static const int SCREEN_WIDTH;
        static const int SCREEN_HEIGHT;
                                Application();
        void					run();


    private:
        void					processInput();
        void					update(sf::Time dt);
        void					render();

        void					registerStates();


    private:
        static const sf::Time	TimePerFrame;

        sf::RenderWindow		mWindow;
        TextureHolder			mTextures;

        StateStack				mStateStack;
};


#endif // APPLICATION_H
