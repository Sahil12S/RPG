#ifndef SPLASH_STATE_H
#define SPLASH_STATE_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "../Game.h"
#include "State.h"
#include "MainMenuState.h"

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
    SplashState( GameDataRef data );

    void Init();

    void HandleInput( const float& dt ) override;
    void Update( const float& dt ) override;
    void Draw() override;
};

#endif // SPLASH_STATE_H