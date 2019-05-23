#include "GameSettingsState.hpp"
#include "MainMenuState.hpp"

// Initializers
void GameSettingsState::InitKeyBinds()
{
    Debug("SETTINGS STATE::Init Key bindings");

    std::fstream ifs(SETTINGS_STATE_KEY_BIND_FILEPATH);

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

void GameSettingsState::InitTextures()
{
}

void GameSettingsState::InitFonts()
{
    Debug("SETTINGS STATE::Init Fonts");
    m_Data->assets.LoadFont("Title Font", TITLE_FONT_FILEPATH);
    m_Data->assets.LoadFont("Button Font", BUTTON_FONT_FILEPATH);
    m_Data->assets.LoadFont("Text Font", TEXT_FONT_FILEPATH);
    m_Data->assets.LoadFont("Debug Font", DEBUG_FONT_FILEPATH);
}

void GameSettingsState::InitSounds()
{
    // Empty for now
}

void GameSettingsState::InitVariables()
{
    Debug("SETTINGS STATE::Init variables");

    m_Modes = sf::VideoMode::getFullscreenModes();

    clock.restart().asSeconds();
    movedLeft = false;
}

void GameSettingsState::InitGui()
{
    Debug("SETTINGS STATE::Init GUI");

    const sf::VideoMode &vm = m_Data->GfxSettings.resolution;

    // Background
    // TODO: Load some texture
    m_Background.setSize(sf::Vector2f(vm.width, vm.height));
    m_Background.setFillColor(sf::Color(30, 30, 30));

    // Initialize HUD
    m_Hud = new gui::HUD(m_Data);
    m_Hud->SetText("Title Font", "SETTINGS", TITLE_SIZE, (vm.width / 2.0f), vm.height / 5.0f);

    // Set Buttons
    m_Buttons["Home"] = new gui::Button(
        vm.width / 3.f - gui::p2pX(BUTTON_WIDTH_PREC, vm) / 2.f,
        vm.height - gui::p2pY(BUTTON_HEIGHT_PERC, vm) / 0.4f,
        gui::p2pX(BUTTON_WIDTH_PREC, vm), gui::p2pY(BUTTON_HEIGHT_PERC, vm),
        &m_Data->assets.GetFont("Button Font"), "Home", gui::calcCharSize(BUTTON_TEXT_SIZE_PERC, vm),
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR));

    m_Buttons["Apply"] = new gui::Button(
        2.f * vm.width / 3.f - gui::p2pX(BUTTON_WIDTH_PREC, vm) / 2.f,
        vm.height - gui::p2pY(BUTTON_HEIGHT_PERC, vm) / 0.4f,
        gui::p2pX(BUTTON_WIDTH_PREC, vm), gui::p2pY(BUTTON_HEIGHT_PERC, vm),
        &m_Data->assets.GetFont("Button Font"), "Apply", gui::calcCharSize(BUTTON_TEXT_SIZE_PERC, vm),
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR));

    m_Buttons["Back"] = new gui::Button(
        gui::p2pX(1.3, vm), gui::p2pY(1.3, vm),
        gui::p2pX(BUTTON_WIDTH_PREC, vm), gui::p2pY(BUTTON_HEIGHT_PERC, vm),
        &m_Data->assets.GetFont("Button Font"), "Back", gui::calcCharSize(BUTTON_TEXT_SIZE_PERC, vm),
        sf::Color(TEXT_IDLE_FILL_COLOR), sf::Color(TEXT_HOVER_FILL_COLOR), sf::Color(TEXT_ACTIVE_FILL_COLOR),
        sf::Color(BUTTON_IDLE_FILL_COLOR), sf::Color(BUTTON_HOVER_FILL_COLOR), sf::Color(BUTTON_ACTIVE_FILL_COLOR));

    std::vector<std::string> modes_str;
    for (auto &mode : m_Modes)
    {
        modes_str.emplace_back(std::to_string(mode.width) + " x " + std::to_string(mode.height));
    }

    m_DropdownList["Resolution"] = new gui::DropDownList(
        vm.width / 2.f - gui::p2pX(LIST_WIDTH_PERC, vm) / 2.f, gui::p2pY(37.f, vm),
        gui::p2pX(LIST_WIDTH_PERC, vm), gui::p2pY(LIST_HEIGHT_PERC, vm),
        m_Data->assets.GetFont("Text Font"),
        modes_str.data(), modes_str.size()

    );

    m_OptionsText.setFont(m_Data->assets.GetFont("Text Font"));
    m_OptionsText.setCharacterSize(gui::calcCharSize(LIST_TEXT_SIZE_PERC, vm));
    m_OptionsText.setPosition(gui::p2pX(26.f, vm), gui::p2pY(37.f, vm));
    m_OptionsText.setFillColor(sf::Color(255, 255, 255, 200));
    m_OptionsText.setString(
        "Resoultion\n\nFullscreen\n\nVsync\n\nAnti-Aliasing");
}

