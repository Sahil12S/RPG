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

    sf::RectangleShape m_HpBarBack;
    sf::RectangleShape m_HpBarInner;

    float m_HpBarMaxWidth;

    void InitFont();
    void InitHPBar();

public:
    PlayerGui( GameDataRef data, Player* player );
    virtual ~PlayerGui();

    void UpdateHPBar( const float& dt );
    void Update( const float& dt );
    void DrawHPBar( sf::RenderTarget& target );
    void Draw( sf::RenderTarget& target );
};

#endif // PLAYERGUI_H