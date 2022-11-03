#define _USE_MATH_DEFINES
#include <math.h>

#include "SFML/Graphics.hpp"

static class SFML_Utilities{

public:
  static float vecLength(sf::Vector2f vec_) {
    return sqrt(vec_.x * vec_.x + vec_.y * vec_.y);
  }

  static float vecAngle(sf::Vector2f vec1_, sf::Vector2f vec2_) {
      return atan2(determinant(vec1_, vec2_), dotProduct(vec1_, vec2_));  // atan2(y, x) or atan2(sin, cos)
  }

  // dot product between vec1[x1, y1] and vec2[x2, y2]
  static float dotProduct(sf::Vector2f vec1_, sf::Vector2f vec2_) {
     return vec1_.x * vec2_.x + vec1_.y * vec2_.y;
  }

  // determinant between vec1[x1, y1] and vec2[x2, y2]
  static float determinant(sf::Vector2f vec1_, sf::Vector2f vec2_) {
      return vec1_.x * vec2_.y - vec1_.y * vec2_.x;
  }

  static float degToRad(float degrees_) {
      return (degrees_ * M_PI / 180.0f);
  }

  static float radToDeg(float radians_) {
      return (radians_ / M_PI * 180.0f);
      
  }

};
