#include<iostream>

/*
Namespaces in cpp provide a way to organize code into logical groups and prevent naming conflicts. They allow you to define named scopes, called namespcaes, where identifiers (such as variables, functions, and classes) can be declared.

Namespaces help in avoiding naming collisions by ensuring that the names of identifiers within a namespaces do not confilict with names in other namespcaces or the global scopes.

access members of namespaces using "::"
*/



namespace MyNamespaces {
    int num = 0;
    void display() {
        std::cout << "inside MyNamespaces" << std::endl;
    }
}