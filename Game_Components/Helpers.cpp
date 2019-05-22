#include "Helpers.h"

namespace gui
{

float p2pX(const float &perc, const sf::VideoMode &resolution)
{
    return std::floor(static_cast<float>(resolution.width * (perc / 100)));
}

float p2pY(const float &perc, const sf::VideoMode &resolution)
{
    return std::floor(static_cast<float>(resolution.height * (perc / 100)));
}

float calcCharSize(const float &perc, const sf::VideoMode &resolution)
{
    return std::floor(static_cast<float>((resolution.height + resolution.width) / perc));
}

} // namespace gui