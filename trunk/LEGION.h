#ifndef __LEGION_H__
#define __LEGION_H__


#include <iostream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>
#include <sstream>
#include <iostream>



class Z_Prime
{
 private:
  static const double phi = 3.0;
 public:
  double operator ()(double x, double input)
  {
    return (phi * (input - x));
  }
};



class ExcitatoryUnit
{
 public:
  double operator()(double x, double y, double input)
  {
    return 3.0 * x - (x * x * x) + 2 - y + input;
  }
};

class InhibitoryUnit
{
 private:
  static const double beta = .1;
  static const double eps = .02;
  static const double gam = 6.0;
 public:
  double operator()(double x, double y)
  {
    return eps * (gam * (1 + tanh(x / beta)) - y);
  }
};


struct Node
{
    double* weights;
    double x, y, I;

    Node()
    {
        x = 0;
        y = 0;
        weights = new double[5];
        I = 0;
    }
};


template <class Ex=ExcitatoryUnit, class In=InhibitoryUnit, class Zp=Z_Prime>
class LEGION
{

public:
double z;
static const int N = 20;
Node ** legion_nodes;
void Init_Weights(double, double);
LEGION();
void Iteration(double);
double Max_X_Grid(Node ** a);
double Min_X_Grid(Node ** a);
double Rand_Range(double a, double b);
void Reset(double,double,double,double);

private:
static const double K = 50.0;
static const double theta_x = .5;
static const double theta_zx = .1;
static const double theta_xz = .1;
static const double rho = .02;

Ex ff;
In gg;
Zp zz;

    double S_Inf(double x, double theta);
    double Gauss_Noise();
    double Sigma_Inf();
    void Runge_Kutta(double x1, double y1, double &x2, double &y2, double input, double h);


};


#include "LEGION.impl"

#endif
