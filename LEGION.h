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

//--Default functions defined in paper --------

class Z_Prime
{
 public:
  double operator ()(double x, double input)
  {
    return (3.0 * (input - x));
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
 public:
  double operator()(double x, double y)
  {
    return .02 * (6.0 * (1 + tanh(x / .1)) - y);
  }
};

//--End Defaults----------------------------------


//A single neuron
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



template <class Ex=ExcitatoryUnit, class In=InhibitoryUnit, class Zp=Z_Prime> //set the default values
class LEGION
{

public:
 double z;
 Node ** legion_nodes;
 void Init_Weights(double, double);
 LEGION(int); 
 LEGION(int,double,double,double,double,double); 
~LEGION();
 void Iteration(double);
 double Max_X_Grid();
 double Min_X_Grid();
 double Rand_Range(double a, double b);
 void Reset(double,double,double,double);
 int N;
 
private:
 double K;
 double theta_x;
 double theta_zx;
 double theta_xz;
 double rho;


 Ex ff;
 In gg;
 Zp zz;

 double S_Inf(double x, double theta);
 void Init_Nodes();
 double Gauss_Noise();
 double Sigma_Inf();
 void Runge_Kutta(double x1, double y1, double &x2, double &y2, double input, double h);


};



//include the function implementations

#include "LEGION.impl"

#endif
