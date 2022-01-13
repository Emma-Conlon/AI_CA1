#include "Board.h"


Board::Board(int index)
{
	m_index = index;
	///creates the boards tiles 
	for (size_t i = 0; i < 4; i++)
	{
		for (size_t j = 0; j < 4; j++)
		{
			m_boardTiles.at(i).at(j).setSize(sf::Vector2f{ m_tileWidth, m_tileWidth });
			m_boardTiles.at(i).at(j).setFillColor(sf::Color::White);
			m_boardTiles.at(i).at(j).setOutlineThickness(1.0f);
			m_boardTiles.at(i).at(j).setOutlineColor(sf::Color::Black);
			m_boardTiles.at(i).at(j).setPosition((m_tileWidth * i), (m_tileWidth * j));
			/// <summary>
			///white pieces on the board
			/// </summary>
			/// <param name="index"></param>
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
	/// <summary>
	/// not used 
	/// </summary>
	/// <param name="dt"></param>
	/// <param name="window"></param>
}

/// this allows the player to pick any position on the board when it is their turn  with a left click
void Board::placement(sf::RenderWindow* window, GameState& T_state)
{

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
						if (getPiece(i, j).getFillColor() == sf::Color::White) {
							m_pieces.at(i).at(j).setFillColor(sf::Color::Yellow);

							T_state = AiTurn;
						}
					}
				}
			}
		}
	}
	

}
/// <summary>
/// draws all the boards tiles and pieces
/// </summary>
/// <param name="window"></param>
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
/// <summary>
/// gets the peice of either the AI and the players piece
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <returns></returns>
sf::CircleShape Board::getPiece(int x , int y)
{
	return m_pieces.at(x).at(y);
}

/// <summary>
/// changes the players position on the board with an x and y value 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
/// <param name="player"></param>
void Board::setPiece(int x, int y, sf::Color player)
{
	m_pieces.at(x).at(y).setFillColor(player);
}

/// <summary>
/// checks victory for the Player in every possible to move
/// </summary>
/// <returns></returns>
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

/// <summary>
/// checks for victory for AI 
/// </summary>
/// <returns></returns>
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
	else if (pos[4] == 2
		&& pos[5] == 2
		&& pos[6] == 2
		&& pos[7] == 2)
	{
		win = true;
	}
	else if (pos[8] == 2
		&& pos[9] == 2
		&& pos[10] == 2
		&& pos[11] == 2)
	{
		win = true;
	}
	else if (pos[12] == 2
		&& pos[13] == 2
		&& pos[14] == 2
		&& pos[15] == 2)
	{
		win = true;
	}
	else if (pos[0] == 2
		&& pos[4] == 2
		&& pos[8] == 2
		&& pos[12] ==2)
	{
		win = true;
	}
	else if (pos[1] == 2
		&& pos[5] == 2
		&& pos[9] == 2
		&& pos[13] == 2)
	{
		win = true;
	}
	else if (pos[2] == 2
		&& pos[6] == 2
		&& pos[10] == 2
		&& pos[14] == 2)
	{
		win = true;
	}
	else if (pos[3] == 2
		&& pos[7] == 2
		&& pos[11] == 2
		&& pos[15] == 2)
	{
		win = true;
	}
	else if (pos[0] == 2
		&& pos[5] == 2
		&& pos[10] == 2
		&& pos[15] == 2)
	{
		win = true;
	}
	else if (pos[3] == 2
		&& pos[6] == 2
		&& pos[9] == 2
		&& pos[12] == 2)
	{
		win = true;
	}
	return win;
}
