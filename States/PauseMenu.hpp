#ifndef PAUSE_MENU_HPP
#define PAUSE_MENU_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"

#include "../Game.hpp"
#include "../Game_Components/Button.hpp"
#include "../Game_Components/HUD.hpp"
#include "../Game_Components/Helpers.hpp"

class Game;
class Button;
class HUD;

class PauseMenu
{
private:
    /* Variables */
    GameDataRef m_Data;

    gui::HUD *m_Hud;

    sf::RectangleShape m_Background;
    sf::RectangleShape m_Container;

    std::map<std::string, gui::Button *> m_Buttons;

    void InitTextures();
    void InitFonts();
    void InitVariables();

public:
    PauseMenu(GameDataRef data);
    virtual ~PauseMenu();

    std::vector<std::string, gui::Button *> GetButtons();

    bool IsButtonPressed(const std::string &key);

    /**
     * Adds a button for Pause Menu
     * 
     * @param key: 
     */
    void AddButton(const std::string key,
                   const float y,
                   const std::string text);

    void Update(const sf::Vector2i &mousePosWindow);

    void Draw(sf::RenderTarget &target);
};

#endif // PAUSE_MENU_HPP