#include "world.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Sleep.hpp>
#include <algorithm>
#include <cmath>
#include <limits>
#include "states/game_state.h"
#include "circle.h"
#include "application.h"
#include <iostream>
#include <fstream>

World::World(sf::RenderWindow& outputTarget)
    : mTarget(outputTarget),
      mTextures(),
      mFonts(),
      m_currentLevelIndex(0),
      m_currentImageIndex(0),
      m_mapNeedsRedraw(false),
      m_levelIsCompleted(false),
      m_cameraOffsetX(0),
      m_cameraOffsetY(0),
      TILEWIDTH(50),
      TILEHEIGHT(85),
      TILEFLOORHEIGHT(40),
      CAM_MOVE_SPEED(5),
      OUTSIDE_DECORATION_PCT(20)
{
    loadTextures();
    loadFonts();
    fillTextureMaps();
    onUserCreated();

    readLevelsFile("res/lvl/starPusherLevels.txt");
    runLevel();
}

World::~World()
{
}

void World::update(sf::Time)
{

}

void World::draw()
{
    if(m_mapNeedsRedraw)
    {
        mTarget.clear();
        drawMap();
        if(m_levelIsCompleted)
        {
            drawWinText();
        }
        drawCurentLevelStatus();
        drawStepCounter();
        mTarget.display();
    }
}

void World::processInput(const sf::Event &event)
{
    if(!m_mapNeedsRedraw)
    {
        return;
    }
    m_input.playerMove = "NONE";
    int mapWidth = m_mapObj.size() * TILEWIDTH;
    int mapHeight = (m_mapObj[0].size() - 1) * TILEFLOORHEIGHT + TILEHEIGHT;
    m_input.cameraUp = false;
    m_input.cameraDown = false;
    m_input.cameraLeft = false;
    m_input.cameraRight = false;
    m_input.MAX_CAM_X_PAN = std::abs(Application::HALF_HEIGHT - int(mapHeight)) + TILEWIDTH;
    m_input.MAX_CAM_Y_PAN = std::abs(Application::HALF_WIDTH  - int(mapWidth)) +  TILEHEIGHT;

    if(event.type == sf::Event::KeyReleased && m_levelIsCompleted)
    {
        nextLevel();
        m_input.playerMove = "NONE";
        m_mapNeedsRedraw = true;
    }

    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Down)
        {
            m_input.playerMove = "DOWN";
        }
        else if(event.key.code == sf::Keyboard::Right)
        {
            m_input.playerMove = "RIGHT";
        }
        else if(event.key.code == sf::Keyboard::Left)
        {
            m_input.playerMove = "LEFT";
        }
        else if(event.key.code == sf::Keyboard::Up)
        {
            m_input.playerMove = "UP";
        }
        else if(event.key.code == sf::Keyboard::N)
        {
            m_mapNeedsRedraw = true;
            //next
            nextLevel();
        }
        else if(event.key.code == sf::Keyboard::B)
        {
            m_mapNeedsRedraw = true;
            //next
            previousLevel();
        }
        else if(event.key.code == sf::Keyboard::R)
        {
            //reset
            runLevel();
        }
        else if(event.key.code == sf::Keyboard::P)
        {
            //backspace 'reset'
            m_currentImageIndex += 1;
            if(m_currentImageIndex >= int(PLAYERIMAGES.size()))
            {
                m_currentImageIndex = 0;
            }
            m_mapNeedsRedraw = true;
            draw();
        }
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        m_input.cameraLeft = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        m_input.cameraRight = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        m_input.cameraDown = true;
    }
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        m_input.cameraUp = true;
    }

    if(m_input.playerMove != "NONE" && !m_levelIsCompleted)
    {
        bool moved = makeMove(m_input.playerMove);
        if(moved)
        {
            m_gameStateObj.stepCounter += 1;
            m_mapNeedsRedraw = true;
        }
        if(isLevelFinished())
        {
            m_levelIsCompleted = true;
        }
        draw();
    }

    if( m_input.cameraUp && m_cameraOffsetY < m_input.MAX_CAM_X_PAN)
    {
        m_cameraOffsetY += CAM_MOVE_SPEED;
        m_mapNeedsRedraw = true;
    }
    else if(m_input.cameraDown && m_cameraOffsetY > -m_input.MAX_CAM_X_PAN)
    {
        m_cameraOffsetY -= CAM_MOVE_SPEED;
        m_mapNeedsRedraw = true;
    }
    if(m_input.cameraLeft && m_cameraOffsetX < m_input.MAX_CAM_Y_PAN)
    {
        m_cameraOffsetX += CAM_MOVE_SPEED;
        m_mapNeedsRedraw = true;
    }
    else if(m_input.cameraRight && m_cameraOffsetX > -m_input.MAX_CAM_Y_PAN)
    {
        m_cameraOffsetX -= CAM_MOVE_SPEED;
        m_mapNeedsRedraw = true;
    }

    if(m_mapNeedsRedraw)
        draw();
}

