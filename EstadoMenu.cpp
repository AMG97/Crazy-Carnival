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
        _input = new Input();
        opcion = JUGAR;
        teclaPulsada = false;
        
        t_titulo.CambiarFuente(_juego->recursos.GetFuente("Z"));
        t_titulo.CambiarTexto("Crazy Carnival");
        t_titulo.CambiarTamanyo(100);
        t_titulo.CentrarOrigen();
        t_titulo.CambiarPosicion((_juego->GetAncho()/2), 150);
        
        t_jugar.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_jugar.CambiarTexto("Jugar");
        t_jugar.CambiarTamanyo(50);
        t_jugar.CentrarOrigen();
        t_jugar.CambiarPosicion((_juego->GetAncho()/2), t_titulo.GetY()+200);
        
        t_ayuda.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_ayuda.CambiarTexto("Ayuda");
        t_ayuda.CambiarTamanyo(50);
        t_ayuda.CentrarOrigen();
        t_ayuda.CambiarPosicion((_juego->GetAncho()/2), t_jugar.GetY()+75);
        
        t_salir.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_salir.CambiarTexto("Salir");
        t_salir.CambiarTamanyo(50);
        t_salir.CentrarOrigen();
        t_salir.CambiarPosicion((_juego->GetAncho()/2), t_ayuda.GetY()+75);
        
        flecha.CambiarTextura(_juego->recursos.GetTextura("Flecha"));
        flecha.CambiarOrigen();
        CambiarFlecha(t_jugar);
        flecha.CambiarColorRojo();
        flecha.Escalar(80.0f, 80.0f); // Escalar al 80%
        
        t_explicar.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_explicar.CambiarTexto("Utiliza las");
        t_explicar.CambiarTamanyo(40);
        t_explicar.CentrarOrigen();
        t_explicar.CambiarPosicion(_juego->GetAncho()/2-120, _juego->GetAlto()-50);
        
        flechas.CambiarTextura(_juego->recursos.GetTextura("Flechas"));
        flechas.CentrarOrigen();
        flechas.CambiarPosicion(_juego->GetAncho()/2, t_explicar.GetY()+8);
        flechas.Escalar(50.0f, 50.0f); // Escalar al 50%
        
        t_explicar2.CambiarFuente(_juego->recursos.GetFuente("DK"));
        t_explicar2.CambiarTexto("para elegir");
        t_explicar2.CambiarTamanyo(40);
        t_explicar2.CentrarOrigen();
        t_explicar2.CambiarPosicion(flechas.GetX()+flechas.GetAncho()+70, t_explicar.GetY());
    }
    
    void EstadoMenu::ManejarEventos()
    {
        if (_input->GetTipoEvento() == _input->Evento().KeyPressed)
        {
            if (_input->Enter()) {
                CambiarEstado();
            }
            
            if (_input->Escape()) {
                _juego->_ventana->Cerrar();
            }
            
            if (_input->Arriba()) {
                opcion--;
                if (opcion < JUGAR)
                {
                    opcion = SALIR;
                }
            }
            
            if (_input->Abajo()) {
                opcion++;
                if (opcion > SALIR)
                {
                    opcion = JUGAR;
                }
            }
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
            case SALIR:
                CambiarFlecha(t_salir);
                break;
        }
    }
    
    void EstadoMenu::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->Dibujar(t_titulo);
        _juego->_ventana->Dibujar(t_jugar);
        _juego->_ventana->Dibujar(t_ayuda);
        _juego->_ventana->Dibujar(t_salir);
        _juego->_ventana->Dibujar(flecha);
        _juego->_ventana->Dibujar(t_explicar);
        _juego->_ventana->Dibujar(flechas);
        _juego->_ventana->Dibujar(t_explicar2);
        
        _juego->_ventana->Mostrar();
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
                _juego->maquina.Anyadir(new EstadoMenuPartidas());
                break;
            case AYUDA:
                _juego->maquina.Anyadir(new EstadoAyuda());
                break;
            case SALIR:
                _juego->_ventana->Cerrar();
                break;
        }
    }
}