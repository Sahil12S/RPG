#ifndef ATTRIBUTE_COMPONENT_H
#define ATTRIBUTE_COMPONENT_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

class AttributeComponent
{
public:
    // Levelling attributes
    int m_Level;
    int m_Exp;
    int m_ExpNext;
    int m_AttributePoints;

    // Attributes
    int m_Vitality;
    int m_Strength;
    int m_Dexterity;
    int m_Agility;
    int m_Intelligence;

    // Stats
    int m_Hp;
    int m_HpMax;
    int m_DamageMin;
    int m_DamageMax;
    int m_Accuracy;
    int m_Defense;
    int m_Luck;


    // Con / Des
    AttributeComponent( int level );
    virtual ~AttributeComponent();

    // Functions
    std::string DebugPrint() const;

    void GainExp( const int& exp );
    
    void UpdateStats( const bool& reset );
    void UpdateLevel();

    void Update();
};

#endif // ATTRIBUTE_COMPONENT_H