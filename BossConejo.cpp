#include "BossConejo.hpp"
#include "EstadoJuego.hpp"
#include "Player.hpp"

namespace Crazy
{
    BossConejo::BossConejo(float posx, float posy) {
        sprite.CambiarTextura(_juego->recursos.GetTextura("Conejo"));
        sprite.CambiarTextRect(0,0,35,50);
        sprite.CambiarOrigen(35/2,50/2);
        sprite.CambiarPosicion(posx, posy);
        sprite.EscalarProporcion(2,2);
        vida=50.0;
        posinix=sprite.GetX();
        posiniy=sprite.GetY();
        contadorSpriteCorrer=0;
        contadorSpriteAtaque1=0;
        contadorSpriteAtaque2=0;
        contadorSpriteSalto=0;
        rojo=false;
        SetDireccion(true);
        velocidad=2.9;
        alcancex=1000;
        alcancey=400;
        movimiento=500;
        danyo=8;
        _arma=NULL; 
        caida=0;
        angulo=0;
        Ataque1=false;
        Ataque2=false;
        zanahorias=false;
    }

    BossConejo::BossConejo(const BossConejo& orig) {
    }

    BossConejo::~BossConejo() {
    }
    void BossConejo::ModificarSprite() {

    }
    
    void BossConejo::ModificarSpriteCorrer() {
        sprite.CambiarTextRect(contadorSpriteCorrer*35,0,35,50);
         if(contadorSpriteCorrer==0){
            sprite.CambiarOrigen(35/2,50/2);
        }
        contadorSpriteCorrer++;
        if(contadorSpriteCorrer==6)
            contadorSpriteCorrer=0;
    }
    void BossConejo::ModificarSpriteAtaque1() {
        sprite.CambiarTextRect(contadorSpriteAtaque1*60,155,60,60);
        if(contadorSpriteAtaque1==0){
            sprite.CambiarOrigen(30,30);
            sprite.Mover(0,-10);
            //sprite.Mover(0,-20)
        }
        contadorSpriteAtaque1++;
        if(contadorSpriteAtaque1==6){
            contadorSpriteAtaque1=0;
            contadorSpriteCorrer=0;
            sprite.CambiarTextRect(contadorSpriteCorrer*35,0,35,50);
            sprite.CambiarOrigen(35/2,50/2);
            Ataque1=false;
            tAtaque.ReiniciarSegundos();
            sprite.Mover(0,10);
        }
    }
    
    void BossConejo::ModificarSpriteAtaque2() {
        sprite.CambiarTextRect(contadorSpriteAtaque2*35,105,35,50);
        contadorSpriteAtaque2++;
        if(contadorSpriteAtaque2==0){
            sprite.CambiarOrigen(35/2,50/2);
            
        }
        if(contadorSpriteAtaque2==1){
            if(zanahorias){
                Proyectil *p=new Proyectil(5,danyo/3,94,sprite);
                Proyectil *p2=new Proyectil(5,2,139,sprite);
                Proyectil *p3=new Proyectil(5,2,184,sprite);
                Proyectil *p4=new Proyectil(5,2,229,sprite);
                Proyectil *p5=new Proyectil(5,2,274,sprite);
                proyectiles.push_back(p);
                proyectiles.push_back(p2);
                proyectiles.push_back(p3);
                proyectiles.push_back(p4);
                proyectiles.push_back(p5);
                zanahorias=false;
            }else{
                Proyectil *p=new Proyectil(5,2,116.5,sprite);
                Proyectil *p2=new Proyectil(5,2,161.5,sprite);
                Proyectil *p3=new Proyectil(5,2,206.5,sprite);
                Proyectil *p4=new Proyectil(5,2,251.5,sprite);
                proyectiles.push_back(p);
                proyectiles.push_back(p2);
                proyectiles.push_back(p3);
                proyectiles.push_back(p4);
                zanahorias=true;
            }
            tAtaque.ReiniciarSegundos();
        }
        if(contadorSpriteAtaque2==3){
            contadorSpriteAtaque2=0;
            Ataque2=false;
            tAtaque2.ReiniciarSegundos();
        }
    }

