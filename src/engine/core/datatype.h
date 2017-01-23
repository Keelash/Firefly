#ifndef DATA
#define DATA

enum DataType {
    DATA_ERR_NOTYPE =   0b0000,
    DATA_MODEL =        0b0001,
    DATA_TEXTURE =      0b0010,
    DATA_FLOAT =        0b0100,
    DATA_INT =          0b1000
};

class Data {
public:
    virtual DataType getType() const = 0;
};

#endif//DATA
