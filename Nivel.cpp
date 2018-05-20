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
#include "EnemigoVolador.hpp"
#include "BossCangrejo.hpp"


namespace Crazy{
    Nivel::Nivel() {
        width=0; height=0;
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
        
        for (int i=0; i < _enemigos.size(); i++)
        {
            Enemigo *tmp= _enemigos[i];
            _enemigos.erase(_enemigos.begin()+i);
            delete tmp;
        }
        _enemigos.clear();

    }

    
    void Nivel::cargarNivel(unsigned short int l) {
        _juego = Juego::Instance();
        _jugador = 0;
        sf::Texture* mapa = 0;
        TiXmlDocument doc,sprite,objects_doc;
        switch(l){
            case 1:
                mapa = &_juego->recursos.GetTextura("Playa");
                sprite = TiXmlDocument("resources/SpritesPlaya.tsx");
                doc = TiXmlDocument("resources/playaG.tmx");
                _juego->_ventana->setBackground(135,207,235);
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
                            bool isObject = false;
                            
                            map->FirstChild()->NextSiblingElement()->QueryIntAttribute("firstgid",&change);

                            if(abs(value) < change){
                                tilemap[name][i][j]->CambiarTextura(*mapa);
                                sprite.FirstChildElement()->QueryIntAttribute("columns",&limit);
                            }else{
                                tilemap[name][i][j]->CambiarTextura(_juego->recursos.GetTextura("Objetos"));
                                tileV-=change-1;
                                objects_doc.FirstChildElement()->QueryIntAttribute("columns",&limit);
                                isObject=true;
                            }

                            tilemap[name][i][j]->CambiarPosicion(48*j,48*i);
                            tilemap[name][i][j]->CambiarOrigen(48/2,48/2);



                            if(name=="Objetos" && tilemap[name][i][j]!=0){
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
                            if(name=="Delante" && isObject && tilemap[name][i][j]!=0){
                                switch(tileV){
                                    case 98: //Es la e verde, la roja será +1 y el resto para atrás
                                        delete tilemap[name][i][j];
                                        tilemap[name][i][j] = 0;
                                        _enemigos.push_back(new EnemigoPistola(48*j,48*i));
                                        break;
                                    case 99:
                                        delete tilemap[name][i][j];
                                        tilemap[name][i][j] = 0;
                                        _enemigos.push_back(new EnemigoVolador(48*j,48*i));
                                        break;
                                }
                            }

                            if(tilemap[name][i][j]!=0){
                                tilemap[name][i][j]->CambiarTextRect(48*(tileV%limit),48*(tileV/limit),48,48);
                                if(value<0)tilemap[name][i][j]->EscalarProporcion(-1,1);
                            }

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
            _camera->CrearCamara(vector2f(240,600), vector2f(_juego->GetAncho(),_juego->GetAlto()), vector2f(width,height));
            _juego->_ventana->setCamara(*_camera);
            peleandoBoss = false; bossMatado=false;
        }else{
            cerr << "Error al cargar el nivel "<<l<<endl;
            exit(0);
        }
        
    }

    void Nivel::update() {
        //camera->setTam(800,1200);
        //camera->mover(2,0);
        _juego->_ventana->setCamara(*_camera);
        _jugador = EstadoJuego::Instance()->_jugador;
        
        
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
        
        _jugador->Update(_enemigos);
        _jugador->GetArma()->Update(_jugador->GetSprite().GetX(),_jugador->GetSprite().GetY(),_enemigos,_jugador);
        
        
        switch(EstadoJuego::Instance()->getNumNivel()){
            case 1:
                if(!bossMatado && !peleandoBoss && _jugador->GetPosX()>48*150){
                    peleandoBoss =true;
                    _enemigos.clear();
                    _enemigos.push_back(new BossCangrejo(_camera->getX()+_camera->getWidth()/2+200,1080));
                    _camera->toggleStatic();
                }
                
                if(peleandoBoss){
                    BossCangrejo* boss = (BossCangrejo*) *_enemigos.begin();
                    
                    if(boss->GetVida()<=0 && boss->animacionMuerte()){
                        _jugador->addPuntuacion(boss->getPuntos());
                        _enemigos.erase(_enemigos.begin());
                        peleandoBoss=false;
                        bossMatado = true;
                        
                        //AQUI LANZAR EL NUEVO NIVEL
                        
                        delete boss;
                    }else if(boss->GetVida()>0){
                        if(boss->GetArma()!=NULL){
                            boss->Update(_jugador->GetSprite().GetX(),_jugador->GetSprite().GetY());
                            boss->GetArma()->Update(boss->GetSprite().GetX(),boss->GetSprite().GetY(),_jugador);
                        }else
                            boss->Update(_jugador->GetSprite().GetX(),_jugador->GetSprite().GetY(),_jugador);
                    }
                    
                    
                }
            break;
        }
        
        if(!peleandoBoss){
            for(int i=0;i<_enemigos.size();i++){
                if(_enemigos[i]->GetVida()<=0){
                    Enemigo *tmp=_enemigos[i];
                    _jugador->addPuntuacion(tmp->getPuntos());
                    _enemigos.erase(_enemigos.begin()+i);
                    delete tmp;
                }else{
                    if(_enemigos[i]->GetArma()!=NULL){
                        _enemigos[i]->Update(_jugador->GetSprite().GetX(),_jugador->GetSprite().GetY());
                        _enemigos[i]->GetArma()->Update(_enemigos[i]->GetSprite().GetX(),_enemigos[i]->GetSprite().GetY(),_jugador);
                    }else
                        _enemigos[i]->Update(_jugador->GetSprite().GetX(),_jugador->GetSprite().GetY(),_jugador);
                }
            }       
        }

    }

    void Nivel::draw(string capa) {
        for (int i = (_camera->getY()-_camera->getHeight()-1)/48 -1; i < 1+(_camera->getY()+_camera->getHeight())/48; i++) {
            for (int j = (_camera->getX()-_camera->getWidth()-1)/48 -1; j < 1+(_camera->getX()+_camera->getWidth())/48; j++) {
                if(i>=0&&i<height && j>=0&&j<width && tilemap[capa][i][j]!=0)
                    _juego->_ventana->DibujarSprite(*tilemap[capa][i][j]);
            }
        }
        
        for(int i=0;i<_enemigos.size();i++){
            _enemigos[i]->Dibujar();
        }
    }
    void Nivel::setPosCamara(float _jugadorX, float _jugadorY){       
        if(!freecam)_camera->setCentro(_jugadorX,_jugadorY); 
        _juego->_ventana->setCamara(*_camera);
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
    
    bool Nivel::isPeleandoBoss() {
        return peleandoBoss;
    }

    


}