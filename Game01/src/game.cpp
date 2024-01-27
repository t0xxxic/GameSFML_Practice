
#include "game.h"

void Game::initVariables() {
  window = nullptr;
  points = 0;
  enemySpawnTimer = 0.f;
  enemySpawnTimerMax = 10.f;
  maxEnemies = 5;
  mouseHeld = false;
  health = 10;
  endGame = false;
}

void Game::initEnemies() {
  enemy.setPosition(sf::Vector2f(0.0f, 0.0f));
  enemy.setSize(sf::Vector2f(50.0f, 50.0f));
  enemy.setFillColor(sf::Color(255, 0, 0, 255));
}

void Game::initWindow() {
  window = new sf::RenderWindow(sf::VideoMode(1600, 900, 32U), title,
                                sf::Style::Titlebar | sf::Style::Close,
                                sf::ContextSettings());
  window->setFramerateLimit(240);
}

Game::Game() {
  initVariables();
  initWindow();
  initEnemies();
}

Game::~Game() { delete window; }

const bool Game::isRunning() const { return window->isOpen(); }

const bool Game::getEndGame() const { return endGame; }

void Game::spawnEnemies() {
  /*
  @return void

  Spawns enemy and sets their colors and position
      -Spawns enemies
      -Sets a random color
      -Sets a random position
      -Adds enemy to the vector
  */

  enemy.setPosition(
      static_cast<float>(
          rand() % static_cast<int>(window->getSize().x - enemy.getSize().x)),
      static_cast<float>(enemy.getSize().y));
  enemy.setFillColor(sf::Color(rand() % static_cast<int>(255),
                               rand() % static_cast<int>(255),
                               rand() % static_cast<int>(255), 255));
  enemies.push_back(enemy);
}

void Game::updateEnemies() {

  // updates the timer for enemy spawning
  if (enemies.size() < maxEnemies) {
    if (enemySpawnTimer >= enemySpawnTimerMax) {
      // Spawn the enemies and reset the timer
      spawnEnemies();
      enemySpawnTimer = 0.f;
    } else {
      enemySpawnTimer += 1.f;
    };
  }

  // Move The Enemies
  for (int i = 0; i < enemies.size(); i++) {
    enemies[i].move(0.f, 1.f);

    // Enemy deletes on off-screen
    if (enemies[i].getPosition().y > window->getSize().y) {
      enemies.erase(enemies.begin() + i);
      health -= 1;
    }

    // set deleted bool true if is clicked upon enemy
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      if (mouseHeld == false) {
        mouseHeld = true;
        bool deleted = false;
        for (size_t i = 0; i < enemies.size() && deleted == false; i++) {
          if (enemies[i].getGlobalBounds().contains(mousePosView)) {
            deleted = true;
            enemies.erase(enemies.begin() + i);
            points += 10;
          }
        }
      }
    } else {
      mouseHeld = false;
    }
  }
}

void Game::renderEnemies() {
  for (sf::RectangleShape &e : enemies) {
    window->draw(e);
  }
}

void Game::displayGameOver() {}

void Game::pollEvents() {
  while (window->pollEvent(event)) {
    if (event.type == sf::Event::Closed)
      window->close();
  }
}

void Game::updateMousePosition() {
  mousePosWindow = sf::Mouse::getPosition(*window);
  mousePosView = window->mapPixelToCoords(mousePosWindow);
}

void Game::render() {

  /*
  return @void

      -clears old frame
      -render frame in window
      -display frame in window

  Renders the Game Object
  */

  // Clear Previous Frame
  window->clear();

  // Draw New Frame
  renderEnemies();

  // Display the New Frame
  window->display();
}

void Game::update() {
  pollEvents();
  if (!endGame) {
    updateMousePosition();
    updateEnemies();
  } else {
    displayGameOver();
  }

  // End Game Condition
  if (health <= 0) {
    endGame = true;
  }
}
