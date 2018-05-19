#pragma once

#include <stack>  // Para la pila de estados
#include "Estado.hpp"
using namespace std;

namespace Crazy
{
    class EstadosManager
    {
    public:
        EstadosManager() { }
        ~EstadosManager() {
            while (estados.size() > 0) {
                estado = estados.top();
                delete estado;
                estado = 0;
                estados.pop();
            }
        }
        
        void Anyadir(Estado* nuevoEstado, bool reemplazar = true);
        void Eliminar();
        
        void ProcesarPilaEstados();
        void SaltarAlMenu();
        
        Estado* &GetEstadoActivo();
        
    private:
        stack<Estado*> estados;
        
        Estado* estado;
        
        bool reemplazando;
        bool anyadiendo;
        bool eliminando;
    };
}