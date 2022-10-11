/**
* Homework 2 - Level Editor Tool
* Ian Richardson
* Started:  October 3rd, 2022
* Finished: October 10th, 2022
*
* Description: Using the basic features of SFML, create a
*  basic grid-based level editor tool that allows a user to
*  load, draw, and save a level as well as export a screenshot
*  of the level to share with friends.
* 
*/

#include <iostream>
#include <stdlib.h>

#include "Grid.hpp"

using namespace sf;

//*****************************************************************************
// Game Loop Functions
//*****************************************************************************
/*
* initialize()
* Load textures into an array to swap between tiles
*/
bool initialize();
/*
* handleInput()
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
void handleInput(RenderWindow& window, Event& e);
/*
* update()
* Updates every tick for grid and current sprite
*/
void update(RenderWindow& window);
/*
* render()
* Render the current window and sprite from set texture
*/
void render(RenderWindow& window, Sprite& sprite);

//*****************************************************************************
// Helper Functions
//*****************************************************************************
/*
* cycleTile()
* Pre:  Sprite, direction (0 - up, 1 - down)
* Post: a selected texture
* Up/down cycles through set 20 tiles
*/
Texture& cycleTile(Sprite& sprite, const short direction);

//*****************************************************************************
// Global Variables
//*****************************************************************************
const int NUM_OF_TILES = 10;
const int WINDOW_W = TILE_SIZE * NUM_OF_TILES;
const int WINDOW_H = TILE_SIZE * NUM_OF_TILES;

int pos_x, pos_y;
Sprite sprite;
Texture current_texture;
static int counter;

Texture* texArray;

Grid g(NUM_OF_TILES, NUM_OF_TILES);

int main()
{
    if (!initialize())
        return -1;

    RenderWindow window(VideoMode(WINDOW_W, WINDOW_H), "Level Editor");

    sprite.setTexture(texArray[0]);

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

/* Game Loop Functions */
bool initialize() {
    int filenum = 0;
    std::string filename = "Tileset/Platformer-";
    filename.append(std::to_string(filenum) + ".png");
    texArray = new Texture[21]; // 20 is static to number of files

    for (int i = 0; i < 21; i++) {
        if (!texArray[i].loadFromFile(filename))
            return -1;
        filename.erase(filename.find_first_of('-') + 1, filename.length());
        filename.append(std::to_string(++filenum) + ".png");
    }
    current_texture = texArray[0];
}

void handleInput(RenderWindow& window, Event& e) {
    // Close window
    if (e.type == Event::Closed)
        window.close();
    if (e.type == Event::MouseButtonPressed) {
        if (e.mouseButton.button == Mouse::Left) {
            g.inputTexture(
                e.mouseButton.x,
                e.mouseButton.y,
                current_texture);
        }
        if (e.mouseButton.button == Mouse::Right) {
            // Remove texture function
        }
    }
    if (e.type == Event::KeyPressed) {
        // Up-Down cycles tile selection
        if (e.key.code == Keyboard::Up)
            current_texture = cycleTile(sprite, 0);
        if (e.key.code == Keyboard::Down)
            current_texture = cycleTile(sprite, 1);

        // Space key creates a screenshot
        if (e.key.code == sf::Keyboard::Space) {
            sf::Texture texture;
            texture.create(window.getSize().x, window.getSize().y);
            texture.update(window);
            if (texture.copyToImage().saveToFile("Homework 2 Screenshot.png"))
            {
                std::cout << "Screenshot saved to Homework 2 Screenshot.png" << std::endl;
            }
        }
    }
}

void update(RenderWindow& window) {
    g.update(pos_x, pos_y);
    sprite.setTexture(current_texture);
}

void render(RenderWindow& window, Sprite& sprite) {
    window.clear();

    // Show current tile on cursor
    sprite.setPosition(sf::Vector2f(
        Mouse::getPosition().x - WINDOW_W + TILE_SIZE,  
        Mouse::getPosition().y - WINDOW_H/2 + TILE_SIZE));
    window.draw(sprite);

    g.render(window);

    window.display();
}

/* Helper Functions */
Texture& cycleTile(Sprite& sprite, const short direction) {
    if (counter < 0)
        counter = 20;
    else if (counter > 20)
        counter = 0;

    // up
    if (direction == 0) {
        counter++;
        return texArray[counter];
    }
    // down
    counter--;
    return texArray[counter];
}