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
        
        for (auto ob : objects) {
            delete ob;
        }
        objects.clear();

    }

    
    void Nivel::cargarNivel(unsigned short int l) {
        _instance = Juego::Instance();
        sf::Texture* mapa = 0;
        TiXmlDocument doc,sprite,objects_doc;
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
        objects_doc = TiXmlDocument("resources/objects.tsx");
        if(mapa!=0){
            doc.LoadFile();
            sprite.LoadFile();objects_doc.LoadFile();

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

                            if(abs(value) < change){
                                tilemap[name][i][j]->CambiarTextura(*mapa);
                                sprite.FirstChildElement()->QueryIntAttribute("columns",&limit);
                            }else{
                                tilemap[name][i][j]->CambiarTextura(_instance->recursos.GetTextura("Objetos"));
                                tileV-=change-1;
                                objects_doc.FirstChildElement()->QueryIntAttribute("columns",&limit);
                            }

                            tilemap[name][i][j]->CambiarPosicion(48*j,48*i);
                            tilemap[name][i][j]->CambiarOrigen(48/2,48/2);



                            if(tilemap[name][i][j]!=0 && name=="Objetos"){
                                switch(tileV+1){
                                    case 1:
                                        objects.push_back(new OBJ_HP(j,i,tilemap[name][i][j],100));
                                        break;
                                    case 2:
                                        objects.push_back(new OBJ_Reloj(j,i,tilemap[name][i][j],200));
                                        break;
                                    case 3:
                                        objects.push_back(new OBJ_Elixir(j,i,tilemap[name][i][j],1000));
                                        break;
                                    case 5:
                                        objects.push_back(new OBJ_Star(j,i,tilemap[name][i][j],500));
                                        break;
                                    default:
                                        objects.push_back(new Objeto(j,i,tilemap[name][i][j],50));
                                        break;
                                }
                            }

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

            freecam = false;
                
                
            _camera = Camara::Instance();
            //camera->CrearCamara(0,504,800,800); cambiar localización para ver personaje
            _camera->CrearCamara(vector2f(240,600), vector2f(_instance->GetAncho(),_instance->GetAlto()), vector2f(width,height));
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
        
        
        //Colision con los objetos
        for (vector<Objeto*>::iterator it = objects.begin() ; it != objects.end(); ++it){
            Objeto* ref = *it;
            if(ref!=0 && ref->colision()){
                vector2f rem = ref->getPosition();
                delete tilemap["Objetos"][(int)rem.getY()][(int)rem.getX()];
                tilemap["Objetos"][(int)rem.getY()][(int)rem.getX()] = 0;
                delete ref;
                objects.erase(it);
            }
        }
        //Fin de la colision
        
        

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
        if(!freecam)_camera->setCentro(_jugadorX,_jugadorY); 
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
    void Nivel::toggleFreeCamera() {
        freecam = !freecam;
    }
    bool Nivel::isCamFree() {
        return freecam;
    }
    
    bool Nivel::ComprobarColision(float x, float y) {
        int x2=round(x/48);
        int y2=round(y/48);
        if(tilemap["Collisionable"][y2][x2]!=0)
            return true;
        else{
            return false;
        }
    }
    


    


}