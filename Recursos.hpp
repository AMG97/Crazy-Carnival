#include <iostream>
using namespace std;
#include <map>
#include <SFML/Graphics.hpp>

namespace Motor
{
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
}