#include "perlin_noise.h"

#include <iostream>

Perlin_Noise::Perlin_Noise(int key, int size) :Noise_Maker(key), size_(size) {
    glm::dvec2 gradient;

    for(int i = 0; i < 2*size*size; i += 2) {
        gradient = glm::dvec2(rand_noise(i + key), rand_noise(i + key + 325));

        this->gradients_.push_back(glm::normalize(gradient));
    }
}

Perlin_Noise::~Perlin_Noise() {

}

double Perlin_Noise::getNoise(double x, double y) {
    int X, Y, Xn, Yn;
    double g00, g01, g10, g11, u, v, l_x0, l_x1;

    X = (x > 0)? (int)x : (int)x - 1;
    Y = (y > 0)? (int)y : (int)y - 1;

    x = x - X;
    y = y - Y;

    X %= this->size_;
    Y %= this->size_;

    Xn = (X+1)%this->size_;
    Yn = (Y+1)%this->size_;

    u = this->quintic_poly(x);
    v = this->quintic_poly(y);

    g00 = glm::dot(this->getGradient(X, Y), glm::dvec2(x, y));
    g01 = glm::dot(this->getGradient(X, Yn), glm::dvec2(x, y - 1.0));
    g10 = glm::dot(this->getGradient(Xn, Y), glm::dvec2(x - 1.0, y));
    g11 = glm::dot(this->getGradient(Xn, Yn), glm::dvec2(x - 1.0, y - 1.0));


    l_x0 = u * g10 + (1.0 - u) * g00;
    l_x1 = u * g11 + (1.0 - u) * g01;


    return v * l_x1 + (1.0 - v) * l_x0;
}

static double noise_div = 1 / 1073741824.0;
double Perlin_Noise::rand_noise(int t) {
    t = (t<<13) ^ t;
    t = (t * (t * t * 15731 + 789221) + 1376312589);
    return 1.0 - (t & 0x7fffffff) * noise_div;
}

glm::dvec2 Perlin_Noise::getGradient(glm::ivec2 &position) {
    return this->gradients_[position.x  + position.y * this->size_];
}

glm::dvec2 Perlin_Noise::getGradient(int x, int y) {
    return this->gradients_[x + y * this->size_];
}

double Perlin_Noise::quintic_poly(const double val) {
    double val_3 = val * val * val;

    return val_3 * (val * (val * 6.0 - 15.0) + 10.0);
}
