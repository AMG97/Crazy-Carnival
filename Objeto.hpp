#pragma once

#include "Player.hpp"
#include "Hud.hpp"

using namespace Crazy;

class Objeto {
public:
    Objeto(int tileX,int tileY,SpriteM* sp,int puntos);
    Objeto(const Objeto& orig);
    virtual ~Objeto();
    
    bool colision();
    vector2f getPosition();
    virtual void objectEffect(){}
    SpriteM* getSprite();
    sf::FloatRect getBound();

protected:
    int valor, p_value;
    vector2f position;
    SpriteM* _sprite;
    Player* _pl_instance;
    Hud* _hud_instance;
};


class OBJ_Reloj : public Objeto{
public:
    OBJ_Reloj(int tileX,int tileY,SpriteM* sp,int puntos):Objeto(tileX,tileY,sp,puntos){}
    void objectEffect();
private:
    
};

class OBJ_HP : public Objeto{
public:
    OBJ_HP(int tileX,int tileY,SpriteM* sp,int puntos);
    void objectEffect();
private:
    float vida;
};

class OBJ_Elixir : public Objeto{
public:
    OBJ_Elixir(int tileX,int tileY,SpriteM* sp,int puntos):Objeto(tileX,tileY,sp,puntos){}
    void objectEffect();
private:
    
};

class OBJ_Star : public Objeto{
public:
    OBJ_Star(int tileX,int tileY,SpriteM* sp,int puntos):Objeto(tileX,tileY,sp,puntos){}
    void objectEffect();
private:
    
};


