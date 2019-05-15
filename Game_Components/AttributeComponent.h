#ifndef ATTRIBUTE_COMPONENT_H
#define ATTRIBUTE_COMPONENT_H

#include "../pch.cpp"
#include "../DEFINITIONS.h"

class AttributeComponent
{
public:
    // Levelling attributes
    unsigned mLevel;
    unsigned mExp;
    unsigned mExpNext;
    unsigned mAttributePoints;

    // Attributes
    unsigned mVitality;
    unsigned mStrength;
    unsigned mDexterity;
    unsigned mAgility;
    unsigned mIntelligence;

    // Stats
    int mHp;
    int mHpMax;
    int mDamageMin;
    int mDamageMax;
    int mAccuracy;
    int mDefense;
    int mLuck;


    // Con / Des
    AttributeComponent( unsigned level );
    virtual ~AttributeComponent();

    // Functions
    void CalculateExpNext();
    void UpdateStats();
    void LevelUp();

    void Update();
};

#endif // ATTRIBUTE_COMPONENT_H