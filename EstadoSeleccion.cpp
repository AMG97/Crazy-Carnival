#include "EstadoSeleccion.hpp"

namespace Crazy
{
    EstadoSeleccion::EstadoSeleccion()
    {
        _juego = Juego::Instance();
    }
    
    EstadoSeleccion* EstadoSeleccion::_pinstance=0;
    
    EstadoSeleccion* EstadoSeleccion::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoSeleccion();
        }
        return _pinstance;
    }
    
    void EstadoSeleccion::Vaciar()
    {
        _pinstance=0;
    }
        
    EstadoSeleccion::~EstadoSeleccion()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoSeleccion::Init()
    {
        _input = new Input();
        opcion = P1;
        contadorSpriteReposo = 0;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_titulo.CambiarTexto("Elige personaje");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->GetAncho()/2), 100);
        
        p1.CambiarTextura(_juego->recursos.GetTextura("Espadachina"));
        p1.CambiarTextRect(0*60, 0*80, 60, 80);
        p1.CambiarOrigen(p1.GetAncho()/2, p1.GetAlto()/2);
        p1.CambiarPosicion((_juego->GetAncho()/2)-150, t_titulo.GetY()+300);
        p1.EscalarProporcion(2, 2);
        
        p2.CambiarTextura(_juego->recursos.GetTextura("Espadachina"));
        p2.CambiarTextRect(0*60, 0*80, 60, 80);
        p2.CambiarOrigen(p2.GetAncho()/2, p2.GetAlto()/2);
        p2.CambiarPosicion(p1.GetX()+300, t_titulo.GetY()+300);
        p2.EscalarProporcion(2, 2);
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        flecha.Rotar(90.0f);
        CambiarFlecha(p1);
        flecha.CambiarColorRojo();
        flecha.Escalar(50.0f, 50.0f); // Escalar al 50%
        
        t_atras.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_atras.CambiarTexto("Volver");
        t_atras.CambiarTamanyo(50);
        t_atras.CentrarOrigen();
        t_atras.CambiarPosicion(100, (_juego->GetAlto()-100));
        
        flechaAtras.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flechaAtras.CambiarOrigen();
        flechaAtras.Rotar(180.0f);
        flechaAtras.CambiarPosicion(60, t_atras.GetY()-30);
        flechaAtras.Escalar(70.0f, 70.0f); // Escalar al 70%
    }
    
    void EstadoSeleccion::ManejarEventos()
    {
        if (_input->GetTipoEvento() == _input->Evento().KeyPressed)
        {
            if (_input->BackSpace()
                || _input->Escape())
            {
                Atras();
            }
            
            if (_input->Izq()) {
                opcion--;
                if (opcion < P1)
                {
                    opcion = P2;
                }
            }
            
            if (_input->Der()) {
                opcion++;
                if (opcion > P2)
                {
                    opcion = P1;
                }
            }
            
            if(_input->Enter()){
                Elegir();
            }
        }
    }
    
    void EstadoSeleccion::Actualizar(float tiempoActual)
    {
        switch (opcion)
        {
            case P1:
                CambiarFlecha(p1);
                break;
            case P2:
                CambiarFlecha(p2);
                break;
        }
    }
    
    void EstadoSeleccion::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->DibujarTexto(t_titulo);
        Animar();
        _juego->_ventana->DibujarSprite(p1);
        _juego->_ventana->DibujarSprite(p2);
        _juego->_ventana->DibujarSprite(flecha);
        _juego->_ventana->DibujarTexto(t_atras);
        _juego->_ventana->DibujarSprite(flechaAtras);

        _juego->_ventana->Mostrar();
    }
    
    void EstadoSeleccion::Atras()
    {
        _juego->maquina.Eliminar();
    }
    
    void EstadoSeleccion::CambiarFlecha(SpriteM personaje)
    {
        flecha.CambiarPosicion(personaje.GetX(),personaje.GetY()-personaje.GetAlto()/2);
    }
    
    void EstadoSeleccion::Elegir()
    {
        EstadoJuego::Instance(); // Creamos el puntero
        switch (opcion)          // Elegimos el personaje
        {
            case P1:
                EstadoJuego::Instance()->Personaje("Espadachina");
                break;
            case P2:
                EstadoJuego::Instance()->Personaje("Espadachina");
                break;
        }
        // Cambiamos de estado la maquina
        _juego->maquina.Anyadir(EstadoJuego::Instance(), true);
    }
    
    void EstadoSeleccion::Animar()
    {
        if (relojAnim.GetSegundos() >= 0.1f)
        {
            switch(opcion)
            {
                case P1:
                    p1.CambiarTextRect(contadorSpriteReposo*60, 0*80, 60, 80);
                    p1.CambiarOrigen(60/2,80/2);
                    break;
                case P2:
                    p2.CambiarTextRect(contadorSpriteReposo*60, 0*80, 60, 80);
                    p2.CambiarOrigen(60/2,80/2);
                    break;
            }
            
            contadorSpriteReposo++;
            if(contadorSpriteReposo == 8)
            {
                contadorSpriteReposo = 0;
            }
            relojAnim.ReiniciarSegundos();
        }
    }
}