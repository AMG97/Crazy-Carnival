#pragma once
#include "Juego.hpp"
#include "tinyxml.h"
#include "tinystr.h"

#define INT_MAX_VALUE 2147483648

using namespace std;

namespace Crazy{
class Nivel {
    public:
        Nivel();
        Nivel(const Nivel& orig);
        virtual ~Nivel();
        
        void cargarNivel(unsigned short int l);
        void update();
        void draw(string capa);
        void clear();
    private:
        map<string,SpriteM***> tilemap;
        vector<string> layers;
        int width, height;
        Juego* instance;
        Camara* camera;
    };

}

