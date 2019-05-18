/*
 * Parent class to manage states of game
 * We will have following states in our game:
 *  1. Splash state -   Where we display logo
 *  2. Menu state   -   Game menu
 *  3. Game state   -   State in which we play our game
 *  4. Pause state  -   When we pause game in between
 *  5. Game Over state  -   When game is over
 *  6. Settings state   - When we go to settings (either from menu or from pause screen)
 */

#ifndef STATE_H
#define STATE_H

// #include "../Game.h"

// Predeclaration
// class Game;
// struct GameData;
// typedef std::shared_ptr<GameData> GameDataRef;

class State
{
// protected:
//     GameDataRef m_Data;

public:
    // State( GameDataRef data );
    
    virtual ~State() {}
    /*
     * Initialize the game state
     */
    virtual void Init() = 0;

    /*
     * Handle input in current state
     */
    virtual void HandleInput( const float& dt ) = 0;

    /*
     * Update frames / game in current state
     */
    virtual void Update( const float& dt ) = 0;

    /*
     * Draw frame in current state
     */
    virtual void Draw() = 0;

    /*
     * Pause game
     */
    virtual void Pause() {};

    /*
     * Resume game
     */
    virtual void Resume() {};
};

#endif // STATE_H