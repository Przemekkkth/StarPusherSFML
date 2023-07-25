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
    fillTextureMaps();
    onUserCreated();

    readLevelsFile("res/lvl/test1.txt");
    runLevel();
}

World::~World()
{
}

void World::update(sf::Time time)
{
    for (auto& unit : vecUnits)
    {
        float fAngleToNewTarget = atan2(unit.vPosition.y - vTarget.y, unit.vPosition.x - vTarget.x) + 3.14159f;
        float delta = circ_shortdiff(unit.fHeading, fAngleToNewTarget, 0.0f, 2.0f * 3.14159f);
        unit.fHeading = circ_add(unit.fHeading, delta * 0.1f * 10.0f, 0.0f, 2.0f * 3.14159f);
        unit.sprite.setOrigin(0, 0);
        unit.sprite.setPosition(unit.vPosition.x, unit.vPosition.y);
        unit.sprite.setOrigin(16, 15);
        unit.sprite.setRotation(unit.fHeading * (180.0f/3.14f));
    }

}

void World::draw()
{
    mTarget.clear();
//    drawEyes();
//    drawHero();
    drawMap();
    mTarget.display();
}

void World::processInput(const sf::Event &event)
{
    if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        vTarget = sf::Vector2f(sf::Mouse::getPosition(mTarget));
    }
}


void World::loadTextures()
{
 //   mTextures.load(Textures::Eye,  "res/eye.png");
  //  mTextures.load(Textures::Hero, "res/hero.png");

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

}

void World::onUserCreated()
{
    int nUnits = 60;
//    for (int i = 0; i < nUnits; i++)
//    {
//        vecUnits.push_back(
//                    //angle, pos, target, sf::sprite
//                    { 0.0f, sf::Vector2f(rand()%Application::SCREEN_WIDTH, rand()% Application::SCREEN_HEIGHT), sf::Vector2f(0.0f, 0.0f), sf::Sprite(mTextures.get(Textures::Eye))});


//    }
}

void World::drawEyes()
{
    for(const Unit &u : vecUnits)
    {
        mTarget.draw(u.sprite);
    }
}

void World::drawHero()
{
    sf::Sprite heroSprite;
    heroSprite.setTexture(mTextures.get(Textures::Hero));
    heroSprite.setOrigin(16, 16);
    heroSprite.setPosition(vTarget.x, vTarget.y);
    mTarget.draw(heroSprite);
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
    //m_mapObj = m_levels[m_currentLevelIndex].mapObj;
    //m_gameStateObj = m_levels[m_currentLevelIndex].startState;
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
                pixmap = TILEMAPPING[' '];
                drawTilemap(spaceRect, pixmap);
                pixmap = mTextures.get(Textures::Star);
                drawTilemap(spaceRect, pixmap);
            }
            else if(std::find(goals.begin(), goals.end(), sf::Vector2i(x,y)) != goals.end())
            {
                pixmap = TILEMAPPING[' '];
                drawTilemap(spaceRect, pixmap);
                pixmap = mTextures.get(Textures::UncoveredGoal);
                drawTilemap(spaceRect, pixmap);
            }


            if(m_gameStateObj.playerPos == sf::Vector2i(x, y))
            {
                pixmap = TILEMAPPING[' '];
                drawTilemap(spaceRect, pixmap);
                pixmap = PLAYERIMAGES.at(m_currentImageIndex);
                drawTilemap(spaceRect, pixmap);
            }

        }
    }
}
