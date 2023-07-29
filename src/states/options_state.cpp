#include "options_state.h"
#include "../application.h"
#include "../GUI/button.h"
#include <iostream>

OptionsState::OptionsState(StateStack &stack, Context context)
    : State(stack, context)
{
    auto backButton = std::make_shared<GUI::Button>(context);
    backButton->setPosition(Application::HALF_WIDTH-200, 500);
    backButton->setText("Back");
    backButton->setCallback([this] ()
    {
        requestStackPop();
        requestStackPush(States::Menu);
    });

    mGUIContainer.pack(backButton);
}

void OptionsState::draw()
{
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    sf::Text titleTxt;
    titleTxt.setString("Options");
    titleTxt.setFont(getContext().fonts->get(Fonts::Main));
    titleTxt.setCharacterSize(74);
    titleTxt.setFillColor(sf::Color::White);
    titleTxt.setOrigin(110, 76);
    titleTxt.setPosition(Application::HALF_WIDTH, 120);
    window.draw(titleTxt);

    int characterSize = 30;

    sf::Text moveLeftTxt;
    moveLeftTxt.setString("left arrow - move left");
    moveLeftTxt.setFont(getContext().fonts->get(Fonts::Main));
    moveLeftTxt.setCharacterSize(characterSize);
    moveLeftTxt.setFillColor(sf::Color::White);
    moveLeftTxt.setPosition(20, 150);
    window.draw(moveLeftTxt);

    sf::Text moveRightTxt;
    moveRightTxt.setString("right arrow - move right");
    moveRightTxt.setFont(getContext().fonts->get(Fonts::Main));
    moveRightTxt.setCharacterSize(characterSize);
    moveRightTxt.setFillColor(sf::Color::White);
    moveRightTxt.setPosition(20, 190);
    window.draw(moveRightTxt);

    sf::Text moveUpTxt;
    moveUpTxt.setString("up arrow - move up");
    moveUpTxt.setFont(getContext().fonts->get(Fonts::Main));
    moveUpTxt.setCharacterSize(characterSize);
    moveUpTxt.setFillColor(sf::Color::White);
    moveUpTxt.setPosition(20, 230);
    window.draw(moveUpTxt);

    sf::Text moveDownTxt;
    moveDownTxt.setString("down arrow - move down");
    moveDownTxt.setFont(getContext().fonts->get(Fonts::Main));
    moveDownTxt.setCharacterSize(characterSize);
    moveDownTxt.setFillColor(sf::Color::White);
    moveDownTxt.setPosition(20, 270);
    window.draw(moveDownTxt);

    sf::Text cameraLeftTxt;
    cameraLeftTxt.setString("A - camera left");
    cameraLeftTxt.setFont(getContext().fonts->get(Fonts::Main));
    cameraLeftTxt.setCharacterSize(characterSize);
    cameraLeftTxt.setFillColor(sf::Color::White);
    cameraLeftTxt.setOrigin(203, 0);
    cameraLeftTxt.setPosition(Application::SCREEN_WIDTH-20, 150);
    window.draw(cameraLeftTxt);

    sf::Text cameraRightTxt;
    cameraRightTxt.setString("D - camera right");
    cameraRightTxt.setFont(getContext().fonts->get(Fonts::Main));
    cameraRightTxt.setCharacterSize(characterSize);
    cameraRightTxt.setFillColor(sf::Color::White);
    cameraRightTxt.setOrigin(203, 0);
    cameraRightTxt.setPosition(Application::SCREEN_WIDTH-20, 190);
    window.draw(cameraRightTxt);

    sf::Text cameraUpTxt;
    cameraUpTxt.setString("W - camera up");
    cameraUpTxt.setFont(getContext().fonts->get(Fonts::Main));
    cameraUpTxt.setCharacterSize(characterSize);
    cameraUpTxt.setFillColor(sf::Color::White);
    cameraUpTxt.setOrigin(203, 0);
    cameraUpTxt.setPosition(Application::SCREEN_WIDTH-20, 230);
    window.draw(cameraUpTxt);

    sf::Text cameraDownTxt;
    cameraDownTxt.setString("S - camera down");
    cameraDownTxt.setFont(getContext().fonts->get(Fonts::Main));
    cameraDownTxt.setCharacterSize(characterSize);
    cameraDownTxt.setFillColor(sf::Color::White);
    cameraDownTxt.setOrigin(203, 0);
    cameraDownTxt.setPosition(Application::SCREEN_WIDTH-20, 270);
    window.draw(cameraDownTxt);

    sf::Text nextLvlTxt;
    nextLvlTxt.setString("n - next level");
    nextLvlTxt.setFont(getContext().fonts->get(Fonts::Main));
    nextLvlTxt.setCharacterSize(30);
    nextLvlTxt.setFillColor(sf::Color::White);
    nextLvlTxt.setPosition(20, 310);
    window.draw(nextLvlTxt);

    sf::Text previousLvlTxt;
    previousLvlTxt.setString("b - previous level");
    previousLvlTxt.setFont(getContext().fonts->get(Fonts::Main));
    previousLvlTxt.setCharacterSize(30);
    previousLvlTxt.setFillColor(sf::Color::White);
    previousLvlTxt.setPosition(20, 350);
    window.draw(previousLvlTxt);

    sf::Text restartLvlTxt;
    restartLvlTxt.setString("r - restart level");
    restartLvlTxt.setFont(getContext().fonts->get(Fonts::Main));
    restartLvlTxt.setCharacterSize(30);
    restartLvlTxt.setFillColor(sf::Color::White);
    restartLvlTxt.setPosition(20, 390);
    window.draw(restartLvlTxt);

    sf::Text changePlayerTxt;
    changePlayerTxt.setString("p - replace hero");
    changePlayerTxt.setFont(getContext().fonts->get(Fonts::Main));
    changePlayerTxt.setCharacterSize(30);
    changePlayerTxt.setFillColor(sf::Color::White);
    changePlayerTxt.setPosition(20, 430);
    window.draw(changePlayerTxt);

    sf::Text backTxt;
    backTxt.setString("Backspace - back to menu");
    backTxt.setFont(getContext().fonts->get(Fonts::Main));
    backTxt.setCharacterSize(30);
    backTxt.setFillColor(sf::Color::White);
    backTxt.setOrigin(backTxt.getGlobalBounds().width, 0);
    backTxt.setPosition(Application::SCREEN_WIDTH-20, 310);
    window.draw(backTxt);

    sf::Text quitTxt;
    quitTxt.setString("Esc - quit game");
    quitTxt.setFont(getContext().fonts->get(Fonts::Main));
    quitTxt.setCharacterSize(30);
    quitTxt.setFillColor(sf::Color::White);
    quitTxt.setOrigin(quitTxt.getGlobalBounds().width, 0);
    quitTxt.setPosition(Application::SCREEN_WIDTH-20, 350);
    window.draw(quitTxt);

    window.draw(mGUIContainer);
}

bool OptionsState::update(sf::Time dt)
{
    return true;
}

bool OptionsState::handleEvent(const sf::Event &event)
{
    mGUIContainer.handleEvent(event);
    if (event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Backspace)
        {
            requestStackPop();
            requestStackPush(States::Menu);
        }
    }
    return false;
}
