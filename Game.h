#pragma once
#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>

#include <SFML/Graphics.hpp>

#include "Snek.h"
#include "Apple.h"

class Game{
    private:
        int screenWidth;
        int screenHeight;
        sf::VideoMode videoMode;
        sf::RenderWindow* window;
        bool isInMainMenu;
        bool endGame;
        sf::Event sfmlEvent;

        Snek snek;
        Apple apple;

        int points;

        sf::Font font;
        sf::Text text;
        sf::Text mainMenuText;
        sf::Text endGameText;

        void initVariables();
        void initWindow();
        void initFonts();
        void initText();

    public:
        //Constructors and Destructors
        Game();
        ~Game();
        //Accessor
        const bool& getEndGame() const;

        //Functions
        const bool running() const;
        void pollEvents();

        void checkWindowBoundsCollision(sf::RenderTarget *target);
        void updateSnek();
        void updateCollision();
        void updateText();
        void update();

        void renderText(sf::RenderTarget* target);
        void renderEndGameText(sf::RenderTarget* target);
        void render();
};