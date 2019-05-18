#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "State.h"
#include "../Game.h"
#include "../Game_Components/Button.h"
#include "../Game_Components/HUD.h"

class Game;
class State;
class Button;
class HUD;

class MainMenuState : public State
{

private:
    /* Variables */
    GameDataRef m_Data;
    std::map<std::string, int> m_KeyBinds;

    sf::RectangleShape m_Background;
    // sf::Texture m_BackgroundTexture;

    gui::HUD* m_Hud;

    std::map<std::string, gui::Button*> m_Buttons;

    // Handle title animation
    sf::Clock clock;

    /* Functions */
    // Initializers
    void InitTextures();
    void InitFonts();
    void InitSounds();
    void InitVariables();
    void InitKeyBinds();
    void InitGui();
    void ResetGui();


public:
    explicit MainMenuState( GameDataRef data );
    virtual ~MainMenuState();

    void Init() override;
    void HandleInput( const float& dt) override;
    void UpdateButtons();
    void Update( const float& dt ) override;
    void DrawButtons( sf::RenderTarget& target );
    void Draw() override;


};
#endif // MAIN_MENU_STATE_H