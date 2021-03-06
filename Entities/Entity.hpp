#ifndef ENTITY_HPP
#define ENTITY_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"

#include "../Game.hpp"
#include "../Game_Components/MovementComponent.hpp"
#include "../Game_Components/AnimationComponent.hpp"
#include "../Game_Components/HitboxComponent.hpp"
#include "../Game_Components/AttributeComponent.hpp"

/* Forward declaration */
struct GameData;
typedef std::shared_ptr<GameData> GameDataRef;

class AnimationComponent;
class MovementComponent;
class HitboxComponent;
class AttributeComponent;

class Entity
{
protected:
    GameDataRef m_Data;

    sf::Sprite m_Sprite;

    MovementComponent *m_MC;
    AnimationComponent *m_AC;
    HitboxComponent *m_HC;
    AttributeComponent *m_AttComp;

public:
    /* Constructors and Destructors*/
    Entity(GameDataRef data);
    virtual ~Entity();

    /* Component functions */
    void SetTexture(sf::Texture &tex);
    void CreateHitboxComponent(const float &offset_x, const float &offset_y,
                               const float &width, const float &height);
    void CreateMovementComponent(const float &maxVelocity, const float &acceleration, const float &deceleration);
    void CreateAnimationComponent(const std::string &texture); // TODO: Use texture rather than name
    void CreateAttributeComponent(const unsigned &level);

    // Getters
    virtual const sf::Vector2f &GetPosition() const;
    virtual const sf::FloatRect GetGlobalBounds() const;
    virtual const sf::Vector2i GetGridPosition(const int &gridSizeI) const;
    virtual const sf::FloatRect GetNextPositionBounds(const float &dt) const;

    // Setters
    // virtual void SetPosition( sf::Vector2f position );
    virtual void SetPosition(const float &x, const float &y);

    /* Functions */
    virtual void Move(const float &dt, const float &dir_x, const float &dir_y);
    virtual void StopVelocity();
    virtual void StopVelocityX();
    virtual void StopVelocityY();

    virtual void Update(const float &dt) = 0;
    virtual void Draw(sf::RenderTarget &target, bool show_hitbox) = 0;
};

#endif // ENTITY_HPP