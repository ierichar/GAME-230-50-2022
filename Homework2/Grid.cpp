#include "Grid.hpp"

Grid::Grid(const int& w, const int& h) {
    this->width = w;
    this->height = h;

    // based on the WIDTH_W and WIDTH_H values
    // considering the 70x70 tiles used
    textureGrid = new sf::Texture* [h];
    for (short i = 0; i < h; ++i) {
        textureGrid[i] = new sf::Texture[w];
    }
    vertices = new sf::Vertex[5];
}

Grid::~Grid() {
    if (textureGrid == nullptr)
        return;
    if (vertices == nullptr)
        return;
    for (short i = 0; i < this->height; i++) {
        textureGrid[i] = nullptr;
    }
}

void Grid::inputTexture(const int& mouse_x, const int& mouse_y, 
    sf::Texture texture) {

    // Find the modulus of the given mouse x and y to fill the 
    //  array with the selected texture
    int x = mouse_x % 10;
    int y = mouse_y % 10;

    textureGrid[y][x] = texture;

    // Round the selected point to the corner vertex position
    x = mouse_x - x;
    y = mouse_y - y;

    vertices[0] = sf::Vertex(
        sf::Vector2f(x, y), sf::Color::Red, sf::Vector2f(0, 0));
    vertices[1] = sf::Vertex(
        sf::Vector2f(x, y + TILE_SIZE), sf::Color::Red, sf::Vector2f(0, 10));
    vertices[2] = sf::Vertex(
        sf::Vector2f(x + TILE_SIZE, y + TILE_SIZE), 
        sf::Color::Red, sf::Vector2f(10, 10));
    vertices[3] = sf::Vertex(
        sf::Vector2f(x + TILE_SIZE, y), sf::Color::Red, sf::Vector2f(10, 0));
    vertices[4] = sf::Vertex(
        sf::Vector2f(x, y), sf::Color::Red, sf::Vector2f(0, 0));
}

void Grid::update(const int& x, const int& y) {

}

void Grid::render(sf::RenderWindow& window) {
    // Draw highlighted area
    window.draw(vertices, 5, sf::LineStrip);

    // Draw remaining grid (static 21)
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            sprite.setTexture(textureGrid[i][j]);
            window.draw(sprite);
}
