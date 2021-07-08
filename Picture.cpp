#include "Picture.h"
#include "iostream"

Picture::Picture(string _path, int _ellipse_num, RenderWindow *_window)
{
	path = _path;
	ellipse_num = _ellipse_num;
	window = _window;

	srand(time(NULL));

	model.loadFromFile(path);

	size = Vector2f(model.getSize().x, model.getSize().y);

	originalTexture.loadFromImage(model);
	originalSprite.setTexture(originalTexture);

	originalSprite.setPosition((800 - size.x) / 2, 800 - size.y);

	current.create(size.x, size.y, Color::White);
	currentEvolved.create(size.x, size.y, Color::White);

	ellipse_array.push_back(Ellipse(randPosition(size), randSize(size / 2.f), randAngle(0, 360), randColor()));

	evolution_number = 0;

	similarity1 = 255;
	similarity2 = 255;
}

void Picture::getSimilarity()
{
	similarity1 = similarity2;
	similarity2 = 0;

	for (int i = 0; i < model.getSize().y; i++)
	{
		for (int j = 0; j < model.getSize().x; j++)
		{
			similarity2 = similarity2 + abs((float)model.getPixel(j, i).r - (float)currentEvolved.getPixel(j, i).r);
			similarity2 = similarity2 + abs((float)model.getPixel(j, i).g - (float)currentEvolved.getPixel(j, i).g);
			similarity2 = similarity2 + abs((float)model.getPixel(j, i).b - (float)currentEvolved.getPixel(j, i).b);
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
	cout << evolution_number << " EVO NUMBER " << endl;
	cout << ellipse_num << "ELLIPSE NUM" << endl;

	if (similarity2 >= similarity1) //got less similar
	{
		similarity2 = similarity1;
		evolution_number++;
		if (!used)
		{
			ellipse_array[i] = Ellipse(randPosition(size), randSize(size / 2.f), randAngle(0, 360), randColor());
			evolution_number = 0;
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

	if (evolution_number > 200)
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
		ellipse_array.push_back(Ellipse(randPosition(size), randSize(size / 2.f), randAngle(0, 360), randColor()));
		evolution_number = 0;
		used = false;
		ellipse_num += 1;
	}

	
}

void Picture::draw()
{
	texture.loadFromImage(currentEvolved);
	sprite.setTexture(texture);

	window->clear(Color::Blue);

	window->draw(sprite);
	window->draw(originalSprite);

	window->display();
}

int Picture::ellipse_number()
{
	return ellipse_num;
}

void Picture::save_picture(string filename)
{
	sprite.getTexture()->copyToImage().saveToFile(filename);
}

