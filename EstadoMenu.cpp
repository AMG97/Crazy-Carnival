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
        text.CambiarFuente(_juego->recursos.GetFuente("DK"));
        text.CambiarTexto("Crazy Carnival");
        text.CambiarTamanyo(50);
        text.CambiarPosicion(_juego->ancho/2, 100);
        
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
        
        _juego->_ventana->draw(text);
        
        _juego->_ventana->Mostrar();
    }
}