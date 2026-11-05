#ifndef DICT_H
#define DICT_H
#include <string>

template <typename V>
class Dict {
    public:
        virtual ~Dict() {}  // destructor virtual (buena práctica en interfaces)

        // Inserta key->value. Lanza std::runtime_error si key ya existe
        virtual void insert(std::string key, V value) = 0;

        // Devuelve el valor de key. Lanza std::runtime_error si no existe
        virtual V search(std::string key) = 0;

        // Elimina key->value y devuelve el valor. Lanza std::runtime_error si no existe
        virtual V remove(std::string key) = 0;

        // Número de elementos del diccionario
        virtual int entries() = 0;
};

#endif