    void BossConejo::ModificarSpriteSalto() {
        
    }

    
    void BossConejo::MoverX(float x){
        float sumx;
        if(x==0)
            sumx=0;
        else if(x>0)
            sumx=x+90/2;
        else
            sumx=x-90/2;
        if(!EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+sumx,sprite.GetY()+30) &&
           !EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+sumx,sprite.GetY()-30) &&
            EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX()+sumx,sprite.GetY()+30*2))
            sprite.Mover(x,0);
        else 
            SetDireccion(!direccionIzq);
    }
    
    void BossConejo::MoverY(){
        if(!EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX(),sprite.GetY()+sprite.GetAlto()/2)){
            caida+=0.4;
            sprite.Mover(0,caida);
        }else{
            if(caida!=0){
                caida=0;
                sprite.CambiarPosicion(sprite.GetX(),floor(sprite.GetY()/48)*48+23); //puede que lo tenga que cambiar
            }
        }
    }
    void BossConejo::Dibujar() {
        _juego->_ventana->DibujarSprite(sprite);
        for(int i=0; i<proyectiles.size();i++)
            proyectiles[i]->Dibujar();
    }
    void BossConejo::Update(int Posx, int Posy) {

    }
    void BossConejo::Update(int Posx, int Posy, Player* p) {
        MoverY();
        float x=sprite.GetX();
        float y=sprite.GetY();
        float diferenciax=Posx-x;
        float diferenciay=Posy-y;
        angulo=atan2(diferenciax,diferenciay)*180/3.14159;
        if(diferenciax<1200 && diferenciay<1200 && diferenciax>-1200 && diferenciay>-1200){
            if(vida<=15){
                if(contadorSpriteAtaque1!=0){
                    contadorSpriteAtaque1=0;
                    sprite.Mover(0,-10);
                }
                if(tAtaque2.GetSegundos()>0.4)
                        Ataque2=true;
                if(tDesp.GetSegundos()>0.1){
                    if(Ataque2){
                        ModificarSpriteAtaque2();
                        tDesp.ReiniciarSegundos();
                    }
                }
            }
            else{
                if(Posx>x)
                {
                    if(direccionIzq)
                        SetDireccion(false);
                    if(Posx-x>50)
                    {
                        MoverX(velocidad);
                        if(tDesp.GetSegundos()>0.2){
                            ModificarSpriteCorrer();
                            tDesp.ReiniciarSegundos();
                        }
                    }
                }
                else if(Posx<x){
                    if(!direccionIzq)
                        SetDireccion(true);
                    if(x-Posx>50)
                    {
                        MoverX(-velocidad);
                        if(tDesp.GetSegundos()>0.2){
                            ModificarSpriteCorrer();
                            tDesp.ReiniciarSegundos();
                        }
                    }
                }
                if(tAtaque.GetSegundos()>1.2 && Posx-x<150 && Posx-x>-150)
                    Ataque1=true;
                if(tDesp.GetSegundos()>0.1){
                    if(Ataque1){
                        ModificarSpriteAtaque1();
                        if(contadorSpriteAtaque1==1){
                            if(p->GetSprite().Interseccion2(sprite)){
                                p->RecibirDanyo(danyo);
                            }
                        }
                        tDesp.ReiniciarSegundos();
                    }
                    else if(tAtaque.GetSegundos()<1.2 && tDesp.GetSegundos()>0.2){
                        ModificarSpriteCorrer();
                        tDesp.ReiniciarSegundos();
                    }
                }
            }
        
            for(int i=0;i<proyectiles.size();i++)
            {
                bool b=proyectiles[i]->Update();
                if(!b || EstadoJuego::Instance()->_level->ComprobarColision(proyectiles[i]->GetProyectil().GetX(),proyectiles[i]->GetProyectil().GetY()))
                    BorrarProyectil(i);
                else if(proyectiles[i]->GetProyectil().Interseccion1(p->GetSprite()))
                {
                    p->RecibirDanyo(proyectiles[i]->GetDanyo());
                    BorrarProyectil(i);
                }
            }
        }
            if(rojo && relojrojo.GetSegundos()<=0.2)
                sprite.CambiarColorRojo();
            else if(rojo && relojrojo.GetSegundos()>0.2){
                rojo=false;
                sprite.Parpadear(false);
            }
    }
    void BossConejo::BorrarProyectil(int i) {
        Proyectil *tmp=proyectiles[i];
        proyectiles.erase(proyectiles.begin()+i);
        delete tmp;
    }


}
