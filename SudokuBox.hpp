#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <functional>

using sf::Vector2f;
using sf::Vector2i;
using sf::Sprite;
using sf::Texture;
using sf::Rect;
using sf::RectangleShape;

using std::function;
using std::bind;

struct RenderText {
public:
	sf::Text text;
	Vector2f position;
	RenderText();
	RenderText(sf::Font* font, Vector2f position, int charSize) {
		this->text = sf::Text();
		this->text.setFont(*font);
		this->text.setCharacterSize(charSize);
		this->text.setPosition(position.x + 25.0f, position.y + 15.0f);
		this->text.setFillColor(sf::Color::Black);
		this->position = position;
	}
	void UpdateString(std::string value) {
		text.setString(value);
	}
	std::string getThisString(sf::Text text) {
		return (std::string)text.getString();
	}
	// Changing the colours of the text.
	void changeColourRed() {
		text.setFillColor(sf::Color::Red);
	}
	void changeColourBlack() {
		text.setFillColor(sf::Color::Black);
	}
	
};

struct Cell {
	public:
		Vector2f position;
		Sprite cellSprite;
		Sprite cellSpriteHighlight;
		Sprite cellSpriteClicked;
		RenderText numberText;
		sf::FloatRect hitbox;
		Vector2i gridPosition;
		int boxNumber;
		int cellNumber;
		bool canChange = true;
		Cell();

		bool highlighted;
		bool cellClicked;
		
		void highlight() {
			highlighted = true;
		}
		void deHighlight() {
			highlighted = false;
		}
		void clickHighlight() {
			cellClicked = true;
		}
		void clickDeHighlight() {
			cellClicked = false;
		}
		
};

struct solveButton {
	public:
		sf::FloatRect solvebuttonHitbox;
		Sprite solvebuttonSprite;
		Vector2f position;
		solveButton();

};

class SudokuBox
{
	public:
		
		Vector2f position;
		Texture* cellTexture;
		Texture* highlightTexture;
		Texture* clickedTexture;
		Texture* solvebuttonTexture;
		Texture* errorTexture;
		sf::Font* font;
		
		sf::FloatRect* cursor;
		bool clicked;
		bool typed;
		char userInput = ' ';
		int t = 0;
		bool solved = false;

		//Difficulty Changer. 0-10 Lower number = higher difficulty | Higher number = lower difficulty.
		int difficulty = 5;

		Cell cells[18][9];
		//Cell partial[9][9];
		solveButton button;

		sf::RectangleShape line1;
		sf::RectangleShape line2;
		sf::RectangleShape line3;
		sf::RectangleShape line4;

		SudokuBox();
		//draw method
		void draw (sf::RenderWindow* window);

		//Initialize Cells method
		void initialize(Texture* cellTexture, Texture* cellTextureHighlight, Texture* clickedTexture, Texture* errorTexture, sf::Font* numberFont, Texture* buttonTexture);

		//Initialize numbers method
		void initNums();
		bool initSolver();

		//Mouse Interaction methods
		void updateCellOnHover();
		void updateCellOnClick();
		void updatebuttonOnClick();

		//Algorythm Methods
		bool isValid(Vector2i currentPos, int currentNum, int boxNumber);
		sf::Vector2i findBlank();
		bool autoSolve(sf::RenderWindow* window);
		bool isEmpty();
		

};

