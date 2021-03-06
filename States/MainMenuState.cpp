#include "MainMenuState.hpp"
#include "GameState.hpp"
#include "GameSettingsState.hpp"
#include "EditorState.hpp"

void MainMenuState::InitTextures()
{
    // Use sprites for background
    m_Background.setSize(sf::Vector2f(m_Data->window.getSize()));
    m_Background.setFillColor(sf::Color(30, 30, 30));
}

void MainMenuState::InitFonts()
{
    m_Data->assets.LoadFont("Title Font", TITLE_FONT_FILEPATH);
    m_Data->assets.LoadFont("Button Font", BUTTON_FONT_FILEPATH);
    // m_Data->assets.LoadFont( "Debug Font", DEBUG_FONT_FILEPATH );
}

void MainMenuState::InitSounds()
{
}

void MainMenuState::InitVariables()
{
    Debug("MAIN MENU STATE::Init Key Variables");

    m_Hud = new gui::HUD(m_Data);
    m_Hud->SetText(
        "Title Font", "RPG",
        gui::calcCharSize(TITLE_SIZE_PERC, m_Data->GfxSettings.resolution),
        (m_Data->GfxSettings.resolution.width / 2.0f),
        m_Data->GfxSettings.resolution.height / 6.0f);
}

void MainMenuState::InitKeyBinds()
{
    Debug("MAIN MENU STATE::Init Key Binds")
        std::fstream ifs(MAIN_MENU_KEY_BIND_FILEPATH);

    if (ifs.is_open())
    {
        std::string keyAction;
        std::string key;

        while (ifs >> keyAction >> key)
        {
            m_KeyBinds[keyAction] = m_Data->input.getSupportedKeys().at(key);
        }
    }
}

void MainMenuState::InitGui()
{
    Debug("MAIN MENU STATE::Init Gui");

    sf::VideoMode &vm = m_Data->GfxSettings.resolution;

    m_Buttons["Exit"] = new gui::Button(
        vm.width / 2.f - gui::p2pX(BUTTON_WIDTH_PREC, vm) / 2.f,
        vm.height - gui::p2pY(BUTTON_HEIGHT_PERC, vm) / 0.4f,
        gui::p2pX(BUTTON_WIDTH_PREC, vm), gui::p2pY(BUTTON_HEIGHT_PERC, vm),
        &m_Data->assets.GetFont("Button Font"), "Exit", gui::calcCharSize(BUTTON_TEXT_SIZE_PERC, vm),
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR));

    m_Buttons["Settings"] = new gui::Button(
        vm.width / 2.f - gui::p2pX(BUTTON_WIDTH_PREC, vm) / 2.f,
        m_Buttons["Exit"]->GetButton().getPosition().y - gui::p2pY(BUTTON_HEIGHT_PERC, vm) / 0.8f,
        gui::p2pX(BUTTON_WIDTH_PREC, vm), gui::p2pY(BUTTON_HEIGHT_PERC, vm),
        &m_Data->assets.GetFont("Button Font"), "Settings", gui::calcCharSize(BUTTON_TEXT_SIZE_PERC, vm),
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR));

    m_Buttons["Editor"] = new gui::Button(
        vm.width / 2.f - gui::p2pX(BUTTON_WIDTH_PREC, vm) / 2.f,
        m_Buttons["Settings"]->GetButton().getPosition().y - gui::p2pY(BUTTON_HEIGHT_PERC, vm) / 0.8f,
        gui::p2pX(BUTTON_WIDTH_PREC, vm), gui::p2pY(BUTTON_HEIGHT_PERC, vm),
        &m_Data->assets.GetFont("Button Font"), "Editor", gui::calcCharSize(BUTTON_TEXT_SIZE_PERC, vm),
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR));

    m_Buttons["Play"] = new gui::Button(
        vm.width / 2.f - gui::p2pX(BUTTON_WIDTH_PREC, vm) / 2.f,
        m_Buttons["Editor"]->GetButton().getPosition().y - gui::p2pY(BUTTON_HEIGHT_PERC, vm) / 0.8f,
        gui::p2pX(BUTTON_WIDTH_PREC, vm), gui::p2pY(BUTTON_HEIGHT_PERC, vm),
        &m_Data->assets.GetFont("Button Font"), "Start", gui::calcCharSize(BUTTON_TEXT_SIZE_PERC, vm),
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR));
}

MainMenuState::MainMenuState(GameDataRef data) : m_Data(std::move(data))
{
}

MainMenuState::~MainMenuState()
{
    Debug("MAIN MENU STATE::Destructor") delete m_Hud;
    for (const auto &button : m_Buttons)
    {
        delete button.second;
    }
}

// @override
void MainMenuState::Init()
{
    Debug("MAIN MENU STATE::Initializing....");

    InitTextures();
    InitFonts();
    InitSounds();
    InitVariables();
    InitKeyBinds();
    InitGui();
    // ResetGui();
}

// @override
void MainMenuState::HandleInput(const float &dt)
{
    sf::Event event;

    while (m_Data->window.pollEvent(event))
    {
        // Check for game close
        if (sf::Event::Closed == event.type || (m_Buttons["Exit"]->isPressed() && m_Data->input.GetKeyTime()))
        {
            m_Data->machine.ClearStates();
            m_Data->machine.RemoveState();
            m_Data->window.close();
        }
    }

    if (m_Buttons["Play"]->isPressed() && m_Data->input.GetKeyTime())
    {
        m_Data->machine.AddState(StateRef(new GameState(m_Data)), true);
    }
    if (m_Buttons["Editor"]->isPressed() && m_Data->input.GetKeyTime())
    {
        m_Data->machine.AddState(StateRef(new EditorState(m_Data)), true);
    }
    if (m_Buttons["Settings"]->isPressed() && m_Data->input.GetKeyTime())
    {
        m_Data->machine.AddState(StateRef(new GameSettingsState(m_Data)), true);
    }
}

void MainMenuState::UpdateButtons()
{
    for (auto button : m_Buttons)
    {
        button.second->Update(m_Data->input.GetViewMousePosition());
    }
}

// @override
void MainMenuState::Update(const float &dt)
{
    m_Data->input.UpdateMousePosition(m_Data->window);
    m_Data->input.UpdateKeyTime(dt);

    UpdateButtons();
}

// @override
void MainMenuState::Draw()
{
    m_Data->window.clear();

    m_Data->window.draw(m_Background);
    /*m_Data->window.draw( m_PlayButton );
        m_Data->window.draw( m_ExitButton );
        m_Data->window.draw( m_SettingsButton );*/

    m_Hud->Draw(m_Data->window);

    // m_Buttons["Settings"]->Draw();

    for (auto button : m_Buttons)
    {
        button.second->Draw(m_Data->window);
    }

    /* Remove later */
    /*sf::Text mouseText;
        mouseText.setPosition( m_Data->input.GetViewMousePosition().x + 5, m_Data->input.GetViewMousePosition().y );
        mouseText.setFont( m_Data->assets.GetFont( "Debug Font" ) );
        mouseText.setCharacterSize( 20 );
        std::stringstream ss;
        ss << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y;
        mouseText.setString( ss.str() );
        m_Data->window.draw( mouseText );*/

    m_Data->window.display();
}