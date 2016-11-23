#ifndef PERLIN_NOISE_H
#define PERLIN_NOISE_H

#include <vector>
#include "abstract_noise.h"
#include "../../../glm_include.h"

class Perlin_Noise : public Noise_Maker {
public:
    Perlin_Noise(int key, int size = 12);
    virtual ~Perlin_Noise();

    double getNoise(double x, double y);

private:
    double rand_noise(int t);

    glm::dvec2 getGradient(glm::ivec2 &position);
    glm::dvec2 getGradient(int x, int y);

    double quintic_poly(const double val);

    int size_;
    std::vector<glm::dvec2> gradients_;
};


#endif // PERLIN_NOISE_H
