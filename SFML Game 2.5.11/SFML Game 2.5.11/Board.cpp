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
				}
			}
		}
	}
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
