#include "MainMenuState.h"
#include "GameState.h"
#include "GameSettingsState.h"
#include "EditorState.h"



void MainMenuState::InitTextures()
{
    // Use sprites for background
    m_Background.setSize(sf::Vector2f(m_Data->window.getSize()));
    m_Background.setFillColor(sf::Color(30, 30, 30));
}

void MainMenuState::InitFonts()
{
    m_Data->assets.LoadFont("Title Font", SCREEN_FONT_FILEPATH);
    m_Data->assets.LoadFont("Button Font", BUTTON_FONT_FILEPATH);
    // m_Data->assets.LoadFont( "Debug Font", DEBUG_FONT_FILEPATH );
}

void MainMenuState::InitSounds()
{
}

void MainMenuState::InitVariables()
{
    m_Hud = new gui::HUD( m_Data );
    m_Hud->SetText(
        "Title Font", "RPG", 
        TITLE_SIZE, 
        ( m_Data->GfxSettings.resolution.width / 2.0f ),
        m_Data->GfxSettings.resolution.height / 6.0f 
    );
}

void MainMenuState::InitKeyBinds()
{
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
    //Draw Buttons
    m_Buttons["Exit"] = new gui::Button(
        m_Data->GfxSettings.resolution.width / 2.f - BUTTON_WIDTH / 2.f,
        m_Data->GfxSettings.resolution.height - BUTTON_HEIGHT / 0.4f,
        BUTTON_WIDTH, BUTTON_HEIGHT,
        &m_Data->assets.GetFont( "Button Font" ), "Exit", BUTTON_TEXT_SIZE,
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR)
    );

    m_Buttons["Settings"] = new gui::Button(
        m_Data->GfxSettings.resolution.width / 2.f - BUTTON_WIDTH / 2.f,
        m_Buttons["Exit"]->GetButton().getPosition().y - BUTTON_HEIGHT / 0.8f,
        BUTTON_WIDTH, BUTTON_HEIGHT,
        &m_Data->assets.GetFont( "Button Font" ), "Settings", BUTTON_TEXT_SIZE,
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR)
    );

    m_Buttons["Editor"] = new gui::Button(
        m_Data->GfxSettings.resolution.width / 2.f - BUTTON_WIDTH / 2.f,
        m_Buttons["Settings"]->GetButton().getPosition().y - BUTTON_HEIGHT / 0.8f,
        BUTTON_WIDTH, BUTTON_HEIGHT,
        &m_Data->assets.GetFont( "Button Font" ), "Editor", BUTTON_TEXT_SIZE,
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR)
    );

    m_Buttons["Play"] = new gui::Button(
        m_Data->GfxSettings.resolution.width / 2.f - BUTTON_WIDTH / 2.f,
        m_Buttons["Editor"]->GetButton().getPosition().y - BUTTON_HEIGHT / 0.8f,
        BUTTON_WIDTH, BUTTON_HEIGHT,
        &m_Data->assets.GetFont( "Button Font" ), "Start", BUTTON_TEXT_SIZE,
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR)
    );

}

MainMenuState::MainMenuState(GameDataRef data) : m_Data(std::move(data))
{
}

MainMenuState::~MainMenuState()
{
    Debug( "Destructor of Main Menu state")
    delete m_Hud;
    for (const auto &button : m_Buttons)
    {
        delete button.second;
    }
}

// @override
void MainMenuState::Init()
{
    Debug("Main Menu State Initializing....");

    InitTextures();
    InitFonts();
    InitSounds();
    InitVariables();
    InitKeyBinds();
    InitGui();
    // ResetGui();
}

// @override
void MainMenuState::HandleInput(float dt)
{
    sf::Event event;

    while (m_Data->window.pollEvent(event))
    {
        // Check for game close
        if (sf::Event::Closed == event.type || ( m_Buttons["Exit"]->isPressed() && m_Data->input.GetKeyTime() ) )
        {
            m_Data->machine.ClearStates();
            m_Data->machine.RemoveState();
            m_Data->window.close();
        }
    }

    if (m_Buttons["Play"]->isPressed() && m_Data->input.GetKeyTime() && m_Data->input.GetKeyTime() )
    {
        m_Data->machine.AddState(StateRef(new GameState(m_Data)), true);
    }
    if (m_Buttons["Editor"]->isPressed() && m_Data->input.GetKeyTime() && m_Data->input.GetKeyTime() )
    {
        m_Data->machine.AddState(StateRef(new EditorState(m_Data)), true);
    }
    if (m_Buttons["Settings"]->isPressed() && m_Data->input.GetKeyTime() && m_Data->input.GetKeyTime() )
    {
        m_Data->machine.AddState(StateRef(new GameSettingsState(m_Data)), true);
    }
}

// @override
void MainMenuState::Update(float dt)
{
    m_Data->input.UpdateMousePosition(m_Data->window);
    m_Data->input.UpdateKeyTime( dt );

    for (auto button : m_Buttons)
    {
        button.second->Update(m_Data->input.GetViewMousePosition());
    }
}

// @override
void MainMenuState::Draw()
{
    m_Data->window.clear();

    m_Data->window.draw(m_Background);
    /*m_Data->window.draw( m_PlayButton );
        m_Data->window.draw( m_ExitButton );
        m_Data->window.draw( m_SettingsButton );*/

    m_Hud->Draw( m_Data->window );

    // m_Buttons["Settings"]->Draw();

    for (auto button : m_Buttons)
    {
        button.second->Draw( m_Data->window );
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