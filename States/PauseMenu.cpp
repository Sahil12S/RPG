#include "PauseMenu.h"
#include "MainMenuState.h"

void PauseMenu::InitTextures()
{
    // Set Background
    m_Background.setSize(sf::Vector2f(m_Data->GfxSettings.resolution.width, m_Data->GfxSettings.resolution.height));
    m_Background.setFillColor(sf::Color(80, 80, 80, 100));

    m_Container.setSize(sf::Vector2f(m_Data->GfxSettings.resolution.width / 4.f, m_Data->GfxSettings.resolution.height));
    m_Container.setFillColor(sf::Color(60, 60, 60, 200));
    m_Container.setPosition(
        sf::Vector2f(m_Data->GfxSettings.resolution.width / 2.f - m_Container.getSize().x / 2.f,
                     20.f));
}

void PauseMenu::InitFonts()
{
    m_Data->assets.LoadFont("Title Font", SCREEN_FONT_FILEPATH);
    m_Data->assets.LoadFont("Button Font", BUTTON_FONT_FILEPATH);
}

void PauseMenu::InitVariables()
{
    m_Hud = new gui::HUD(m_Data);
    m_Hud->SetText("Title Font", "PAUSED", TITLE_SIZE, (m_Container.getPosition().x + m_Container.getSize().x / 2.f),
                   m_Data->window.getSize().y / 6.0f);
}

PauseMenu::PauseMenu(GameDataRef data) : m_Data(std::move(data))
{
    Debug("PAUSE MENU::Initializing...")
        InitTextures();
    InitFonts();
    InitVariables();
}

PauseMenu::~PauseMenu()
{
    Debug("PAUSE MENU::Destructor") delete m_Hud;
    for (const auto &button : m_Buttons)
    {
        delete button.second;
    }
}

bool PauseMenu::IsButtonPressed(const std::string &key)
{
    return m_Buttons[key]->isPressed();
}

void PauseMenu::AddButton(const std::string key,
                          const float y,
                          const std::string text)
{
    m_Buttons[key] = new gui::Button(
        m_Container.getPosition().x + m_Container.getSize().x / 2.f - gui::p2pX(BUTTON_WIDTH_PREC, m_Data->GfxSettings.resolution) / 2.f,
        y,
        gui::p2pX(BUTTON_WIDTH_PREC, m_Data->GfxSettings.resolution), gui::p2pY(BUTTON_HEIGHT_PERC, m_Data->GfxSettings.resolution),
        &m_Data->assets.GetFont("Button Font"), text, BUTTON_TEXT_SIZE,
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR));
}

void PauseMenu::Update(const sf::Vector2i &mousePosWindow)
{
    // Update mouse position for buttons
    for (auto &button : m_Buttons)
    {
        button.second->Update(sf::Vector2f(mousePosWindow));
    }
}

void PauseMenu::Draw(sf::RenderTarget &target)
{
    // m_Data->window.draw( m_Background );
    // m_Data->window.draw( m_Container );
    // m_Hud->Draw( true );

    // for ( auto button : m_Buttons )
    // {
    //     button.second->Draw();
    // }
    target.draw(m_Background);
    target.draw(m_Container);
    m_Hud->Draw(target);

    for (auto button : m_Buttons)
    {
        button.second->Draw(target);
    }
    // m_Data->window.display();
}