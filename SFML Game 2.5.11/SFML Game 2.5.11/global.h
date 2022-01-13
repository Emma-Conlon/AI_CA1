#pragma once
/// <summary>
/// this allows us to find out whos turn it is, what difficulty the AI is on and if it ends up in a draw
/// </summary>
enum  GameState
{
	playerTurn,
	AiTurn,
	GameEndedDraw,
	GameEndedWinPlayer,
	GameEndedWinAi,
	Difficulty
};

