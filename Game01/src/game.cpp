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

void Game::initFonts() {
  if (!font.loadFromFile("assets/fonts/astonpoliz.ttf")) {
    std::cout << "Error :: Game :: Init Font :: Failed to load font!"
              << std::endl;
  }
}

void Game::initText() {
  uiText.setFont(font);
  uiText.setPosition(20, 20);
  uiText.setCharacterSize(24);
  uiText.setFillColor(sf::Color(255, 0, 0, 255));
  uiText.setString("TEXT");
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
  initFonts();
  initText();
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
  int type = rand() % 5;
  switch (type) {
  case 0:
    enemy.setFillColor(sf::Color::Red);
    enemy.setSize(sf::Vector2f(15.0f, 15.0f));
    break;
  case 1:
    enemy.setFillColor(sf::Color::Green);
    enemy.setSize(sf::Vector2f(25.0f, 25.0f));
    break;
  case 2:
    enemy.setFillColor(sf::Color::Blue);
    enemy.setSize(sf::Vector2f(35.0f, 35.0f));
    break;
  case 3:
    enemy.setFillColor(sf::Color::Cyan);
    enemy.setSize(sf::Vector2f(45.0f, 45.0f));
    break;
  case 4:
    enemy.setFillColor(sf::Color::Magenta);
    enemy.setSize(sf::Vector2f(50.0f, 50.0f));
    break;
  default:
    enemy.setFillColor(sf::Color::Yellow);
    enemy.setSize(sf::Vector2f(65.0f, 65.0f));
    break;
  }

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
    enemies[i].move(0.f, 0.7f);

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

            if (enemies[i].getFillColor() == sf::Color::Red) {
              points += 10;
              health += 1;
            }
            if (enemies[i].getFillColor() == sf::Color::Green)
              points += 10;
            if (enemies[i].getFillColor() == sf::Color::Blue)
              points += 7;
            if (enemies[i].getFillColor() == sf::Color::Cyan)
              points += 5;
            if (enemies[i].getFillColor() == sf::Color::Magenta)
              points += 3;

            deleted = true;
            enemies.erase(enemies.begin() + i);
          }
        }
      }
    } else {
      mouseHeld = false;
    }
  }
}

void Game::updateText() {
  std::stringstream ss;

  ss << "Points : " << points << "\n"
     << "Health : " << health << std::endl;
  uiText.setString(ss.str());
}

void Game::renderEnemies() {
  for (sf::RectangleShape &e : enemies) {
    window->draw(e);
  }
}

void Game::renderText() { window->draw(uiText); }

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
  renderText();

  // Display the New Frame
  window->display();
}

void Game::update() {
  pollEvents();
  updateText();
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
