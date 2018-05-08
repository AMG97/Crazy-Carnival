#pragma once
#include "Comportamiento.hpp"
#include <Box2D/Box2D.h>

// Constantes
#define REPOSO 0
#define CORRER_DER 1
#define CORRER_IZQ 2
#define SALTO_DER 3
#define SALTO_IZQ 4

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
        short int GetCorrerDer();
        short int GetCorrerIzq();
        short int GetSaltarDer();
        short int GetSaltarIzq();
        short int GetReposo();
        void SetEstado(short int est);
        void CambiarDireccion();
        
        //float GetVelocidadSalto();
        void SetVelocidadSalto(float velS);
        
        void ModificarSprite();
        
        
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
        
        short int estado;
        
        short int contadorSpriteCorrer;
        short int contadorSpriteSalto;
        short int contadorSpriteReposo;
        
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
        float velSalto;
    };
}