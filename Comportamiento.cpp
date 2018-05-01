#include "Comportamiento.hpp"

namespace Crazy
{
    Comportamiento::Comportamiento()
    {
        
    }
    
    float Comportamiento::GetVida()
    {
        return vida;
    }
    
    float Comportamiento::GetTotalVida()
    {
        return totalVida;
    }
    
    void Comportamiento::SetVida(float v)
    {
        vida = v;
    }
    
    void Comportamiento::ModificarVida(float modificador)
    {
        vida += modificador;
        if (vida < 0)
        {
            vida = 0;
        }
        else if (vida > totalVida)
        {
            vida = totalVida;
        }
    }
}