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
		//particle.Velocity = sf::Vector2f(thor::Random(0, 50), thor::Random(0, 50));
		sf::Vector2f randDirection(thor::Random(GetEmissionZone().GetPosition().x - 100, GetEmissionZone().GetPosition().x + 100), thor::Random(GetEmissionZone().GetPosition().y - 100, GetEmissionZone().GetPosition().y + 100));
        //if(randDirection != sf::Vector2f())
            particle.Velocity = 200.f * thor::UnitVector(randDirection);
		//system.Set

		system.AddParticle(particle);
	}
}
