#ifndef GRAPHICS_SETTINGS_HPP
#define GRAPHICS_SETTINGS_HPP

#include "../pch.cpp"

class GraphicsSettings
{
private:
public:
    GraphicsSettings();

    // Variables
    std::string title;
    sf::VideoMode resolution;
    bool fullscreen;
    bool verticalSync;
    unsigned frameRateLimit;
    sf::ContextSettings contextSettings;
    std::vector<sf::VideoMode> videoModes;

    void SaveToFile(const std::string &path);
    void LoadFromFile(const std::string &path);
};

#endif // GRAPHICS_SETTINGS_HPP