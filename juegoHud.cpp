/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   juegoHud.cpp
 * Author: fv
 * 
 * Created on March 24, 2018, 12:14 PM
 */

#include <iostream>
#include <SFML/Graphics.hpp>
#include "juegoHud.h"

using namespace std;

JuegoHud::JuegoHud() {
}

//JuegoHud::JuegoHud(const juegoHud& orig) {
//}

JuegoHud::~JuegoHud() {
}
sf::Texture JuegoHud::establecerTexturas(sf::String direccion)
{
    sf::Texture textura;
    if(!textura.loadFromFile(direccion))
    {    
        std::cerr << "Error al cargar el sprite";
        exit(0);
    }
    return textura;
}

