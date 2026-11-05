#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <ostream>
#include <stdexcept>
#include <string>
#include "Dict.h"
#include "TableEntry.h"

#include "../PRA_2627_P1/ListLinked.h"  // ¡ADAPTA A TU RUTA!

template <typename V>
class HashTable : public Dict<V> {

    private:
        int n;                                // elementos almacenados
        int max;                              // número de cubetas
        ListLinked<TableEntry<V>>* table;     // array de cubetas (listas)

        // Función hash: suma de ASCII de la clave, módulo nº de cubetas
        int h(std::string key) {
            int suma = 0;
            for (int i = 0; i < (int)key.size(); i++) {
                suma += int(key.at(i));
            }
            return suma % max;
        }

    public:
        HashTable(int size) {
            n = 0;
            max = size;
            table = new ListLinked<TableEntry<V>>[max];
        }

        ~HashTable() {
            delete[] table;
        }

        int capacity() {
            return max;
        }

        // ---- métodos heredados de Dict<V> ----
        void insert(std::string key, V value) override {
            int cubeta = h(key);
            if (table[cubeta].search(TableEntry<V>(key)) != -1)
                throw std::runtime_error("Key '" + key + "' already exists!");
            table[cubeta].prepend(TableEntry<V>(key, value));  // al principio de la lista
            n++;
        }

        V search(std::string key) override {
            int cubeta = h(key);
            int pos = table[cubeta].search(TableEntry<V>(key));
            if (pos == -1)
                throw std::runtime_error("Key '" + key + "' not found!");
            return table[cubeta].get(pos).value;
        }

        V remove(std::string key) override {
            int cubeta = h(key);
            int pos = table[cubeta].search(TableEntry<V>(key));
            if (pos == -1)
                throw std::runtime_error("Key '" + key + "' not found!");
            V valor = table[cubeta].get(pos).value;
            table[cubeta].remove(pos);
            n--;
            return valor;
        }

        int entries() override {
            return n;
        }

        // ---- métodos propios ----
        V operator[](std::string key) {
            return search(key);
        }

        friend std::ostream& operator<<(std::ostream& out, const HashTable<V>& th) {
            out << "HashTable [entries: " << th.n << ", capacity: " << th.max << "]\n";
            out << "==============\n\n";
            for (int i = 0; i < th.max; i++) {
                out << "== Cubeta " << i << " ==\n\n";
                out << th.table[i] << "\n\n";
            }
            out << "==============\n\n";
            return out;
        }
};

#endif
