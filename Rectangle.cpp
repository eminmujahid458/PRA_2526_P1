#include "Rectangle.h"
#include <cmath>

bool Rectangle::check(Point2D* v) {
    double a = Point2D::distance(v[0], v[1]);
    double b = Point2D::distance(v[2], v[3]);
    double c = Point2D::distance(v[1], v[2]);
    double d = Point2D::distance(v[3], v[0]);
    return (a == b) && (c == d);
}

Rectangle::Rectangle() : Shape() {
    vs = new Point2D[N_VERTICES];
    vs[0] = Point2D(-1,  0.5);
    vs[1] = Point2D( 1,  0.5);
    vs[2] = Point2D( 1, -0.5);
    vs[3] = Point2D(-1, -0.5);
}

Rectangle::Rectangle(std::string color, Point2D* vertices) : Shape(color) {
    if (!check(vertices)) {
        throw std::invalid_argument(" Provided vertices do not build a valid rectangle!");
    }
    vs = new Point2D[N_VERTICES];
    for (int i = 0; i < N_VERTICES; i++) {
        vs[i] = vertices[i];
    }
}

Rectangle::Rectangle(const Rectangle &r) : Shape(r.color) {
    vs = new Point2D[N_VERTICES];
    for (int i = 0; i < N_VERTICES; i++) {
        vs[i] = r.vs[i];
    }
}

Rectangle::~Rectangle() {
    delete[] vs;
}

Point2D Rectangle::get_vertex(int ind) const {
    if (ind < 0 || ind >= N_VERTICES) {
        throw std::out_of_range("Índice fuera de rango");
    }
    return vs[ind];
}

Point2D Rectangle::operator[](int ind) const {
    return get_vertex(ind);
}

void Rectangle::set_vertices(Point2D* vertices) {
    if (!check(vertices)) {
        throw std::invalid_argument(" Provided vertices do not build a valid rectangle!");
    }
    for (int i = 0; i < N_VERTICES; i++) {
        vs[i] = vertices[i];
    }
}

Rectangle& Rectangle::operator=(const Rectangle &r) {
    if (this != &r) {
        delete[] vs;
        color = r.color;
        vs = new Point2D[N_VERTICES];
        for (int i = 0; i < N_VERTICES; i++) {
            vs[i] = r.vs[i];
        }
    }
    return *this;
}

double Rectangle::area() const {
    double base = Point2D::distance(vs[0], vs[1]);
    double altura = Point2D::distance(vs[1], vs[2]);
    return base * altura;
}

double Rectangle::perimeter() const {
    double base = Point2D::distance(vs[0], vs[1]);
    double altura = Point2D::distance(vs[1], vs[2]);
    return 2 * (base + altura);
}

void Rectangle::translate(double incX, double incY) {
    for (int i = 0; i < N_VERTICES; i++) {
        vs[i].x += incX;
        vs[i].y += incY;
    }
}

void Rectangle::print() const {
    std::cout << "[Rectangle: color = " << color;
    for (int i = 0; i < N_VERTICES; i++) {
        std::cout << "; v" << i << " = " << vs[i];
    }
    std::cout << "]";
}

std::ostream& operator<<(std::ostream &out, const Rectangle &r) {
    r.print();
    return out;
}

