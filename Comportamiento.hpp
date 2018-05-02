#pragma once
#include "Juego.hpp"

namespace Crazy
{
    class Comportamiento
    {
    public:
        Comportamiento();
        float GetVida();
        float GetTotalVida();
        SpriteM GetSpriteM();
        void SetVida(float v);
        void SetVelocidad(float vel);
        float GetVelocidad();
        void SetVelocidadSalto(float velS);
        float GetVelocidadSalto();
        int GetEstadoPersonaje();
        void ModificarVida(float modificador);
        void ModificarSprite();
        void Mover(float posX, float posY);
        void Dibujar();
        
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
        
                
    protected:
        Juego* _juego;
        SpriteM spJugador; 
        
        //TO DO patron façade con box2d
        b2World* _mundo;
        b2Body* _cuerpo;
        b2BodyDef cuerpoDef;
        b2Fixture *_fixCuerpo;
        b2FixtureDef fixCuerpoDef;
        b2PolygonShape formaCuerpo;
        
        float vida;
        float totalVida;
        float posicionInicial;
        float velocidad;
        int contadorSpriteCorrer;
        int contadorSpriteReposo;
        int contadorSpriteSalto;
        int estadoPersonaje;
    };
}