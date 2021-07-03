#include <SFML/Graphics.hpp>
#include "Ellipse.h"
#include "iostream"


using namespace std;
using namespace sf;

Ellipse::Ellipse()
{
}

Ellipse::Ellipse(Vector2f const& _position, Vector2f const& _size, float const& _angle, Color const& _color)
{
	position = _position; // location of center of ellipse
	size = _size / 2.f; //height and width of ellipse divided by 2 for ease of calculation for future
	angle = _angle; // angle at which ellipse is put on image
	color = _color;

}

void Ellipse::createFocus()
{
	float c = sqrt(size.x * size.x + size.y * size.y);
	float radians = angle * 3.14159265359 / 180.f;
	shift = Vector2f(c * cos(radians), c * sin(radians));
	focus1 = position + shift;
	focus2 = position - shift;

	cout << focus1.x << "asdf " << endl;

}

void Ellipse::move(Vector2f _vector)
{
	position = position + _vector;
}

void Ellipse::rotate(float _angle)
{
	angle = angle + _angle;
}

void Ellipse::scale(Vector2f _scale)
{
	size = size + _scale;
}

void Ellipse::putEllipse(Image &image)
{
	for (int i = max(position.x-size.x, 0.f); i < min(float(image.getSize().x), position.x + size.x); i++)
	{
		for (int j = max(position.y - size.y, 0.f); j < min(float(image.getSize().y), position.y+size.y); j++)
		{
			if (Distance(focus1, Vector2f(i, j)) + Distance(focus2, Vector2f(i, j)) < size.x * 2)
			{
				image.setPixel(i, j, Color::Yellow);
			}
		}
	}
}
