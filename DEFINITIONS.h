#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#ifndef DEBUG
#define Debug(x) std::cout << "\033[34m[DEBUG] \033[0m" << x << std::endl;
#else
#define Debug(x)
#endif

#ifndef ERROR
#define Error(err, name) std::cout << "\033[31m[ERROR] \033[0m" << err << " " << name << std::endl;
#else
#define Error(err)
#endif

// Textures
#define GAME_BACKGROUND_FILEPATH "../Resources/img/background.png"
#define PLAYER_SHEET_FILEPATH "../Resources/img/player2.png"
#define TILES_TEXTURE_FILEPATH "../Resources/img/tilesheet.png"
#define CALLOUT_TEXTURE_FILEPATH "../Resources/img/callout.png"

// Fonts
#define TITLE_FONT_FILEPATH "../Resources/font/Good_Brush.otf"
#define BUTTON_FONT_FILEPATH "../Resources/font/Twopath_Regular.otf"
#define TEXT_FONT_FILEPATH "../Resources/font/Marlboro.ttf"
#define DEBUG_FONT_FILEPATH "../Resources/font/Alexandria.ttf"

// Key binds
#define GENERAL_KEY_BIND_FILEPATH "../Config/KeyBindings/KeyBinds.ini"
#define GAMESTATE_KEY_BIND_FILEPATH "../Config/KeyBindings/GameStateKeyBinds.ini"
#define MAIN_MENU_KEY_BIND_FILEPATH "../Config/KeyBindings/MainMenuKeyBinds.ini"
#define SETTINGS_STATE_KEY_BIND_FILEPATH "../Config/KeyBindings/SettingsStateKeyBinds.ini"
#define PAUSE_STATE_KEY_BIND_FILEPATH "../Config/KeyBindings/PauseStateKeyBinds.ini"
#define EDITOR_STATE_KEY_BIND_FILEPATH "../Config/KeyBindings/EditorStateKeyBinds.ini"

/**
 * Button Percentages
 * Larger the value, larger the buttons
 */
#define BUTTON_WIDTH_PREC 10.4
#define BUTTON_HEIGHT_PERC 6.5
/**
 * Dropdown List Percentages
 * Larger the value, larger the buttons
 */
#define LIST_WIDTH_PERC 9.2
#define LIST_HEIGHT_PERC 4.75

/**
 * Text size percentages
 * Smaller the value, larger the text
 */
#define BUTTON_TEXT_SIZE_PERC 60
#define LIST_TEXT_SIZE_PERC 75

// For Buttons
#define TEXT_IDLE_FILL_COLOR 170, 170, 170, 200
#define TEXT_HOVER_FILL_COLOR 250, 250, 250, 250
#define TEXT_ACTIVE_FILL_COLOR 20, 20, 20, 50

#define BUTTON_IDLE_FILL_COLOR 70, 70, 70, 0
#define BUTTON_HOVER_FILL_COLOR 150, 150, 150, 0
#define BUTTON_ACTIVE_FILL_COLOR 20, 20, 20, 0

// For Dropdown list
#define LIST_TEXT_IDLE_FILL_COLOR 225, 225, 225, 150
#define LIST_TEXT_HOVER_FILL_COLOR 250, 250, 250, 255
#define LIST_TEXT_ACTIVE_FILL_COLOR 20, 20, 20, 50

#define LIST_IDLE_FILL_COLOR 40, 40, 40, 150
#define LIST_HOVER_FILL_COLOR 150, 150, 150, 200
#define LIST_ACTIVE_FILL_COLOR 20, 20, 20, 150

#define OUTLINE_COLOR_IDLE 255, 255, 255, 200
#define OUTLINE_COLOR_HOVER 255, 255, 255, 255
#define OUTLINE_COLOR_ACTIVE 20, 20, 20, 50

#define SPLASH_STATE_SHOW_TIME 0.5f

// Tile variables
#define TITLE_SIZE 80
#define SCALE_X 2.f
#define SCALE_Y 2.f
#define TILE_WIDTH 50
#define TILE_HEIGHT 40

// Tile Map variables
#define GRID_SIZE 64.f
#define MAP_WIDTH 100
#define MAP_HEIGHT 100
#define LAYERS 1

// For Player
#define PLAYER_MOVEMENT_SPEED 150.0f
#define WALK_ANIMATION_DURATION 12.f

// For View
#define CAMERA_SPEED 200.f

enum class ButtonState
{
    eBtnIdle,
    eBtnHover,
    eBtnActive
};

enum class MovementStates
{
    eIdle,
    eMoving,
    eMovingLeft,
    eMovingRight,
    eMovingUp,
    eMovingDown,
};

enum class AttackFace
{
    eNone,
    eAttackFaceLeft,
    eAttackFaceRight
};

enum class PlayerStates
{
    eAlive,
    eDead
};

enum class TileType
{
    eDefault,
    eDamaging,
    eDoodad,
};

#endif // DEFINITIONS_H