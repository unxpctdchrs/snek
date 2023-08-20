#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

enum DIRECTION{UP = 0, DOWN, LEFT, RIGHT};

class Snek{
private:
    std::vector<sf::RectangleShape> shape;
    
    float movementSpeed;
    float snekWidth;
    float snekHeight;

    void initVariables();
    void initShape();
    DIRECTION dir;
public:
    Snek();
    virtual ~Snek();
    void reset();
    //Accessors
    const sf::RectangleShape& getShape() const;  
    const sf::RectangleShape& getShapeBack() const;  
    const float& getSize() const;  

    //Modifiers
    
    //Functions
    void keyboardInput();
    void updateInput();
    void updateSnekLength(sf::Vector2f position);
    void updateWindowBoundsCollision(const sf::RenderTarget* target);
    void update(sf::RenderTarget* target);
    void render(sf::RenderTarget* target);
};
