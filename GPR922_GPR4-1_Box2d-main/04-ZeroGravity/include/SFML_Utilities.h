#pragma once
#include "SFML/Graphics.hpp"

#define _MATH_DEFINES_DEFINED
#define _USE_MATH_DEFINES // for C++
#include <cmath>

#define M_PI 3.14159265358979323846
constexpr float epsilon = 0.0001f;

float dotProduct(sf::Vector2f vec1_, sf::Vector2f vec2_);

float determinant(sf::Vector2f vec1_, sf::Vector2f vec2_);

float vecLength(sf::Vector2f vec_);

float vecDistance(sf::Vector2f p1, sf::Vector2f p2);

float vecAngle(sf::Vector2f vec1_, sf::Vector2f vec2_);

float degToRad(float degrees_);

float radToDeg(float radians_);
