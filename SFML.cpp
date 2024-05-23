// SFML.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#include <sfml/Graphics.hpp>

#include <SFML/Graphics/Image.hpp>

#include "functions.h"

int main() {

    float cr = 0.f, ci = 0.f;

    std::cout << "Enter 0 0 for mandelbrot and float float for julias set\n";

    std::cin >> cr >> ci;

    sf::Image image;

    sf::Event event;

    sf::Texture texture;

    vec2 constant = { cr, ci }; // { -0.8f, 0.156 };

    sf::Vector2u window_size({ 1980, 1080 });

    sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "test");

    window.setFramerateLimit(60);

    image.create(window_size.x, window_size.y, sf::Color::Black);

    drawNext({ float(window_size.x), float(window_size.y) }, constant, image, abs(cr) < 1e-7 && abs(ci) < 1e-7);

    texture.loadFromImage(image);
    
    while (window.isOpen()) {

        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed) window.close();

            window.clear(sf::Color::Black);

            window.draw(sf::Sprite(texture));

            window.display();
        }
    }
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
