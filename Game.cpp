#include "Game.h"

void Game::initVariables()
{
    this->screenWidth = 800;
    this->screenHeight = 600;
    this->isInMainMenu = true;
    this->endGame = false;
    this->points = 0;
}

void Game::initWindow()
{
    this->videoMode = sf::VideoMode(this->screenWidth, this->screenHeight);
    this->window = new sf::RenderWindow(this->videoMode, "Snek", sf::Style::Close | sf::Style::Titlebar);
    this->window->setFramerateLimit(60);
}

void Game::initFonts()
{
    if(!this->font.loadFromFile("Fonts/DeterminationMonoWebRegular-Z5oq.ttf")){
        std::cout<< "ERROR::GAME::INITFONTS COUlD NOT LOAD DeterminationMonoWebRegular.ttf" <<std::endl;
    }
}

void Game::initText()
{
    //Main menu Text
    this->mainMenuText.setFont(this->font);
    this->mainMenuText.setFillColor(sf::Color::White);
    this->mainMenuText.setCharacterSize(60);
    this->mainMenuText.setPosition(sf::Vector2f(70, 240));
    this->mainMenuText.setString("PRESS W A S D to Start");

    //points
    this->text.setFont(this->font);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(24);
    this->text.setPosition(sf::Vector2f(330, 0));

    //Game over Text
    this->endGameText.setFont(this->font);
    this->endGameText.setFillColor(sf::Color::Red);
    this->endGameText.setCharacterSize(60);
    this->endGameText.setPosition(sf::Vector2f(260, 240));
    this->endGameText.setString("Game Over");
}

// Constructors and Destructors
Game::Game()
{
    this->initVariables();
    this->initWindow();
    this->initFonts();
    this->initText();
}

Game::~Game()
{
    delete this->window;
}

const bool &Game::getEndGame() const
{
    return this->endGame;
}

// Functions
const bool Game::running() const
{
    return this->window->isOpen();
}

void Game::pollEvents()
{
    while(this->window->pollEvent(this->sfmlEvent)){
        switch (this->sfmlEvent.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        case sf::Event::KeyPressed:
            if(this->sfmlEvent.key.code == sf::Keyboard::Escape){
                this->window->close();
            }
        default:
            break;
        }
    }
}

void Game::checkWindowBoundsCollision(sf::RenderTarget *target)
{
    if(this->snek.getShape().getGlobalBounds().left <= 0.f){
        this->endGame = true;
    }
    //Right
    else if(this->snek.getShape().getGlobalBounds().left + this->snek.getShape().getGlobalBounds().width >= target->getSize().x){
        this->endGame = true;
    }

    //Top
    if(this->snek.getShape().getGlobalBounds().top <= 0.f){
        this->endGame = true;
    }
    //Bottom
    else if(this->snek.getShape().getGlobalBounds().top + this->snek.getShape().getGlobalBounds().height >= target->getSize().y){
        this->endGame = true;
    }
}

void Game::updateSnek()
{
    this->snek.update(this->window);
}

void Game::updateCollision()
{
    if(this->snek.getShape().getGlobalBounds().intersects(this->apple.getShape().getGlobalBounds())){
        this->points++;
        this->apple.setPos();
        sf::Vector2f newPosition = this->snek.getShapeBack().getPosition();
        this->snek.updateSnekLength(newPosition);
    }
}

void Game::updateText()
{
    std::stringstream ss;
    ss << "Points: " << this->points <<std::endl;

    this->text.setString(ss.str()); 
}

void Game::update()
{
    this->pollEvents();
    this->updateSnek();
    this->updateCollision();   
    this->updateText();
    this->checkWindowBoundsCollision(this->window);
}

void Game::renderText(sf::RenderTarget *target)
{
    target->draw(this->text);
}

void Game::renderEndGameText(sf::RenderTarget *target)
{
    target->draw(this->endGameText);
}

void Game::render()
{
    //first in each rendering loop, you want 
    //to clear the window first and then do stuff
    this->window->clear();

    //render stuff
    if(this->isInMainMenu == true){
        this->window->draw(this->mainMenuText);
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W) | sf::Keyboard::isKeyPressed(sf::Keyboard::A) | sf::Keyboard::isKeyPressed(sf::Keyboard::S) | sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
            this->isInMainMenu = false;
        }
    }else{
        if(!this->endGame){
            this->window->clear();
            //Render Points Text
            this->renderText(this->window);

            this->snek.render(this->window);
            this->apple.render(this->window);
        }
        else{
            this->renderEndGameText(this->window);
        }
    }

    this->window->display();
}

