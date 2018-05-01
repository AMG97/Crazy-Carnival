#pragma once
#include "Comportamiento.hpp"

namespace Crazy
{
    class Player : public Comportamiento
    {
    public:
        Player();
        float GetEnfriamiento();
        void SetEnfriamiento(float e);
        
    private:
        float enfriamiento;
    };
}