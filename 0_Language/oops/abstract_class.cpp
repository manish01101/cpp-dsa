/*
An abstract class in C++ is a class that cannot be instantiated directly and is designed to be inherited by other classes. It must contain at least one pure virtual function, indicated by = 0 in its declaration. Abstract classes can also contain:
Concrete (implemented) methods: Functions with a defined body.
Member variables: Data members that store state.
Constructors and destructors: These can be defined.
*/
class Shape {
public:
    virtual void draw() = 0; // Pure virtual function
    void setColor(std::string color) { 
        this->color = color; 
    }
protected:
    std::string color;
};

class Circle : public Shape {
public:
    void draw() override {
        // Implementation for drawing a Circle
    }
};