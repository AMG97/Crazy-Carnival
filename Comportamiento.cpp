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
    
    void Comportamiento::SetVida(float v)
    {
        vida = v;
    }
}