#ifndef TILE_H
#define TILE_H

#include "../pch.cpp"
#include "../Game.h"

class Tile
{
private:
    GameDataRef m_Data;

protected:
    sf::RectangleShape m_Shape;
    short m_Type;
    bool m_Collision;

public:
    /**
     * Constructor - Create a tile with given parameters
     * 
     * @param grid_x - Position of grid relative of X axis
     * @param gird_y - Position of grid relative to Y axis
     * @param gridSizeF - Size of grid in floating point
     * @param texture - texture sheet for tiles
     * @param texture_rect - rectangle shape that marks specific area on texture sheet for the tile
     * @param collision - toggles if tile should have collision or not. Default is false
     * @param type - changes type of tile( default, damaging, doodad )
     */
    Tile(unsigned grid_x, unsigned grid_y, float gridSizeF,
         const sf::Texture &texture, const sf::IntRect &texture_rect,
         bool collision = false, short type = 0);

    /**
     * Destructor
     */
    virtual ~Tile();

    /**
     * Accessor for type of tile( default, damaging, doodad(deferred render) )
     * 
     * @return short: returns enum type of tile
     */
    const short &GetType() const;

    /**
     * Accessor to check if tile has collision or not
     * 
     * @return short: returns true if it has collision, false otherwise
     */
    const bool &GetCollision() const;

    /**
     * Accessor to retrieve positions of tile
     * 
     * @return sf::Vector2f: returns floating point coordinates of tile
     */
    const sf::Vector2f &GetPosition() const;

    /**
     * Accessor to retrieve global bounds if tile
     * 
     * @return sf::FloatRect: returns floating rectangle in relative to global space
     */
    const sf::FloatRect GetGlobalBounds() const;

    /**
     * Accessor to get all tile data as a string
     * 
     * @return string: returns tile data converted to as string
     */
    const std::string GetAsString() const;

    /**
     * Checks if current tile is intersecting with tile provided.
     * 
     * @param bounds: FloatRect boundary of tile
     * 
     * @return bool: returns true if tile if intersecting if given boundary, false otherwise
     */
    bool Intersects(const sf::FloatRect bounds) const;

    void Update();
    void Draw(sf::RenderTarget &target);
};

#endif // TILE_H
