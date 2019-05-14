#ifndef TEXTURE_SELECTOR_H
#define TEXTURE_SELECTOR_H

#include "../pch.cpp"
#include "../Game.h"
#include "Button.h"

namespace gui
{
    class TextureSelector
    {
        private:
            float m_KeyTime;
            const float m_KeyTimeMax;
            // Size of each tile
            float m_GridSize;
            
            // To manage texture selector
            bool m_Active;
            bool m_Hidden;

            // Button to toggle texture selector window
            gui::Button* m_HideBtn;
            // Bounds of texture selector area
            sf::RectangleShape m_Bounds;
            sf::Sprite m_Sheet;
            // Rectangle to select each tile
            sf::RectangleShape m_Selector;
            // Mouse position in grid
            sf::Vector2u m_MousePosGrid;
            sf::IntRect m_TextuerRect;
            

        public:
            TextureSelector(
                const float& x, const float& y, const float& width, const float& height,
                const float& grid_size, const sf::Texture* texture_sheet,
                sf::Font& font, std::string text
            );
            virtual ~TextureSelector();

            // Accessors
            bool GetActive() const;
            const sf::IntRect& GetTextureRect() const;
            bool GetKeyTime();

            // Functions
            void UpdateKeyTime( const float& dt );
            void Update( const float& dt, const sf::Vector2i& mousePostion );
            void Draw( sf::RenderTarget& target );
    };
}
#endif // TEXTURE_SELECTOR_H