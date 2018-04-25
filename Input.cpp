#include "Input.hpp"

namespace Motor
{
    Input::Input()
    {
        _ventana = Ventana::Instance();
    }
    
    void Input::CerrarVentana()
    {
        _ventana->Cerrar();
    }
    
    unsigned short int Input::BucleEventosMenu()
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (_ventana->pollEvent(event))
        {
            switch(event.type)
            {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    CerrarVentana();
                break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla
                    switch(event.key.code)
                    {
                        //Mapeo del cursor
                        case sf::Keyboard::Space:
                            cout << "Jugar" << endl;
                            return 1;
                        break;

                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            CerrarVentana();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            cout << event.key.code << endl;
                        break;
                    }
                break;
            }
        }
        
        return 0;
    }
    
    void Input::BucleEventosJuego()
    {
        //Bucle de obtención de eventos
        sf::Event event;
        while (_ventana->pollEvent(event))
        {
            switch(event.type)
            {
                //Si se recibe el evento de cerrar la ventana la cierro
                case sf::Event::Closed:
                    CerrarVentana();
                break;
                    
                //Se pulsó una tecla, imprimo su codigo
                case sf::Event::KeyPressed:
                    
                    //Verifico si se pulsa alguna tecla
                    switch(event.key.code)
                    {

                        //Tecla ESC para salir
                        case sf::Keyboard::Escape:
                            CerrarVentana();
                        break;
                        
                        //Cualquier tecla desconocida se imprime por pantalla su código
                        default:
                            cout << event.key.code << endl;
                        break;
                    }
                break;
            }
        }
    }
}