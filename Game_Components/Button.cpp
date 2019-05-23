#include "Button.h"

namespace gui
{

Button::Button(const float &x, const float &y, const float &width, const float &height,
               sf::Font *font, std::string text, unsigned character_size,
               sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
               sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
               sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
               short unsigned id) : m_Font(font)
{
    m_ButtonState = ButtonState::eBtnIdle;
    m_Id = id;

    m_Shape.setPosition(sf::Vector2f(x, y));
    m_Shape.setSize(sf::Vector2f(width, height));
    m_Shape.setFillColor(m_BtnIdleColor);
    m_Shape.setOutlineThickness(1.f);
    m_Shape.setOutlineColor(outline_idle_color);

    m_Text.setFont(*m_Font);
    m_Text.setString(text);
    m_Text.setFillColor(text_idle_color);
    m_Text.setCharacterSize(character_size);
    m_Text.setPosition(
        m_Shape.getPosition().x + m_Shape.getGlobalBounds().width / 2.0f - m_Text.getGlobalBounds().width / 2.0f,
        m_Shape.getPosition().y);

    m_TextIdleColor = text_idle_color;
    m_TextHoverColor = text_hover_color;
    m_TextActiveColor = text_active_color;

    m_BtnIdleColor = idle_color;
    m_BtnHoverColor = hover_color;
    m_BtnActiveColor = active_color;

    m_OutlineIdleColor = outline_idle_color;
    m_OutlineHoverColor = outline_hover_color;
    m_OutlineActiveColor = outline_active_color;
}

Button::~Button()
{
}

// Accessors
bool Button::isPressed() const
{
    if (m_ButtonState == ButtonState::eBtnActive)
    {
        return true;
    }
    return false;
}

const std::string Button::getText() const
{
    return m_Text.getString();
}

const short unsigned &Button::getId() const
{
    return m_Id;
}

const sf::RectangleShape &Button::GetButton() const
{
    return m_Shape;
}

// Modifiers
void Button::setText(std::string text)
{
    m_Text.setString(text);
}

void Button::setId(const short unsigned id)
{
    m_Id = id;
}

// Functions
void Button::Update(const sf::Vector2f &mousePosition)
{
    // Update button hover with mouse position
    m_ButtonState = ButtonState::eBtnIdle;

    // Hover
    if (m_Shape.getGlobalBounds().contains(mousePosition))
    {
        m_ButtonState = ButtonState::eBtnHover;

        // Active
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            m_ButtonState = ButtonState::eBtnActive;
        }
    }

    // Set the button color
    switch (m_ButtonState)
    {
    case ButtonState::eBtnIdle:
        m_Shape.setFillColor(m_BtnIdleColor);
        m_Text.setFillColor(m_TextIdleColor);
        m_Text.setOutlineColor(m_OutlineIdleColor);
        break;
    case ButtonState::eBtnHover:
        m_Shape.setFillColor(m_BtnHoverColor);
        m_Text.setFillColor(m_TextHoverColor);
        m_Text.setOutlineColor(m_OutlineHoverColor);
        break;
    case ButtonState::eBtnActive:
        m_Shape.setFillColor(m_BtnActiveColor);
        m_Text.setFillColor(m_TextActiveColor);
        m_Text.setOutlineColor(m_OutlineActiveColor);
        break;

    default:
        m_Shape.setFillColor(sf::Color::Red);
        m_Text.setFillColor(sf::Color::Blue);
        m_Text.setOutlineColor(sf::Color::Green);
        break;
    }
}

void Button::Draw(sf::RenderTarget &target)
{
    target.draw(m_Shape);
    target.draw(m_Text);
}

} // namespace gui