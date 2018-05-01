#include "Player.hpp"

namespace Crazy
{
    Player::Player()
    {
        vida = 200.0f;
    }
    
    float Player::GetVida()
    {
        return vida;
    }
    
    void Player::SetVida(float v)
    {
        vida = v;
    }
}