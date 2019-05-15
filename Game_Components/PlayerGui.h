#ifndef PLAYERGUI_H
#define PLAYERGUI_H

#include "../Entities/Player.h"

class Player;

class PlayerGui
{
private:
    Player* m_Player;

public:
    PlayerGui( Player* player );
    virtual ~PlayerGui();

    void Update( const float& dt );
    void Draw( sf::RenderTarget& target );
};

#endif // PLAYERGUI_H