#include "AttributeComponent.h"


AttributeComponent::AttributeComponent( int level )
{
    m_Level = level;
    m_Exp = 0;
    m_ExpNext = static_cast<int>( ( 50 / 3 ) * ( pow( m_Level + 1, 3 ) - 6 * pow( m_Level + 1, 2 ) + ( ( m_Level + 1 ) * 17 ) - 12 ) );
    m_AttributePoints = 2;

    m_Vitality = 1;
    m_Strength = 1;
    m_Dexterity = 1;
    m_Agility = 1;
    m_Intelligence = 1;

    UpdateLevel();
    UpdateStats( true );
}

AttributeComponent::~AttributeComponent()
{

}

// Functions
std::string AttributeComponent::DebugPrint() const
{
    std::stringstream ss;
    ss << "Level: " << m_Level << '\n'
        << "Exp: " << m_Exp << '\n'
        << "Exp Next: " << m_ExpNext << '\n'
        << "Attp: " << m_AttributePoints << '\n';

    return ss.str();
}

void AttributeComponent::GainExp( const int& exp )
{
    m_Exp += exp;
    UpdateLevel();
}

void AttributeComponent::UpdateStats( const bool& reset )
{
    m_HpMax         = m_Vitality * 5 + m_Vitality + m_Strength + m_Intelligence / 5;
    m_DamageMax     = m_Strength * 2 + m_Strength / 2 + m_Intelligence / 5;
    m_DamageMin     = m_Strength * 2 + m_Strength / 4 + m_Intelligence / 5;
    m_Accuracy      = m_Dexterity * 5 + m_Dexterity / 3 + m_Intelligence / 5;
    m_Defense       = m_Agility * 2 + m_Agility / 4 + m_Intelligence / 5;
    m_Luck          = m_Intelligence * 2 + m_Intelligence / 5;

    if( reset )
    {
        m_Hp = m_HpMax;
    }
}

void AttributeComponent::UpdateLevel()
{
    while( m_Exp >= m_ExpNext )
    {
        ++m_Level;
        m_Exp -= m_ExpNext;
        m_ExpNext = static_cast<int>( ( 50 / 3 ) * ( pow( m_Level + 1, 3 ) - 6 * pow( m_Level + 1, 2 ) + ( ( m_Level + 1 ) * 17 ) - 12 ) );
        ++m_AttributePoints;
    }
}

void AttributeComponent::Update()
{
    UpdateLevel();
}