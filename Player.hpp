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
#define MORIR 7

namespace Crazy
{
    class Player : public Comportamiento
    {
    public:
        Player();
        float GetEnfriamiento();
        float GetTotalEnfriamiento();
        void SetEnfriamiento(float e);
        void setElixir(bool v);
        bool getElixir();
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
        short int GetMorir();
        void SetEstado(short int est);
        void CambiarDireccion();
        bool getDireccion();
        void Dibujar();
        
        //float GetVelocidadSalto();
        void SetVelocidadSalto(float velS);
        
        virtual void ModificarSprite()=0;
        float GetTAtque2();
        virtual float GetTAtaque1()=0;
        virtual void Reposo(int n)=0;
        virtual void Update(vector<Enemigo*> e)=0;
        void SetVElocidadSalto(float v);
        float GetVelocidadSalto();
        bool isAttacking();
        void setInvulnerable(bool esInvulnerable);
        bool getInvulnerable();
        void MoverX(float x);
        void MoverY();
        
        int GetLastPared();
        void tparedRestart();
        float Gettpared();
        int getContadorInvulnerable();
        void AumentarContadorInvulnerable();
        
    protected:
        float totalEnfriamiento;
        float enfriamiento;
        bool ataqueEspecial;
        bool golpear;
        bool elixir;
        int puntuacion;
        bool invulnerable;
        
        short int estado;
        Reloj tAtaque2;
        bool Atacado2;
        bool atacando;
        
        Reloj tpared;
        
        float velSalto;
        float caida;
        short int contadorSpriteCorrer;
        short int contadorSpriteSalto;
        short int contadorSpriteReposo;
        short int contadorSpriteAtaque1;
        short int contadorSpriteAtaque2;
        
        int lastpared;
        int contadorInvulnerable;
    };
}