#include "Board.h"


Board::Board(int index)
{
	m_index = index;

	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m_boardTiles.at(i).at(j).setSize(sf::Vector2f{ m_tileWidth, m_tileWidth });
			m_boardTiles.at(i).at(j).setFillColor(sf::Color::White);
			m_boardTiles.at(i).at(j).setOutlineThickness(1.0f);
			m_boardTiles.at(i).at(j).setOutlineColor(sf::Color::Black);
			m_boardTiles.at(i).at(j).setPosition((m_tileWidth * i), (m_tileWidth * j));
			m_pieces.at(i).at(j).setRadius(m_tileWidth/2);
			m_pieces.at(i).at(j).setFillColor(sf::Color::White);
			m_pieces.at(i).at(j).setOutlineThickness(1.0f);
			m_pieces.at(i).at(j).setOutlineColor(sf::Color::Black);
			m_pieces.at(i).at(j).setPosition((m_tileWidth * i), (m_tileWidth * j));
		}
	}
}

void Board::update(sf::Time dt, sf::RenderWindow* window)
{

}
//
void Board::placement(sf::RenderWindow* window, GameState& T_state)
{
<<<<<<< HEAD
	if (T_state == GameState::playerTurn)
	{
		for (size_t i = 0; i < 4; i++)
		{
			for (size_t j = 0; j < 4; j++)
			{
				if (m_boardTiles.at(i).at(j).getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
				{
					if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
					{
						m_pieces.at(i).at(j).setFillColor(sf::Color::Yellow);
						//T_state = GameState::AiTurn;
					}
=======
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			if (m_boardTiles.at(i).at(j).getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window))))
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
				{
					m_pieces.at(i).at(j).setFillColor(sf::Color::Yellow);
					T_state = GameState::AiTurn;
>>>>>>> fcf3fd67b24724fd0acd4039bfd8ec3ea8d6b721
				}
			}
		}
	}
<<<<<<< HEAD
	if (T_state == GameState::AiTurn)
	{
		
	}
=======
>>>>>>> fcf3fd67b24724fd0acd4039bfd8ec3ea8d6b721
}

void Board::draw(sf::RenderWindow* window)
{
	for (int  i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			window->draw(m_boardTiles.at(i).at(j));
			window->draw(m_pieces.at(i).at(j));
		}
	}
}

sf::CircleShape Board::getPiece(int x , int y)
{
	return m_pieces.at(x).at(y);
}

bool Board::victoryCheckPlayer()
{
	bool win = false;
	std::array<int, 16> pos;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_pieces.at(i).at(j).getFillColor() == sf::Color::Yellow)
			{
				pos[j * 4 + i] = 1;
			}
		
		}
	}
	if (pos[0] == 1
		&& pos[1] == 1
		&& pos[2] == 1
		&& pos[3] == 1)
	{
		win = true;
	}
	else if (pos[4] == 1
		&& pos[5] == 1
		&& pos[6] == 1
		&& pos[7] == 1)
	{
		win = true;
	}
	else if (pos[8] == 1
		&& pos[9] == 1
		&& pos[10] == 1
		&& pos[11] == 1)
	{
		win = true;
	}
	else if (pos[12] == 1
		&& pos[13] == 1
		&& pos[14] == 1
		&& pos[15] == 1)
	{
		win = true;
	}
	else if (pos[0] == 1
		&& pos[4] == 1
		&& pos[8] == 1
		&& pos[12] == 1)
	{
		win = true;
	}
	else if (pos[1] == 1
		&& pos[5] == 1
		&& pos[9] == 1
		&& pos[13] == 1)
	{
		win = true;
	}
	else if (pos[2] == 1
		&& pos[6] == 1
		&& pos[10] == 1
		&& pos[14] == 1)
	{
		win = true;
	}
	else	if (pos[3] == 1
		&& pos[7] == 1
		&& pos[11] == 1
		&& pos[15] == 1)
	{
		win = true;
	}
	else if (pos[0] == 1
		&& pos[5] == 1
		&& pos[10] == 1
		&& pos[15] == 1)
	{
		win = true;
	}
	else if (pos[3] == 1
		&& pos[6] == 1
		&& pos[9] == 1
		&& pos[12] == 1)
	{
		win = true;
	}
	return win;
}

bool Board::victoryCheckAI()
{
	std::array<int, 16> pos;
	bool win = false;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (m_pieces.at(i).at(j).getFillColor() == sf::Color::Red)
			{
				pos[j * 4 + i] = 2;
			}

		}
	}
	if (pos[0] == 2
		&& pos[1] == 2
		&& pos[2] == 2
		&& pos[3] == 2)
	{
		win = true;
	}
	if (pos[4] == 2
		&& pos[5] == 2
		&& pos[6] == 2
		&& pos[7] == 2)
	{
		win = true;
	}
	if (pos[8] == 2
		&& pos[9] == 2
		&& pos[10] == 2
		&& pos[11] == 2)
	{
		win = true;
	}
	if (pos[12] == 2
		&& pos[13] == 2
		&& pos[14] == 2
		&& pos[15] == 2)
	{
		win = true;
	}
	if (pos[0] == 2
		&& pos[4] == 2
		&& pos[8] == 2
		&& pos[12] ==2)
	{
		win = true;
	}
	if (pos[1] == 2
		&& pos[5] == 2
		&& pos[9] == 2
		&& pos[13] == 2)
	{
		win = true;
	}
	if (pos[2] == 2
		&& pos[6] == 2
		&& pos[10] == 2
		&& pos[14] == 2)
	{
		win = true;
	}
	if (pos[3] == 2
		&& pos[7] == 2
		&& pos[11] == 2
		&& pos[15] == 2)
	{
		win = true;
	}
	if (pos[0] == 2
		&& pos[5] == 2
		&& pos[10] == 2
		&& pos[15] == 2)
	{
		win = true;
	}
	if (pos[3] == 2
		&& pos[6] == 2
		&& pos[9] == 2
		&& pos[12] == 2)
	{
		win = true;
	}
	return false;
}
