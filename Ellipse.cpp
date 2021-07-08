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

	createFocus();

}

void Ellipse::createFocus()
{
	
	float hypotenuse = max(size.x, size.y);
	float smaller = min(size.x, size.y);

	a = max(size.x, size.y);

	float centerToFocus = sqrt(pow(hypotenuse, 2) - pow(smaller, 2));

	float radians = angle * 3.14159265359 / 180.f;

	// rotate

	shift = Vector2f((centerToFocus * cos(radians)), (centerToFocus * sin(radians)));
	
	//float c = sqrt(size.x * size.x - size.y * size.y);
	
	//shift = Vector2f(c * cos(radians), c * sin(radians));
	focus1 = position + shift;
	focus2 = position - shift;
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
	for (int i = max(position.y-a, 0.f); i < min(float(image.getSize().y), position.y + a); i++)
	{
		for (int j = max(position.x - a, 0.f); j < min(float(image.getSize().x), position.x+a); j++)
		{
			if (Distance(focus1, Vector2f(j, i)) + Distance(focus2, Vector2f(j, i)) < size.x * 2)
			{
				/*
				cout << size.x * 2 << " SIZE" << endl;
				cout << Distance(focus1, Vector2f(j, i)) + Distance(focus2, Vector2f(j, i)) << " TOTAL" << endl;
				cout << focus1.x << " " << focus1.y << " | " << focus2.x << " " << focus2.y << " FOCUS" << endl;
				cout << position.x << " " << position.y << " POSITION" << endl;
				cout << j << " " << i << " current coords" << endl;

				*/

				image.setPixel(j, i, Color::Color(color.a / 255.f * color.r + (1 - color.a / 255.f) * image.getPixel(j, i).r,
										color.a / 255.f * color.g + (1 - color.a / 255.f) * image.getPixel(j, i).g,
										color.a / 255.f * color.b + (1 - color.a / 255.f) * image.getPixel(j, i).b,
										255));

				//cout << j << " " << i << " put coords" << endl;
			}
		}
	}
}
