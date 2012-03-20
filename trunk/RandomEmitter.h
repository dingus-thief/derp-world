#ifndef RANDOMEMITTER_H
#define RANDOMEMITTER_H
#include <Thor/Math/Random.hpp>
#include <Thor/Particles/Emitter.hpp>


class RandomEmitter : public thor::Emitter
{
    public:
        typedef std::tr1::shared_ptr<RandomEmitter> Ptr;

        static Ptr Create(float particlesPerSecond, sf::Time particleLifetime);

        RandomEmitter(float particlesPerSecond, sf::Time particleLifetime);

        virtual void Emit(Adder& system, sf::Time dt);

    private:
};

#endif // RANDOMEMITTER_H
