#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include <string.h>
#include <iostream>


class Level{
public:
	Level(sf::RenderWindow* hwnd, Input* in);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();

private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();
	void moveCircle(float deltaTime);
	void movePlayer(float deltaTime);
	void alterSpeed();

	sf::CircleShape m_circle;
	sf::CircleShape player;
	sf::Text m_text;
	sf::Font m_font;
	sf::Vector2i m_increment;

	float m_circleSpeed;
	float m_playerSpeed;

	// Default variables for level class.
	sf::RenderWindow* window;
	Input* input;
};