void World::loadTextures()
{
    mTextures.load(Textures::UncoveredGoal, "res/sprite/redselector.png");
    mTextures.load(Textures::CoveredGoal,   "res/sprite/selector.png");
    mTextures.load(Textures::Star,          "res/sprite/star.png");
    mTextures.load(Textures::Corner,        "res/sprite/wall_block_tall.png");
    mTextures.load(Textures::Wall,          "res/sprite/wood_block_tall.png");
    mTextures.load(Textures::InsideFloor,   "res/sprite/plain_block.png");
    mTextures.load(Textures::OutsideFloor,  "res/sprite/grass_block.png");
    mTextures.load(Textures::Title,         "res/sprite/star_title.png");
    mTextures.load(Textures::Solved,        "res/sprite/star_solved.png");
    mTextures.load(Textures::Princess,      "res/sprite/princess.png");
    mTextures.load(Textures::Boy,           "res/sprite/boy.png");
    mTextures.load(Textures::Catgirl,       "res/sprite/catgirl.png");
    mTextures.load(Textures::Horngirl,      "res/sprite/horngirl.png");
    mTextures.load(Textures::Pinkgirl,      "res/sprite/pinkgirl.png");
    mTextures.load(Textures::Rock,          "res/sprite/rock.png");
    mTextures.load(Textures::ShortTree,     "res/sprite/tree_short.png");
    mTextures.load(Textures::TallTree,      "res/sprite/tree_tall.png");
    mTextures.load(Textures::UglyTree,      "res/sprite/tree_ugly.png");
}

void World::loadFonts()
{
    mFonts.load(Fonts::Main, "res/fonts/juniory.ttf");
}

void World::onUserCreated()
{

}

void World::fillTextureMaps()
{
    TILEMAPPING={
        {'x', mTextures.get(Textures::Corner)},
        {'#', mTextures.get(Textures::Wall)},
        {'o', mTextures.get(Textures::InsideFloor)},
        {' ', mTextures.get(Textures::OutsideFloor)}
    };

    OUTSIDEDECOMAPPING = {
        {'1', mTextures.get(Textures::Rock)},
        {'2', mTextures.get(Textures::ShortTree)},
        {'3', mTextures.get(Textures::TallTree)},
        {'4', mTextures.get(Textures::UglyTree)},
    };

    PLAYERIMAGES = {
        mTextures.get(Textures::Princess),
        mTextures.get(Textures::Boy),
        mTextures.get(Textures::Catgirl),
        mTextures.get(Textures::Horngirl),
        mTextures.get(Textures::Pinkgirl)
    };
}

void World::decorateMap()
{
    // Remove the non-wall characters from the map data
    sf::Vector2i startPos = m_gameStateObj.playerPos;
    for(int x = 0; x < int(m_mapObj.size()); ++x)
    {
        for(int y = 0; y < int(m_mapObj[0].size()); ++y)
        {
            if(     m_mapObj[x][y] == '$' ||
                    m_mapObj[x][y] == '.' ||
                    m_mapObj[x][y] == '@' ||
                    m_mapObj[x][y] == '+' ||
                    m_mapObj[x][y] == '*' )
            {
                m_mapObj[x][y] = ' ';
            }
        }
    }
    // Flood fill to determine inside/outside floor tiles.
    floodFill(startPos.x, startPos.y, ' ', 'o');
    //Convert the adjoined walls into corner tiles.
    for(int x = 0; x < int(m_mapObj.size()); ++x)
    {
        for(int y = 0; y < int(m_mapObj[0].size()); ++y)
        {
            if(m_mapObj[x][y] == '#' )
            {
                if( (isWall(x, y-1) && isWall(x+1, y) ) ||
                    (isWall(x+1, y) && isWall(x, y+1) ) ||
                    (isWall(x, y+1) && isWall(x-1, y) ) ||
                    (isWall(x-1, y) && isWall(x, y-1) )  )
                {
                    m_mapObj[x][y] = 'x';
                }
            }
            else if(m_mapObj[x][y] == ' ' &&
                    rand()%100 < OUTSIDE_DECORATION_PCT)
            {
                int size = OUTSIDEDECOMAPPING.size();
                int randomIdx = rand() % size;
                char keys[4] = {'1', '2', '3', '4'};
                char c = keys[randomIdx];
                m_mapObj[x][y] = c;
            }

        }
    }
}

