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
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void EstadoMenu::Init()
    {
        
    }
    
    void EstadoMenu::ManejarEventos()
    {
        
    }
    
    void EstadoMenu::Actualizar(float tiempoActual)
    {
        
    }
    
    void EstadoMenu::Dibujar(float tiempoActual)
    {
        
    }
}