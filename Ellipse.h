#pragma once
#include <SFML/Graphics.hpp>
#include "UsefulFunctions.h"

using namespace std;
using namespace sf;

class Ellipse
{
public:
	Ellipse();
	Ellipse(Vector2f const& _position, Vector2f const& _size, float const& _angle, Color const& _color);

	void createFocus();
	void move(Vector2f _vector);
	void rotate(float _angle);
	void scale(Vector2f _scale);
	void putEllipse(Image &image);

	Color color;


private:
	Vector2f position;
	Vector2f size;
	float angle;
	

	Vector2f shift;
	Vector2f focus1;
	Vector2f focus2;



};