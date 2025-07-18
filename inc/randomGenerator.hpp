#ifndef RANDOM_GENERATOR_HPP
#define RANDOM_GENERATOR_HPP

#include <random>

class RandomGenerator {
public:
    static std::mt19937& getGenerator() {
        static std::random_device rd;
        static std::mt19937 gen(rd());  // is only created once
        return gen;
    }
};

#endif //RANDOM_GENERATOR_HPP
