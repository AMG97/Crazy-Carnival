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
        create(sf::VideoMode(ancho, alto), titulo);

        //Activa la sincronizacion vertical (60 fps)
        setVerticalSyncEnabled(true); 
        setFramerateLimit(60);
    }
    
    bool Ventana::EstaAbierta() {
        return isOpen();
    }
    
    void Ventana::Limpiar()
    {
        clear();
    }
    
    void Ventana::Mostrar()
    {
        display();
    }
    
    void Ventana::Cerrar()
    {
        close();
    }
}