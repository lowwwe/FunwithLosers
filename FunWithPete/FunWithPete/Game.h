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

	void setupVertexArray();
	
	void setupFontAndText();
	void setupSprite();
	void processMouseClicks(sf::Event t_event);
	void setupShape();

	sf::RenderWindow m_window; // main SFML window
	sf::Font m_ArialBlackfont; // font used by message
	sf::Text m_welcomeMessage; // text used for message on screen
	sf::Texture m_logoTexture; // texture used for sfml logo
	sf::Sprite m_logoSprite; // sprite used for sfml logo
	bool m_exitGame; // control exiting game

	sf::VertexArray m_points;// vertex array for drawing
	sf::Color m_colour; // drawing colour
	int cornerx[4] ={ 0,128,128,0 };
	int cornery[4] = { 0,0,128,128 };
	int m_index = 0;
	sf::CircleShape m_circle;
	sf::RectangleShape m_rectangel;
};

#endif // !GAME_HPP

