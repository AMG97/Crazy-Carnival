/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   hud.cpp
 * Author: fv
 * 
 * Created on March 24, 2018, 12:03 PM
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "hud.h"
#include "juegoHud.h"

Hud::Hud() {
    
    //Se genera la textura y se asigna a los sprites
    texturaHud = juego->establecerTexturas("/home/fv/NetBeansProjects/Crazy-Carnival/resources/HUD.png");
    spRecipVida.setTexture(texturaHud);
    spVida.setTexture(texturaHud);
    
    //Se elige el sprite del sheet
    spRecipVida.setTextureRect(sf::IntRect(0*40, 0*210, 40, 210));
    //Se sitúa el centro del sprite y su ubicación
    spRecipVida.setOrigin(40/2, 210/2);
}

Hud::Hud(const Hud& orig) {
}

Hud::~Hud() {
}

