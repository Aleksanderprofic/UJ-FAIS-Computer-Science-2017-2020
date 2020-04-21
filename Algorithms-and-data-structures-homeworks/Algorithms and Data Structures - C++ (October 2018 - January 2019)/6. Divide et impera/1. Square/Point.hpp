#pragma once
#include <iostream>
#include <random>
#include <cmath>

std::random_device rd;
std::default_random_engine generator{rd()};
std::uniform_int_distribution<double> distribution(1, 100000);

class Point {
     private:
     double x, y;

     public:
     Point(double x_, double y_): x(x_), y(y_) {};
     Point() {};

     double getX() {
          return this->x;
     }
     
     double getY() {
          return this->y;
     }

     static Point genPoint() {
          double x = distribution(generator)/100000.0;
          double y = distribution(generator)/100000.0;
          Point p(x,y);
          return p;
     }

     static double length(Point p1, Point p2) {
          return sqrt(pow(p1.getX() - p2.getX(), 2) + pow(p1.getY() - p2.getY(), 2));
     }

     void operator*() {
          printf("(%.5f, %.5f)\n", this->x, this->y);
     }

     bool operator!=(Point point) {
          return (this->x != point.x && this->y != point.y);
     }

     bool operator==(Point point) {
          return (this->x == point.x && this->y == point.y);
     }
};