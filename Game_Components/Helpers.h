#ifndef HELPERS_H
#define HELPERS_H

#include "../pch.h"
#include "../DEFINITIONS.h"

namespace gui
{
/**
 * Coverts a percentage value to pixels relative to screen in x-axis
 * 
 * @param perc: percentage value
 * @param resolution: resolution of screen
 * @return calculated float pixel value
*/
float p2pX(const float &prec, const sf::VideoMode &resolution);

/**
 * Coverts a percentage value to pixels relative to screen in y-axis
 * 
 * @param perc: percentage value
 * @param resolution: resolution of screen
 * @return calculated float pixel value
*/
float p2pY(const float &prec, const sf::VideoMode &resolution);

/**
 * Coverts a percentage value of character size to pixels relative to screen resolution
 * 
 * @param perc: percentage value
 * @param resolution: resolution of screen
 * @return calculated float pixel value
*/
float calcCharSize(const float &perc, const sf::VideoMode &resolution);

} // namespace gui
#endif // HELPERS_H