#include "SudokuBox.hpp"
#include "Game.hpp"
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <string>
#include <Windows.h>

// Drawing the board
void SudokuBox::draw(sf::RenderWindow* window)
{
	for (int y = 0; y < 9; y++)
	{
		for (int x = 0; x < 9; x++) 
		{
			window->draw(cells[x][y].cellSprite);
			window->draw(cells[x][y].numberText.text);
			window->draw(button.solvebuttonSprite);
			window->draw(this->line1);
			window->draw(this->line2);
			window->draw(this->line3);
			window->draw(this->line4);
			
		}
	}
}



void SudokuBox::initialize(Texture* cellTexture, Texture* cellTextureHighlight, Texture* clickedTexture, Texture* errorTexture, sf::Font* numberFont, Texture* buttonTexture)
{
	int Boardsize = 9;
	float scale = 0.5f;
	float tileSize = 128.0f;
	float gridSpacing = tileSize * scale;
	int boxCounterX = 0;
	int boxCounterY = 0;
	int loopCounter = 0;
	
	this->cellTexture = cellTexture;
	this->highlightTexture = cellTextureHighlight;
	this->clickedTexture = clickedTexture;
	this->errorTexture = errorTexture;

	this->font = numberFont;

	this->line1.setPosition(190.5f, 0);
	this->line1.setSize(sf::Vector2f(5, 576));
	this->line1.setFillColor(sf::Color::Black);
	this->line2.setPosition(382.5f, 0);
	this->line2.setSize(sf::Vector2f(5, 576));
	this->line2.setFillColor(sf::Color::Black);
	this->line3.setPosition(576, 190.5f);
	this->line3.setRotation(90.0f);
	this->line3.setSize(sf::Vector2f(5, 576));
	this->line3.setFillColor(sf::Color::Black);
	this->line4.setPosition(576, 382.5f);
	this->line4.setRotation(90.0f);
	this->line4.setSize(sf::Vector2f(5, 576));
	this->line4.setFillColor(sf::Color::Black);

	for (int horizontal = 0; horizontal < 3; horizontal++) {

		for (int vertical = 0; vertical < 3; vertical++) {


			for (int x = boxCounterX; x < boxCounterX + 3; x++)
			{

				for (int y = boxCounterY; y < boxCounterY + 3; y++)
				{
					cells[x][y] = Cell();
					//partial[x][y] = Cell();

					cells[x][y].boxNumber = loopCounter;
					//partial[x][y].boxNumber = loopCounter;

					// Generating position for each cell
					sf::Vector2f pos = sf::Vector2f(x * gridSpacing, y * gridSpacing);

					// set cell position
					cells[x][y].position = pos;
					cells[x][y].gridPosition = sf::Vector2i(x, y);
					std::cout << "x: " << cells[x][y].gridPosition.x << " y: " << cells[x][y].gridPosition.y << std::endl;
					//partial[x][y].position = pos;
					//partial[x][y].gridPosition = sf::Vector2i(x, y);

					// load the sprite through the pointer texture passed in
					cells[x][y].cellSprite.setTexture(*this->cellTexture);
					cells[x][y].cellSpriteHighlight.setTexture(*this->highlightTexture);
					cells[x][y].cellSpriteClicked.setTexture(*this->clickedTexture);
					cells[x][y].cellSprite.setScale(scale, scale);
					cells[x][y].cellSprite.setPosition(pos);
					// load the text through the pointer text passed in
					cells[x][y].numberText = RenderText(this->font, pos, 24);
					cells[x][y].numberText.text.setString(" ");
					cells[x][y].cellNumber = 0;
					//partial[x][y].cellNumber = 0;

					// Generate the hitbox
					cells[x][y].hitbox = sf::FloatRect(pos.x, pos.y, gridSpacing, gridSpacing);
				}

			}
			loopCounter += 1;
			boxCounterY += 3;
		}
		boxCounterX += 3;
		boxCounterY = 0;

	}
	boxCounterX = 9;
	boxCounterY = 0;
	//Init the "copy" or "second" board for logic and algoritym purposes.
	for (int horizontal = 0; horizontal < 3; horizontal++) {

		for (int vertical = 0; vertical < 3; vertical++) {


			for (int x = boxCounterX; x < boxCounterX + 3; x++)
			{

				for (int y = boxCounterY; y < boxCounterY + 3; y++)
				{
					cells[x][y] = Cell();

					cells[x][y].boxNumber = loopCounter;

					// Generating position for each cell
					sf::Vector2f pos = sf::Vector2f(x * gridSpacing, y * gridSpacing);

					// set cell position
					cells[x][y].position = pos;
					cells[x][y].gridPosition = sf::Vector2i(x, y);
					std::cout << "x: " << cells[x][y].gridPosition.x << " y: " << cells[x][y].gridPosition.y << " Second time" << std::endl;

					cells[x][y].cellNumber = 0;

				}

			}
			loopCounter += 1;
			boxCounterY += 3;
		}
		boxCounterX += 3;
		boxCounterY = 0;

	}

	button.position = { 600.0f, 100.0f };
	button.solvebuttonHitbox = { 600.0f, 100.0f, 209.0f, 91.0f };
	this->solvebuttonTexture = buttonTexture;
	button.solvebuttonSprite.setTexture(*solvebuttonTexture);
	button.solvebuttonSprite.setPosition(button.position);

	
}
// WIP
bool SudokuBox::initSolver() {
	int x = 0;
	int y = 0;
	bool full = true;
	//std::cout << "x: " << x << "  y: " << y << std::endl;
	int number = 0;

	// Check if empty
	for (int i = 9; i < 18; i++) {
		for (int j = 0; j < 9; j++) {
			if (cells[i][j].cellNumber == 0) {
				full = false;
			}
		}
	} 
	if (full == true) {
		return true;
	}
	// Find blank
	for (int i = 9; i < 18; i++) {
		for (int j = 0; j < 9; j++) {
			if (cells[i][j].cellNumber == 0) {
				y = j;
				x = i;
			}
		}
	}

	for (number = 0; number < 9; number++)
	{

		if (isValid(cells[x][y].gridPosition, (number + 1), cells[x][y].boxNumber) == true) {
			cells[x][y].cellNumber = number + 1;
			cells[x][y].numberText.UpdateString(std::to_string(number + 1));
			cells[x][y].cellSprite.setTexture(*highlightTexture);
			if (initSolver() == true) {
				return true;
			}
			cells[x][y].cellNumber = 0;
		}

	}

	return false;
}

