#ifndef SPLASH_STATE_HPP
#define SPLASH_STATE_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"

#include "../Game.hpp"
#include "State.hpp"
#include "MainMenuState.hpp"

class Game;
class State;
class MainMenuState;

class SplashState : public State
{
private:
    GameDataRef m_Data;
    sf::Clock m_Clock;
    sf::Sprite m_BackgroundSprite;

public:
    /*
     * Splash State doesn't need any key bindings
     */
    SplashState(GameDataRef data);

    void Init();

    void HandleInput(const float &dt) override;
    void Update(const float &dt) override;
    void Draw() override;
};

#endif // SPLASH_STATE_HPP