#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Main.hpp>

#ifndef PARTICLE_EFFECT_H
#define PARTICLE_EFFECT_H

#define NUM_OF_PARTICLES 10

using namespace sf;

class ParticleEffect {
private:
	class Particle {
	private:
		Shape* shape;
		Vector2f velocity;
		float lifespan;
	public:
		Particle(float);	// constructor
		bool update(RenderWindow&);
		bool render(RenderWindow&);
		Vector2f getPosition() const;
		bool isAlive() const;
		~Particle();
	};

	Particle* particle;

public:
	ParticleEffect();
	bool update(RenderWindow&);
	bool render(RenderWindow&);
	bool Emit();
	bool AddParticle();
	~ParticleEffect();
};

#endif // ParticleEffect.h