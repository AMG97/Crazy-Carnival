#pragma once
#include "Juego.hpp"
#include "tinyxml.h"
#include "tinystr.h"
#include "box.h"
#include "Objeto.hpp"

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
        void iniciarFisicas();
        void setPosCamara(float _jugadorX, float _jugadorY);
        int getAnchura();
        int getAltura();
        Camara * getCamara();
        void toggleFreeCamera();
        bool isCamFree();
        bool ComprobarColision(float x, float y);
    private:
        map<string,SpriteM***> tilemap;
        vector<string> layers;
        vector<Objeto*> objects;
        vector<Enemigo*> _enemigos;
        
        int width, height;
        Juego* _juego;
        Player* _jugador;
        Camara* _camera; bool freecam;
        b2World* _mundo;
        vector<b2Body*> collisions;
        b2FixtureDef ground_fixdef;
        
        
        
    };

}

