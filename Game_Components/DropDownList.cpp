#include "DropDownList.h"

namespace gui
{
DropDownList::DropDownList(
    const float &x, const float &y,
    const float &width, const float &height,
    sf::Font &font, std::string list[],
    unsigned numOfElements, unsigned default_idx) : m_Font(font), keyTime(0.f), keyTimeMax(1.f), m_ShowList(false)
{
    m_ActiveElement = new gui::Button(
        x, y, width, height,
        &m_Font, list[default_idx], 35,
        sf::Color(LIST_TEXT_IDLE_FILL_COLOR), sf::Color(LIST_TEXT_HOVER_FILL_COLOR), sf::Color(LIST_TEXT_ACTIVE_FILL_COLOR),
        sf::Color(LIST_IDLE_FILL_COLOR), sf::Color(LIST_HOVER_FILL_COLOR), sf::Color(LIST_ACTIVE_FILL_COLOR),
        sf::Color(OUTLINE_COLOR_IDLE), sf::Color(OUTLINE_COLOR_HOVER), sf::Color(OUTLINE_COLOR_ACTIVE));

    // outlineColor = { sf::Color(  ),
    //             sf::Color(  ),
    //             sf::Color( 2) };

    for (size_t i = 0; i < numOfElements; i++)
    {
        m_List.emplace_back(
            new gui::Button(
                x, y + ((i + 1) * height), width, height,
                &m_Font, list[i], 35,
                sf::Color(LIST_TEXT_IDLE_FILL_COLOR), sf::Color(LIST_TEXT_HOVER_FILL_COLOR), sf::Color(LIST_TEXT_ACTIVE_FILL_COLOR),
                sf::Color(LIST_IDLE_FILL_COLOR), sf::Color(LIST_HOVER_FILL_COLOR), sf::Color(LIST_ACTIVE_FILL_COLOR),
                sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(20, 20, 20, 0),
                i));
    }
}

DropDownList::~DropDownList()
{
    delete m_ActiveElement;
    for (size_t i = 0; i < m_List.size(); i++)
    {
        delete m_List[i];
    }
}

const short unsigned &DropDownList::getActiveElementId()
{
    return m_ActiveElement->getId();
}

bool DropDownList::GetKeyTime()
{
    if (keyTime >= keyTimeMax)
    {
        keyTime = 0.f;
        return true;
    }
    return false;
}

void DropDownList::UpdateKeyTime(const float &dt)
{
    if (keyTime < keyTimeMax)
    {
        keyTime += 10.f * dt;
    }
}

void DropDownList::Update(const float &dt, const sf::Vector2f &mousePosition)
{
    UpdateKeyTime(dt);
    m_ActiveElement->Update(mousePosition);

    // Show and hide the list
    if (m_ActiveElement->isPressed() && GetKeyTime())
    {
        m_ShowList = !m_ShowList;
    }

    // Set current resolution on click
    if (m_ShowList)
    {
        for (auto &i : m_List)
        {
            i->Update(mousePosition);

            if (i->isPressed() && GetKeyTime())
            {
                m_ShowList = false;
                m_ActiveElement->setText(i->getText());
                m_ActiveElement->setId(i->getId());
            }
        }
    }
}

void DropDownList::Draw(sf::RenderTarget &target)
{
    m_ActiveElement->Draw(target);

    if (m_ShowList)
    {
        for (auto &i : m_List)
        {
            i->Draw(target);
        }
    }
}
} // namespace gui