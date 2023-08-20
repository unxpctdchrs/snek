#include "Snek.h"

void Snek::initVariables()
{
    this->movementSpeed = 3.f;
    this->snekWidth = 20.f;
    this->snekHeight = 20.f;
}

void Snek::initShape()
{
    for (int i = 0; i < 1; ++i) {
        sf::RectangleShape segment(sf::Vector2f(this->snekWidth, this->snekHeight));
        segment.setFillColor(sf::Color::Cyan);
        segment.setPosition(400 + i * this->snekWidth, 350);
        this->shape.push_back(segment);
    }    
}

Snek::Snek()
{   
    this->initVariables();
    this->initShape();
}

Snek::~Snek()
{

}

void Snek::reset()
{
    this->initVariables();
    this->initShape();
}

const sf::RectangleShape &Snek::getShape() const
{
    return shape.back();
}

const sf::RectangleShape &Snek::getShapeBack() const
{
    if(!this->shape.empty()){
        return this->shape.back();
    }    
}

const float &Snek::getSize() const
{
    return this->snekWidth;
}

void Snek::keyboardInput()
{
    //store the previous direction
    DIRECTION previousDir = this->dir;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->dir = UP;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->dir = LEFT;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->dir = DOWN;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->dir = RIGHT;
    }

    //check the current input so the snake can't make a 180 degrees turn
    if ((previousDir == LEFT && this->dir == RIGHT) ||
        (previousDir == RIGHT && this->dir == LEFT) ||
        (previousDir == UP && this->dir == DOWN) ||
        (previousDir == DOWN && this->dir == UP)) {
        this->dir = previousDir;
    }
}

void Snek::updateInput()
{
    //Keyboard input
    this->keyboardInput();

    //update the head
    if(this->dir == UP){
        this->shape[0].setPosition(this->shape[0].getPosition() + sf::Vector2f(0.f, -this->movementSpeed));
    }
    if(this->dir == LEFT){
        this->shape[0].setPosition(this->shape[0].getPosition() + sf::Vector2f(-this->movementSpeed, 0.f));
    }
    if(this->dir == DOWN){
        this->shape[0].setPosition(this->shape[0].getPosition() + sf::Vector2f(0.f, this->movementSpeed));
    }
    if(this->dir == RIGHT){
        this->shape[0].setPosition(this->shape[0].getPosition() + sf::Vector2f(this->movementSpeed, 0.f));
    }

    // Update the rest of the body segments
    for (size_t i = this->shape.size() - 1; i > 0; i--) {
        this->shape[i].setPosition(this->shape[i - 1].getPosition());
    }
}

void Snek::updateSnekLength(sf::Vector2f position)
{
    sf::RectangleShape newSegment(sf::Vector2f(this->getSize(), this->getSize()));
    newSegment.setFillColor(sf::Color::Cyan);
    newSegment.setPosition(position);
    this->shape.push_back(newSegment);
}

void Snek::updateWindowBoundsCollision(const sf::RenderTarget *target)
{
    //UPDATE BOUNDS EVERY POSITION CHANGE
    //Left
    if(this->shape[0].getGlobalBounds().left <= 0.f){
        this->shape[0].setPosition(0.f, this->shape[0].getGlobalBounds().top);
    }
    //Right
    else if(this->shape[0].getGlobalBounds().left + this->shape[0].getGlobalBounds().width >= target->getSize().x){
        this->shape[0].setPosition(target->getSize().x - this->shape[0].getGlobalBounds().width, this->shape[0].getGlobalBounds().top);
    }

    //Top
    if(this->shape[0].getGlobalBounds().top <= 0.f){
        this->shape[0].setPosition(this->shape[0].getGlobalBounds().left, 0.f);
    }
    //Bottom
    else if(this->shape[0].getGlobalBounds().top + this->shape[0].getGlobalBounds().height >= target->getSize().y){
        this->shape[0].setPosition(this->shape[0].getGlobalBounds().left, target->getSize().y - this->shape[0].getGlobalBounds().height);
    }
}

void Snek::update(sf::RenderTarget *target)
{
    this->updateInput();
    this->updateWindowBoundsCollision(target);
}

void Snek::render(sf::RenderTarget *target)
{
    for (const auto &segment : this->shape)
    {
        target->draw(segment);    
    }  
}
