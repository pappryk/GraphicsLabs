#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "Circle.h"
#include "CircleRGB.h"
#include "CircleHSV.h"
#include "CircleHSL.h"
#include "CircleCMY.h"

void DrawToTexture(sf::RenderTexture& texture, CircleHSL& circleHSL, CircleHSV& circleHSV, CircleCMY& circleCMY, CircleRGB& circleRGB, float scaleColor);

