#include "Picture.h"
#include "iostream"

Picture::Picture(string _path, int _ellipse_nb, RenderWindow *_window)
{
	srand(time(NULL));

	evolution_number = 0;

	similarity1 = 255;
	similarity2 = 255;

	path = _path;
	ellipse_nb = _ellipse_nb;
	window = _window;

	model.loadFromFile(path);

	texture.loadFromImage(model);
	size = Vector2f(texture.getSize().x, texture.getSize().y);

	current.create(size.x, size.y, Color::Red);
	currentEvolved.create(size.x, size.y, Color::Blue);

	sprite.setTexture(texture);
	original.setTexture(texture);
	original.setPosition(500, 300);
	//sprite.setPosition((800 - size.x) / 2, 800 - size.y);

	//ellipse_array.push_back(Ellipse(randPosition(size), randSize(size / 2.f), randAngle(0, 360), Color::Yellow));
	ellipse_array.push_back(Ellipse(Vector2f(50, 50), Vector2f(12, 30), 66, Color::Yellow));

}

void Picture::getSimilarity()
{
	similarity1 = similarity2;
	similarity2 = 0;

	for (int i = 0; i < model.getSize().x; i++)
	{
		for (int j = 0; j < model.getSize().y; j++)
		{
			similarity2 = similarity2 + abs((float)model.getPixel(i, j).r - (float)currentEvolved.getPixel(i, j).r);
			similarity2 = similarity2 + abs((float)model.getPixel(i, j).g - (float)currentEvolved.getPixel(i, j).g);
			similarity2 = similarity2 + abs((float)model.getPixel(i, j).b - (float)currentEvolved.getPixel(i, j).b);
		}
	}
	similarity2 = similarity2 / (3 * float(model.getSize().x) * float(model.getSize().y) * 2.55);
}


void Picture::mutate()
{
	int i = ellipse_array.size() - 1;
	
	ellipse_current = ellipse_array[i];

	ellipse_array[i].move(randVector2f(-10, 10));
	ellipse_array[i].scale(randSize(randVector2f(-10, 10)));
	ellipse_array[i].rotate(randAngle(-10, 10));

	ellipse_array[i].createFocus();

	ellipse_array[i].color.r += randFloat(-10, 10);
	ellipse_array[i].color.g += randFloat(-10, 10);
	ellipse_array[i].color.b += randFloat(-10, 10);
	ellipse_array[i].color.a += randFloat(-10, 10);

	currentEvolved = current;
	ellipse_array[i].putEllipse(currentEvolved);

	getSimilarity();

	cout << similarity1 << endl;

	if (similarity2 >= similarity1) //got less similar
	{
		similarity2 = similarity1;
		evolution_number++;
		if (!used)
		{
			ellipse_array.push_back(Ellipse(randPosition(size), randSize(size / 2.f), randAngle(0, 360), Color::Yellow));
			evolution_number = 0;
			cout << "D" << endl;
		}
		else
		{
			ellipse_array[i] = ellipse_current;
		}
	}

	else // more similar
	{
		used = true;
		evolution_number = 0;
		draw();
	}

	if (evolution_number > 500)
	{
		if (!used)
		{
			ellipse_array.pop_back();
			currentEvolved = current;
		}
		else
		{
			currentEvolved = current;
			ellipse_current.putEllipse(currentEvolved);
			current = currentEvolved;
		}
		ellipse_array.push_back(Ellipse(randPosition(size), randSize(size / 2.f), randAngle(0, 360), Color::Green));
		evolution_number = 0;
		used = false;
	}
	
}

void Picture::draw()
{
	texture.loadFromImage(currentEvolved);
	sprite.setTexture(texture);

	window->clear(Color::White);

	window->draw(sprite);
	window->draw(original);

	window->display();
}

