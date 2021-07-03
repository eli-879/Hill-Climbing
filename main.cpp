#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Picture.h"
#include "iostream"

using namespace std;
using namespace sf;

int main() {
	string path = "5head.png";

	const int height = 800;
	const int width = 800;

	RenderWindow window(VideoMode(width, height), "Title");

	Event event;

	Picture picture(path, 1, &window);

	while (window.isOpen()) 
	{
		while (window.pollEvent(event)) 
		{
			if (event.type == sf::Event::Closed) 
			{
				window.close();
			}

			picture.mutate();

		}
	}
	return 0;
}