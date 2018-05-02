/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Nivel.cpp
 * Author: fv
 * 
 * Created on May 1, 2018, 6:32 PM
 */

#include "Nivel.hpp"


namespace Crazy{
    Nivel::Nivel() {
    }

    Nivel::Nivel(const Nivel& orig) {
    }

    Nivel::~Nivel() {
    }
    
    void Nivel::cargarNivel(unsigned short int l) {
        instance = Juego::Instance();
        sf::Texture* mapa = 0;
        TiXmlDocument doc,sprite,objects;
        switch(l){
            case 1:
                mapa = &instance->recursos.GetTextura("Playa");
                sprite = TiXmlDocument("resources/SpritesPlaya.tsx");
                doc = TiXmlDocument("resources/playaG.tmx");
                instance->_ventana->setBackground(135,207,235);
                break;
               
            default:
                mapa = 0;
                break;
        }
        objects = TiXmlDocument("resources/objects.tsx");
        if(mapa!=0){
                doc.LoadFile();
                sprite.LoadFile();objects.LoadFile();

                TiXmlElement* map = doc.FirstChildElement("map");
                int mapX, mapY, layers;
                map->QueryIntAttribute("width",&mapX);
                map->QueryIntAttribute("height",&mapY);
            //    const string Objects_dir;
            //    map->FirstChildElement("image")->Attribute("source");

                
                TiXmlElement* layer = map->FirstChildElement("layer");

                while(layer){
                    
                    TiXmlElement* tile = layer->FirstChildElement("data")->FirstChildElement("tile");
                    
                    string name = layer->FirstAttribute()->Value();
                    tilemap[name] = new SpriteM**[mapY];
                    
                    int zeros = 0, valores = 0;
                    for (int i = 0; i < mapY; i++) {
                        tilemap[name][i] = new SpriteM*[mapX];
                        for (int j = 0; j < mapX; j++) {                            
                            int value=0;
                            tile->QueryIntAttribute("gid",&value);
                            value = abs(value);
                            if(value>50000)value = value-INT_MAX-1;
                            
                            if(value==0) tilemap[name][i][j] = 0;
                            else tilemap[name][i][j] = new SpriteM();
                              
                            if(tilemap[name][i][j]!=0){
                                int tileV = abs(value)-1, limit = 1, change;
                                map->FirstChild()->NextSiblingElement()->QueryIntAttribute("firstgid",&change);
                                if(abs(value) < change){
                                    tilemap[name][i][j]->CambiarTextura(*mapa);
                                    sprite.FirstChildElement()->QueryIntAttribute("columns",&limit);
                                }else{
                                    tilemap[name][i][j]->CambiarTextura(instance->recursos.GetTextura("Objetos"));
                                    tileV-=change-1;
                                    objects.FirstChildElement()->QueryIntAttribute("columns",&limit);
                                }
                                tilemap[name][i][j]->CambiarPosicion(48*j,48*i);
                                tilemap[name][i][j]->CambiarOrigen(48/2,48/2);


                                tilemap[name][i][j]->CambiarTextRect(48*(tileV%limit),48*(tileV/limit),48,48);
                                if(value<0)tilemap[name][i][j]->EscalarProporcion(-1,1);


                            }
                            if((i+1)*(j+1)<mapX*mapY)tile = tile->NextSiblingElement();
                        }
                    }
                    layer = layer->NextSiblingElement("layer");
                }
                
                width = mapX;
                height = mapY;
        }else{
            cerr << "Error al cargar el nivel "<<l<<endl;
            exit(0);
        }
        
        camera = Camara::Instance();
        camera->CrearCamara(0,504,800,800);
        instance->_ventana->setCamara(*camera);
        
        
        
    }

    void Nivel::update() {
        camera->setTam(300,300);
    }

    void Nivel::draw(string capa) {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if(tilemap[capa][i][j]!=0)
                    instance->_ventana->Dibujar(*tilemap[capa][i][j]);
            }
        }
    }



}