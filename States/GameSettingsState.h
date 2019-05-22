#ifndef GAME_SETTINGS_STATE_H
#define GAME_SETTINGS_STATE_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

#include "../Game.h"
#include "State.h"
#include "../Game_Components/HUD.h"
#include "../Game_Components/Button.h"
#include "../Game_Components/DropDownList.h"
#include "../Game_Components/Helpers.h"

class Game;
class State;
class Button;
class DropDownList;
class HUD;

class GameSettingsState : public State
{
private:
    /* Variables */
    GameDataRef m_Data;
    gui::HUD *m_Hud;

    std::map<std::string, int> m_KeyBinds;

    sf::RectangleShape m_Background;
    sf::Text m_OptionsText;

    std::map<std::string, gui::Button *> m_Buttons;
    std::map<std::string, gui::DropDownList *> m_DropdownList;

    std::vector<sf::VideoMode> m_Modes;

    // Handle title animation
    sf::Clock clock;
    bool movedLeft;

    /* Functions */
    // Initializers
    void InitKeyBinds();
    void InitTextures();
    void InitFonts();
    void InitSounds();
    void InitVariables();
    void InitGui();
    // void InitDropDownList();
    // void InitTexts();
    void ResetGui();

public:
    GameSettingsState(GameDataRef data);
    ~GameSettingsState();

    // Initializes the state
    void Init() override;

    void HandleInput(const float &dt) override;
    void UpdateGui(const float &dt);
    void Update(const float &dt) override;
    void Draw() override;
};

#endif // GAME_SETTINGS_STATE_H