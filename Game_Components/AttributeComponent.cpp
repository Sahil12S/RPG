#include "AttributeComponent.h"


AttributeComponent::AttributeComponent( unsigned level )
{
    mLevel = level;
    mExp = 0;
    mExpNext = 0;
    mAttributePoints = 3;

    mVitality = 1;
    mStrength = 1;
    mDexterity = 1;
    mAgility = 1;
    mIntelligence = 1;

    UpdateStats();
}

AttributeComponent::~AttributeComponent()
{

}

// Functions
void CalculateExpNext()
{
    
}

void AttributeComponent::UpdateStats()
{

}

void LevelUp()
{

}

void Update()
{

}