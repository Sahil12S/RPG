#include "PlayerGui.h"

PlayerGui::PlayerGui( Player* player )
{
    m_Player = player;
}

PlayerGui::~PlayerGui()
{
    delete m_Player;
}

void PlayerGui::Update( const float& dt )
{

}

void PlayerGui::Draw( sf::RenderTarget& target )
{

}