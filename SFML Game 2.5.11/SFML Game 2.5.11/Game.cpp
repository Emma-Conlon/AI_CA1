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
	
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
	for (auto& board : m_gameboard->m_boards)
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
		if (current == Difficulty)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
			{
				diff = 1;
				m_type.setString("AI Difficulty:Easy");
				current = playerTurn;
			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
			{
				diff = 3;
				m_type.setString("AI Difficulty:Hard");
				current = playerTurn;
			}
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


	m_gameboard->update(m_window);

	
		if (current == playerTurn) {
			m_welcomeMessage.setString("Players Turn");
			m_gameboard->m_bored->placement(&m_window, current);
			m_gameboard->victoryCheck(current);




		}

		if (current == AiTurn)
		{
			m_welcomeMessage.setString("AI Turn");
			ai.init(current);
			ai.preformMove(*m_gameboard, diff);


			
			if(m_gameboard->victoryCheck(current)==0)
			{
				current = playerTurn;
			}

		}

	
	if (current == GameEndedWinPlayer)
	{
		m_welcomeMessage.setString("Player won");
	}
	if (current == GameEndedWinAi)
	{
		m_welcomeMessage.setString("AI won");
	}

}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Blue);
	
	m_gameboard->m_bored->draw(&m_window);
	m_window.draw(m_welcomeMessage);
	m_window.draw(m_type);
	for (size_t i = 0; i < m_gameboard->m_boardSwitchButtons.size(); i++)
	{
		m_window.draw(m_gameboard->m_boardSwitchButtons[i]);
		m_window.draw(m_gameboard->m_boardSwitchTexts[i]);
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
	m_welcomeMessage.setString("PickAiDifficulty");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(150.0f, 1450.0f);
	m_welcomeMessage.setCharacterSize(80U);
	m_welcomeMessage.setOutlineColor(sf::Color::Red);
	m_welcomeMessage.setFillColor(sf::Color::Black);
	m_welcomeMessage.setOutlineThickness(3.0f);

	m_type.setFont(m_ArialBlackfont);
	m_type.setString(" 1=Easy 2=Hard");
	m_type.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_type.setPosition(850.0f, 1450.0f);
	m_type.setCharacterSize(80U);
	m_type.setOutlineColor(sf::Color::Green);
	m_type.setFillColor(sf::Color::Black);
	m_type.setOutlineThickness(3.0f);

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



