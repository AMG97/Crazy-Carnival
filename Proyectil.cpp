#include "Proyectil.hpp"

namespace Crazy
{
    Proyectil::Proyectil(int n, float dan, float ang, SpriteM sp) 
    {
        _juego= Juego::Instance();
        switch (n)
        {
            case 1:
                sprite.CambiarTextura(_juego->recursos.GetTextura("Puñal"));
                alcance=400;
                danyo=dan*1.5;
                velocidad=5;
            break;
            
            case 2:
                sprite.CambiarTextura(_juego->recursos.GetTextura("Bala"));
                alcance=750;
                danyo=dan;
                velocidad=6;
            break;
            case 3:
                sprite.CambiarTextura(_juego->recursos.GetTextura("Cangrejo"));
                sprite.CambiarTextRect(0,70*4,20,20);
                danyo=dan;
                velocidad=6;
                alcance=1200;
            break;
                
        }
        angulo=ang*3.14159/180;
        if(angulo>0)
            angulo-=0.05;
        else
            angulo+=0.05;
        PosIniX=sp.GetX();
        PosIniY=sp.GetY();
        if(n==2){
            PosIniX=PosIniX+50*sin(angulo);
            PosIniY=PosIniY+50*cos(angulo)-10;
        }
        sprite.CambiarPosicion(PosIniX, PosIniY);
        sprite.EscalarProporcion(2.2,2.2);
        sprite.Rotar(-angulo*180/3.14159+90);
    }
    

    Proyectil::Proyectil(const Proyectil& orig) {
    }

    Proyectil::~Proyectil() {
    }
    
    void Proyectil::Dibujar()
    {
        _juego->_ventana->DibujarC(sprite);
    }
    
    bool Proyectil::Update()
    {
        sprite.Mover(sin(angulo)*velocidad,cos(angulo)*velocidad);
        float distancia=sqrt(pow(PosIniX-sprite.GetX(),2)+pow(PosIniY-sprite.GetY(),2));
        if(distancia>alcance)
            return false;
        else
            return true;
    }
    
    SpriteM Proyectil::GetProyectil()
    {
        return sprite;
    }
    
    float Proyectil::GetDanyo()
    {
        return danyo;
    }
    bool Proyectil::direccion() {
        if(sin(angulo)>0)
            return false;
        else
            return true;
    }

}

