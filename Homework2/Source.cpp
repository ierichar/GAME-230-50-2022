/**
* Homework 2 - Level Editor Tool
* Ian Richardson
* October 3rd, 2022
*
* Description: Using the basic features of SFML, create a
*  basic grid-based level editor tool that allows a user to
*  load, draw, and save a level as well as export a screenshot
*  of the level to share with friends.
*
* Controls:
*  Left Mouse Click - Places the currently selected tile on the
*   grid cell the mouse is hovering over
*  Up Arrow - Goes to the next available tile in the tileset (if you
*   are at the end of available tiles in the tileset, then it will
*   loop around to the first tile).
*  Down Arrow - Goes to the previously available tile in the tileset
*   (if you are at the beginning of available tiles in the tileset,
*   then it will loop around to the last tile).
*  Space Bar - Saves a .png image of your current level to the working
    directory with the filename "Homework 2 Screenshot.png"
*  'l' Key - Saves your current level to a file called "level.txt" in the working directory
*  's' Key - Loads a level from "level.txt" in the working directory into your current level
*/

#include <iostream>

#include "Grid.hpp"

using namespace sf;

/* Game Loop Functions */
void handleInput(RenderWindow& window, Event& e);
void update(RenderWindow& window);
void render(RenderWindow& window, Sprite& sprite);

/* Global Variables */
const int NUM_OF_TILES = 10;
const int WINDOW_W = TILE_SIZE * NUM_OF_TILES;
const int WINDOW_H = TILE_SIZE * NUM_OF_TILES;

int pos_x, pos_y;
Texture texture;

Grid g(WINDOW_W, WINDOW_H);

int main()
{
    RenderWindow window(VideoMode(WINDOW_W, WINDOW_H), "Level Editor");

    Sprite sprite;
    if (!texture.loadFromFile("Tileset/Platformer-0.png"))
        return -1;
    sprite.setTexture(texture);

    Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            handleInput(window, event);
        }
        update(window);
        render(window, sprite);
    }
}

void handleInput(RenderWindow& window, Event& e) {
    if (e.type == Event::Closed)
        window.close();
    if (e.type == Event::MouseButtonPressed &&
        e.mouseButton.button == Mouse::Left)
    {
        std::cout << "x:" << e.mouseButton.x << " ";
        std::cout << "y:" << e.mouseButton.y << std::endl;

        // adjust to estimate
        g.inputTexture(
            e.mouseButton.x, 
            e.mouseButton.y,
            texture);
    }
}

void update(RenderWindow& window) {
    g.update(pos_x, pos_y);
}

void render(RenderWindow& window, Sprite& sprite) {
    window.clear();

    sprite.setPosition(sf::Vector2f(
        Mouse::getPosition().x - WINDOW_W + TILE_SIZE,  
        Mouse::getPosition().y - WINDOW_H/2 + TILE_SIZE));
    window.draw(sprite);
    g.render(window);

    window.display();
}
