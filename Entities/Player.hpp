#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"
#include "Entity.hpp"
#include "../Game.hpp"
#include "../Game.hpp"
#include "../Game_Components/MovementComponent.hpp"
#include "../Game_Components/HUD.hpp"

class Player : public Entity
{
private:
    GameDataRef m_Data;

    /* Variables */
    bool m_IsAttacking;
    int m_AttackCount;
    AttackFace m_LastAttackFace;
    AttackFace m_CurrentFace;

    // sf::Clock m_MovementClock;
    // Clock to handle Attack
    sf::Clock m_AttackClock;

    /* Initializers */
    void InitTextures();
    void InitSounds();
    void InitVariables();
    void InitComponents();

public:
    // Constructor / Destructor
    explicit Player(GameDataRef data);
    virtual ~Player() override;

    // Accessors
    AttributeComponent *GetAttributeComponent();

    /* Functions */
    void LoseHP(const int &hp);
    void GainHP(const int &hp);
    void LoseExp(const int &exp);
    void GainExp(const int &exp);

    void Attack();
    void UpdateAnimation(const float &dt);
    void Update(const float &dt) override;
    void Draw(sf::RenderTarget &target, bool show_hitbox = false) override;
};

#endif // PLAYER_HPP