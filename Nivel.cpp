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
#include "EstadoJuego.hpp"


namespace Crazy{
    Nivel::Nivel() {
    }

    Nivel::Nivel(const Nivel& orig) {
    }

    Nivel::~Nivel() {
        clear();        
    }
    ///Elimina todo el contenido del nivel
    void Nivel::clear() {
        for (auto l : layers) {
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if(tilemap[l][i][j]!=0)
                        delete tilemap[l][i][j];
                }
                delete[] tilemap[l][i];
            }
            delete tilemap[l];
            tilemap.erase(l);
        }
        layers.clear();
    }

    
    void Nivel::cargarNivel(unsigned short int l) {
        _instance = Juego::Instance();
        sf::Texture* mapa = 0;
        TiXmlDocument doc,sprite,objects;
        switch(l){
            case 1:
                mapa = &_instance->recursos.GetTextura("Playa");
                sprite = TiXmlDocument("resources/SpritesPlaya.tsx");
                doc = TiXmlDocument("resources/playaG.tmx");
                _instance->_ventana->setBackground(135,207,235);
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
                            if(value<0){
                                //value = 0;
                                cout<<value<<endl;
                            }
                            
                            if(value>50000)value = value-INT_MAX_VALUE;
                            
                            
                            if(value==0) tilemap[name][i][j] = 0;
                            else tilemap[name][i][j] = new SpriteM();
                              
                            if(tilemap[name][i][j]!=0){
                                int tileV = abs(value)-1, limit = 1, change;
                                map->FirstChild()->NextSiblingElement()->QueryIntAttribute("firstgid",&change);
                                if(i==16&&j==1)cout<<abs(value)<<endl;
                                
                                if(abs(value) < change){
                                    tilemap[name][i][j]->CambiarTextura(*mapa);
                                    sprite.FirstChildElement()->QueryIntAttribute("columns",&limit);
                                    if(i==16&&j==1)cout<<"Entra aquí"<<endl;
                                }else{
                                    tilemap[name][i][j]->CambiarTextura(_instance->recursos.GetTextura("Objetos"));
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
                cout<<"mapY"<<mapY<<endl;
                
                
                
            _camera = Camara::Instance();
            //camera->CrearCamara(0,504,800,800); cambiar localización para ver personaje
            _camera->CrearCamara(240,600,_instance->GetAncho(),_instance->GetAlto());
            _instance->_ventana->setCamara(*_camera);
        }else{
            cerr << "Error al cargar el nivel "<<l<<endl;
            exit(0);
        }
        
    }

    void Nivel::update() {
        //camera->setTam(800,1200);
        //camera->mover(2,0);
        _instance->_ventana->setCamara(*_camera);
    }

    void Nivel::draw(string capa) {
        for (int i = (_camera->getY()-_camera->getHeight()-1)/48 -1; i < 1+(_camera->getY()+_camera->getHeight())/48; i++) {
            for (int j = (_camera->getX()-_camera->getWidth()-1)/48 -1; j < 1+(_camera->getX()+_camera->getWidth())/48; j++) {
                if(i>=0&&i<height && j>=0&&j<width && tilemap[capa][i][j]!=0)
                    _instance->_ventana->DibujarC(*tilemap[capa][i][j]);
            }
        }
        //cout<<"Sale"<<endl;
    }
    void Nivel::setPosCamara(float _jugadorX, float _jugadorY){       
        if(_jugadorX >= 500 && _jugadorX <= 10000)
        {
            if(_jugadorY <= 40*30 && _jugadorY >= -40*30){
                _camera->setCentro(_jugadorX,_jugadorY);
            }
            else if(_jugadorY > 40*30)
            {
                _camera->setCentro(_jugadorX,43*30);
            }
            else if(_jugadorY < -40*30)
            {
                _camera->setCentro(_jugadorX,-43*30);
            }
        }
        if(_jugadorX < 500)
        {
            if(_jugadorY <= 40*30 && _jugadorY >= -40*30){
                _camera->setCentro(500,_jugadorY-3*30);
            }
            else if(_jugadorY > 40*30)
            {
                _camera->setCentro(500,43*30);
            }
            else if(_jugadorY < -40*30)
            {
                _camera->setCentro(500,-43*30);
            }
        }
        if(_jugadorX > 10000)
        {
            if(_jugadorY <= 40*30 && _jugadorY >= -40*30){
                _camera->setCentro(10000,_jugadorY);
            }
            else if(_jugadorY > 40*30)
            {
                _camera->setCentro(10000,43*30);
            }
            else if(_jugadorY < -40*30)
            {
                _camera->setCentro(10000,-43*30);
            }
        }
         
        _instance->_ventana->setCamara(*_camera);
    }
    Camara* Nivel::getCamara(){
        return _camera;
    }
    
    int Nivel::getAltura(){
        return height;
    }

    int Nivel::getAnchura() {
        return width;
    }

    


}