void World::readLevelsFile(std::string pathFile)
{
    std::string text;
    std::vector< std::string > dataContent;
    int maxWidth = -1;
    std::ifstream readFile(pathFile);

    while (getline (readFile, text)) {
        // Output the text from the file
        std::cout << text << std::endl;
        std::cout << text.length() << std::endl;
        //QString line = stream.readLine();
        if(text[0] == ';')
        {
            continue;
        }
        if(text.length() && text != "\r")
        {
            dataContent.push_back(text);
        }
        if ((!text.length() || text == "\r") && dataContent.size() > 0)
        {
            if(!dataContent.size())
            {
                continue;
            }
            //Find the longest row in the map
            for(int i = 0; i < int(dataContent.size()); ++i)
            {
                if(int(dataContent[i].size()) > maxWidth)
                {
                    maxWidth = dataContent[i].length();
                }
            }
            //Be sure map is rectange
            for(int i = 0; i < int(dataContent.size()); ++i)
            {

                if(int(dataContent[i].length()) < maxWidth)
                {
                    for(int j = 0; j <= maxWidth - int(dataContent[i].length()); ++j)
                    {
                        dataContent[i] += " ";
                    }
                }
            }

            //Resize and fill map object
            std::vector < std::vector <char> > mapObj;
            mapObj.resize(maxWidth);

            for(int y = 0; y < int(dataContent.size()); ++y)
            {
                for(int x = 0; x < maxWidth; ++x)
                {
                    if(dataContent[y][x] == char('-'))
                    {
                        dataContent[y][x] = char(' ');
                    }
                    mapObj[x].push_back(dataContent[y][x]);
                }
            }
            //Loop through the spaces in the map and find the @, ., and $
            //characters for the starting game state.

            sf::Vector2i startPos;
            std::vector < sf::Vector2i > goals;
            std::vector < sf::Vector2i > stars;

            for(int x = 0; x < maxWidth; ++x)
            {
                for(int y = 0; y < int(mapObj[x].size()); ++y)
                {
                    if(mapObj[x][y] == char('@') || mapObj[x][y] == char('+'))
                    {
                        // '@' is player, '+' is player & goal
                        startPos.x = x;
                        startPos.y = y;
                    }
                    if(mapObj[x][y] == char('.') || mapObj[x][y] == char('+') || mapObj[x][y] == char('*'))
                    {
                        // '.' is goal, '*' is star & goal
                        sf::Vector2i p(x, y);
                        goals.push_back(p);
                    }
                    if(mapObj[x][y] == char('$') || mapObj[x][y] == char('*'))
                    {
                        // '$' is star
                        sf::Vector2i p(x,y);
                        stars.push_back(p);
                    }
                }
            }
            ////////////
            GameData gameStateObj;
            gameStateObj.playerPos = startPos;
            gameStateObj.stepCounter = 0;
            gameStateObj.starsPos = stars;

            Level levelObj;
            levelObj.width  = maxWidth;
            levelObj.height = dataContent.size();
            levelObj.mapObj = mapObj;
            levelObj.goals  = goals;
            levelObj.startState = gameStateObj;

            m_levels.push_back(levelObj);
            ///clear
            dataContent.clear();
            maxWidth = -1;
            mapObj.clear();

        }
    }

    // Close the file
    readFile.close();
}

void World::runLevel()
{
    m_mapObj.clear();


    m_levelObj     = m_levels[m_currentLevelIndex];
    m_mapObj       = m_levelObj.mapObj;
    m_gameStateObj = m_levelObj.startState;

    decorateMap();
    m_mapNeedsRedraw = true;
    m_cameraOffsetX = m_cameraOffsetY = 0;
    m_levelIsCompleted = false;
}

