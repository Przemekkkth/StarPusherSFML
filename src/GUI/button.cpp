#include "button.h"
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cmath>

namespace GUI
{

Button::Button(State::Context context)
: mCallback()
, mSprite(context.textures->get(Textures::Buttons))
, mText("", context.fonts->get(Fonts::Main), 44)
, mIsToggle(false)
{
    changeTexture(Normal);
    mSprite.scale(2.0f, 2.0f);

    sf::FloatRect bounds = mSprite.getLocalBounds();
    mText.setPosition(bounds.width * mSprite.getScale().x/ 2.f, bounds.height * mSprite.getScale().y / 2.f);
    mText.setStyle(sf::Text::Bold);
}

void Button::setCallback(Callback callback)
{
    mCallback = std::move(callback);
}

void Button::setText(const std::string& text, sf::Text::Style style)
{
    mText.setString(text);
    mText.setStyle(style);
    sf::FloatRect bounds = mText.getLocalBounds();
    mText.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

void Button::setTextColor(sf::Color color)
{
    mText.setFillColor(color);
}

void Button::setToggle(bool flag)
{
    mIsToggle = flag;
}

void Button::setOrigin(float x, float y)
{
    mSprite.setOrigin(x, y);
}

void Button::setCenterOrigin()
{
    setOrigin(mSprite.getGlobalBounds().width * mSprite.getScale().x/2, mSprite.getGlobalBounds().height * mSprite.getScale().y/2);
}

bool Button::isSelectable() const
{
    return true;
}

void Button::select()
{
    Component::select();

    changeTexture(Selected);
}

void Button::deselect()
{
    Component::deselect();

    changeTexture(Normal);
}

void Button::activate()
{
    Component::activate();

    // If we are toggle then we should show that the button is pressed and thus "toggled".
    if (mIsToggle)
        changeTexture(Pressed);

    if (mCallback)
        mCallback();

    // If we are not a toggle then deactivate the button since we are just momentarily activated.
    if (!mIsToggle)
        deactivate();
}

void Button::deactivate()
{
    Component::deactivate();

    if (mIsToggle)
    {
        // Reset texture to right one depending on if we are selected or not.
        if (isSelected())
            changeTexture(Selected);
        else
            changeTexture(Normal);
    }
}

void Button::handleEvent(const sf::Event&)
{
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    target.draw(mSprite, states);
    target.draw(mText, states);
}

void Button::changeTexture(Type buttonType)
{
    sf::IntRect textureRect(0, 50*buttonType, 200, 50);
    mSprite.setTextureRect(textureRect);
}

}
