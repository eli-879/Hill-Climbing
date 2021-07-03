#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <time.h>
#include "Ellipse.h"
#include "UsefulFunctions.h"


using namespace std;
using namespace sf;

class Picture
{
public:
	Picture(string _path, int _ellipse_nb, RenderWindow *_window);

	void getSimilarity();
	void mutate();
	void draw();

	Image model;
	Image current;
	Image currentEvolved;

	Texture texture;

	Sprite sprite;
	Sprite original;

private:
	RenderWindow* window;
	string path;
	int ellipse_nb;
	Vector2f size;

	Ellipse ellipse_current;
	vector<Ellipse> ellipse_array;

	int evolution_number;
	float similarity1;
	float similarity2;

	bool used;


};