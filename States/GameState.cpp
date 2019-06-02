#include "GameState.hpp"
#include "MainMenuState.hpp"

void GameState::InitView()
{
    Debug("GAME STATE::Init View");
    m_View.setSize(sf::Vector2f(m_Data->GfxSettings.resolution.width, m_Data->GfxSettings.resolution.height));
    m_View.setCenter(
        sf::Vector2f(
            m_Data->GfxSettings.resolution.width / 2.f,
            m_Data->GfxSettings.resolution.height / 2.f));

    m_RenderSprite.setTexture(m_RenderTexture.getTexture());
    m_RenderSprite.setTextureRect(
        sf::IntRect(
            0,
            0,
            m_Data->GfxSettings.resolution.width,
            m_Data->GfxSettings.resolution.height));
}

void GameState::InitVariables()
{
    Debug("GAME STATE::Init Variables");
    m_Paused = false;
}

void GameState::InitTextures()
{
    Debug("GAME STATE::Init Textures");
}

void GameState::InitFonts()
{
    Debug("GAME STATE::Init Fonts");
    m_Data->assets.LoadFont("Debug Font", DEBUG_FONT_FILEPATH);
    m_Data->assets.LoadFont("Hud Font", TEXT_FONT_FILEPATH);
    // m_Data->assets.LoadFont("Button Font", TEXT_FONT_FILEPATH);
}

void GameState::InitSounds()
{
    // Nothing for now
}

void GameState::InitKeyBinds()
{
    Debug("GAME STATE::Init Key Binds");
    // Read Key Bindings from file
    std::ifstream ifs(GAMESTATE_KEY_BIND_FILEPATH);

    if (ifs.is_open())
    {
        std::string keyAction;
        std::string key;
        while (ifs >> keyAction >> key)
        {
            m_KeyBinds[keyAction] = m_Data->input.getSupportedKeys().at(key);
        }
    }

    ifs.close();
}

void GameState::InitPauseMenu()
{
    Debug("GAME STATE::Init Pause Menu");
    m_PauseMenu = new PauseMenu(m_Data);
    m_PauseMenu->AddButton("Quit", m_Data->GfxSettings.resolution.height / 1.2f, "Quit");
}

void GameState::InitComponents()
{
    // hud["timer"] = new gui::HUD( m_Data );
    // hud["timer"]->SetText("Hud Font", "Remaining Time: 0", 50, m_Data->GfxSettings.resolution.width / 6, m_Data->GfxSettings.resolution.height / 25 );
    // hud["score"] = new gui::HUD( m_Data );
    // hud["score"]->SetText("Hud Font", "Score: 0", 50, m_Data->GfxSettings.resolution.width / 1.2, m_Data->GfxSettings.resolution.height / 25 );
}

void GameState::InitPlayers()
{
    Debug("GAME STATE::Init Players");
    // Initialize player & spawn it
    m_Player = new Player(m_Data);
    // m_Player->SetPosition( m_Data->GfxSettings.resolution.width / 2.f, m_Data->GfxSettings.resolution.height / 2.f );
    m_Player->SetPosition(gui::p2pX(26.f, m_Data->GfxSettings.resolution), gui::p2pY(27.8, m_Data->GfxSettings.resolution));
}

void GameState::InitPlayerGui()
{
    Debug("GAME STATE::Init PlayerGUI");
    m_PlayerGui = new PlayerGui(m_Data, m_Player);
}

void GameState::InitTileMap()
{
    Debug("GAME STATE::Init TileMap");
    // m_TileMap = new TileMap( m_Data, "myMap.txt" );
    m_TileMap = new TileMap(m_Data, MAP_WIDTH, MAP_HEIGHT, TILES_TEXTURE_FILEPATH);
    m_TileMap->LoadFromFile("myMap.txt");
}

GameState::GameState(GameDataRef data) : m_Data(std::move(data))
{
}

GameState::~GameState()
{
    Debug("GAME STATE::Destructor");
    delete m_Player;
    delete m_TileMap;
    delete m_PauseMenu;
    delete m_PlayerGui;
}

void GameState::Init()
{
    Debug("GAME STATE::Initializing...");

    InitView();
    InitVariables();
    InitTextures();
    InitFonts();
    InitSounds();

    InitKeyBinds();
    InitPauseMenu();
    InitComponents();
    InitPlayers();
    InitPlayerGui();
    InitTileMap();

    m_CursorText.setFont(m_Data->assets.GetFont("Debug Font"));
    m_CursorText.setFillColor(sf::Color::White);
    m_CursorText.setCharacterSize(20);
    m_CursorText.setPosition(m_Data->input.GetViewMousePosition().x + 20, m_Data->input.GetViewMousePosition().y);
}

