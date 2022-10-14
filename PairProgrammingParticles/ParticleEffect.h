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

#define LO -5.f
#define HI 5.f

using namespace sf;

class ParticleEffect {
private:
	class Particle {
	private:
		CircleShape* shape;
		Vector2f velocity;
		float lifespan;

	public:
		// Constructors & Deconstructors
		Particle(const std::string&, Vector2f&, const float, Vector2f&);
		~Particle();

		// Game Loop Functions
		void update();
		void render(RenderWindow&);

		// Helper Functions
		Vector2f getPosition() const;
		bool isAlive() const;
	};

	Particle* particles[NUM_OF_PARTICLES];

public:
	// Constructors & Deconstructors
	ParticleEffect();
	~ParticleEffect();

	// Game Loop Functions
	void update();
	void render(RenderWindow&);

	// Helper Functions
	void Emit(const float, const float);
	void AddParticle(short, const std::string&, Vector2f&, const float, 
		Vector2f&);
	float RandomFloat() const;
};


#endif // ParticleEffect.h