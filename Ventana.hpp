#pragma once
using namespace std;
#include <iostream>
#include <SFML/Graphics.hpp>

namespace Motor
{
    class Ventana
    {
    public:
        static Ventana* Instance();
        ~Ventana();
        
        void CrearVentana(int ancho, int alto, string titulo);
        bool EstaAbierta();
        void Limpiar();
        void Mostrar();
        
    private:
        Ventana() { };
        Ventana(const Ventana &);
        Ventana &operator=(const Ventana &);
        static Ventana* _pinstance;
        
        sf::RenderWindow window;
    };
}