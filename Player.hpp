#pragma once
#include "Comportamiento.hpp"
#include <Box2D/Box2D.h>
#include "Arma.hpp"
#include "Enemigo.hpp"

// Constantes
#define REPOSO 0
#define CORRER 1
#define SALTO 2
#define ATAQUE1 3
#define ATAQUE2 4

namespace Crazy
{
    class Player : public Comportamiento
    {
    public:
        Player(string textura);
        float GetEnfriamiento();
        float GetTotalEnfriamiento();
        void SetEnfriamiento(float e);
        
        void ModificarEnfriamiento(float modificador);
        
        bool GetAtaqueEspecial();
        void SetAtaqueEspecial(bool ataque);
        bool AtaqueEspecialActivado();
        
        void Curar(float cura);
        void RecibirDanyo(float danyo);
        
        short int GetEstado();
        short int GetCorrer();
        short int GetSaltar();
        short int GetReposo();
        short int GetAtaque1();
        short int GetAtaque2();
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
        
        
        // Box2D
        b2World* GetMundo();
        void SetMundo();
        b2Body* GetCuerpo();
        void SetCuerpo();
        b2BodyDef GetCuerpoDefinicion();
        void SetCuerpoDefinicionPosicion(float32 posX, float32 posY);
        b2Fixture* GetFixtureCuerpo();
        void SetFixtureCuerpo();
        b2FixtureDef GetFixtureCuerpoDefinicion();
        void SetFixtureCuerpoDefinicion();
        b2PolygonShape GetForma();
        void SetForma();
        
        void SetAhora();
        float GetXAhora();
        float GetYAhora();
        
        void Saltar();
        
    private:
        float totalEnfriamiento;
        float enfriamiento;
        bool ataqueEspecial;
        bool golpear;
        
        short int estado;
        Reloj tAtaque2;
        bool Atacado2;
        
        float velSalto;
        
        short int contadorSpriteCorrer;
        short int contadorSpriteSalto;
        short int contadorSpriteReposo;
        short int contadorSpriteAtaque1;
        short int contadorSpriteAtaque2;
        
        b2World* _mundo; // pa la gravedad
        b2Body* _cuerpo; // esto se le asocia al sprite
        
        // esto define las fisicas
        b2BodyDef cuerpoDef;
        b2Fixture *_fixCuerpo;
        b2FixtureDef fixCuerpoDef;
        b2PolygonShape formaCuerpo; //bounding box, posiblemente
        
        
        // Prueba
        int xAhora;
        int yAhora;
        bool guardado;
    };
}