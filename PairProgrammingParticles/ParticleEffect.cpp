#include "ParticleEffect.h"

using namespace sf;

//*****************************************************************************
// Particle 
//*****************************************************************************
// Constructors & Deconstructors
ParticleEffect::Particle::Particle(const std::string& str_shape, 
	Vector2f& initialPosition, const float lifespan, 
	Vector2f& initialVelocity) {
	if (str_shape == "Circle")
		shape = new sf::CircleShape;
	shape->setPosition(initialPosition);
	
	// Add params later
	shape->setRadius(200);
	shape->setFillColor(sf::Color::Red);

	this->lifespan = lifespan;
	this->velocity = initialVelocity;
}

ParticleEffect::Particle::~Particle() {
	delete shape;
	shape = nullptr;
}

// Game Loop Functions
void ParticleEffect::Particle::update() {
	shape->setPosition(shape->getPosition() - velocity);

	// Test speed relative to framerate
	lifespan -= 0.01f;
}

void ParticleEffect::Particle::render(RenderWindow& window) {
	window.draw(*shape);
}

// Helper Functions
Vector2f ParticleEffect::Particle::getPosition() const {
	return this->shape->getPosition();
}

bool ParticleEffect::Particle::isAlive() const {
	if (lifespan <= 0)
		return false;
	return true;
}

//*****************************************************************************
// ParticleEffect
//*****************************************************************************
ParticleEffect::ParticleEffect() {
	for (auto x : particles)
		x = nullptr;
}

ParticleEffect::~ParticleEffect() {
	for (auto x : particles) {
		delete x;
		x = nullptr;
	}
}

void ParticleEffect::update() {
	for (auto x : particles)
		x->update();
}

void ParticleEffect::render(RenderWindow& window) {
	for (auto x : particles)
		x->render(window);
}

void ParticleEffect::Emit(const float x, const float y) {
	// Applies force to particles (start moving here)
	Vector2f temp, position;
	position.x = x;
	position.y = y;
	for (short i = 0; i < NUM_OF_PARTICLES; ++i) {
		temp.x = RandomFloat();
		temp.y = RandomFloat();
		this->AddParticle(i, "Circle", position, 100000, temp);
	}
}

void ParticleEffect::AddParticle(short i, const std::string& str_shape,
	Vector2f& initialPosition, const float lifespan, Vector2f& initialVector) {

	particles[i] = new Particle(str_shape, initialPosition, lifespan, 
		initialVector);
}

float ParticleEffect::RandomFloat() const {
	// Credit to:
	//https://stackoverflow.com/questions/686353/random-float-number-generation
	srand((unsigned)time(NULL));
	float random = LO + static_cast <float> (rand()) /
		(static_cast <float> (RAND_MAX / (HI - LO)));
	return random;
}
