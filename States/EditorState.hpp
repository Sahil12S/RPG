#ifndef EDITOR_STATE_HPP
#define EDITOR_STATE_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"
#include "../Game.hpp"
#include "State.hpp"
#include "MainMenuState.hpp"
#include "PauseMenu.hpp"
#include "../Game_Components/Button.hpp"
#include "../Game_Components/HUD.hpp"
#include "../Game_Components/TextureSelector.hpp"
#include "../Map/TileMap.hpp"

class Game;
class State;
class MainMenuState;
class PauseMenu;
class Button;
class HUD;
class TextureSelector;
class TileMap;

class EditorState : public State
{
private:
    GameDataRef m_Data;
    sf::View m_MainView;

    gui::HUD *m_Hud;
    gui::TextureSelector *m_TS;

    PauseMenu *m_PauseMenu;
    TileMap *m_TileMap;

    std::map<std::string, int> m_KeyBinds;
    std::map<std::string, gui::Button *> m_Buttons;

    bool m_Paused;
    bool m_Collision;
    short m_Type;
    int m_Layer;
    bool m_TileAddLock;

    sf::RectangleShape m_SelectorRect;
    sf::RectangleShape m_SideBar;

    // Places a rectangle on tile sheet which decides which texture we are using.
    sf::IntRect m_TextureRect;

    sf::Text m_CursorText;

    // Initializers
    void InitVariables();
    void InitView();
    void InitTextures();
    void InitFonts();
    void InitSounds();
    void InitKeyBinds();
    void InitTexts();
    void InitPauseMenu();
    void InitTileMap();
    void InitGui();

public:
    EditorState(GameDataRef data);
    ~EditorState();

    void PauseState();
    void UnpauseState();

    void Init() override;
    void HandleInput(const float &dt) override;

    void UpdateGui(const float &dt);
    void UpdatePauseMenuButtons();
    void Update(const float &dt) override;
    void Draw() override;
};

#endif // EDITOR_STATE_HPP