#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

float Distance(Vector2f const& u, Vector2f const& v);

Vector2f randPosition(Vector2f size);

float randAngle(int const& min, int const& max);

Vector2f randSize(Vector2f size);

Vector2f randVector2f(float const& min, float const& max);

float randFloat(float const& min, float const& max);

Color randColor();




