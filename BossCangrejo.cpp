#include "BossCangrejo.hpp"
#include "EstadoJuego.hpp"
#include "Player.hpp"

namespace Crazy
{
    BossCangrejo::BossCangrejo(float posx, float posy) {
        sprite.CambiarTextura(_juego->recursos.GetTextura("Cangrejo"));
        sprite.CambiarTextRect(0,0,90,70);
        sprite.CambiarOrigen(90/2,70/2);
        sprite.CambiarPosicion(posx, posy);
        sprite.EscalarProporcion(2,2);
        vida=VIDA;
        posinix=sprite.GetX();
        posiniy=sprite.GetY();
        contadorSpriteCorrer=0;
        contadorSpriteAtaque1=0;
        contadorSpriteAtaque2=0;
        rojo=false;
        SetDireccion(true);
        velocidad=2.3;
        alcancex=1000;
        alcancey=400;
        movimiento=500;
        danyo=13;
        _arma=NULL; 
        caida=0;
        angulo=0;
        Ataque1=false;
        Ataque2=false;
        muerto = false;
        puntos = 5000;
        
        Clock_animacionEntrada.ReiniciarSegundos();
        contadorEntrada=0;
        contadorMuerte=0;
        
        for (int i = 0; i < 3; i++) {
            burbujasInicio[i] = 0;
        }

    }

    BossCangrejo::BossCangrejo(const BossCangrejo& orig) {
    }

    BossCangrejo::~BossCangrejo() {
    }
    void BossCangrejo::ModificarSprite() {

    }
    
    void BossCangrejo::ModificarSpriteCorrer() {
        sprite.CambiarTextRect(contadorSpriteCorrer*90,0,90,70);
        contadorSpriteCorrer++;
        if(contadorSpriteCorrer==5)
            contadorSpriteCorrer=0;
    }
    void BossCangrejo::ModificarSpriteAtaque1() {
        sprite.CambiarTextRect(contadorSpriteAtaque1*90,70,90,70);
        contadorSpriteAtaque1++;
        if(contadorSpriteAtaque1==2){
            contadorSpriteAtaque1=0;
            Ataque1=false;
            tAtaque.ReiniciarSegundos();
        }
    }
    
    void BossCangrejo::ModificarSpriteAtaque2() {
        sprite.CambiarTextRect(contadorSpriteAtaque2*90,70*2,90,70);
        contadorSpriteAtaque2++;
        if(contadorSpriteAtaque2==3){
            if(tAtaqueFinal.GetSegundos()>=5){
                Proyectil *p1=new Proyectil(3,danyo-3,angulo+8,sprite);
                Proyectil *p2=new Proyectil(3,danyo-3,angulo,sprite);
                Proyectil *p3=new Proyectil(3,danyo-3,angulo-8,sprite);
                proyectiles.push_back(p1);
                proyectiles.push_back(p2);
                proyectiles.push_back(p3);
                tAtaqueFinal.ReiniciarSegundos();
            }
            else{
                Proyectil *p=new Proyectil(3,danyo,angulo,sprite);
                proyectiles.push_back(p);
            }
        }
        if(contadorSpriteAtaque2==5){
            contadorSpriteAtaque2=0;
            Ataque2=false;
            tAtaque2.ReiniciarSegundos();
        }
    }
    
