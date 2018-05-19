#include "Arma.hpp"
#include "Enemigo.hpp" 
#include "Player.hpp"
#include "Nivel.hpp"
#include "EstadoJuego.hpp"

namespace Crazy
{
    Arma::Arma(int n, float x, float y, bool p) 
    {
        _juego= Juego::Instance();
        tipo=0;
        player=p;
        switch (tipo)
        {
            case 0:
                sprite.CambiarTextura(_juego->recursos.GetTextura("Enemigo-Pistola1"));
                danyo=8;
            break;
            case 1:
                sprite.CambiarTextura(_juego->recursos.GetTextura("Espada1"));
                danyo=10;
            break;
            case 2:
                sprite.CambiarTextura(_juego->recursos.GetTextura("Espada2"));
                danyo=12;
            break;
        }
        sprite.CambiarTextRect(0,0,60,80);
        sprite.CambiarOrigen(60/2,80/2);
        sprite.CambiarPosicion(x,y);
        sprite.EscalarProporcion(1.5, 1.5);
    }

    Arma::Arma(const Arma& orig) {
    }

    Arma::~Arma() {
    }
    
    void Arma::Dibujar()
    {
        if(tipo!=0)
            _juego->_ventana->DibujarSprite(sprite);
        for(int i=0; i<proyectiles.size();i++)
            proyectiles[i]->Dibujar();
    }
    
    void Arma::ModificarSprite(int estado, int n, int x, int y, float angulo)
    {
                sprite.CambiarPosicion(x,y);
        switch (estado)
        {
            case REPOSO:
                sprite.CambiarTextRect(n*60,0,60,80);
                sprite.CambiarOrigen(30, 40);
            break;
            
            case SALTO:
                sprite.CambiarTextRect(n*60,7*80,60,90);
                sprite.CambiarOrigen(30, 45);
            break;
            
            case CORRER:
                sprite.CambiarTextRect(n*60,80,60,80);
                sprite.CambiarOrigen(30, 40);
            break;
            
            case ATAQUE2:
                sprite.CambiarTextRect(n*100,360,100,80);
                sprite.CambiarOrigen(50, 40);
            break;
            
            case ATAQUE1:
                    sprite.CambiarTextRect(n*100,150,100,90);
                    sprite.CambiarOrigen(50, 45);
            break;
        }
    }
    
    void Arma::CambiarDireccion(){
        sprite.EscalarProporcion(-1.0, 1.0);
    }
    
    
    
    
    void Arma::Update(float x, float y, vector<Enemigo*> e, Player *p){
        sprite.CambiarPosicion(x,y);
        bool colision=false;
        for(int i=0;i<proyectiles.size();i++){
            bool b=proyectiles[i]->Update();
            if(!b || EstadoJuego::Instance()->_level->ComprobarColision(proyectiles[i]->GetProyectil().GetX(),proyectiles[i]->GetProyectil().GetY()))
                BorrarProyectil(i);
            else{
                for(int j=0;j<e.size() && colision==false;j++){
                    if(proyectiles[i]->GetProyectil().Interseccion1(e[j]->GetSprite()))
                    {
                        p->ModificarEnfriamiento(5);
                        e[j]->RecibirDanyo(proyectiles[i]->GetDanyo());
                        BorrarProyectil(i);
                        colision=true;
                    }
                }
            }
        }
    }
    float Arma::GetDanyo(){
        return danyo;
    }
    
    void Arma::Update(float x, float y, Player* p){
        sprite.CambiarPosicion(x,y-15);
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
    
    void Arma::BorrarProyectil(int i)
    {
        Proyectil *tmp=proyectiles[i];
        proyectiles.erase(proyectiles.begin()+i);
        delete tmp;
    }
    
    void Arma::Disparar(float angulo)
    {
        int t;
        if(tipo==1 || tipo==2)
            t=1;
        else
            t=2;
        Proyectil *p=new Proyectil(t,danyo,angulo,sprite);
        proyectiles.push_back(p);
    }
}



