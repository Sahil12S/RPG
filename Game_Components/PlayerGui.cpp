#include "PlayerGui.h"

void PlayerGui::InitFont()
{
    Debug("PLAYER GUI::Init Fonts")
    m_Data->assets.LoadFont( "Gui Font", TEXT_FONT_FILEPATH );
}

void PlayerGui::InitLevelBar()
{
    Debug("PLAYER GUI::Init Level Bar")
    float width = 50.f;
    float height = 30.f;
    float x = 20.f;
    float y = 20.f;

    m_LevelBarBack.setSize( sf::Vector2f( width, height ) );
    m_LevelBarBack.setFillColor( sf::Color( 50, 50, 50, 200 ) );
    m_LevelBarBack.setPosition( x, y );

    m_LevelBarText.setFont( m_Data->assets.GetFont( "Gui Font" ) );
    m_LevelBarText.setCharacterSize( 18 );
    m_LevelBarText.setPosition( m_LevelBarBack.getPosition().x + 10.f, m_LevelBarBack.getPosition().y + 6.f );

}
void PlayerGui::InitExpBar()
{
    Debug("PLAYER GUI::Init Exp Bar")
    float width = 200.f;
    float height = 30.f;
    float x = 20.f;
    float y = 60.f;

    m_ExpBarMaxWidth = width;

    m_ExpBarBack.setSize( sf::Vector2f( width, height ) );
    m_ExpBarBack.setFillColor( sf::Color( 50, 50, 50, 200 ) );
    m_ExpBarBack.setPosition( x, y );

    m_ExpBarInner.setSize( sf::Vector2f( width, height ) );
    m_ExpBarInner.setFillColor( sf::Color( 20, 20, 250, 200 ) );
    m_ExpBarInner.setPosition( m_ExpBarBack.getPosition() );
    
    m_ExpBarText.setFont( m_Data->assets.GetFont( "Gui Font" ) );
    m_ExpBarText.setCharacterSize( 14 );
    m_ExpBarText.setPosition( m_ExpBarBack.getPosition().x + 10.f, m_ExpBarBack.getPosition().y + 6.f );
}

void PlayerGui::InitHPBar()
{
    Debug("PLAYER GUI::Init HP Bar")
    float width = 300.f;
    float height = 50.f;
    float x = 20.f;
    float y = 100.f;

    m_HpBarMaxWidth = width;

    m_HpBarBack.setSize( sf::Vector2f( width, height ) );
    m_HpBarBack.setFillColor( sf::Color( 50, 50, 50, 200 ) );
    m_HpBarBack.setPosition( x, y );

    m_HpBarInner.setSize( sf::Vector2f( width, height ) );
    m_HpBarInner.setFillColor( sf::Color( 250, 20, 20, 200 ) );
    m_HpBarInner.setPosition( m_HpBarBack.getPosition() );
    
    m_HpBarText.setFont( m_Data->assets.GetFont( "Gui Font" ) );
    m_HpBarText.setCharacterSize( 18 );
    // std::cout <<m_HpBarBack.getPosition().y + m_HpBarBack.getGlobalBounds().height / 2 - m_HpBarText.getGlobalBounds().height / 2 << '\n';
    m_HpBarText.setPosition(
        m_HpBarBack.getPosition().x + 10.f,
        m_HpBarBack.getPosition().y + 14.f
    );
}

PlayerGui::PlayerGui( GameDataRef data, Player* player ) : m_Data( std::move( data ) )
{
    m_Player = player;

    InitFont();
    InitLevelBar();
    InitExpBar();
    InitHPBar();
}

PlayerGui::~PlayerGui()
{
    Debug("PLAYER GUI::Destructor")
    delete m_Player;
}

void PlayerGui::UpdateLevelBar( )
{
    m_LevelBarString = std::to_string( m_Player->GetAttributeComponent()->m_Level );
    m_LevelBarText.setString( m_LevelBarString );

}

void PlayerGui::UpdateExpBar( )
{
    float percent = static_cast<float>( m_Player->GetAttributeComponent()->m_Exp ) / static_cast<float>( m_Player->GetAttributeComponent()->m_ExpNext );
    m_ExpBarInner.setSize( sf::Vector2f(
        static_cast<float>( std::floor( m_ExpBarMaxWidth * percent ) ),
        m_ExpBarInner.getSize().y
    ) );

    m_ExpBarString = std::to_string( m_Player->GetAttributeComponent()->m_Exp ) + " / " + std::to_string( m_Player->GetAttributeComponent()->m_ExpNext );
    m_ExpBarText.setString( m_ExpBarString );
}

void PlayerGui::UpdateHPBar( )
{
    float percent = static_cast<float>( m_Player->GetAttributeComponent()->m_Hp ) / static_cast<float>( m_Player->GetAttributeComponent()->m_HpMax );
    m_HpBarInner.setSize( sf::Vector2f(
        static_cast<float>( std::floor( m_HpBarMaxWidth * percent ) ),
        m_HpBarInner.getSize().y
    ) );

    m_HpBarString = std::to_string( m_Player->GetAttributeComponent()->m_Hp ) + " / " + std::to_string( m_Player->GetAttributeComponent()->m_HpMax );
    m_HpBarText.setString( m_HpBarString );
}

void PlayerGui::Update( const float& dt )
{
    UpdateLevelBar( );
    UpdateExpBar( );
    UpdateHPBar( );
}

void PlayerGui::DrawLevelBar( sf::RenderTarget& target )
{
    target.draw( m_LevelBarBack );
    target.draw( m_LevelBarText );
}

void PlayerGui::DrawExpBar( sf::RenderTarget& target )
{
    target.draw( m_ExpBarBack );
    target.draw( m_ExpBarInner );
    target.draw( m_ExpBarText );
}

void PlayerGui::DrawHPBar( sf::RenderTarget& target )
{
    target.draw( m_HpBarBack );
    target.draw( m_HpBarInner );
    target.draw( m_HpBarText );
}

void PlayerGui::Draw( sf::RenderTarget& target )
{
    DrawLevelBar( target );
    DrawExpBar( target );
    DrawHPBar( target );
}