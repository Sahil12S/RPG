#include "TextureSelector.hpp"

namespace gui
{
TextureSelector::TextureSelector(
    const float &x, const float &y, const float &width, const float &height,
    const float &grid_size, const sf::Texture *texture_sheet,
    sf::Font &font, std::string text) : m_KeyTime(0.f), m_KeyTimeMax(1.f)
{
    m_GridSize = grid_size;
    m_Active = false;
    m_Hidden = false;
    float offset = grid_size;

    m_Bounds.setSize(sf::Vector2f(width, height));
    m_Bounds.setPosition(x + offset, y);
    m_Bounds.setFillColor(sf::Color(50, 50, 50, 100));
    m_Bounds.setOutlineThickness(1.f);
    m_Bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

    m_Sheet.setTexture(*texture_sheet);
    m_Sheet.setPosition(x + offset, y);

    /*
         * Check if our bounds is well within available size of sheet
         * If it is, then set the texture
         */

    if (m_Sheet.getGlobalBounds().width > m_Bounds.getGlobalBounds().width)
    {
        m_Sheet.setTextureRect(sf::IntRect(0, 0, m_Bounds.getGlobalBounds().width, m_Sheet.getGlobalBounds().height));
    }

    if (m_Sheet.getGlobalBounds().height > m_Bounds.getGlobalBounds().height)
    {
        m_Sheet.setTextureRect(sf::IntRect(0, 0, m_Sheet.getGlobalBounds().width, m_Bounds.getGlobalBounds().height));
    }

    m_Selector.setSize(sf::Vector2f(m_GridSize, m_GridSize));
    m_Selector.setPosition(x + offset, y);
    m_Selector.setFillColor(sf::Color::Transparent);
    m_Selector.setOutlineThickness(1.f);
    m_Selector.setOutlineColor(sf::Color::Red);

    m_TextuerRect.width = static_cast<int>(m_GridSize);
    m_TextuerRect.height = static_cast<int>(m_GridSize);

    // Drawing the button
    m_HideBtn = new gui::Button(
        y, x, 50.f, 50.f,
        &font, text, 14,
        sf::Color(LIST_TEXT_IDLE_FILL_COLOR), sf::Color(LIST_TEXT_HOVER_FILL_COLOR), sf::Color(LIST_TEXT_ACTIVE_FILL_COLOR),
        sf::Color(LIST_IDLE_FILL_COLOR), sf::Color(LIST_HOVER_FILL_COLOR), sf::Color(LIST_ACTIVE_FILL_COLOR));
}

TextureSelector::~TextureSelector()
{
    delete m_HideBtn;
}

bool TextureSelector::GetActive() const
{
    return m_Active;
}

bool TextureSelector::GetKeyTime()
{
    if (m_KeyTime >= m_KeyTimeMax)
    {
        m_KeyTime = 0.f;
        return true;
    }
    return false;
}

const sf::IntRect &TextureSelector::GetTextureRect() const
{
    return m_TextuerRect;
}

void TextureSelector::UpdateKeyTime(const float &dt)
{
    if (m_KeyTime < m_KeyTimeMax)
    {
        m_KeyTime += 10.f * dt;
    }
}

void TextureSelector::Update(const float &dt, const sf::Vector2i &mousePostion)
{
    UpdateKeyTime(dt);
    m_HideBtn->Update(static_cast<sf::Vector2f>(mousePostion));

    if (m_HideBtn->isPressed() && GetKeyTime())
    {
        m_Hidden = !m_Hidden;
    }

    if (!m_Hidden)
    {
        if (m_Bounds.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePostion)))
        {
            m_Active = true;
        }
        else
        {
            m_Active = false;
        }

        if (m_Active)
        {
            m_MousePosGrid.x = (mousePostion.x - static_cast<int>(m_Bounds.getPosition().x)) / static_cast<unsigned>(m_GridSize);
            m_MousePosGrid.y = (mousePostion.y - static_cast<int>(m_Bounds.getPosition().y)) / static_cast<unsigned>(m_GridSize);

            m_Selector.setPosition(
                m_Bounds.getPosition().x + m_MousePosGrid.x * m_GridSize,
                m_Bounds.getPosition().y + m_MousePosGrid.y * m_GridSize);

            m_TextuerRect.left = static_cast<int>(m_Selector.getPosition().x - static_cast<int>(m_Bounds.getPosition().x));
            m_TextuerRect.top = static_cast<int>(m_Selector.getPosition().y - static_cast<int>(m_Bounds.getPosition().y));
        }
    }
}

void TextureSelector::Draw(sf::RenderTarget &target)
{
    m_HideBtn->Draw(target);

    if (!m_Hidden)
    {
        target.draw(m_Bounds);
        target.draw(m_Sheet);
        if (m_Active)
        {
            target.draw(m_Selector);
        }
    }
}
} // namespace gui