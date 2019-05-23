#ifndef MOVEMENTCOMPONENT_HPP
#define MOVEMENTCOMPONENT_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"

class MovementComponent
{
private:
    sf::Sprite &m_Sprite;

    float m_MaxVelocity;
    float m_Acceleration;
    float m_Deceleration;

    sf::Vector2f m_Velocity;

    // Initializer functions

public:
    MovementComponent(sf::Sprite &sprite, const float &maxVelocity,
                      const float &acceleration = 1.f, const float &deceleration = 1.f);
    virtual ~MovementComponent();

    // Getters & Setters
    const sf::Vector2f &GetVelocity() const;
    const float &GetMaxVelocity() const;

    bool GetState(const MovementStates &state) const;
    void StopVelocity();
    void StopVelocityX();
    void StopVelocityY();

    // Functions
    void Move(const float &dt, const float &dir_x, const float &dir_y);
    void Update(const float &dt);
};

#endif //MOVEMENTCOMPONENT_HPP
