#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Picture.h"
#include "iostream"

using namespace std;
using namespace sf;

int getIndex(string word, char c);

int main() {
	string path = "aruler.jpeg";

	int index = getIndex(path, '.');
	
	string substring = path.substr(0, index);

	cout << substring << endl;

	string filename;
	string jpg = ".jpg";
	string jpeg = ".jpeg";
	string png = ".png";

	int increment = 25;

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
			filename = "Incremental Pictures/a" + substring + std::to_string(num / increment) + jpeg;
			cout << filename << endl;
			picture.save_picture(filename);
		}
	}
	return 0;
}

int getIndex(string word, char c)
{
	int length = word.length();
	for (int i = 0; i < length; i++)
	{
		if (word[i] == c) {
			return i;
		}
	}
}