#pragma once

#include "tinyxml/tinyxml.h"
#include <iostream> 
#include <map>

using namespace std;

namespace Crazy{
    class GestorArchivo {
    public:
        static GestorArchivo* Instance();
        void Iniciar(unsigned short int n_slot);
        virtual ~GestorArchivo();
        
        void borrarSlot();
        bool borrarGuardado();
        void guardarPartida();
        void guardarStats();
        void nuevoSlot();
        void cargarPartida();
        bool exists(string nombre);
        void cargarStats();
        float getStat(string name);
        bool setStat(string name, float valor);
        bool addStat(string name, float valor);
        map<string, float>* getTotalStats();
    private:
        static GestorArchivo* pinstance;
        GestorArchivo();
        
        TiXmlDocument doc_stat, doc_save;
        map<string, float> stats;
        
        unsigned short int slot;
    };

}