#ifndef TABLEENTRY_H
#define TABLEENTRY_H
#include <string>
#include <ostream>

template <typename V>
struct TableEntry {
    std::string key;
    V value;

    TableEntry(std::string key, V value) : key(key), value(value) {}
    TableEntry(std::string key) : key(key), value() {}
    TableEntry() : key(""), value() {}

    // Se comparan por CLAVE
    friend bool operator==(const TableEntry<V>& a, const TableEntry<V>& b) {
        return a.key == b.key;
    }
    friend bool operator!=(const TableEntry<V>& a, const TableEntry<V>& b) {
        return !(a == b);
    }
    friend bool operator<(const TableEntry<V>& a, const TableEntry<V>& b) {
        return a.key < b.key;
    }
    friend bool operator>(const TableEntry<V>& a, const TableEntry<V>& b) {
        return a.key > b.key;
    }

    // Formato de la salida esperada: ('a' => 1)
    friend std::ostream& operator<<(std::ostream& out, const TableEntry<V>& te) {
        out << "('" << te.key << "' => " << te.value << ")";
        return out;
    }
};

#endif
