#include "UsefulFunctions.h"

float Distance(Vector2f const& u, Vector2f const& v)
{
	return sqrt(pow(u.x - v.x, 2) + pow(u.y - v.y, 2));
}

Vector2f randPosition(Vector2f size)
{
	return Vector2f(rand() % (int)size.x + 1, rand() % (int)size.y + 1);
}

float randAngle(int const& min, int const& max)
{
	return rand() % max + min;
}

Vector2f randSize(Vector2f size)
{
	return Vector2f((float)(rand() / (float)RAND_MAX) * size.x, (float)(rand() / (float)RAND_MAX) * size.y);
}

Vector2f randVector2f(float const& min, float const& max)
{
	return Vector2f((min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1)), (min + 1) + (((float)rand()) / (float)RAND_MAX) * (max - (min + 1)));
}

float randFloat(float const& min, float const& max)
{
	return (float)rand() / RAND_MAX * (max - min) + min;
}

Color randColor()
{
	return Color::Color((float)rand() / RAND_MAX * 255, (float)rand() / RAND_MAX * 255, (float)rand() / RAND_MAX * 255, (float)rand() / RAND_MAX * 255);
}
