#ifndef GAME_HPP
#define GAME_HPP

#include "pch.cpp"

#include "Engine_Managers/AssetManager.hpp"
#include "Engine_Managers/InputManager.hpp"
#include "Engine_Managers/StateMachine.hpp"
#include "Engine_Managers/GraphicsSettings.hpp"
#include "Entities/Entity.hpp"

class AssetManager;
class InputManager;
class StateMachine;
class GraphicsSettings;
class Entity;

struct GameData
{
    StateMachine machine;
    AssetManager assets;
    InputManager input;
    sf::RenderWindow window;
    GraphicsSettings GfxSettings;
};

typedef std::shared_ptr<GameData> GameDataRef;

class Game
{
private:
    float dt;

    sf::Clock m_Clock;

    GameDataRef m_Data = std::make_shared<GameData>();

    void InitVariables();
    void InitGraphicsSettings();
    void InitWindow();
    void InitStates();

    void UpdateDt();

public:
    Game();
    virtual ~Game();
    void Run();
};

#endif // GAME_HPP