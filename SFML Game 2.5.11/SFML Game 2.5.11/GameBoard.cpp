#include "GameBoard.h"

GameBoard::GameBoard()
{
	m_font.loadFromFile("ASSETS\\FONTS\\ariblk.ttf");
	int boardIndex{};
	for (auto& board : m_boards)
	{
		board = new Board(boardIndex);
		++boardIndex;
	}

	for (size_t i = 0; i < m_boardSwitchButtons.size(); i++)
	{
		m_boardSwitchButtons[i].setFillColor(sf::Color::Black);
		m_boardSwitchButtons[i].setSize(sf::Vector2f{ 400.0f, 350.0f });
		m_boardSwitchButtons[i].setPosition(1400.0f, 350.0f * i);
		m_boardSwitchButtons[i].setOutlineThickness(1.5f);
		m_boardSwitchButtons[i].setOutlineColor(sf::Color::Red);

		m_boardSwitchTexts[i].setFont(m_font);
		m_boardSwitchTexts[i].setCharacterSize(40u);
		m_boardSwitchTexts[i].setString("Board\n   " + std::to_string(i + 1));
		m_boardSwitchTexts[i].setPosition(m_boardSwitchButtons[i].getPosition().x + 20.0f,
			m_boardSwitchButtons[i].getPosition().y + m_boardSwitchButtons[i].getGlobalBounds().height / 3.0f);
		m_boardSwitchTexts[i].setFillColor(sf::Color::White);
	}
	m_bored = m_boards[0];
	m_currentBoardButton = &m_boardSwitchButtons[0];
	m_currentBoardButton->setFillColor(m_selectedBoardColor);
}
void GameBoard::update(sf::RenderWindow &m_window)
{
	
	for (int i = 0; i < m_boardSwitchButtons.size(); i++)
	{
		if (m_boardSwitchButtons[i].getGlobalBounds().contains(m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window))))
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
			{
				m_currentBoardButton->setFillColor(sf::Color::Black);
				m_currentBoardButton = &m_boardSwitchButtons[i];
				m_currentBoardButton->setFillColor(m_selectedBoardColor);
				m_bored = m_boards.at(i);


			}
		}
	}

}
void GameBoard::victoryCheck(GameState& current)
{
	std::array<int, 16> pos1;
	std::array<int, 16> pos2;
	std::array<int, 16> pos3;
	std::array<int, 16> pos4;
	bool win = false;
	for (int i = 0; i < 4; i++)
	{

		if (m_boards[i]->victoryCheckAI())
		{
			current = GameEndedWinAi;
		}

		if (m_boards[i]->victoryCheckPlayer())
		{
			current = GameEndedWinPlayer;
		}

	}
	for (int j = 0; j < 4; j++)
	{
		for (int k = 0; k < 4; k++)
		{
			pos1[k * 4 + j] = 5;
			if (m_boards[0]->getPiece(j, k).getFillColor() == sf::Color::Yellow)
			{
				pos1[k * 4 + j] = 1;
			}
			if (m_boards[0]->getPiece(j, k).getFillColor() == sf::Color::Red)
			{
				pos1[k * 4 + j] = 2;
			}
			if (m_boards[1]->getPiece(j, k).getFillColor() == sf::Color::Yellow)
			{
				pos2[k * 4 + j] = 1;
			}
			if (m_boards[1]->getPiece(j, k).getFillColor() == sf::Color::Red)
			{
				pos2[k * 4 + j] = 2;
			}
			if (m_boards[2]->getPiece(j, k).getFillColor() == sf::Color::Yellow)
			{
				pos3[k * 4 + j] = 1;
			}
			if (m_boards[2]->getPiece(j, k).getFillColor() == sf::Color::Red)
			{
				pos3[k * 4 + j] = 2;
			}
			if (m_boards[3]->getPiece(j, k).getFillColor() == sf::Color::Yellow)
			{
				pos4[k * 4 + j] = 1;
			}
			if (m_boards[3]->getPiece(j, k).getFillColor() == sf::Color::Red)
			{
				pos4[k * 4 + j] = 2;
			}
		}
	}

	for (int i = 0; i < 16; i++)
	{
		if (pos1[i] == 1 && pos2[i] == 1 && pos3[i] == 1 && pos4[i] == 1)
		{
			current = GameEndedWinPlayer;
		}
		if (pos1[i] == 2 && pos2[i] == 2 && pos3[i] == 2 && pos4[i] == 2)
		{
			current = GameEndedWinAi;
		}
	}
	for (int i = 0; i < 4; i++)
	{
		int j = i + 4;
		int k = j + 4;
		int l = k + 4;

		if (pos1[i] == 1 && pos2[j] == 1 && pos3[k] == 1 && pos4[l] == 1)
		{
			current = GameEndedWinPlayer;
		}
		if (pos1[i] == 2 && pos2[j] == 2 && pos3[k] == 2 && pos4[l] == 2)
		{
			current = GameEndedWinAi;
		}
		if (pos1[l] == 1 && pos2[k] == 1 && pos3[j] == 1 && pos4[i] == 1)
		{
			current = GameEndedWinPlayer;
		}
		if (pos1[l] == 2 && pos2[k] == 2 && pos3[j] == 2 && pos4[i] == 2)
		{
			current = GameEndedWinAi;
		}

	}//works
	if (pos1[0] == 1 && pos2[5] == 1 && pos3[10] == 1 && pos4[15] == 1)
	{
		current = GameEndedWinPlayer;
	}
	if (pos1[0] == 2 && pos2[5] == 2 && pos3[10] == 2 && pos4[15] == 2)
	{
		current = GameEndedWinAi;
	}
	if (pos1[15] == 1 && pos2[10] == 1 && pos3[5] == 1 && pos4[0] == 1)
	{
		current = GameEndedWinPlayer;
	}
	if (pos1[15] == 2 && pos2[10] == 2 && pos3[5] == 2 && pos4[0] == 2)
	{
		current = GameEndedWinAi;
	}


	//
	if (pos1[3] == 1 && pos2[6] == 1 && pos3[9] == 1 && pos4[12] == 1)
	{
		current = GameEndedWinPlayer;
	}
	if (pos1[3] == 2 && pos2[6] == 2 && pos3[9] == 2 && pos4[12] == 2)
	{
		current = GameEndedWinAi;
	}
	if (pos1[12] == 1 && pos2[9] == 1 && pos3[6] == 1 && pos4[3] == 1)
	{
		current = GameEndedWinPlayer;
	}
	if (pos1[12] == 2 && pos2[9] == 2 && pos3[6] == 2 && pos4[3] == 2)
	{
		current = GameEndedWinAi;
	}
	for (int i = 0; i < 13; i += 4)
	{
		int j = i + 1;
		int k = j + 1;
		int l = k + 1;

		if (pos1[i] == 1 && pos2[j] == 1 && pos3[k] == 1 && pos4[l] == 1)
		{
			current = GameEndedWinPlayer;
		}
		if (pos1[i] == 2 && pos2[j] == 2 && pos3[k] == 2 && pos4[l] == 2)
		{
			current = GameEndedWinAi;
		}
		if (pos1[l] == 1 && pos2[k] == 1 && pos3[j] == 1 && pos4[i] == 1)
		{
			current = GameEndedWinPlayer;
		}
		if (pos1[l] == 2 && pos2[k] == 2 && pos3[j] == 2 && pos4[i] == 2)
		{
			current = GameEndedWinAi;
		}
	}
}