/// <summary>
/// @author Peter Lowe
/// @date December 2019
/// estimate 2 hours
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
	m_window{ sf::VideoMode{ 800U, 600U, 32U }, "SFML Game" },
	m_exitGame{false} //when true game will exit
{
	setupFontAndText(); // load font 
	setupSprite(); // load texture
	setupVertexArray();
	setupShape();
}

/// <summary>
/// default destructor we didn't dynamically allocate anything
/// so we don't need to free it, but mthod needs to be here
/// </summary>
Game::~Game()
{
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
		if (sf::Event::MouseButtonReleased == newEvent.type)
		{
			processMouseClicks(newEvent);
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
	if (sf::Keyboard::Y == t_event.key.code)
	{
		m_colour = sf::Color::Yellow;
	}
	if (sf::Keyboard::B == t_event.key.code)
	{
		m_colour = sf::Color::Blue;
	}
	if (sf::Keyboard::R == t_event.key.code)
	{
		m_colour = sf::Color::Red;
	}
	if (sf::Keyboard::T == t_event.key.code)
	{
		m_points.setPrimitiveType(sf::Triangles);	
	}
	if (sf::Keyboard::Q  == t_event.key.code)
	{
		m_points.setPrimitiveType(sf::Quads);
	}
	if (sf::Keyboard::L == t_event.key.code)
	{
		m_points.setPrimitiveType(sf::LinesStrip);
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
}

/// <summary>
/// draw the frame and then switch buffers
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color::Black);
	m_window.draw(m_points, &m_logoTexture);
	//m_window.draw(m_welcomeMessage);
	//m_window.draw(m_logoSprite);
	m_window.draw(m_circle);
	m_window.draw(m_rectangel);
	m_window.display();
}

void Game::setupVertexArray()
{
	sf::Vertex newVertex;
	m_colour = sf::Color(240, 35, 96, 255);
	m_points.setPrimitiveType(sf::Quads);
	m_points.clear();
	//newVertex.position = sf::Vector2f{ 100.0f,100.0f };
	//newVertex.color = m_colour;
	//m_points.append(newVertex);
	//newVertex.position = sf::Vector2f{ 200.0f,100.0f };
	//newVertex.color = m_colour;
	//m_points.append(newVertex);

	//newVertex.position = sf::Vector2f{ 500.0f,200.0f };
	//newVertex.color = m_colour;
	//m_points.append(newVertex);
	//newVertex.position = sf::Vector2f{ 200.0f,200.0f };
	//newVertex.color = m_colour;
	//m_points.append(newVertex);

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
	m_welcomeMessage.setString("SFML Game");
	m_welcomeMessage.setStyle(sf::Text::Underlined | sf::Text::Italic | sf::Text::Bold);
	m_welcomeMessage.setPosition(40.0f, 40.0f);
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

void Game::processMouseClicks(sf::Event t_event)
{

	sf::Vertex newVertex;
	newVertex.position.x = t_event.mouseButton.x;
	newVertex.position.y = t_event.mouseButton.y;
	newVertex.color = sf::Color::White;
	newVertex.texCoords.x = cornerx[m_index];
	newVertex.texCoords.y = cornery[m_index];
	m_index = (m_index + 1)% 4;

	if (sf::Mouse::Left == t_event.mouseButton.button)
	{
		m_colour.r = (m_colour.r + 20U) % 255;
		std::cout << m_colour.r << std::endl;
	}
	else
	{
		m_colour.r = (m_colour.r - 20U) % 255;
		std::cout << m_colour.r << std::endl;
	}
	m_points.append(newVertex);
}

void Game::setupShape()
{
	m_circle.setFillColor( sf::Color::Red);
	m_circle.setRadius(550.0f);
	m_circle.setPosition(400.0f, 400.0f);
	m_circle.setPointCount(120);

	m_rectangel.setFillColor(sf::Color::Green);
	m_rectangel.setPosition(10, 10);
	m_rectangel.setSize(sf::Vector2f(50.0f, 200.0f));
}
