#pragma once
#include "Comportamiento.hpp"

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
        
        void ModificarSprite();
        
    private:
        float totalEnfriamiento;
        float enfriamiento;
        bool ataqueEspecial;
        
        short int estado;
        
        short int contadorSpriteCorrer;
        short int contadorSpriteSalto;
        short int contadorSpriteReposo;
    };
}