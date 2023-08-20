#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

class Apple{
private:
    sf::CircleShape shape;
    void initShape();

public:
    Apple();
    virtual ~Apple();

    void setPos();
    const sf::CircleShape& getShape() const;

    void update();
    void render(sf::RenderTarget* target);
};