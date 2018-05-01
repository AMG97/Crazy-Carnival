/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Objeto.cpp
 * Author: fv
 * 
 * Created on April 29, 2018, 6:01 PM
 */

#include "Objeto.hpp"

Objeto::Objeto(int tileX, int tileY, int tileValue, sf::Texture& textura, int puntos) {
    x = tileX; y = tileY; tile = tileValue-1; valor = puntos;
       
    sprite = sf::Sprite(textura);
    sprite.setTextureRect(sf::IntRect(32*(tile%4),32*(tile/4),32,32));
    
    sprite.setPosition(x*32,y*32);
}

Objeto::Objeto(const Objeto& orig) {
}

Objeto::~Objeto() {
}

bool Objeto::colision(){
    Player* p_instance = Player::Instance();
    
    if(p_instance!=0){
        sf::FloatRect p_bounds = p_instance->getGlobalBounds();
        if(p_bounds.intersects(sprite.getGlobalBounds())){
            p_instance->addPoints(valor);
            return true;
        }
    }
    return false;
}

void Objeto::draw(sf::RenderWindow &app) {
    app.draw(sprite);
}

sf::Sprite Objeto::getSprite() {
    return sprite;
}

sf::FloatRect Objeto::getBound() {
    return sprite.getGlobalBounds();
}

void CdReducer::reducirCooldown() {
    Player* p_instance = Player::Instance();
    
    if(p_instance!=0){
        p_instance->setEnfriamiento(0);
    }
}

void HP::curar(float vida) {
    Player* p_instance = Player::Instance();
    
    if(p_instance!=0){
        p_instance->curar(vida);
    }
}

void Elixir::anyadir_resucitar() {
    Player* p_instance = Player::Instance();
    
    if(p_instance!=0){
        p_instance->setElixir(true);
    }
}
