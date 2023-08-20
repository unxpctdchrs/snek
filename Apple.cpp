#include "Apple.h"

void Apple::initShape()
{
    this->setPos();
    this->shape.setRadius(6.f);
    this->shape.setFillColor(sf::Color::Red);
}


Apple::Apple() //sf::RenderWindow &window
{
    this->initShape();
}

Apple::~Apple()
{

}

void Apple::setPos()
{
    this->shape.setPosition(sf::Vector2f(
        static_cast<float>(rand() % 600), 
        static_cast<float>(rand() % 400)
    ));
}

const sf::CircleShape &Apple::getShape() const
{
    return this->shape;
}

void Apple::update()
{

}

void Apple::render(sf::RenderTarget *target)
{
    target->draw(this->shape);
}
