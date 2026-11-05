#ifndef BSTREEDICT_H
#define BSTREEDICT_H

#include <ostream>
#include <stdexcept>
#include "Dict.h"
#include "BSTree.h"
#include "TableEntry.h"

template <typename V>
class BSTreeDict : public Dict<V> {

    private:
        BSTree<TableEntry<V>>* tree;   // el ABB que guarda las parejas

    public:
        BSTreeDict() {
            tree = new BSTree<TableEntry<V>>();
        }

        ~BSTreeDict() {
            delete tree;   // el destructor de BSTree libera los nodos
        }

        // ---- métodos heredados de Dict<V> ----
        void insert(std::string key, V value) override {
            tree->insert(TableEntry<V>(key, value));
        }

        V search(std::string key) override {
            return tree->search(TableEntry<V>(key)).value;
        }

        V remove(std::string key) override {
            V valor = search(key);                  // si no existe, lanza excepción aquí
            tree->remove(TableEntry<V>(key));
            return valor;
        }

        int entries() override {
            return tree->size();
        }

        // ---- métodos propios ----
        V operator[](std::string key) {
            return search(key);
        }

        friend std::ostream& operator<<(std::ostream& out, const BSTreeDict<V>& bs) {
            out << *bs.tree;
            return out;
        }
};

#endif
