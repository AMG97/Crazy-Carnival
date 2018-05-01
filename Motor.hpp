#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
using namespace std;

namespace Motor
{
    class Reloj : public sf::Clock {
    public:
        Reloj() { };
        float ReiniciarMilisegundos();
        float ReiniciarSegundos();
        float GetSegundos();
        float GetMilisegundos();
    };
    
    class Texto : public sf::Text {
    public:
        Texto() { };
        void CambiarFuente(sf::Font& fuente);
        void CambiarTexto(string text);
        void CambiarTamanyo(int tam);
        void CambiarPosicion(float x, float y);
        void CentrarOrigen();
        void CambiarOrigen(float x, float y);
        
        float GetOrigenX();
        float GetOrigenY();
        float GetAncho();
        float GetAlto();
        float GetTop();
        float GetLeft();
        float GetX();
        float GetY();
    };
    
    class Recursos
    {
    public:
        Recursos() {};
        ~Recursos() {};
        
        void CargarTextura(string nombre, string fichero);
        sf::Texture &GetTextura(string nombre);
        
        void CargarFuente(string nombre, string fichero);
        sf::Font &GetFuente(string nombre);
        
    private:
        map<string, sf::Texture> texturas;
        map<string, sf::Font> fuentes;
    };
    
    class SpriteM : public sf::Sprite {
    public:
        SpriteM() { };
        void CambiarTextura(sf::Texture &textura);
        void CambiarPosicion(float x, float y);
        void CentrarOrigen();
        void CambiarOrigen();
        void CambiarOrigen(float x, float y);
        void CambiarColorRojo();
        void Rotar(float angulo);
        void Escalar(float x, float y);
        void Parpadear (bool parpadeo);
        
        float GetAncho();
        float GetAlto();
        float GetX();
        float GetY();
    };
    
    class Ventana
    {
    public:
        static Ventana* Instance();
        ~Ventana();
        
        void CrearVentana(int ancho, int alto, string titulo);
        bool EstaAbierta();
        void Limpiar();
        void Mostrar();
        void Cerrar();
        void Dibujar(Texto txt);
        void Dibujar(SpriteM sprite);
        sf::RenderWindow& GetVentana();
        
    private:
        Ventana() { };
        Ventana(const Ventana &);
        Ventana &operator=(const Ventana &);
        static Ventana* _pinstance;
        
        sf::RenderWindow window;
    };
    
    class Input
    {
    public:
        struct Teclas {
            bool Pausar;
            bool Arriba;
            bool Abajo;
            bool Izq;
            bool Der;
            bool Enter;
            bool BackSpace;
            bool Escape;
            bool RatonIzq;
            bool RatonDer;
        };
        Input();
        void CerrarVentana();
        bool BucleEventos();
        Teclas GetTeclas();
        float GetPosicionRatonX();
        float GetPosicionRatonY();
        
    private:
        Ventana* _ventana;
        Teclas teclas;
    };
}