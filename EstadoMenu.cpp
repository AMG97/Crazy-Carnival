#include "EstadoMenu.hpp"
#include "Texto.hpp"
using namespace Motor;


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
    }
    
    void EstadoMenu::ManejarEventos()
    {
        
    }
    
    void EstadoMenu::Actualizar(float tiempoActual)
    {
        
    }
    
    void EstadoMenu::Dibujar(float tiempoActual)
    {
        _juego->_ventana->Limpiar();
        
        _juego->_ventana->draw(t_titulo);
        _juego->_ventana->draw(t_jugar);
        _juego->_ventana->draw(t_ayuda);
        
        _juego->_ventana->Mostrar();
    }
}