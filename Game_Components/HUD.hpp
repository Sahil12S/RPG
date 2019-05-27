#ifndef HUD_HPP
#define HUD_HPP

#include "../pch.cpp"

#include "../Game.hpp"

namespace gui
{
class HUD
{
private:
    GameDataRef m_Data;
    sf::Font font;
    std::string text;
    sf::Vector2f offset;

    sf::Text m_Text;

public:
    HUD(GameDataRef data);
    virtual ~HUD();

    void SetText(const std::string &fontName, const std::string &text, const float &size, const float &x, const float &y);

    const std::string &GetText() const;

    void Move(const std::string &font, const float &x, const float &y);
    void Reset();

    void UpdateText(const std::string text);
    void Draw(sf::RenderTarget &target);
};
} // namespace gui
#endif // HUD_HPP