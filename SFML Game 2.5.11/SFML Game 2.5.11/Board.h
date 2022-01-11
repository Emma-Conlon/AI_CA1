#ifndef BOARD_H
#define BOARD_H

#include <array>
//#include "Piece.h"
#include <SFML/Graphics.hpp>
#include "global.h"
class Board
{
private:
	float m_tileWidth{ 350.0f };
	std::array<std::array<sf::RectangleShape, 4>, 4> m_boardTiles;
	std::array<std::array<sf::CircleShape,4>, 4> m_pieces;
	int m_index;

public:
	Board(int index);
	std::array<std::array<sf::CircleShape, 4>, 4> m_pieces;

	void update(sf::Time dt, sf::RenderWindow* window);
	void placement(sf::RenderWindow* window,GameState &T_state);
	void draw(sf::RenderWindow* window);
	sf::CircleShape getPiece(int x, int y);
	bool victoryCheckPlayer();

	int index() { return m_index; }
<<<<<<< HEAD
	bool victoryCheckAI();
=======
	
>>>>>>> fcf3fd67b24724fd0acd4039bfd8ec3ea8d6b721
};

#endif // !BOARD_H
