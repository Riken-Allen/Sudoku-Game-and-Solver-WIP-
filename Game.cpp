#include "Game.hpp"
#include <iostream>

RenderWindow* Game::swindow;
void Game::LoadAssets() {



	cellTexture.loadFromFile("tileGrey_01.png");

	if (!cellTextureHighlight.loadFromFile("tileGreen_01.png"));

	if (!clickedTexture.loadFromFile("tileBlue_01.png"));

	if (!errorTexture.loadFromFile("tileRed_01.png"));

	if (!solvebuttonTexture.loadFromFile("SolveButton.png")) {
		std::cout << "Failed to load solve button" << std::endl;
	}
	if (!numberFont.loadFromFile("cuyabra.otf"));

	board = new SudokuBox();
	board->initialize(&cellTexture, &cellTextureHighlight , &clickedTexture, &errorTexture, &numberFont, &solvebuttonTexture);
	board->initNums();
	board->cursor = &cursor;
	loaded = false;
}

void Game::LoadWindow() {
	window = new sf::RenderWindow(sf::VideoMode(876, 576), "Sudoku Game");
	window->setFramerateLimit(30);
	window->setVerticalSyncEnabled(false);
	Game::swindow = window;
}

void Game::Run() {
	Clock timer;
	float time = 0.0f;
	//board->autoSolve(window);

	while (window->isOpen())
	{
		sf::Time t = timer.restart();
		time += t.asSeconds();

		if (time >= 1.0f) {
			time = 0.0f;
		}

		sf::Event event;
		while (window->pollEvent(event))
		{
	
			if (event.type == sf::Event::Closed)
				window->close();
			if (event.type == sf::Event::MouseMoved)
			{
				cursor = sf::FloatRect(event.mouseMove.x, event.mouseMove.y, 1, 1);
				//std::cout << "new mouse x: " << event.mouseMove.x << std::endl;
				//std::cout << "new mouse y: " << event.mouseMove.y << std::endl;
			}
			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					board->clicked = true;
				}

			}
			if (event.type == sf::Event::KeyPressed)
			{
				board->typed = true;
			}
			if (event.type == sf::Event::TextEntered)
			{
				if (event.text.unicode > 47 && event.text.unicode < 58)
					board->userInput = event.text.unicode;
			}


		}

		board->updateCellOnHover();
		board->updateCellOnClick();
		board->updatebuttonOnClick();

		window->clear();
		board->draw(window);
		window->display();

	}
}

Game::Game() {
	LoadWindow();
	LoadAssets();
	Run();
}


Game::~Game() {
	delete board;
	delete window;
}