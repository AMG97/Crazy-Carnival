#pragma once
#include "Comportamiento.hpp"

namespace Crazy
{
    class Player : public Comportamiento
    {
    public:
        Player();
        float GetEnfriamiento();
        float GetTotalEnfriamiento();
        void SetEnfriamiento(float e);
        
        void ModificarEnfriamiento(float modificador);
        
        bool GetAtaqueEspecial();
        void SetAtaqueEspecial(bool ataque);
        bool AtaqueEspecialActivado();
        
        int GetEstadoPersonaje();
        void SetEstadoPersonaje(int estado);
        
        void Curar(float cura);
        void RecibirDanyo(float danyo);
        
        
    private:
        float totalEnfriamiento;
        float enfriamiento;
        bool ataqueEspecial;
        
        int contadorSpriteReposo;
        int contadorSpriteCorrer;
        int contadorSpriteSalto;
    };
}