void World::drawTilemap(sf::FloatRect rect, const sf::Texture &tex)
{
    sf::Sprite sprite(tex);
    sprite.setPosition(rect.left, rect.top);
    sprite.setScale(rect.width/tex.getSize().x, rect.height/tex.getSize().y);
    mTarget.draw(sprite);
}

void World::drawMap()
{
    std::vector < sf::Vector2i> goals = m_levelObj.goals;
    for(int x = 0; x < int(m_mapObj.size()); ++x)
    {
        for(int y = 0; y < int(m_mapObj[x].size()); ++y)
        {
            sf::FloatRect spaceRect = sf::FloatRect(x*TILEWIDTH+m_cameraOffsetX, y*TILEFLOORHEIGHT+m_cameraOffsetY,
                                    TILEWIDTH, TILEHEIGHT);
            sf::Texture pixmap;
           // std::cout << "Map " << m_mapObj[x][y] << std::endl;
            bool isDraw = false;
            if(TILEMAPPING.find(m_mapObj[x][y]) != TILEMAPPING.end())
            {
                //baseTile = TILEMAPPING[m_mapObj[x][y]]
                pixmap = TILEMAPPING[m_mapObj[x][y]];
                isDraw = true;
            }
            else if(OUTSIDEDECOMAPPING.find(m_mapObj[x][y]) != OUTSIDEDECOMAPPING.end())
            {
                pixmap = TILEMAPPING[' '];
                isDraw = true;
            }
            if(isDraw)
            {
                drawTilemap(spaceRect, pixmap);
            }

            if(OUTSIDEDECOMAPPING.find(m_mapObj[x][y]) != OUTSIDEDECOMAPPING.end())
           {
                pixmap = OUTSIDEDECOMAPPING[m_mapObj[x][y]];
                drawTilemap(spaceRect, pixmap);
            }
            else if(std::find(m_gameStateObj.starsPos.begin(), m_gameStateObj.starsPos.end(), sf::Vector2i(x,y)) != m_gameStateObj.starsPos.end())
            {
                if(std::find(goals.begin(), goals.end(), sf::Vector2i(x,y)) != goals.end())
                {
                    pixmap = mTextures.get(Textures::CoveredGoal);
                    drawTilemap(spaceRect, pixmap);
                }
                pixmap = mTextures.get(Textures::Star);
                drawTilemap(spaceRect, pixmap);
            }
            else if(std::find(goals.begin(), goals.end(), sf::Vector2i(x,y)) != goals.end())
            {
                pixmap = mTextures.get(Textures::UncoveredGoal);
                drawTilemap(spaceRect, pixmap);
            }


            if(m_gameStateObj.playerPos == sf::Vector2i(x, y))
            {
                pixmap = PLAYERIMAGES.at(m_currentImageIndex);
                drawTilemap(spaceRect, pixmap);
            }

        }
    }
}

void World::drawStepCounter()
{
    sf::Text text;
    text.setString(sf::String("Steps: ")+sf::String(std::to_string(m_gameStateObj.stepCounter)));
    text.setFont(mFonts.get(Fonts::Main));
    int mapHeight = (m_mapObj[0].size() - 1) * TILEFLOORHEIGHT + TILEHEIGHT;
    sf::Vector2i point = sf::Vector2i(m_cameraOffsetX, mapHeight+0.05*Application::SCREEN_HEIGHT);
    text.setCharacterSize(0.05*Application::SCREEN_HEIGHT);
    text.setFillColor(sf::Color::White);
    text.setPosition(point.x+m_cameraOffsetX, point.y+m_cameraOffsetY);
    mTarget.draw(text);
}

void World::drawCurentLevelStatus()
{
    sf::Text text;
    text.setString("Level " + std::to_string(m_currentLevelIndex) + " of " + std::to_string(m_levels.size()));
    int mapHeight = (m_mapObj[0].size() - 1) * TILEFLOORHEIGHT + TILEHEIGHT;
    sf::Vector2i point = sf::Vector2i(m_cameraOffsetX, mapHeight);
    text.setFont(mFonts.get(Fonts::Main));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(0.05*Application::SCREEN_HEIGHT);
    text.setPosition(point.x + m_cameraOffsetX, point.y + m_cameraOffsetY);
    mTarget.draw(text);
}

void World::drawWinText()
{
    sf::Sprite sprite;
    sprite.setTexture(mTextures.get(Textures::Solved));
    sprite.setOrigin(sprite.getGlobalBounds().width/2.0f,
                     sprite.getGlobalBounds().height/2.0f);
    sprite.setPosition(Application::HALF_WIDTH, Application::HALF_HEIGHT);
    mTarget.draw(sprite);
}

