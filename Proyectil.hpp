/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Proyectil.hpp
 * Author: fv
 *
 * Created on April 27, 2018, 7:08 PM
 */

#ifndef PROYECTIL_HPP
#define PROYECTIL_HPP
#include <iostream>
using namespace std;

class Proyectil {
public:
    Proyectil(int n, float dan, float ang, sf::Sprite sf);
    bool update();
    sf::Sprite getProyectil();
    float getDanyo();
    void draw(sf::RenderWindow &window);
    Proyectil(const Proyectil& orig);
    virtual ~Proyectil();
private:
    sf::Texture texturaProyectil;
    sf::Sprite proyectil;
    int alcance;
    float danyo;
    float angulo;
    int velocidad;
    sf::Vector2f posini;
    sf::Vector2f pos;
};

#endif /* PROYECTIL_HPP */

