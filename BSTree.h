#ifndef BSTREE_H
#define BSTREE_H

#include <ostream>
#include <stdexcept>
#include "BSNode.h"

template <typename T>
class BSTree {
    private:
        int nelem;           // número de elementos
        BSNode<T>* root;     // nodo raíz

        // ---------- BÚSQUEDA ----------
        BSNode<T>* search(BSNode<T>* n, T e) const {
            if (n == nullptr)
                throw std::runtime_error("Element not found!");
            else if (n->elem < e)
                return search(n->right, e);
            else if (n->elem > e)
                return search(n->left, e);
            else
                return n;
        }

        // ---------- INSERCIÓN ----------
        BSNode<T>* insert(BSNode<T>* n, T e) {
            if (n == nullptr) {
                nelem++;                       // nodo nuevo: sube el contador
                return new BSNode<T>(e);
            }
            else if (n->elem == e)
                throw std::runtime_error("Duplicated element!");
            else if (n->elem < e)
                n->right = insert(n->right, e);
            else
                n->left = insert(n->left, e);
            return n;
        }

        // ---------- RECORRIDO INORDEN ----------
        void print_inorder(std::ostream& out, BSNode<T>* n) const {
            if (n != nullptr) {
                print_inorder(out, n->left);
                out << n->elem << " ";
                print_inorder(out, n->right);
            }
        }

        // ---------- ELIMINACIÓN ----------
        BSNode<T>* remove(BSNode<T>* n, T e) {
            if (n == nullptr)
                throw std::runtime_error("Element not found!");
            else if (n->elem < e)
                n->right = remove(n->right, e);
            else if (n->elem > e)
                n->left = remove(n->left, e);
            else {
                if (n->left != nullptr && n->right != nullptr) {
                    // 2 descendientes: sustituir por el máximo del subárbol izquierdo
                    n->elem = max(n->left);
                    n->left = remove_max(n->left);
                    nelem--;
                } else {
                    // 0 o 1 descendiente
                    BSNode<T>* aux = n;
                    n = (n->left != nullptr) ? n->left : n->right;
                    delete aux;                // liberamos el nodo borrado
                    nelem--;
                }
            }
            return n;
        }

        T max(BSNode<T>* n) const {
            if (n == nullptr)
                throw std::runtime_error("Element not found!");
            else if (n->right != nullptr)
                return max(n->right);
            else
                return n->elem;
        }

        BSNode<T>* remove_max(BSNode<T>* n) {
            if (n->right == nullptr) {
                BSNode<T>* izq = n->left;
                delete n;                      // el máximo se libera aquí
                return izq;
            } else {
                n->right = remove_max(n->right);
                return n;
            }
        }

        // ---------- DESTRUCCIÓN ----------
        void delete_cascade(BSNode<T>* n) {
            if (n != nullptr) {
                delete_cascade(n->left);
                delete_cascade(n->right);
                delete n;
            }
        }

    public:
        BSTree() : nelem(0), root(nullptr) {}

        ~BSTree() { delete_cascade(root); }

        int size() const { return nelem; }

        T search(T e) const { return search(root, e)->elem; }

        T operator[](T e) const { return search(e); }

        void insert(T e) { root = insert(root, e); }

        void remove(T e) { root = remove(root, e); }

        friend std::ostream& operator<<(std::ostream& out, const BSTree<T>& bst) {
            bst.print_inorder(out, bst.root);
            return out;
        }
};

#endif