// Generate a board that can be solved - WIP.
void SudokuBox::initNums() {
	bool filled = false;
	int randomNum = 0;
	
	srand(time(NULL));
	// Loop through the whole board.
	for (int x = 0; x < 9; x++) {
		for (int y = 0; y < 9; y++) {
			// Generate a random number. This is not the number being put into the board. It's determining if there will be a number in that space.
			randomNum = rand() % 11;
			if (randomNum < difficulty) {
				// Sometimes the board will generate a number that will make the board impossible to solve. Make sure to find a number to fill that spot first.
				while (filled == false) {
					// Generate a random number. IMPORTANT: If that number is valid in the space specifically, then put it there.
					randomNum = rand() % 10;
					if (isValid(cells[x+9][y].gridPosition, randomNum, cells[x+9][y].boxNumber) == true) {
						cells[x+9][y].cellNumber = randomNum;
						
						// This will check if the generated number will make the board impossible to solve or not.
						if (initSolver() == true) {
							filled = true;
							cells[x + 9][y].numberText.UpdateString(std::to_string(randomNum));
							cells[x + 9][y].canChange = false;
							cells[x][y].cellNumber = cells[x + 9][y].cellNumber;
							cells[x][y].numberText.UpdateString(std::to_string(cells[x+9][y].cellNumber));
							cells[x][y].canChange = false;
						}
						else {
							for (int i = 0; i < 9; i++) {
								for (int j = 0; j < 9; j++) {
									cells[i + 9][j].cellNumber = cells[i][j].cellNumber;
								}
							}
							filled = false;
							cells[x + 9][y].cellNumber = 0;
						}
					}
					
				}
				filled = false;

				/*else {
					//std::cout << "isValid is working \n";
					cells[x][y].numberText.UpdateString(" ");
					cells[x][y].cellNumber = 0;
				}*/
			}
		}
	}
	
}
// When the cursor hovers over a cell, it will highlight it.
void SudokuBox::updateCellOnHover() {
	if (solved == false) {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				if (cursor->intersects(cells[i][j].hitbox)) {
					cells[i][j].cellSprite.setTexture(*clickedTexture);
					cells[i][j].highlight();
				}
				else {
					cells[i][j].cellSprite.setTexture(*cellTexture);
					cells[i][j].deHighlight();
				}
			}
		}
	}
	
}
// When a cell is clicked, change the texture and allow editing of the number.
void SudokuBox::updateCellOnClick() {
	// Loop through the board.
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {	
			// If the mouse is over the cell, the user clicks the mouse, and that cell is able to be changed (as in it's not part of the starting board), then continue. 
			if (cells[i][j].highlighted == true && clicked == true && typed == true) {
				if (cells[i][j].canChange == true) {
					cells[i][j].cellSprite.setTexture(*clickedTexture);
					std::string userTempInput(1, userInput);
					cells[i][j].numberText.UpdateString(userTempInput);
					cells[i][j].cellNumber = std::stoi(userTempInput);
					//std::cout << cells[i][j].cellNumber << std::endl;
					// If the number the user inputs is invalid, then change that number to red coloured text.
					if (isValid(cells[i][j].gridPosition, cells[i][j].cellNumber, cells[i][j].boxNumber) == false) {
						//std::cout << "isValid activated";
						cells[i][j].numberText.changeColourRed();
					}
					else {
						cells[i][j].numberText.changeColourBlack();
					}
					clicked = false;
					typed = false;					
				}
				else {
					clicked = false;
					typed = false;
				}
				
			}
		}
	}
}
// Checking if the solve button is clicked
void SudokuBox::updatebuttonOnClick() {
	if (cursor->intersects(button.solvebuttonHitbox) && clicked == true) {
		clicked = false;
		autoSolve(Game::swindow);
	}
}

