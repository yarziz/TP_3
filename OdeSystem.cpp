#ifndef _ODE_SYSTEM_CPP

#include "OdeSystem.h"
#include <iostream>
#include <cmath>

using namespace Eigen;
using namespace std;

// Constructeur par défaut
OdeSystem::OdeSystem()
{}

//Constructeur de lotka
LotkaVolterraOdeSystem::LotkaVolterraOdeSystem(double a, double b, double c, double d){
  _a=a;
  _b=b;
  _c=c;
  _d=d;
}

PendulumOdeSystem::PendulumOdeSystem(double m, double l, double k){
  _m=m;
  _l=l;
  _k=k;
}

PendulumOdeSystem::PendulumOdeSystem(double m, double l){
  _m=m;
  _l=l;
  _k=0.;
}

Chute::Chute(double m, double k){
  _m=m;
  _k=k;
}

Chutequa::Chutequa(double m, double k){
  _m=m;
  _k=k;
}



// Destructeur par défaut
OdeSystem::~OdeSystem()
{}

// Initialisation du nom du fichier
void OdeSystem::InitializeFileName(const std::string file_name)
{
  _file_out.open(file_name);
}

// Renvoie le vecteur _f
const VectorXd & OdeSystem::GetF() const
{
  return _f;
}


// Construit le vecteur f(t, sol)
//void OdeSystem::BuildF(const double t, const VectorXd & sol)
//{
//  _f = sol;
//}

// Enregistre la solution
// Pour le moment : sol_1, sol_2 ...
void OdeSystem::SaveSolution(const double t, const VectorXd & sol)
{
  _file_out << t;
  for (int i = 0 ; i < sol.rows() ; ++i)
    {
      // _file_out << " " << sol(i);
      _file_out << " " << abs(sol(i));
    }
  _file_out << std::endl;
}



void FirstExampleOdeSystem::BuildF(const double t, const VectorXd & sol)
{
  _f = sol; // f(t,X) = X pour résoudre X’ = X
}

void SecondExampleOdeSystem::BuildF(const double t, const VectorXd & sol)
{
  _f.resize(2);
  _f[0] =-sol[1]; 
  _f[1] =sol[0];
}

void ThirdExampleOdeSystem::BuildF(const double t, const VectorXd & sol)
{
  _f;
  _f =t*sol*sol; 
}

void LotkaVolterraOdeSystem::BuildF(const double t, const VectorXd & sol)
{
  _f.resize(2);
  _f[0] =sol[0]*(_a-_b*sol[1]);
  _f[1] =sol[1]*(_c*sol[0]-_d);
}

void PendulumOdeSystem::BuildF(const double t, const VectorXd & sol)
{
  double g=9.81;
  _f.resize(2);
  _f[0] =-(g/_l)*(sin(sol[1]))-(_k/(_m*_l*_l))*sol[0];
  _f[1] =sol[0];
}

void Chute::BuildF(const double t, const VectorXd & sol)
{
  double g=9.81;
  _f.resize(2);
  _f[0]=-g-((_k/_m)*sol[0]);
  _f[1]=sol[0];
}

void Chutequa::BuildF(const double t, const VectorXd & sol)
{
  double g=9.81;
  _f.resize(2);
  _f[0]=g-(_k/_m)*pow(sol[0],2.);
  _f[1]=sol[0];
}






#define _ODE_SYSTEM_CPP
#endif
