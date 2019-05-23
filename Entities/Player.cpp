#include "Player.h"

void Player::InitTextures()
{
    m_Data->assets.LoadTexture("Player Sheet", PLAYER_SHEET_FILEPATH);
}

void Player::InitSounds()
{
}

void Player::InitVariables()
{
    m_IsAttacking = false;
    m_AttackCount = 0;
    m_CurrentFace = AttackFace::eAttackFaceRight;
    m_LastAttackFace = AttackFace::eNone;
}

void Player::InitComponents()
{
}

Player::Player(GameDataRef data) : Entity(data), m_Data(move(data))
{
    InitTextures();
    InitSounds();
    InitVariables();
    InitComponents();

    // Set acceleration and deceleration
    CreateMovementComponent(PLAYER_MOVEMENT_SPEED, 1500, 500);
    CreateAnimationComponent("Player Sheet"); // Send texture
    // OffsetX, OffsetY, width, height
    CreateHitboxComponent(35.f, 20.f, 30.f, 60.f);
    CreateAttributeComponent(0);

    // Animation name, animation timer, start pos X, start pos Y, frames X, frames Y, tile size
    // Lesser the timer, faster the animation speed
    m_AC->AddAnimation("IDLE", 15, 0, 0, 4, 1, TILE_WIDTH, TILE_HEIGHT);
    m_AC->AddAnimation("WALK", 10, 0, 1, 6, 1, TILE_WIDTH, TILE_HEIGHT);
    m_AC->AddAnimation("ATTACK0", 7, 0, 3, 6, 1, TILE_WIDTH, TILE_HEIGHT);
    m_AC->AddAnimation("ATTACK1", 7, 0, 4, 5, 1, TILE_WIDTH, TILE_HEIGHT);

    // Implement later
    // m_AC->AddAnimation("TURN_ATTACK", 67, 0, 5, 6, 1, TILE_WIDTH, TILE_HEIGHT );
}

Player::~Player()
{
}

// Accessors
AttributeComponent *Player::GetAttributeComponent()
{
    return m_AttComp;
}

// Functions
void Player::LoseHP(const int &hp)
{
    m_AttComp->m_Hp -= hp;
    if (m_AttComp->m_Hp < 0)
    {
        m_AttComp->m_Hp = 0;
    }
}

void Player::GainHP(const int &hp)
{
    m_AttComp->m_Hp += hp;
    if (m_AttComp->m_Hp > m_AttComp->m_HpMax)
    {
        m_AttComp->m_Hp = m_AttComp->m_HpMax;
    }
}

void Player::LoseExp(const int &exp)
{
    if (m_AttComp->m_Exp > exp)
    {
        m_AttComp->m_Exp -= exp;
    }
    else
    {
        m_AttComp->m_Exp = 0;
    }
}

void Player::GainExp(const int &exp)
{
    m_AttComp->GainExp(exp);
}

void Player::Attack()
{
    if (m_LastAttackFace == AttackFace::eNone)
    {
        m_LastAttackFace = m_CurrentFace;
    }
    m_IsAttacking = true;
}

void Player::UpdateAnimation(const float &dt)
{
    if (m_AttackClock.getElapsedTime().asSeconds() > 1.3f)
    {
        m_AttackCount = 0;
        m_AttackClock.restart();
        m_LastAttackFace = m_CurrentFace;
    }
    if (m_IsAttacking)
    {
        /*
        // Set the origin in facing direction
        if ( m_Sprite.getScale().x < 0.f )  // Facing left
        {
            m_Sprite.setOrigin( 50.f + 2.f, 0.f );
            m_HC->UpdatePosition( 25.f, 10.f, 45.f, 70.f );
        }
        else    // Facing right
        {
            m_Sprite.setOrigin( 0.f + 2.f, 0.f );
            m_HC->UpdatePosition( 60.f, 10.f, 45.f, 70.f );
        }

        if ( m_AC->Play( "ATTACK"+ std::to_string(m_AttackCount), dt, true ) )
        {
            m_IsAttacking = false;
            m_AttackCount = (m_AttackCount + 1 ) % 2 ;
            m_AttackClock.restart().asSeconds();

            // Reset position after player is done attacking
            // Set the origin in facing direction
            if ( m_Sprite.getScale().x < 0.f )  // Facing left
            {
                m_Sprite.setOrigin( 50.f, 0.f );
                // m_HC->UpdatePosition( 50.f, 20.f, 30.f, 60.f );
            }
            else    // Facing right
            {
                m_Sprite.setOrigin( 0.f, 0.f );
                // m_HC->UpdatePosition( 50.f, 20.f, 30.f, 60.f );
            }
        }
        */
    }

    if (m_MC->GetState(MovementStates::eIdle))
    {
        m_AC->Play("IDLE", dt);
    }
    else if (m_MC->GetState(MovementStates::eMovingLeft))
    {
        m_CurrentFace = AttackFace::eAttackFaceLeft;

        if (m_Sprite.getScale().x > 0.f)
        {
            // Set Proper origin
            m_Sprite.setOrigin(50.f, 0.f);
            m_Sprite.setScale(-SCALE_X, SCALE_Y);
        }
        m_AC->Play("WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity());
    }
    else if (m_MC->GetState(MovementStates::eMovingRight))
    {
        m_CurrentFace = AttackFace::eAttackFaceRight;

        if (m_Sprite.getScale().x < 0.f)
        {
            m_Sprite.setOrigin(0.f, 0.f);
            m_Sprite.setScale(SCALE_X, SCALE_Y);
        }
        m_AC->Play("WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity());
    }
    else if (m_MC->GetState(MovementStates::eMovingUp) || m_MC->GetState(MovementStates::eMovingDown) || m_MC->GetState(MovementStates::eMoving))
    {
        m_AC->Play("WALK", dt, m_MC->GetVelocity().x, m_MC->GetMaxVelocity());
    }
}

void Player::Update(const float &dt)
{
    m_MC->Update(dt);
    UpdateAnimation(dt);
    m_HC->Update();
}

void Player::Draw(sf::RenderTarget &target)
{
    target.draw(m_Sprite);

    m_HC->Draw(target);
}