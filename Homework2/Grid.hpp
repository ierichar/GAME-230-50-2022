#ifndef GRID_H
#define GRID_H

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#define TILE_SIZE 70

class Grid {
private:
    int width, height;
    sf::Vertex* vertices;
    sf::Texture** textureGrid;
public:
    //*************************************************************************
    // Constructor/Deconstructor
    //*************************************************************************
    /*
    * Grid()
    * Pre: int, int
    * Constructor that takes width and height int values
    */
    Grid(const int&, const int&);
    ~Grid();
    //*************************************************************************
    // Game Loop Functions
    //*************************************************************************
    /*
    * update()
    * Pre:  int, int
    * Post: void
    * Update function that maintains updated values
    */
    void update(const int&, const int&);
    /*
    * render()
    * Pre:  RenderWindow
    * Post: void
    * Render function that loads sprites into render buffer before display
    */
    void render(sf::RenderWindow&);
    //*************************************************************************
    // Helper Functions
    //*************************************************************************
    void inputTexture(const int&, const int&, sf::Texture&);
};

#endif // Grid