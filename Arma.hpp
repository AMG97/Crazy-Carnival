/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arma.hpp
 * Author: fv
 *
 * Created on April 28, 2018, 4:02 PM
 */

#ifndef ARMA_HPP
#define ARMA_HPP
#include <SFML/Graphics.hpp>
#include "juegoHud.hpp"
#include "iostream"
#include "Proyectil.hpp"

class Arma {
public:
    Arma(int n, sf::Vector2f pos);
    Arma(const Arma& orig);
    void borrarProyectil(int i);
    virtual ~Arma();
    void draw(sf::RenderWindow& window);
    void update(sf::Vector2f pos,vector<Enemigo*>e);
    void update(sf::Vector2f pos, Player* p);
    void modificarSpriteCorrer(int n, sf::Vector2f pos);
    void modificarSpriteReposo(int n, sf::Vector2f pos);
    void modificarSpriteAtaque1(int n, int n2, sf::Vector2f pos);
    void modificarSpriteAtaque2(int n, sf::Vector2f pos);
    void scale(float nx, float ny);
    sf::Sprite getSprite();
    void disparar(float angulo);
    void setDanyo();
    float getDanyo();
private:
    float danyo;
    sf::Texture texturaArma;
    sf::Sprite arma;
    JuegoHud *juego;
    std::vector<Proyectil*> proyectiles;
    int tipo;
};

#endif /* ARMA_HPP */