// Checking if the number is valid in that specific spot. No duplicates in rows, columns, or box. IMPORTANT: Doesn't check if that number will make the board unsolvable.
bool SudokuBox::isValid(Vector2i currentPos, int Num, int boxNumber) {
	int currentNum = Num;
	int currentNumCompare;
	int currentPosX = currentPos.x;
	int currentPosY = currentPos.y;
	int startX = 0;
	int startY = 0;
	int boxNum = boxNumber;
	int multiply = 1;
	int i = 0;
	if (boxNumber >= 9) {
		multiply = 2;
		i = 9;
	}

	//Check the x coordinate to make sure there are no duplicate numbers. If duplicates exist, then return false, else go to check Y coordinate.
	for (int j = i; j < (9 * multiply); j++) {
		currentNumCompare = cells[j][currentPosY].cellNumber;
		if (currentNumCompare == currentNum && j != currentPosX) {
			return false;
		}
	}
	//Check the y coordinate to make sure there are no duplicate numbers. If duplicates exist, then return false, else go to check boxes.
	for (int j = 0; j < 9; j++) {
		//std::cout << currentPosX << std::endl;
		currentNumCompare = cells[currentPosX][j].cellNumber;
		if (currentNumCompare == currentNum && j != currentPosY) {
			return false;
		}
	}
	/* BOX ORDER:
	| 0 | 3 | 6 | 9  | 12 | 15 |
	| 1 | 4 | 7 | 10 | 13 | 16 |
	| 2 | 5 | 8 | 11 | 14 | 17 |
	*/
	switch (boxNum) {
	case 0:
		startX = 0;
		startY = 0;
		break;
	case 1:
		startX = 0;
		startY = 3;
		break;
	case 2:
		startX = 0;
		startY = 6;
		break;
	case 3:
		startX = 3;
		startY = 0;
		break;
	case 4:
		startX = 3;
		startY = 3;
		break;
	case 5:
		startX = 3;
		startY = 6;
		break;
	case 6:
		startX = 6;
		startY = 0;
		break;
	case 7:
		startX = 6;
		startY = 3;
		break;
	case 8:
		startX = 6;
		startY = 6;
		break;
	case 9:
		startX = 9;
		startY = 0;
		break;
	case 10:
		startX = 9;
		startY = 3;
		break;
	case 11:
		startX = 9;
		startY = 6;
		break;
	case 12:
		startX = 12;
		startY = 0;
		break;
	case 13:
		startX = 12;
		startY = 3;
		break;
	case 14:
		startX = 12;
		startY = 6;
		break;
	case 15:
		startX = 15;
		startY = 0;
		break;
	case 16:
		startX = 15;
		startY = 3;
		break;
	case 17:
		startX = 15;
		startY = 6;
		break;
	}
	//std::cout << "StartX: " << startX << std::endl;
	//std::cout << "StartY: " << startY << std::endl;
	for (int i = startX; i < (startX + 3); i++) {
		for (int j = startY; j < (startY + 3); j++) {
			currentNumCompare = cells[i][j].cellNumber;
			if (currentNumCompare == currentNum && i != currentPosX && j != currentPosY) {
				//std::cout << "Caught one!"  << std::endl;
				return false;
			}
		}
	}

	return true;
}
// Find a cell that doesn't contain a number.
sf::Vector2i SudokuBox::findBlank() {
	sf::Vector2i coords = {0, 0};
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (cells[i][j].cellNumber == 0) {
				coords.y = j;
				coords.x = i;
				return coords;
			}
		}
	}
	return coords;
}
// Check if the board is full or not.
bool SudokuBox::isEmpty() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (cells[i][j].cellNumber == 0) {
				return true;
			}
		}
	}
	return false;
}
// The auto solving algorithym. Uses the backtracking algorythm - WIP.
bool SudokuBox::autoSolve(sf::RenderWindow* window) {
	sf::Vector2i coords;
	int x = 0;
	int y = 0;
	//std::cout << "x: " << x << "  y: " << y << std::endl;
	int number = 0;

	if (isEmpty() == false) {
		std::cout << "Board is full!";
		solved = true;
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cells[i][j].cellSprite.setTexture(*highlightTexture);
			}
		}
		return true;
	}

	coords = findBlank();
	x = coords.x;
	y = coords.y;


	for (number = 0; number < 9; number++)
	{
		if (isValid(cells[x][y].gridPosition, (number + 1), cells[x][y].boxNumber) == true) {
			std::cout << "This is valid lol   x: " << x << " y: " << y << std::endl;
			cells[x][y].cellNumber = number + 1;
			cells[x][y].numberText.UpdateString(std::to_string(number + 1));
			cells[x][y].cellSprite.setTexture(*highlightTexture);
			//std::cout << "Number that we're assigning to this cell: " << (number + 1) << std::endl;
			window->clear();
			for (int i = 0; i < 9; i++) {
				for (int j = 0; j < 9; j++) {
					window->draw(cells[i][j].cellSprite);
					window->draw(cells[i][j].numberText.text);	
					window->draw(this->line1);
					window->draw(this->line2);
					window->draw(this->line3);
					window->draw(this->line4);
				}
			}
			window->display();
			Sleep(50);
			
			if (autoSolve(window) == true) {
				return true;
			}
			cells[x][y].cellNumber = 0;
			cells[x][y].numberText.UpdateString(std::to_string(0));
			cells[x][y].cellSprite.setTexture(*errorTexture);
		}

	}

	return false;



}


SudokuBox::SudokuBox() {

}

RenderText::RenderText() {

}

Cell::Cell() {

}

solveButton::solveButton()
{

}

