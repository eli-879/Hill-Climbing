#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Picture.h"
#include "iostream"

using namespace std;
using namespace sf;

int main() {
	string path = "aruler.jpeg";

	string filename;
	string jpg = ".jpg";
	string jpeg = ".jpeg";
	string png = ".png";

	int increment = 50;

	const int height = 800;
	const int width = 800;

	RenderWindow window(VideoMode(width, height), "Title");

	Picture picture(path, 1, &window);

	while (window.isOpen()) 
	{
		picture.mutate();
		int num = picture.ellipse_number();
		if (num % increment == 0)
		{
			filename = "Incremental Pictures/aruler" + std::to_string(num / increment) + jpeg;
			picture.save_picture(filename);
		}
	}
	return 0;
}