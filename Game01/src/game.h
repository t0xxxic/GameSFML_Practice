#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <ctime>
#include <iostream>
#include <sstream>
#include <vector>

class Game {
private:
  // variables
  sf::RenderWindow *window;
  sf::Event event;
  const sf::String title = "Game01";

  // MousePosition
  sf::Vector2i mousePosWindow;
  sf::Vector2f mousePosView;

  // Resources
  sf::Font font;

  // Text
  sf::Text uiText;

  // Game Objects
  std::vector<sf::RectangleShape> enemies;
  sf::RectangleShape enemy;

  // GameLogics
  unsigned points;
  float enemySpawnTimer;
  float enemySpawnTimerMax;
  int maxEnemies;
  bool mouseHeld;
  int health;
  bool endGame;

  // privateFunction
  void initWindow();
  void initVariables();
  void initEnemies();
  void initFonts();
  void initText();

public:
  // Const/Dest
  Game();
  virtual ~Game();

  // Accessors
  const bool isRunning() const;
  const bool getEndGame() const;

  // Functions
  void spawnEnemies();
  void updateEnemies();
  void updateText();
  void displayGameOver();

  void pollEvents();
  void updateMousePosition();

  void render();
  void renderEnemies();
  void renderText();
  void update();
};
