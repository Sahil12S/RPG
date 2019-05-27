#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"

#include "../Game.hpp"
#include "State.hpp"
#include "PauseMenu.hpp"
#include "../Map/TileMap.hpp"
#include "../Entities/Player.hpp"
#include "../Game_Components/PlayerGui.hpp"

class Game;
class State;
class PauseMenu;
class TileMap;
class Player;
class PlayerGui;

class GameState : public State
{
private:
    /* Variables */
    GameDataRef m_Data;
    sf::View m_View;
    // We will load whole texture at one go
    sf::RenderTexture m_RenderTexture;
    sf::Sprite m_RenderSprite;

    std::map<std::string, int> m_KeyBinds;

    Player *m_Player;
    TileMap *m_TileMap;
    PauseMenu *m_PauseMenu;
    PlayerGui *m_PlayerGui;

    sf::Sprite m_BackgroundSprite;

    sf::Text m_CursorText;

    bool m_Paused;

    std::map<std::string, gui::HUD *> hud;

    // Initializers
    void InitView();
    void InitVariables();
    void InitTextures();
    void InitFonts();
    void InitSounds();

    void InitKeyBinds();
    void InitPauseMenu();
    void InitComponents();
    void InitPlayers();
    void InitPlayerGui();
    void InitTileMap();

public:
    GameState(GameDataRef data);
    virtual ~GameState();

    void PauseState();
    void UnpauseState();

    void Init() override;

    void UpdateView(const float &dt);
    void HandleInput(const float &dt) override;

    void UpdatePlayerGui(const float &dt);
    void UpdatePauseMenuButtons();
    void UpdateGui();
    void UpdateTileMap(const float &dt);

    void Update(const float &dt) override;
    void Draw() override;
};
#endif // GAME_STATE_HPP