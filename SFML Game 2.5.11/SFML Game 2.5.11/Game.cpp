/// <summary>
/// @author Peter Lowe
/// @date May 2019
///
/// you need to change the above lines or lose marks
/// </summary>

#include "Game.h"
#include <iostream>



/// <summary>
/// default constructor
/// setup the window properties
/// load and setup the text 
/// load and setup thne image
/// </summary>
Game::Game() :
	m_window{ sf::VideoMode{ 1800U, 1600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{ 
	setupFontAndText(); // load font 
	setupSprite(); // load texture
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

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
	for (auto& board : m_boards)
	{
		delete board;
	}
}


/// <summary>
/// main game loop
/// update 60 times per second,
/// process update as often as possible and at least 60 times per second
/// draw as often as possible but only updates are on time
/// if updates run slow then don't render frames
/// </summary>
void Game::run()
{	
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const float fps{ 60.0f };
	sf::Time timePerFrame = sf::seconds(1.0f / fps); // 60 fps
	while (m_window.isOpen())
	{
		processEvents(); // as many as possible
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			timeSinceLastUpdate -= timePerFrame;
			processEvents(); // at least 60 fps
			update(timePerFrame); //60 fps
		}
		render(); // as many as possible
	}
}
/// <summary>
/// handle user and system events/ input
/// get key presses/ mouse moves etc. from OS
/// and user :: Don't do game update here
/// </summary>
void Game::processEvents()
{
	sf::Event newEvent;
	while (m_window.pollEvent(newEvent))
	{
		if ( sf::Event::Closed == newEvent.type) // window message
		{
			m_exitGame = true;
		}
		if (sf::Event::KeyPressed == newEvent.type) //user pressed a key
		{
			processKeys(newEvent);
		}
	}
}


/// <summary>
/// deal with key presses from the user
/// </summary>
/// <param name="t_event">key press event</param>
void Game::processKeys(sf::Event t_event)
{
	if (sf::Keyboard::Escape == t_event.key.code)
	{
		m_exitGame = true;
	}
}

/// <summary>
/// Update the game world
/// </summary>
/// <param name="t_deltaTime">time interval per frame</param>
void Game::update(sf::Time t_deltaTime)
{
	if (m_exitGame)
	{
		m_window.close();
	}


	

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
<<<<<<< HEAD
	
	if (current == playerTurn) {
		m_welcomeMessage.setString("Players Turn");
		m_bored->placement(&m_window,current);
		victoryCheck();

=======
	if (current == playerTurn) {
		m_welcomeMessage.setString("Players Turn");
		m_bored->placement(&m_window,current);
		
>>>>>>> fcf3fd67b24724fd0acd4039bfd8ec3ea8d6b721
	}
	if (current == AiTurn)
	{
		m_welcomeMessage.setString("AI Turn");
		//ai stuff
	}
<<<<<<< HEAD
	
	if (current == GameEndedWinPlayer)
	{
		m_welcomeMessage.setString("Player won");
	}
	if (current == GameEndedWinAi)
	{
		m_welcomeMessage.setString("AI won");
	}
=======
>>>>>>> fcf3fd67b24724fd0acd4039bfd8ec3ea8d6b721
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Blue);
	
	m_bored->draw(&m_window);
	m_window.draw(m_welcomeMessage);
	for (size_t i = 0; i < m_boardSwitchButtons.size(); i++)
	{
		m_window.draw(m_boardSwitchButtons[i]);
		m_window.draw(m_boardSwitchTexts[i]);
	}
	m_window.display();
}

/// <summary>
/// load the font and setup the text message for screen
/// </summary>
void Game::setupFontAndText()
{
	if (!m_ArialBlackfont.loadFromFile("ASSETS\\FONTS\\ariblk.ttf"))
	{
		std::cout << "problem loading arial black font" << std::endl;
	}
	m_welcomeMessage.setFont(m_ArialBlackfont);
	m_welcomeMessage.setString("Players Turn");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(450.0f, 1450.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

}

/// <summary>
/// load the texture and setup the sprite for the logo
/// </summary>
void Game::setupSprite()
{
	if (!m_logoTexture.loadFromFile("ASSETS\\IMAGES\\SFML-LOGO.png"))
	{
		// simple error message if previous call fails
		std::cout << "problem loading logo" << std::endl;
	}
	m_logoSprite.setTexture(m_logoTexture);
	m_logoSprite.setPosition(300.0f, 180.0f);
}

void Game::victoryCheck()
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
			for (int i = 0; i < 13; i+=4 )
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

