#pragma once
#include "Juego.hpp"
#include "tinyxml.h"
#include "tinystr.h"

#define INT_MAX 2147483647

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
    private:
        map<string,SpriteM***> tilemap;
        int width, height;
        Juego* instance;
        Camara* camera;
    };

}

