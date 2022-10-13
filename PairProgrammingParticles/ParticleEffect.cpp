#include "ParticleEffect.h"

/* Particle */
ParticleEffect::Particle::Particle(float lifespan) {
	shape = new sf::CircleShape;
	this->lifespan = lifespan;
	this->velocity = Vector2f(0., 0.);
}

bool ParticleEffect::Particle::update(RenderWindow&) {

}

bool ParticleEffect::Particle::render(RenderWindow&) {

}

Vector2f ParticleEffect::Particle::getPosition() const {
	return this->shape->getPosition();
}

bool ParticleEffect::Particle::isAlive() const {

}

ParticleEffect::Particle::~Particle() {
	delete shape;
	shape == nullptr;
}

/* Particle Effect */
ParticleEffect::ParticleEffect() {
	;
}