#ifndef DROPDOWN_LIST_HPP
#define DROPDOWN_LIST_HPP

#include "../pch.cpp"
#include "../DEFINITIONS.hpp"

#include "Button.hpp"
#include "Helpers.hpp"

namespace gui
{
class DropDownList
{
private:
     sf::Font &m_Font;
     Button *m_ActiveElement;

     float keyTime;
     float keyTimeMax;

     bool m_ShowList;
     std::vector<Button *> m_List;

public:
     DropDownList(
         const float &x, const float &y,
         const float &width, const float &height,
         sf::Font &font, std::string list[],
         unsigned numOfElements, unsigned default_idx = 0);
     virtual ~DropDownList();

     // Accessors
     /*
         * getActiveElementId: Returns ID of active element in dropdown list
         */
     const short unsigned &getActiveElementId();

     // Functions
     /*
         * GetKeyTime: Key time will prevent spamming of one button
         */
     bool GetKeyTime();
     /*
         * UpdateKeyTime: Updates key time for Dropdown list
         */
     void UpdateKeyTime(const float &dt);

     /*
         * Update: Update time and mouse position for Dropdown list
         */
     void Update(const float &dt, const sf::Vector2f &mousePosition);
     /*
         * Draw: Draw objects on target
         */
     void Draw(sf::RenderTarget &target);
};
} // namespace gui

#endif // DROPDOWN_LIST_HPP