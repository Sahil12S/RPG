#include "PlayerGui.h"

void PlayerGui::InitFont()
{
    m_Data->assets.LoadFont( "Gui Font", TEXT_FONT_FILEPATH );
}

void PlayerGui::InitHPBar()
{
    float width = 300.f;
    float height = 50.f;
    float x = 20.f;
    float y = 20.f;

    m_HpBarMaxWidth = width;

    m_HpBarBack.setSize( sf::Vector2f( width, height ) );
    m_HpBarBack.setFillColor( sf::Color( 50, 50, 50, 200 ) );
    m_HpBarBack.setPosition( x, y );

    m_HpBarInner.setSize( sf::Vector2f( width, height ) );
    m_HpBarInner.setFillColor( sf::Color( 250, 20, 20, 200 ) );
    m_HpBarInner.setPosition( m_HpBarBack.getPosition() );
}

PlayerGui::PlayerGui( GameDataRef data, Player* player ) : m_Data( std::move( data ) )
{
    m_Player = player;

    InitFont();
    InitHPBar();
}

PlayerGui::~PlayerGui()
{
    delete m_Player;
}

void PlayerGui::UpdateHPBar( const float& dt )
{
    float percent = static_cast<float>( m_Player->GetAttributeComponent()->m_Hp ) / static_cast<float>( m_Player->GetAttributeComponent()->m_HpMax );
    m_HpBarInner.setSize( sf::Vector2f(
        static_cast<float>( std::floor( m_HpBarMaxWidth * percent ) ),
        m_HpBarInner.getSize().y
    ) );
}

void PlayerGui::Update( const float& dt )
{
    UpdateHPBar( dt );
}

void PlayerGui::DrawHPBar( sf::RenderTarget& target )
{
    target.draw( m_HpBarBack );
    target.draw( m_HpBarInner );

}

void PlayerGui::Draw( sf::RenderTarget& target )
{
    DrawHPBar( target );
}