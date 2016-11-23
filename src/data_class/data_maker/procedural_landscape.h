#ifndef PROCEDURAL_LANDSCAPE_H
#define PROCEDURAL_LANDSCAPE_H

#include "src/data_class/database.h"

class Procedural_Landscape {
public:
    static void CreateLandscape(DataBase *data, int resolution);
};

#endif // PROCEDURAL_LANDSCAPE_H
