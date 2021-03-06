#ifndef _TIME_SCHEME_CPP

#include "TimeScheme.h"
#include <iostream>

using namespace Eigen;
using namespace std;

/************
 * TimeScheme *
 *************/

// Constructeur par défaut (ne pas oublier de mettre votre pointeur à 0 !!)
TimeScheme::TimeScheme() : _sys(0)
{}

// Destructeur
TimeScheme::~TimeScheme()
{}

// Initialisation de vos différentes variables
void TimeScheme::Initialize(double t0, double dt, VectorXd & sol0, string results, OdeSystem* sys)
{
  _dt = dt;
  _t = t0 ;
  _sol0 = sol0;
  _sol = sol0;
  _sys = sys;
  if (results.size() > 0)
  {
    _sys->InitializeFileName(results);
  }
}

// Enregistre la solution : fait appel à OdeSystem car la solution
// que l'on souhaite sauvegarder peut être différente de _sol SaveSolution
// le système
void TimeScheme::SaveSolution()
{
  _sys->SaveSolution(_t, _sol);
}

// Renvoie _sol (pratique pour calculer l'ordre de votre méthode)
const VectorXd & TimeScheme::GetIterateSolution() const
{
  return _sol;
}

/************
 * EulerExp *
 *************/

// Schéma en temps par défaut : ici Euler Explicite
// Avancer d'un pas de temps
void EulerExp::Advance(int n)
{
  _sys->BuildF(_t, _sol);
  _sol += _dt*_sys->GetF();
  _t += _dt;
}

void Runge3::Advance(int n)
{
  _sys->BuildF(_t, _sol);
  VectorXd a=_sys->GetF();
  _sys->BuildF(_t+_dt/2., _sol+(_dt/2.)*a);
  VectorXd b=_sys->GetF();
  _sys->BuildF(_t+_dt, _sol-_dt*a+2*_dt*b);
  VectorXd c=_sys->GetF();
  _sol += (_dt/6.)*(a+4*b+c);
  _t += _dt;
}

void Runge4::Advance(int n)
{
  _sys->BuildF(_t, _sol);
  VectorXd a=_sys->GetF();
  _sys->BuildF(_t+_dt/2., _sol+(_dt/2.)*a);
  VectorXd b=_sys->GetF();
  _sys->BuildF(_t+_dt/2., _sol+(_dt/2.)*b);
  VectorXd c=_sys->GetF();
  _sys->BuildF(_t+_dt, _sol+_dt*c);
  VectorXd d=_sys->GetF();
  _sol += (_dt/6.)*(a+2*b+2*c+d);
  _t += _dt;
}


void Adam::Advance(int n){
  if(n==0){
     _sys->BuildF(_t, _sol);
     VectorXd a=_sys->GetF();
     _sys->BuildF(_t+_dt/2., _sol+(_dt/2.)*a);
     VectorXd b=_sys->GetF();
     _sys->BuildF(_t+_dt, _sol-_dt*a+2*_dt*b);
     VectorXd c=_sys->GetF();
     _sol += (_dt/6.)*(a+4*b+c);
     _a=a;
     _t += _dt;
    }
  
   if(n==1){
     _sys->BuildF(_t, _sol);
     VectorXd a=_sys->GetF();
     _sys->BuildF(_t+_dt/2., _sol+(_dt/2.)*a);
     VectorXd b=_sys->GetF();
     _sys->BuildF(_t+_dt, _sol-_dt*a+2*_dt*b);
     VectorXd c=_sys->GetF();
     _sol += (_dt/6.)*(a+4*b+c);
     _b=a;
     _t += _dt;
   }

   if(n>1){
     _sys->BuildF(_t, _sol);
     _sol += (_dt/12.)*(23*_sys->GetF()-16*_b+5*_a);
     _a=_b;
     _b=_sys->GetF();
     _t += _dt; 
     }
}


#define _TIME_SCHEME_CPP
#endif
