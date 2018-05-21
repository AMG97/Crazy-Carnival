#pragma once
#include "Enemigo.hpp"
#include "Arma.hpp"
#include "Juego.hpp"
#include "Proyectil.hpp"

#define T_ENTRADA 9
#define T_MUERTE 4
#define VIDA 250

namespace Crazy
{
    class Player;
    class BossCangrejo: public Enemigo {
    public:
        BossCangrejo(float posx, float posy);
        BossCangrejo(const BossCangrejo& orig);
        virtual ~BossCangrejo();
        void Update(int Posx, int Posy, Player *p);
        void Update(int Posx, int Posy);
        void Dibujar();
        void ModificarSpriteCorrer();
        void ModificarSpriteAtaque1();
        void ModificarSprite();
        void ModificarSpriteAtaque2();
        void MoverX(float x);
        void MoverY();
        void BorrarProyectil(int i);
        
        bool animacionMuerte();
    private:
        float danyo;
        int contadorSpriteAtaque2;
        float caida;
        bool Ataque2;
        Reloj tAtaque2;
        Reloj tAtaqueFinal;
        vector<Proyectil*> proyectiles;
        bool muerto;
        
        //Animaciones
        vector<Proyectil*> animacionExplote;
        Reloj Clock_explotarBurbuja;
        Reloj Clock_animacionEntrada;
        int contadorEntrada;
        Reloj Clock_animacionMuerte;
        int contadorMuerte;
        SpriteM* burbujasInicio[3];
        
        void animacionEntrada();
        
    };

}

