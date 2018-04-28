#pragma once
#include "Reloj.hpp"

namespace Motor
{
    Reloj::Reloj() 
    {
        
    }
    
    float Reloj::RestartMiliseconds()
    {
        return restart().asMilliseconds();
    }
}

