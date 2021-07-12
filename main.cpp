#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include "Picture.h"
#include "iostream"
#include <direct.h>

using namespace std;
using namespace sf;

int getIndex(string word, char c);

int main() {
	string path;
	int check;
	string filename;

	check = _mkdir("Incremental Pictures");

	cout << "Pleae enter filename of picture (e.g. cat.jpg): ";
	cin >> path;

	//string path = "aruler.jpeg";

	// splicing filename into name and extension part
	int index = getIndex(path, '.');
	string substring = path.substr(0, index);
	string filetype = path.substr(index + 1);

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
			filename = "Incremental Pictures/" + substring + std::to_string(num / increment) + "." + filetype;
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