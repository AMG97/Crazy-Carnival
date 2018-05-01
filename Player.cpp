#include "Player.hpp"

namespace Crazy
{
    Player::Player()
    {
        //this->Comportamiento();
        vida = 200.0f;
    }
    
    float Player::GetEnfriamiento()
    {
        return enfriamiento;
    }
    
    void Player::SetEnfriamiento(float e)
    {
        enfriamiento = e;
    }
}