#include "state.h"
#include "state_stack.h"

State::Context::Context(sf::RenderWindow& window, TextureHolder& textures)
: window(&window)
, textures(&textures)
{
}

State::State(StateStack& stack, Context context)
: mStack(&stack)
, mContext(context)
{

}

State::~State()
{
}

void State::requestStackPush(States::ID stateID)
{
    mStack->pushState(stateID);
}

void State::requestStackPop()
{
    mStack->popState();
}

void State::requestStateClear()
{
    mStack->clearStates();
}

State::Context State::getContext() const
{
    return mContext;
}
