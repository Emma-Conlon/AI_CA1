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
	int m_index;

public:
	Board(int index);
	std::array<std::array<sf::CircleShape, 4>, 4> m_pieces;
	std::array<std::array<sf::RectangleShape, 4>, 4> m_boardTiles;

	void update(sf::Time dt, sf::RenderWindow* window);
	void placement(sf::RenderWindow* window,GameState &T_state);
	void draw(sf::RenderWindow* window);
	sf::CircleShape getPiece(int x, int y);
	void setPiece(int x, int y, sf::Color player);
	bool victoryCheckPlayer();

	int index() { return m_index; }
	bool victoryCheckAI();

};

#endif // !BOARD_H
