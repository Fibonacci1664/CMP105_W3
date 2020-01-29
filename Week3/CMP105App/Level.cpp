#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects

	m_circle.setRadius(20);
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setOrigin(sf::Vector2f(m_circle.getRadius(), m_circle.getRadius()));
	m_circle.setOutlineColor(sf::Color::Yellow);
	m_circle.setOutlineThickness(2);
	m_circle.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));

	player.setRadius(30);
	player.setFillColor(sf::Color::Yellow);
	player.setOrigin(sf::Vector2f(player.getRadius(), player.getRadius()));
	player.setOutlineColor(sf::Color::Red);
	player.setOutlineThickness(2);
	player.setPosition(sf::Vector2f(window->getSize().x / 2, window->getSize().y / 2));

	m_circleSpeed = 10;

	if (!m_font.loadFromFile("font/arial.ttf"))
	{
		std::cerr << "Error loading file!\n";
	}

	m_text.setFont(m_font);
	m_text.setCharacterSize(16);
	m_text.setString("Current Speed = " + std::to_string(m_circleSpeed));
	m_text.setOrigin(sf::Vector2f(m_text.getLocalBounds().width / 2, m_text.getLocalBounds().height / 2));
	m_text.setPosition(sf::Vector2f(window->getSize().x / 2, 50));
	m_text.setFillColor(sf::Color::Red);

	m_increment = sf::Vector2i(4, 4);
	m_playerSpeed = 200;
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	movePlayer(dt);
	alterSpeed();
}

// Update game objects
void Level::update(float dt)
{
	moveCircle(dt);
	m_text.setString("Current Speed = " + std::to_string(m_circleSpeed));
}

void Level::moveCircle(float deltaTime)
{
	if ((m_circle.getPosition().x + m_circle.getRadius() > window->getSize().x && m_increment.x > 0)
		|| (m_circle.getPosition().x - m_circle.getRadius() < 0 && m_increment.x < 0))
	{
		m_increment.x = -m_increment.x;
	}

	if ((m_circle.getPosition().y + m_circle.getRadius() > window->getSize().y && m_increment.y > 0)
		|| (m_circle.getPosition().y - m_circle.getRadius() < 0 && m_increment.y < 0))
	{
		m_increment.y = -m_increment.y;
	}

	// When to specify an sf::Vector and when not to??
	m_circle.setPosition(sf::Vector2f(m_circle.getPosition().x + (m_increment.x * m_circleSpeed * deltaTime), m_circle.getPosition().y + (m_increment.y *m_circleSpeed * deltaTime)));
}

void Level::alterSpeed()
{
	if (input->isKeyDown(sf::Keyboard::Add))
	{
		input->setKeyUp(sf::Keyboard::Add);
		m_circleSpeed += 1;
	}

	if (input->isKeyDown(sf::Keyboard::Subtract))
	{
		input->setKeyUp(sf::Keyboard::Subtract);
		m_circleSpeed -= 1;
	}

	if (m_circleSpeed <= 0)
	{
		m_circleSpeed = 1;
	}
}

void Level::movePlayer(float deltaTime)
{
	if (input->isKeyDown(sf::Keyboard::Left))
	{
		// Move left, checking bounds.
		player.setPosition(sf::Vector2f(player.getPosition().x - (m_playerSpeed * deltaTime), player.getPosition().y));
		
		if (player.getPosition().x - player.getRadius() < 0)
		{
			player.setPosition(sf::Vector2f(0 + player.getRadius(), player.getPosition().y));
		}
	}

	if (input->isKeyDown(sf::Keyboard::Right))
	{
		// Move right, checking bounds.
		player.setPosition(sf::Vector2f(player.getPosition().x + (m_playerSpeed * deltaTime), player.getPosition().y));

		if (player.getPosition().x + player.getRadius() > window->getSize().x)
		{
			player.setPosition(sf::Vector2f(window->getSize().x - player.getRadius(), player.getPosition().y));
		}
	}	

	if (input->isKeyDown(sf::Keyboard::Up))
	{
		// Move up, checking bounds.
		player.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y - (m_playerSpeed * deltaTime)));

		if (player.getPosition().y - player.getRadius() < 0)
		{
			player.setPosition(sf::Vector2f(player.getPosition().x, 0 + player.getRadius()));
		}
	}

	if (input->isKeyDown(sf::Keyboard::Down))
	{
		// Move down, checking bounds.
		player.setPosition(sf::Vector2f(player.getPosition().x, player.getPosition().y + (m_playerSpeed * deltaTime)));

		if (player.getPosition().y + player.getRadius() > window->getSize().y)
		{
			player.setPosition(sf::Vector2f(player.getPosition().x, window->getSize().y - player.getRadius()));
		}
	}
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(m_circle);
	window->draw(player);
	window->draw(m_text);
	endDraw();
}

// clear back buffer
void Level::beginDraw()
{
	window->clear(sf::Color(100, 149, 237));
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}