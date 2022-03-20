#pragma once
#include <SFML/Graphics.hpp>
#include "SudokuBox.hpp"

using sf::Texture;
using sf::Font;
using sf::RenderWindow;
using sf::Text;
using sf::Rect;
using sf::RectangleShape;
using sf::Clock;

class Game
{
public:
	Texture cellTexture;
	Texture cellTextureHighlight;
	Texture errorTexture;
	Texture clickedTexture;
	Texture solvebuttonTexture;
	Font numberFont;
	RenderWindow* window;
	static RenderWindow* swindow;
	SudokuBox* board;
	sf::FloatRect cursor;
	Clock timer;
	float time;
	bool loaded = false;

	void LoadAssets();
	void LoadWindow();
	void Run();
	Game();

	~Game();
};

