#ifndef ABSTRACT_NOISE_H
#define ABSTRACT_NOISE_H

class Abstract_Noise2D {
public:
    virtual double getNoise(double x, double y) = 0;
};

class Noise_Maker : public Abstract_Noise2D {
public:
    Noise_Maker(int key): key_(key) {  }

protected:
    int key_;
};

#endif // ABSTRACT_NOISE_H