void GameState::UpdateView(const float &dt)
{
    // To control large number of decimals, we floor it down
    m_View.setCenter(
        std::floor(m_Player->GetPosition().x - (static_cast<float>(m_Data->input.GetWindowMousePosition().x) - static_cast<float>(m_Data->GfxSettings.resolution.width)) / 5.f),
        std::floor(m_Player->GetPosition().y - (static_cast<float>(m_Data->input.GetWindowMousePosition().y) - static_cast<float>(m_Data->GfxSettings.resolution.height)) / 5.f));
}

void GameState::HandleInput(const float &dt)
{
    sf::Event event;

    while (m_Data->window.pollEvent(event))
    {
        // Check for window close
        if (sf::Event::Closed == event.type)
        {
            m_Data->machine.ClearStates();
            m_Data->machine.RemoveState();
            m_Data->window.close();
        }
    }

    if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key(m_KeyBinds["QUIT"]))) &&
        m_Data->input.GetKeyTime())
    {
        m_Paused = !m_Paused;
    }

    /*
    * Handle movements
    */
    if (!m_Paused)
    {
        // Walk Left
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_KeyBinds["MOVE_LEFT"])))
        {
            m_Player->Move(dt, -1.0f, 0.0f);
        }

        // Walk right
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_KeyBinds["MOVE_RIGHT"])))
        {
            m_Player->Move(dt, 1.0f, 0.0f);
        }

        // Walk Up
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_KeyBinds["MOVE_UP"])))
        {
            m_Player->Move(dt, 0.0f, -1.0f);
            if (m_Data->input.GetKeyTime())
            {
                m_Player->GainExp(10);
            }
        }

        // Walk Down
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_KeyBinds["MOVE_DOWN"])))
        {
            m_Player->Move(dt, 0.0f, 1.0f);
            if (m_Data->input.GetKeyTime())
            {
                m_Player->LoseExp(1);
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_Data->input.GetKeyTime())
        {
        }
    }
}

void GameState::UpdatePlayerGui(const float &dt)
{
    m_PlayerGui->Update(dt);
}

void GameState::UpdatePauseMenuButtons()
{
    if (m_PauseMenu->IsButtonPressed("Quit") && m_Data->input.GetKeyTime())
    {
        m_Data->machine.AddState(StateRef(new MainMenuState(m_Data)), true);
    }
}

void GameState::UpdateGui()
{
    std::stringstream ss;
    ss << "View Pos: " << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y << '\n'
       << "Grid Pos: " << m_Data->input.GetGridMousePosition().x << ", " << m_Data->input.GetGridMousePosition().y << '\n';
    m_CursorText.setString(ss.str());
    m_CursorText.setPosition(
        m_Data->input.GetViewMousePosition().x + gui::p2pX(1.f, m_Data->GfxSettings.resolution),
        m_Data->input.GetViewMousePosition().y);
}

void GameState::UpdateTileMap(const float &dt)
{
    m_TileMap->Update();
    // std::cout << "update TM" << '\n';
    m_TileMap->UpdateCollision(m_Player, dt);
}

void GameState::Update(const float &dt)
{
    m_Data->input.UpdateMousePosition(m_Data->window, &m_View);
    m_Data->input.UpdateKeyTime(dt);

    UpdateGui();

    if (!m_Paused)
    {
        UpdateView(dt);
        UpdateTileMap(dt);

        m_Player->Update(dt);
        UpdatePlayerGui(dt);
    }
    else
    {
        this->m_PauseMenu->Update(m_Data->input.GetWindowMousePosition());
        this->UpdatePauseMenuButtons();
    }
}

void GameState::Draw()
{
    // TODO: WORK WITH RENDER TEXTURE TO DISPLAY ALL AT ONCE
    m_Data->window.clear();

    m_Data->window.setView(m_View);
    m_TileMap->Draw(m_Data->window, m_Player->GetGridPosition(static_cast<int>(GRID_SIZE)), false);

    m_Player->Draw(m_Data->window, false);
    m_TileMap->RenderDeferred(m_Data->window);

    m_Data->window.setView(m_Data->window.getDefaultView());
    m_PlayerGui->Draw(m_Data->window);

    if (m_Paused)
    {
        m_PauseMenu->Draw(m_Data->window);
    }

    m_Data->window.setView(m_View);
    m_Data->window.draw(m_CursorText);
    // m_Data->window.draw( m_CursorText );

    m_Data->window.display();

    /*
    m_RenderTexture.clear();
    m_RenderTexture.setView( m_View );
    m_Map->Draw( m_RenderTexture );

    m_Player->Draw( m_RenderTexture );

    if ( m_Paused )
    {
        m_RenderTexture.setView( m_RenderTexture.getDefaultView() );
        m_PauseMenu->Draw( m_RenderTexture );
    } 
    m_RenderTexture.display();

    m_Data->window.clear();
    m_RenderSprite.setTexture( m_RenderTexture.getTexture() );
    m_Data->window.draw( m_RenderSprite );
    m_Data->window.display();
    */
}