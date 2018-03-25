/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   juegoHud.h
 * Author: fv
 *
 * Created on March 24, 2018, 12:14 PM
 */

#ifndef JUEGOHUD_H
#define JUEGOHUD_H

class JuegoHud {
public:
    JuegoHud();
    //JuegoHud(const JuegoHud& orig);
    virtual ~JuegoHud();
    sf::Texture establecerTexturas(sf::String direccion);
private:

};

#endif /* JUEGOHUD_H */

