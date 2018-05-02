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
        void CambiarTextRect(int x, int y, int width, int height);
        void CambiarPosicion(float x, float y);
        void CentrarOrigen();
        void CambiarOrigen();
        void CambiarOrigen(float x, float y);
        void CambiarColorRojo();
        void Rotar(float angulo);
        void Escalar(float x, float y);
        void EscalarProporcion(float x, float y);
        void Parpadear(bool parpadeo);
        
        float GetAncho();
        float GetAlto();
        float GetX();
        float GetY();
    };
    
    class Camara
    {
    public:
        static Camara* Instance();
        ~Camara();
        void CrearCamara(float centroX, float centroY, float ancho, float alto);
        sf::View& GetCamara();
        void setTam(float x, float y);

    private:
        Camara() { };
        Camara(const Camara &);
        Camara &operator=(const Camara &);
        static Camara* _pinstance2;
        
        sf::View camara;
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
        void setCamara(Camara &camara);
        void setBackground(int r, int g, int b);
        sf::RenderWindow& GetVentana();
        
    private:
        Ventana() { };
        Ventana(const Ventana &);
        Ventana &operator=(const Ventana &);
        static Ventana* _pinstance;
        
        sf::RenderWindow window;
        sf::Color background;
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
			
            //Pruebas
            bool D;
            bool C;
            bool F;
            bool R;
            bool E;
            bool Q;
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