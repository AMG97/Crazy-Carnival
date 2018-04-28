#include "EstadoMenu.hpp"

namespace Crazy
{
    EstadoMenu::EstadoMenu()
    {
        _juego = Juego::Instance();
    }
    
    EstadoMenu* EstadoMenu::_pinstance=0;
    
    EstadoMenu* EstadoMenu::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new EstadoMenu();
        }
        return _pinstance;
    }
    
    EstadoMenu::~EstadoMenu()
    {
        delete _input;
        _input = NULL;
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoMenu::Init()
    {
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Crazy Carnival");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CambiarOrigen(t_titulo.GetAncho()/2, t_titulo.GetAlto()/2);
        t_titulo.CambiarPosicion((_juego->ancho/2), 150);
        
        t_jugar.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_jugar.CambiarTexto("Jugar");
        t_jugar.CambiarTamanyo(50);
        t_jugar.CambiarOrigen(t_jugar.GetAncho()/2, t_jugar.GetAlto()/2);
        t_jugar.CambiarPosicion((_juego->ancho/2), t_titulo.GetY()+200);
        
        t_ayuda.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_ayuda.CambiarTexto("Ayuda");
        t_ayuda.CambiarTamanyo(50);
        t_ayuda.CambiarOrigen(t_ayuda.GetAncho()/2, t_ayuda.GetAlto()/2);
        t_ayuda.CambiarPosicion((_juego->ancho/2), t_jugar.GetY()+75);
        
        _input = new Input();
        opcion = JUGAR;
        teclaPulsada = false;
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        CambiarFlecha(t_jugar);
        flecha.CambiarColorRojo();
        flecha.Escalar(80.0f, 80.0f); // Escalar al 80%
    }
    
    void EstadoMenu::ManejarEventos()
    {
        teclaPulsada = _input->BucleEventos();
        
        if (teclaPulsada) {
            if (_input->GetPressed().Arriba) {
                opcion--;
                if (opcion < JUGAR)
                {
                    opcion = AYUDA;
                }
            }

            if (_input->GetPressed().Abajo) {
                opcion++;
                if (opcion > AYUDA)
                {
                    opcion = JUGAR;
                }
            }
            
            if (_input->GetPressed().Enter) {
                CambiarEstado();
            }
            
            teclaPulsada = false;
        }
    }
    
    void EstadoMenu::Actualizar(float tiempoActual)
    {
        switch (opcion)
        {
            case JUGAR:
                CambiarFlecha(t_jugar);
                break;
            case AYUDA:
                CambiarFlecha(t_ayuda);
                break;
        }
    }
    
    void EstadoMenu::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->draw(t_titulo);
        _juego->_ventana->draw(t_jugar);
        _juego->_ventana->draw(t_ayuda);
        
        _juego->_ventana->draw(flecha);
        
        _juego->_ventana->Mostrar();
    }
    
    void EstadoMenu::Jugar()
    {
        _juego->maquina.Anyadir(new EstadoJuego());
    }
    
    void EstadoMenu::CambiarFlecha(Texto texto)
    {
        flecha.CambiarPosicion(texto.GetLeft()-10,texto.GetY()+texto.GetOrigenY()/2);
    }
    
    void EstadoMenu::CambiarEstado()
    {
        switch (opcion)
        {
            case JUGAR:
                _juego->maquina.Anyadir(new EstadoJuego());
                break;
            case AYUDA:
                //_juego->maquina.Anyadir(new EstadoAyuda());
                cout <<"AYUDA";
                break;
        }
    }
}