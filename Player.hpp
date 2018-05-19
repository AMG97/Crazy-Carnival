#pragma once
#include "Comportamiento.hpp"
#include <Box2D/Box2D.h>
#include "Arma.hpp"
#include "Enemigo.hpp"

// Constantes
#define REPOSO 0
#define CORRER 1
#define CORRERATRAS 5
#define SALTO 2
#define ATAQUE1 3
#define ATAQUE2 4
#define DESLIZARSE 6

namespace Crazy
{
    class Player : public Comportamiento
    {
    public:
        Player(string textura);
        float GetEnfriamiento();
        float GetTotalEnfriamiento();
        void SetEnfriamiento(float e);
        void SetElixir(bool v);
        void addPuntuacion(int puntos);
        void setPuntuacion(int puntos);
        int getPuntuacion();
        
        void ModificarEnfriamiento(float modificador);
        
        bool GetAtaqueEspecial();
        void SetAtaqueEspecial(bool ataque);
        bool AtaqueEspecialActivado();
        
        void Curar(float cura);
        void RecibirDanyo(float danyo);
        
        short int GetEstado();
        short int GetCorrer();
        short int GetCorrerAtras();
        short int GetSaltar();
        short int GetReposo();
        short int GetAtaque1();
        short int GetAtaque2();
        short int GetDeslizarse();
        void SetEstado(short int est);
        void CambiarDireccion();
        bool getDireccion();
        void Dibujar();
        
        //float GetVelocidadSalto();
        void SetVelocidadSalto(float velS);
        
        void ModificarSprite();
        float GetTAtque2();
        void Reposo(int n);
        void Update(vector<Enemigo*> e);
        void SetVElocidadSalto(float v);
        float GetVelocidadSalto();
        
        void MoverX(float x);
        void MoverY();
        
        void Saltar();
        
        int GetLastPared();
        
        void tparedRestart();
        float Gettpared();
        
    private:
        float totalEnfriamiento;
        float enfriamiento;
        bool ataqueEspecial;
        bool golpear;
        bool elixir;
        int puntuacion;
        
        short int estado;
        Reloj tAtaque2;
        bool Atacado2;
        
        Reloj tpared;
        
        float velSalto;
        float caida;
        short int contadorSpriteCorrer;
        short int contadorSpriteSalto;
        short int contadorSpriteReposo;
        short int contadorSpriteAtaque1;
        short int contadorSpriteAtaque2;
        
        int lastpared;
    };
}