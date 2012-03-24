#include "RandomEmitter.h"

RandomEmitter::RandomEmitter(float particlesPerSecond, sf::Time particleLifetime) : thor::Emitter(particlesPerSecond, particleLifetime)
{
    //ctor
}

RandomEmitter::Ptr RandomEmitter::Create(float particlesPerSecond, sf::Time particleLifetime)
{
	return Ptr(new RandomEmitter(particlesPerSecond, particleLifetime));
}

void RandomEmitter::Emit(Adder& system, sf::Time dt)
{
	const unsigned int nbParticles = ComputeNbParticles(dt);

	for (unsigned int i = 0; i < nbParticles; ++i)
	{
		// Create particle and specify parameters
		thor::Particle particle = CreateParticlePrototype();

		// Influence of emission angle
		particle.Velocity = sf::Vector2f(thor::Random(-200, 200), thor::Random(-200, 200));

		system.AddParticle(particle);
		//system.Set

		system.AddParticle(particle);
	}
}
