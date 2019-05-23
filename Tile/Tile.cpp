#include "Tile.hpp"

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF,
           const sf::Texture &texture, const sf::IntRect &texture_rect,
           bool collision, short type)
{
    m_Shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
    m_Shape.setFillColor(sf::Color::White);
    // m_Shape.setOutlineThickness( 1.f );
    // m_Shape.setOutlineColor( sf::Color::Black );
    m_Shape.setPosition(static_cast<float>(grid_x) * gridSizeF, static_cast<float>(grid_y) * gridSizeF);
    m_Shape.setTexture(&texture);
    m_Shape.setTextureRect(texture_rect);

    m_Type = type;
    m_Collision = collision;
}

Tile::~Tile()
{
}

const short &Tile::GetType() const
{
    return m_Type;
}

const bool &Tile::GetCollision() const
{
    return m_Collision;
}

const sf::Vector2f &Tile::GetPosition() const
{
    return m_Shape.getPosition();
}

const sf::FloatRect Tile::GetGlobalBounds() const
{
    return m_Shape.getGlobalBounds();
}

const std::string Tile::GetAsString() const
{
    std::stringstream ss;
    ss << m_Shape.getTextureRect().left << " " << m_Shape.getTextureRect().top << " " << m_Collision << " " << m_Type;

    return ss.str();
}

bool Tile::Intersects(const sf::FloatRect bounds) const
{
    return m_Shape.getGlobalBounds().intersects(bounds);
}

void Tile::Update()
{
}

void Tile::Draw(sf::RenderTarget &target)
{
    target.draw(m_Shape);
}