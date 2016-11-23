#ifndef FRACTIONAL_BROWNIAN_MOTION_H
#define FRACTIONAL_BROWNIAN_MOTION_H


#include <memory>
#include <typeinfo>
#include "abstract_noise.h"

class Fractional_Brownian_Motion : public Abstract_Noise2D {
public:
    Fractional_Brownian_Motion(int octaves, double frequency, double persistance, Noise_Maker* noise_maker);
    ~Fractional_Brownian_Motion() {  }

    double getNoise(double x, double y);
private:
    int octaves_;
    double frequency_;
    double persistance_;

    Abstract_Noise2D* noise_maker_;
};

Fractional_Brownian_Motion::Fractional_Brownian_Motion(int octaves, double frequency, double persistance, Noise_Maker* noise_maker):
    octaves_(octaves),
    frequency_(frequency),
    persistance_(persistance),
    noise_maker_(noise_maker)
{
}

double Fractional_Brownian_Motion::getNoise(double x, double y) {
    double amplitude = 1.0;
    double f = this->frequency_;
    double r = 0.0;
    double geo_lim;

    for (int i = 0; i < this->octaves_; i++) {
        r += this->noise_maker_->getNoise(x * f, y * f) * amplitude;
        amplitude *= this->persistance_;
        f *= 2;
    }

    geo_lim = (1 - this->persistance_) / (1 - amplitude);
    return r * geo_lim;
}


#endif // FRACTIONAL_BROWNIAN_MOTION_H