    void BossCangrejo::MoverX(float x){
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
    
    void BossCangrejo::MoverY(){
        if(!EstadoJuego::Instance()->_level->ComprobarColision(sprite.GetX(),sprite.GetY()+sprite.GetAlto()/2)){
            caida+=0.4;
            sprite.Mover(0,caida);
        }else{
            if(caida!=0){
                caida=0;
                sprite.CambiarPosicion(sprite.GetX(),floor(sprite.GetY()/48)*48+13);
            }
        }
    }
    void BossCangrejo::Dibujar() {
        _juego->_ventana->DibujarSprite(sprite);
        for(int i=0; i<proyectiles.size();i++)
            proyectiles[i]->Dibujar();
        
        for (int i = 0; i < animacionExplote.size(); i++) {
            float secs=0.65; 
            Proyectil* bala = animacionExplote[i];
            int x = bala->GetProyectil()->GetX();
            int y = bala->GetProyectil()->GetY();
            
            if(Clock_explotarBurbuja.getElapsedTime().asSeconds()>secs)animacionExplote.erase(animacionExplote.begin()+i);
            else if(Clock_explotarBurbuja.getElapsedTime().asSeconds()>0.8*secs) bala->GetProyectil()->CambiarTextRect(72+80*4,280,80,74);
            else if(Clock_explotarBurbuja.getElapsedTime().asSeconds()>0.6*secs) bala->GetProyectil()->CambiarTextRect(72+80*3,280,80,74);
            else if(Clock_explotarBurbuja.getElapsedTime().asSeconds()>0.4*secs) bala->GetProyectil()->CambiarTextRect(72+80*2,280,80,74);
            else if(Clock_explotarBurbuja.getElapsedTime().asSeconds()>0.2*secs) bala->GetProyectil()->CambiarTextRect(72+80*1,280,80,74);
            else if(Clock_explotarBurbuja.getElapsedTime().asSeconds()>0.05*secs) bala->GetProyectil()->CambiarTextRect(72+80*0,280,80,74);
            
            bala->Dibujar();
        }
        
        
        for (int i = 0; i < 3; i++) {
            if(burbujasInicio[i]!=0)Juego::Instance()->_ventana->DibujarSprite(*burbujasInicio[i],Camara::Instance());
        }
        
    }

    void BossCangrejo::Update(int Posx, int Posy) {

    }

    void BossCangrejo::animacionEntrada(){
        float tiempo = Clock_animacionEntrada.getElapsedTime().asSeconds();
        
        if(burbujasInicio[0]==0){
            for (int i = 0; i < 3; i++) {
                burbujasInicio[i] = new SpriteM();
                burbujasInicio[i]->CambiarTextura(_juego->recursos.GetTextura("Cangrejo"));
                burbujasInicio[i]->CambiarTextRect(0,70*4,20,20);
                burbujasInicio[i]->EscalarProporcion(2,2);
            }
        }else{
            int width = Camara::Instance()->getWidth();
            burbujasInicio[0]->CambiarPosicion(width-tiempo*40+30,-0.5*pow(tiempo*10,2)+600);
            burbujasInicio[1]->CambiarPosicion(width-tiempo*45+60,-0.4*pow(tiempo*10,2)+700);
            burbujasInicio[2]->CambiarPosicion(width-tiempo*45+90,-0.3*pow(tiempo*10,2)+700);
        }
        
        if(tiempo>0.88*T_ENTRADA){
            sprite.CambiarTextRect(4*90,2*70,90,70);
        }else if(tiempo>0.8*T_ENTRADA){
            sprite.CambiarTextRect(3*90,2*70,90,70);
        }else if(tiempo>0.35*T_ENTRADA && tiempo<0.65*T_ENTRADA){
            MoverX(-velocidad);
            if(tDesp.GetSegundos()>0.2){
                ModificarSpriteCorrer();
                tDesp.ReiniciarSegundos();
            }
        }
    }
        
    bool BossCangrejo::animacionMuerte() {
        if(EstadoJuego::Instance()->_level->isPeleandoBoss()&&Clock_animacionMuerte.GetSegundos()>3*T_MUERTE)
            Clock_animacionMuerte.ReiniciarSegundos();
        
        float tiempo = Clock_animacionMuerte.GetSegundos();
        
        if(tiempo>0.5*T_MUERTE){
            sprite.CambiarTextRect(1*90,3*70,90,70);
        }else if(tiempo>0.15*T_MUERTE){
            sprite.CambiarTextRect(0*90,3*70,90,70);
        }else if(tiempo>0.1*T_MUERTE){
            sprite.CambiarTextRect(1*90,2*70,90,70);
        }else if(tiempo>0.05*T_MUERTE){
            sprite.CambiarTextRect(0*90,2*70,90,70);
        }
        
        
        for (int i = 0; i < proyectiles.size(); i++) {
            BorrarProyectil(i);
        }

        
        if(tiempo>T_MUERTE)
            return true;
        else
            return false;
    }

    
    void BossCangrejo::Update(int Posx, int Posy, Player* p) {
        MoverY();
        if(!muerto && Clock_animacionEntrada.getElapsedTime().asSeconds()>T_ENTRADA){
            if(burbujasInicio[0]!=0){
                for (int i = 0; i < 3; i++) {
                    delete burbujasInicio[i];
                    burbujasInicio[i]=0;
                }
            }
            
            float x=sprite.GetX();
            float y=sprite.GetY();
            float diferenciax=Posx-x;
            float diferenciay=Posy-y;
            angulo=atan2(diferenciax,diferenciay)*180/3.14159;
            if(diferenciax<1200 && diferenciay<1200 && diferenciax>-1200 && diferenciay>-1200){
                if(abs(diferenciax)<300 && abs(diferenciay)<alcancey){
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
                    if(tAtaque.GetSegundos()>1.5 && Posx-x<150 && Posx-x>-150)
                        Ataque1=true;
                    if(tDesp.GetSegundos()>0.1){
                        if(Ataque1){
                            ModificarSpriteAtaque1();
                            if(contadorSpriteAtaque1==1){
                                if(p->GetSprite().Interseccion(sprite)){
                                    if(p->GetSprite().InterseccionPixel(&sprite))
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
                }else if(abs(diferenciax)<alcancex && abs(diferenciay)<alcancey){
                    if(tAtaque2.GetSegundos()>1)
                            Ataque2=true;
                    if(tDesp.GetSegundos()>0.1){
                        if(Ataque2){
                            ModificarSpriteAtaque2();
                            tDesp.ReiniciarSegundos();
                        }
                        else if(tAtaque.GetSegundos()<2 && tDesp.GetSegundos()>0.2){
                            ModificarSpriteCorrer();
                            tDesp.ReiniciarSegundos();
                        }
                    }
                }
                for(int i=0;i<proyectiles.size();i++)
                {
                    bool b=proyectiles[i]->Update();
                    if(!b || EstadoJuego::Instance()->_level->ComprobarColision(proyectiles[i]->GetProyectil()->GetX(),proyectiles[i]->GetProyectil()->GetY()))
                        BorrarProyectil(i);
                    else if(proyectiles[i]->GetProyectil()->InterseccionContiene(p->GetSprite()))
                    {
                        if(!p->isAttacking()){
                            p->RecibirDanyo(proyectiles[i]->GetDanyo());
                            BorrarProyectil(i);
                        }else{
                            Clock_explotarBurbuja.ReiniciarSegundos();
                            proyectiles[i]->GetProyectil()->Mover(-80/2,-74/2);
                            animacionExplote.push_back(proyectiles[i]);
                            proyectiles.erase(proyectiles.begin()+i);
                        }    
                    }
                }
            }

            if(rojo && relojrojo.GetSegundos()<=0.2)
                sprite.CambiarColorRojo();
            else if(rojo && relojrojo.GetSegundos()>0.2){
                rojo=false;
                sprite.Parpadear(false);
            }
            
            if(vida<=0){
                muerto=true;
            }
        }else if(!muerto){
            animacionEntrada();
        }
    }
    void BossCangrejo::BorrarProyectil(int i) {
        Proyectil *tmp=proyectiles[i];
        proyectiles.erase(proyectiles.begin()+i);
        delete tmp;
    }


}

