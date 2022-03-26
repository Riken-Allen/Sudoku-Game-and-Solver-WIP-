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
	// Textures
	Texture cellTexture;
	Texture cellTextureHighlight;
	Texture errorTexture;
	Texture clickedTexture;
	Texture solvebuttonTexture;
	// Font
	Font numberFont;
	// Window
	RenderWindow* window;
	static RenderWindow* swindow;

	SudokuBox* board;

	// Cursor
	sf::FloatRect cursor;
	// Timer
	Clock timer;
	float time;
	bool loaded = false;

	void LoadAssets();
	void LoadWindow();
	void Run();
	Game();

	~Game();
};

