#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"

namespace gui
{

class Button
{
private:
    ButtonState m_ButtonState;
    unsigned short m_Id;

    sf::RectangleShape m_Shape;
    sf::Font *m_Font;
    sf::Text m_Text;

    sf::Color m_TextIdleColor;
    sf::Color m_TextHoverColor;
    sf::Color m_TextActiveColor;

    sf::Color m_BtnIdleColor;
    sf::Color m_BtnHoverColor;
    sf::Color m_BtnActiveColor;

    sf::Color m_OutlineIdleColor;
    sf::Color m_OutlineHoverColor;
    sf::Color m_OutlineActiveColor;

public:
    Button(
        const float &x, const float &y, const float &width, const float &height,
        sf::Font *font, std::string text, unsigned character_size,
        sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
        sf::Color idle_color, sf::Color hover_color, sf::Color active_color,
        sf::Color outline_idle_color = sf::Color::Transparent, sf::Color outline_hover_color = sf::Color::Transparent, sf::Color outline_active_color = sf::Color::Transparent,
        short unsigned id = 0);

    virtual ~Button();

    // sf::RectangleShape& GetButton();

    // Accessors
    bool isPressed() const;
    const std::string getText() const;
    const short unsigned &getId() const;
    const sf::RectangleShape &GetButton() const;

    // Modifiers
    void setText(std::string text);
    void setId(const short unsigned id);

    void Update(const sf::Vector2f &mousePosition);

    // Draw the button
    void Draw(sf::RenderTarget &target);
};

} // namespace gui
#endif // BUTTON_HPP