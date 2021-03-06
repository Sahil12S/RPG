#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"

#include "../Tile/Tile.hpp"
#include "../Game.hpp"

class Game;

class TileMap
{
private:
    GameDataRef m_Data;

    float m_GridSizeF;
    int m_GridSizeI;
    // Number of grids in world
    sf::Vector2i m_MaxSizeWorldGrid;
    // Size of grid ( num of grid x size of grid )
    sf::Vector2f m_MaxSizeWorldF;
    int m_Layers;

    // 3D vector to store tiles and layers
    std::vector<std::vector<std::vector<std::vector<Tile *>>>> m_Map;

    // Store tiles that we want to render later
    std::stack<Tile *> deferredRenderStack;

    std::string m_TextureFile;
    // sf::Texture m_TileSheet;
    sf::RectangleShape m_CollisionBox;

    // Culling
    int fromX;
    int toX;
    int fromY;
    int toY;
    int layer;

    // Clear: clears all the tiles from map
    void Clear();

public:
    TileMap(GameDataRef data, int width, int height, const std::string &texture_file);
    TileMap(GameDataRef data, const std::string file_name);
    virtual ~TileMap();

    const sf::Texture *GetTileSheet() const;
    int GetLayerSize(const int &x, const int &y, const int &layer) const;
    bool TileEmpty(const int &x, const int &y, const int &z) const;

    // Functions
    void AddTile(const int &x, const int &y, const int &z, const sf::IntRect &texture_rect, const bool &collision, const short &type);
    // Remove tile from map
    void RemoveTile(const int &x, const int &y, const int &z);
    // Save complete tilemap to a text file
    void SaveToFile(const std::string file_name);
    // Load map from a text file
    void LoadFromFile(const std::string file_name);

    void UpdateCollision(Entity *entity, const float &dt);
    void Update();
    // We can render using position rather than player
    void Draw(sf::RenderTarget &target, const sf::Vector2i &gridPosition, bool show_collision = true);
    void RenderDeferred(sf::RenderTarget &target);
};

#endif // TILEMAP_HPP