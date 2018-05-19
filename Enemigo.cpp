#include "Enemigo.hpp"
#include "EstadoJuego.hpp"

namespace Crazy
{
    Enemigo::Enemigo() {
        contadorSpriteCorrer=0;
        contadorSpriteAtaque1=0;
        Ataque1=false;
        rojo=false;
        angulo=0;
        SetDireccion(true);
    }

    Enemigo::Enemigo(const Enemigo& orig) {
    }

    Enemigo::~Enemigo() {
    }
    
    void Enemigo::SetDireccion(bool direccion)
    {
        if(!direccion && direccionIzq){
            CambiarDireccionDer();
        }
        else if(direccion && !direccionIzq){
            CambiarDireccionIzq();
        }
        direccionIzq=direccion;
    }
    
    void Enemigo::Dibujar(){
        _juego->_ventana->DibujarSprite(sprite);
        _arma->Dibujar();
    }
    
    void Enemigo::RecibirDanyo(float dan){
        vida-=dan;
        rojo=true;
        relojrojo.ReiniciarSegundos();
    }

    int Enemigo::getPuntos() {
        return puntos;
    }

}
