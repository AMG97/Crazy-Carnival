#include "Ventana.hpp"
namespace Motor
{
    Ventana* Ventana::_pinstance=0;
    
    Ventana* Ventana::Instance()
    {
        if (_pinstance == 0)
        {
            _pinstance = new Ventana();
        }
        return _pinstance;
    }
    
    Ventana::~Ventana()
    {
        delete _pinstance;
        _pinstance = NULL;
    }
    
    void Ventana::CrearVentana(int ancho, int alto, string titulo) {
        window.create(sf::VideoMode(ancho, alto), titulo);

        //Activa la sincronizacion vertical (60 fps)
        window.setVerticalSyncEnabled(true); 
        window.setFramerateLimit(60);
    }
    
    bool Ventana::EstaAbierta() {
        return window.isOpen();
    }
    
    void Ventana::Limpiar()
    {
        window.clear();
    }
    
    void Ventana::Mostrar()
    {
        window.display();
    }
}