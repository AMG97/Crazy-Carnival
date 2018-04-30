/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Objeto.hpp
 * Author: fv
 *
 * Created on April 29, 2018, 6:01 PM
 */

#ifndef OBJETO_HPP
#define OBJETO_HPP

#include "player.hpp"


struct Objeto {
public:
    Objeto(int tileX,int tileY,int tileValue, sf::Texture& textura,int puntos);
    Objeto(const Objeto& orig);
    virtual ~Objeto();
    
    bool colision();
    void draw(sf::RenderWindow &app);
    sf::Sprite getSprite();
    sf::FloatRect getBound();
private:
    int x, y, tile, valor;
    sf::Sprite sprite;
};


class CdReducer : Objeto{
public:
    CdReducer(int tileX,int tileY,int tileValue, sf::Texture& textura,int puntos):Objeto(tileX,tileY,tileValue,textura,puntos){}
    void reducirCooldown();
private:
    
};

class HP : Objeto{
public:
    HP(int tileX,int tileY,int tileValue, sf::Texture& textura,int puntos):Objeto(tileX,tileY,tileValue,textura,puntos){}
    void curar(float vida);
private:
    
};

class Elixir : Objeto{
public:
    Elixir(int tileX,int tileY,int tileValue, sf::Texture& textura,int puntos):Objeto(tileX,tileY,tileValue,textura,puntos){}
    void anyadir_resucitar();
private:
    
};

class Star : Objeto{
public:
    Star(int tileX,int tileY,int tileValue, sf::Texture& textura,int puntos):Objeto(tileX,tileY,tileValue,textura,puntos){}
    void activarGodMode();
private:
    
};

#endif /* OBJETO_HPP */