bool World::isWall(int x, int y)
{
    if(x < 0 || x >= int(m_mapObj.size()) || y < 0 || y >= int(m_mapObj[x].size()))
    {
        return false;
    }
    else if(m_mapObj[x][y] == '#' || m_mapObj[x][y] == 'x')
    {
        return true;
    }
    return false;
}

void World::floodFill(int x, int y, char oldChar, char newChar)
{
    if(m_mapObj[x][y] == oldChar)
    {
        m_mapObj[x][y] = newChar;
    }

    if(x < int(m_mapObj.size()-1) && m_mapObj[x+1][y] == oldChar)
    {
        floodFill(x+1, y, oldChar, newChar); // call right
    }
    if(x > 0 && m_mapObj[x-1][y] == oldChar)
    {
        floodFill(x-1, y, oldChar, newChar); // call left
    }
    if(y < int(m_mapObj[x].size()) && m_mapObj[x][y+1] == oldChar)
    {
        floodFill(x, y+1, oldChar, newChar); // call down
    }
    if(y > 0 && m_mapObj[x][y-1] == oldChar)
    {
        floodFill(x, y-1, oldChar, newChar); // call up
    }
}

void World::nextLevel()
{
    m_currentLevelIndex++;
    if(m_currentLevelIndex >= int(m_levels.size()))
    {
        m_currentLevelIndex = 0;
    }
    runLevel();
}

void World::previousLevel()
{
    m_currentLevelIndex--;
    if(m_currentLevelIndex < 0)
    {
        m_currentLevelIndex = 0;
    }
    runLevel();
}

bool World::makeMove(std::string playerMoveTo)
{
    sf::Vector2i playerPos = m_gameStateObj.playerPos;
    std::vector<sf::Vector2i> stars = m_gameStateObj.starsPos;
    int xOffset = 0, yOffset = 0;
    std::cout << "PM " << playerMoveTo << std::endl;
    if(playerMoveTo == "UP")
    {
        xOffset = 0;
        yOffset = -1;
    }
    else if(playerMoveTo == "RIGHT")
    {
        xOffset = 1;
        yOffset = 0;
    }
    else if(playerMoveTo == "LEFT")
    {
        xOffset = -1;
        yOffset = 0;
    }
    else if(playerMoveTo == "DOWN")
    {
        xOffset = 0;
        yOffset = 1;
    }

    if( isWall(playerPos.x+xOffset, playerPos.y+yOffset))
    {
        return false;
    }
    else
    {
        if(std::find(stars.begin(), stars.end(), sf::Vector2i(playerPos.x + xOffset, playerPos.y + yOffset)) != stars.end())
        {
            if(!isBlocked(playerPos.x + (xOffset*2), playerPos.y + (yOffset*2)))
            {
                int index = -1;
                for(int i = 0; i < int(stars.size()); ++i)
                {
                    if(stars.at(i) == sf::Vector2i(playerPos.x + xOffset, playerPos.y + yOffset))
                    {
                        index = i;
                    }
                }
                if(index != -1)
                {
                    stars[index] = sf::Vector2i(stars[index].x+xOffset, stars[index].y+yOffset);
                }
            }
            else
            {
                return false;
            }
        }
        m_gameStateObj.starsPos = stars;
        m_gameStateObj.playerPos = sf::Vector2i(playerPos.x+xOffset, playerPos.y+yOffset);
        return true;
    }
}

bool World::isBlocked(int x, int y)
{
    if(isWall(x, y))
    {
        return true;
    }
    else if(x < 0 || x >= int(m_mapObj.size()) || y < 0 || y >= int(m_mapObj[x].size()))
    {
        return true;
    }
    else if( std::find(m_gameStateObj.starsPos.begin(), m_gameStateObj.starsPos.end(), sf::Vector2i(x,y)) != m_gameStateObj.starsPos.end() )
    {
        return true;
    }
    return false;
}

bool World::isLevelFinished()
{
    for(int i = 0; i < int(m_levelObj.goals.size()); ++i)
    {
        if( std::find(m_gameStateObj.starsPos.begin(), m_gameStateObj.starsPos.end(), m_levelObj.goals.at(i) ) == m_gameStateObj.starsPos.end() )
        {
            return false;
        }
    }
    return true;
}


