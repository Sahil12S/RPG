#include "Game.hpp"
#include "States/SplashState.hpp"

void Game::InitVariables()
{
    dt = 0.f;
}

void Game::InitGraphicsSettings()
{
    m_Data->GfxSettings.LoadFromFile("Config/graphics.ini");
}

void Game::InitWindow()
{
    if (m_Data->GfxSettings.fullscreen)
    {
        // std::cout << "FULLSCREEN" << std::endl;
        m_Data->window.create(
            m_Data->GfxSettings.resolution,
            m_Data->GfxSettings.title,
            sf::Style::Fullscreen,
            m_Data->GfxSettings.contextSettings);
    }
    else
    {
        // std::cout << "NOT FULLSCREEN" << std::endl;
        m_Data->window.create(
            m_Data->GfxSettings.resolution,
            m_Data->GfxSettings.title,
            sf::Style::Titlebar | sf::Style::Close,
            m_Data->GfxSettings.contextSettings);
    }

    m_Data->window.setFramerateLimit(m_Data->GfxSettings.frameRateLimit);
    m_Data->window.setVerticalSyncEnabled(m_Data->GfxSettings.verticalSync);
}

void Game::InitStates()
{
    m_Data->machine.AddState(StateRef(new SplashState(m_Data)));
}

Game::Game()
{
    InitVariables();
    InitGraphicsSettings();
    InitWindow();
    InitStates();
}

Game::~Game()
{
}

void Game::UpdateDt()
{
    /*
    * Updates the dt variable with time it takes to update & render one frame
    */
    dt = m_Clock.restart().asSeconds();
}

void Game::Run()
{
    while (m_Data->window.isOpen())
    {
        UpdateDt();
        m_Data->machine.ProcessStateChange();

        if (m_Data->window.hasFocus())
        {
            m_Data->machine.GetActiveState()->HandleInput(dt);
            m_Data->machine.GetActiveState()->Update(dt);
        }

        m_Data->machine.GetActiveState()->Draw();
    }
}