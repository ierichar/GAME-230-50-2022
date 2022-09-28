#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#include <iostream>

/**
* Homework 1 - Simple SFML Painting Tool
* Ian Richardson
* September 27th, 2022
* 
* Description: A simple paint tool that allows for different brush options
*  and the ability to save the window as a screenshot.
* 
* Controls:
*  Move mouse - draw
*  r - set color red
*  g - " green
*  b - " blue
*  mouse wheel up - increase brush radius
*  mouse wheel down - decrease brush radius
*  p - save window as screenshot
*/

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Ian Drawing Program (IDP)");

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Image screenshot;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            // Press r, g, b for (r)ed, (g)reen, (b)lue
            // Save RGB colors on brush
            if ((event.type == sf::Event::KeyPressed) &&
                (event.key.code == sf::Keyboard::R))
                shape.setFillColor(sf::Color::Red);
            if ((event.type == sf::Event::KeyPressed) &&
                (event.key.code == sf::Keyboard::G))
                shape.setFillColor(sf::Color::Green);
            if ((event.type == sf::Event::KeyPressed) &&
                (event.key.code == sf::Keyboard::B))
                shape.setFillColor(sf::Color::Blue);

            // Scroll down/up
            // Adjust size of brush based on mouse wheel up or down
            if (event.type == sf::Event::MouseWheelMoved)
                if (event.mouseWheel.delta > 0)
                    shape.setRadius(shape.getRadius() + 4);
                else shape.setRadius(shape.getRadius() - 4);
            
            // Space key creates a screenshot
            if ((event.type == sf::Event::KeyPressed) &&
                (event.key.code == sf::Keyboard::Space)) {
                sf::Texture texture;
                texture.create(window.getSize().x, window.getSize().y);
                texture.update(window);
                if (texture.copyToImage().saveToFile("Homework 1 Screenshot.png"))
                {
                    std::cout << "Screenshot saved to Homework 1 Screenshot.png" << std::endl;
                }
            }
        }

        // window.clear();
        shape.setPosition(
            sf::Mouse::getPosition(window).x - shape.getRadius(), 
            sf::Mouse::getPosition(window).y - shape.getRadius());
        window.draw(shape);
        window.display();
    }

    return 0;
}