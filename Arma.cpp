/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Arma.cpp
 * Author: fv
 * 
 * Created on April 28, 2018, 4:02 PM
 */

#include "Arma.hpp"

Arma::Arma(int n) {
    if(n==1){
        texturaArma=juego->establecerTexturas("resources/espada1.png");
    }else if(n==2){
        texturaArma=juego->establecerTexturas("resources/espada2.png");
    }
    tipo=n;
    arma.setTexture(texturaArma);
    arma.setTextureRect(sf::IntRect(0*60, 0*80, 60, 80));
    arma.setOrigin(60/2, 80/2);
    arma.setPosition(640/2, 480/2);
}

void Arma::modificarSpriteReposo(int n, sf::Vector2f pos){
    arma.setTextureRect(sf::IntRect(n*60, 0*80, 60, 80));
    arma.setOrigin(30,40);
    arma.setPosition(pos);
}

void Arma::modificarSpriteCorrer(int n, sf::Vector2f pos){
    arma.setPosition(pos);
    arma.setTextureRect(sf::IntRect(n*60, 1*80, 60, 80));
    arma.setOrigin(30,40);
}

void Arma::modificarSpriteAtaque2(int n, sf::Vector2f pos){
    arma.setPosition(pos);
    arma.setTextureRect(sf::IntRect(n*100, 360, 100, 80));
    arma.setOrigin(50,40);
}

void Arma::modificarSpriteAtaque1(int n, int n2, sf::Vector2f pos){
    if(n2==1){
        arma.setPosition(pos);
        arma.setTextureRect(sf::IntRect(n*90, 240, 90, 120));
        arma.setOrigin(45,60);
    }else{
        arma.setPosition(pos);
        arma.setTextureRect(sf::IntRect(n*100, 150, 100, 90));
        arma.setOrigin(50,45);
    }
}

sf::Sprite Arma::getSprite(){
    return arma;
}

void Arma::scale(float nx, float ny){
    arma.scale(nx,ny);
}

void Arma::draw(sf::RenderWindow& window){
    window.draw(arma);
    for(int i=0;i<proyectiles.size();i++){
        proyectiles[i]->draw(window);
    }
}

void Arma::update(sf::Vector2f pos){
    arma.setPosition(pos.x,pos.y-10);
    for(int i=0;i<proyectiles.size();i++){
        bool b=proyectiles[i]->update();
        if(!b){
            Proyectil *tmp=proyectiles[i];
            proyectiles.erase(proyectiles.begin()+i);
            delete tmp;
        }
    }
}

void Arma::disparar(float angulo){
    int t;
    if(tipo==1 || tipo==2){
        t=1;
    }
    Proyectil *p=new Proyectil(t, danyo, angulo, arma);
    proyectiles.push_back(p);
}

Arma::Arma(const Arma& orig) {
}

Arma::~Arma() {
}

