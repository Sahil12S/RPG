#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "../Game.h"
#include "../Entities/Player.h"

class Game;
// struct GameDataRef;
class Player;


class PlayerGui
{
private:
    GameDataRef m_Data;
    Player* m_Player;

    sf::Font m_Font;
    // EXP Bar
    std::string m_ExpBarString;
    float m_ExpBarMaxWidth;
    sf::Text m_ExpBarText;
    sf::RectangleShape m_ExpBarBack;
    sf::RectangleShape m_ExpBarInner;

    // HP Bar
    std::string m_HpBarString;
    float m_HpBarMaxWidth;
    sf::Text m_HpBarText;
    sf::RectangleShape m_HpBarBack;
    sf::RectangleShape m_HpBarInner;


    void InitFont();
    void InitExpBar();
    void InitHPBar();

public:
    PlayerGui( GameDataRef data, Player* player );
    virtual ~PlayerGui();

    void UpdateExpBar( );
    void UpdateHPBar( );
    void Update( const float& dt );

    void DrawExpBar( sf::RenderTarget& target );
    void DrawHPBar( sf::RenderTarget& target );
    void Draw( sf::RenderTarget& target );
};

#endif // PLAYERGUI_H