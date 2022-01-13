#pragma once
#include"Board.h"
class GameBoard
{
public:
	GameBoard();
	std::array<Board*, 4> m_boards;
	Board* m_bored;
	void update(sf::RenderWindow& m_window);
	bool ended = false;
	sf::Font m_font;
	sf::Color m_selectedBoardColor{ 255, 0, 0 };
	std::array<sf::RectangleShape, 4> m_boardSwitchButtons;
	std::array<sf::Text, 4> m_boardSwitchTexts;
	sf::RectangleShape* m_currentBoardButton;
	int victoryCheck(GameState &current);
	bool checkStraight();
};

