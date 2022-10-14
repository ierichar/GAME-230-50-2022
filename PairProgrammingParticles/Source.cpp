/**
* Pair Programming Simple Particle Effect Exercise
* 
* Authors: Adam Carter, Ian Richardson
* 
* Started:  October 13th, 2022
* Finished: October 17th, 2022
* 
* Description: This program is a simple Particle and ParticleEffect class to 
*   create a particle effect on left mouse clicks. Specifically, the particle,
*   particle effect, and game classes should have the following 
*   requirements/constraints:
*    - A particle class that maintains a shape, velocity, and lifespan. Your 
*       particles should all be one shape, such as a circle (do NOT worry 
*       about inheritance or polymorphism yet).
*   - A particle effect class that creates and maintains an array of particles.
*       These particles should be stored on and removed from the heap. The 
        array should not be dynamically allocated (i.e., you can make an 
        assumption that it will be the same number of particles 
        created/destroyed every time for the particle effect).
*   - Your game class should be modified so that it maintains a particle effect
*       pointer and creates a new particle effect whenever there is a left 
*       mouse click.
* 
* Controls:
*  LMB - generate particle effect
*/

#include "ParticleEffect.h"

#include <iostream>

using namespace sf;

//*****************************************************************************
// Game Loop Functions
//*****************************************************************************
void handleInput(RenderWindow& window, Event e, ParticleEffect* PE);
void update(ParticleEffect* PE);
void render(RenderWindow& window, ParticleEffect* PE);

//*****************************************************************************
// Constants
//*****************************************************************************
#define WINDOW_W 800
#define WINDOW_H 600

int main()
{
    RenderWindow window(VideoMode(WINDOW_W, WINDOW_H), "Particle Program");

    ParticleEffect* PE = nullptr;

    Event event;
    while (window.isOpen())
    {
        while (window.pollEvent(event))
        {
            handleInput(window, event, PE);
        }
        update(PE);
        render(window, PE);
    }

    return 0;
}

void handleInput(RenderWindow& window, Event e, ParticleEffect* PE) {
    if (e.type == Event::Closed)
        window.close();
    if (e.type == Event::MouseButtonPressed) {
        if (e.mouseButton.button == Mouse::Left) {
            if (PE != nullptr) {
                delete PE;
                PE = nullptr;
            }
            // window.clear(); // Bad practice? (move to render)
            PE = new ParticleEffect();
            PE->Emit(e.mouseButton.x, e.mouseButton.y);
        }
    }
}

void update(ParticleEffect* PE) {
    if (PE != nullptr)
        PE->update();
}

void render(RenderWindow& window, ParticleEffect* PE) {
    if (PE != nullptr)
        PE->render(window);

    window.display();
}