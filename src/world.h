#ifndef WORLD_H
#define WORLD_H
#include "utils/resource_holder.h"
#include "utils/resource_identifiers.h"
#include "unit.h"
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <vector>
#include <array>
#include <queue>

#include <list>
#include "level.h"
#include "game_data.h"
#include "utils/input.h"

// Forward declaration
namespace sf
{
    class RenderTarget;
    class Event;
}

class World : private sf::NonCopyable
{
    public:
                                            World(sf::RenderWindow& outputTarget);
                                            ~World();
        void								update(sf::Time);
        void								draw();

        void processInput(const sf::Event& event);
        bool isWinActivated();
    private:
        void								loadTextures();
        void                                loadFonts();
        void                                onUserCreated();
        void                                drawEyes();
        void                                drawHero();

        sf::Vector2f vTarget;
        std::vector<Unit> vecUnits;

    private:
        sf::RenderWindow&					mTarget;
        TextureHolder						mTextures;
        FontHolder                          mFonts;

        std::map<char, sf::Texture> TILEMAPPING;
        std::map<char, sf::Texture> OUTSIDEDECOMAPPING;
        std::vector<sf::Texture> PLAYERIMAGES;

        std::vector<Level> m_levels;
        int m_currentLevelIndex;
        int m_currentImageIndex;
        std::vector< std::vector< char> > m_mapObj;
        GameData m_gameStateObj;
        Level m_levelObj;
        bool m_mapNeedsRedraw;
        bool m_levelIsCompleted;
        int m_cameraOffsetX, m_cameraOffsetY;
        Input m_input;

        const int TILEWIDTH;              //= 50;
        const int TILEHEIGHT;             //= 85;
        const int TILEFLOORHEIGHT;        //= 40;
        const int CAM_MOVE_SPEED ;        //= 5;
        const int OUTSIDE_DECORATION_PCT; //= 20;

        void fillTextureMaps();
        void decorateMap();
        void readLevelsFile(std::string pathFile);
        void runLevel();
        void drawTilemap(sf::FloatRect rect, const sf::Texture& tex);
        void drawMap();
        void drawStepCounter();
        void drawCurentLevelStatus();
        void drawWinText();
        bool isWall(int x, int y);
        void floodFill(int x, int y, char oldChar, char newChar);
        void nextLevel();
        void previousLevel();
        bool makeMove(std::string playerMoveTo);
        bool isBlocked(int x, int y);
        bool isLevelFinished();
};
#endif // WORLD_H
