/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Proyectil.cpp
 * Author: fv
 * 
 * Created on April 27, 2018, 7:08 PM
 */

#include <SFML/Graphics.hpp>

#include "Proyectil.hpp"

Proyectil::Proyectil(int n, float dan, float ang, sf::Sprite sf) {
    if(n==1){
        texturaProyectil.loadFromFile("resources/puñal.png");
        alcance=300;
        danyo=dan;
        velocidad=3;
    }else if(n==2){
        texturaProyectil.loadFromFile("resources/bala.png");
        alcance=400;
        danyo=dan;
        velocidad=4;
    }
    angulo=ang;
    proyectil.setTexture(texturaProyectil);
    posini=sf::Vector2f(sf.getPosition().x+sf.getGlobalBounds().width*sin(ang)/2,sf.getPosition().y+sf.getGlobalBounds().height*cos(ang)/2);
    pos=posini;
    proyectil.scale(1.5,1.5);
    proyectil.setOrigin(proyectil.getGlobalBounds().width/2,proyectil.getGlobalBounds().height/2);
    proyectil.setPosition(pos);
    proyectil.rotate(-angulo*180/3.1415+90);
}
void Proyectil::draw(sf::RenderWindow& window){
    window.draw(proyectil);
}
bool Proyectil::update(){
    proyectil.move(sin(angulo)*velocidad,cos(angulo)*velocidad);
    pos=proyectil.getPosition();
    float distancia=sqrt(pow(posini.x-pos.x,2)+pow(posini.y-pos.y,2));
    if(distancia>alcance){
        return false;
    }
    return true;
}

sf::Sprite Proyectil::getProyectil(){
    return  proyectil;
}

float Proyectil::getDanyo(){
    return danyo;
}

Proyectil::Proyectil(const Proyectil& orig) {
}

Proyectil::~Proyectil() {
}