void GameSettingsState::ResetGui()
{
    Debug("SETTINGS STATE::Reset GUI");

    delete m_Hud;

    // Delete buttons
    for (auto it = m_Buttons.begin(); it != m_Buttons.end(); it++)
    {
        delete it->second;
    }
    m_Buttons.clear();

    // Delete Drop Down list
    for (auto it = m_DropdownList.begin(); it != m_DropdownList.end(); it++)
    {
        delete it->second;
    }
    m_DropdownList.clear();

    InitGui();
}

GameSettingsState::GameSettingsState(GameDataRef data) : m_Data(std::move(data))
{
}

GameSettingsState::~GameSettingsState()
{
    Debug("SETTINGS STATE::Destructor");

    delete m_Hud;
    for (const auto &button : m_Buttons)
    {
        delete button.second;
    }

    for (const auto &dl : m_DropdownList)
    {
        delete dl.second;
    }
    // delete m_DropdownList;
}

void GameSettingsState::Init()
{
    Debug("SETTINGS STATE::Initializing...");

    InitKeyBinds();
    InitTextures();
    InitSounds();
    InitFonts();
    InitVariables();
    InitGui();
}

void GameSettingsState::HandleInput(const float &dt)
{
    sf::Event event;

    while (m_Data->window.pollEvent(event))
    {
        if (sf::Event::Closed == event.type)
        {
            m_Data->machine.ClearStates();
            m_Data->machine.RemoveState();
            m_Data->window.close();
        }
    }

    // Go back to Main Menu on Button click or Escape
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(m_KeyBinds["QUIT"])) ||
        m_Buttons["Home"]->isPressed())
    {
        // If there are more than 1 state in stack, remove all but active one
        m_Data->machine.ClearStates();
        m_Data->machine.AddState(StateRef(new MainMenuState(m_Data)), true);
    }

    // Go back to last active state or home
    if (m_Buttons["Back"]->isPressed())
    {
        if (m_Data->machine.GetStatesCount() > 1)
        {
            m_Data->machine.RemoveState();
        }
        else
        {
            m_Data->machine.AddState(StateRef(new MainMenuState(m_Data)), true);
        }
    }

    if (m_Buttons["Apply"]->isPressed())
    {
        // TODO: for test, remove later
        m_Data->GfxSettings.resolution = m_Modes[m_DropdownList["Resolution"]->getActiveElementId()];
        m_Data->window.create(m_Data->GfxSettings.resolution, m_Data->GfxSettings.title, sf::Style::Default);
        ResetGui();
    }
}

void GameSettingsState::UpdateGui(const float &dt)
{
    for (auto button : m_Buttons)
    {
        button.second->Update(m_Data->input.GetViewMousePosition());
    }

    for (auto dl : m_DropdownList)
    {
        dl.second->Update(dt, m_Data->input.GetViewMousePosition());
    }
}

void GameSettingsState::Update(const float &dt)
{
    m_Data->input.UpdateMousePosition(m_Data->window);

    UpdateGui(dt);
}

void GameSettingsState::Draw()
{
    m_Data->window.clear();

    m_Data->window.draw(m_Background);

    m_Hud->Draw(m_Data->window);

    for (auto button : m_Buttons)
    {
        button.second->Draw(m_Data->window);
    }

    for (auto dl : m_DropdownList)
    {
        dl.second->Draw(m_Data->window);
    }

    m_Data->window.draw(m_OptionsText);

    // Draw coordinates on mouse pointer for debugging
    sf::Text mouseText;
    mouseText.setPosition(m_Data->input.GetViewMousePosition().x + 20, m_Data->input.GetViewMousePosition().y);
    mouseText.setFont(m_Data->assets.GetFont("Debug Font"));
    mouseText.setCharacterSize(20);
    std::stringstream ss;
    ss << m_Data->input.GetViewMousePosition().x << ", " << m_Data->input.GetViewMousePosition().y;
    mouseText.setString(ss.str());
    m_Data->window.draw(mouseText);

    m_Data->window.display();
}