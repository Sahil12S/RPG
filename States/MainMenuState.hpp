#ifndef MAIN_MENU_STATE_HPP
#define MAIN_MENU_STATE_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"

#include "State.hpp"
#include "../Game.hpp"
#include "../Game_Components/Button.hpp"
#include "../Game_Components/HUD.hpp"
#include "../Game_Components/Helpers.hpp"

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

    gui::HUD *m_Hud;

    std::map<std::string, gui::Button *> m_Buttons;

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
    explicit MainMenuState(GameDataRef data);
    virtual ~MainMenuState();

    void Init() override;
    void HandleInput(const float &dt) override;
    /**
     * Update buttons with current mouse position
     */
    void UpdateButtons();
    void Update(const float &dt) override;
    void DrawButtons(sf::RenderTarget &target);
    void Draw() override;
};
#endif // MAIN_MENU_STATE_HPP