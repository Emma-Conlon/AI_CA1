/// <summary>
/// author Pete Lowe May 2019
/// you need to change the above line or lose marks
/// </summary>
#ifndef GAME_HPP
#define GAME_HPP
/// <summary>
/// include guards used so we don't process this file twice
/// same as #pragma once
/// Don't forget the endif at the bottom
/// </summary>

#include <SFML/Graphics.hpp>
#include"Board.h"
#include "global.h"
class Game
{
public:
	Game();
	~Game();
	/// <summary>
	/// main method for game
	/// </summary>
	void run();
	
private:

	void processEvents();
	void processKeys(sf::Event t_event);
	void update(sf::Time t_deltaTime);
	void render();
	std::array<Board*, 4> m_boards;
	void setupFontAndText();
	void setupSprite();
	Board* m_bored;
	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game
	
	sf::Font m_font;
	sf::Color m_selectedBoardColor{ 255, 0, 0 };
	std::array<sf::RectangleShape, 4> m_boardSwitchButtons;
	std::array<sf::Text, 4> m_boardSwitchTexts;
	sf::RectangleShape* m_currentBoardButton;
	void victoryCheck();
	GameState current = playerTurn;
};

#endif // !GAME_HPP

