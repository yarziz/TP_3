#ifndef _TIME_SCHEME_H

#include "OdeSystem.h"

class TimeScheme
{
  public:
    // Constructeur par défaut
    TimeScheme();
    // Destructeur par défaut - Si la classe ne contient pas de destructeur par défaut
    // alors le compilateur en génère un implicitement.
    ~TimeScheme();
    // Initialisation de vos différentes variables
    void Initialize(double t0, double dt, Eigen::VectorXd & sol0, std::string name_file, OdeSystem* sys);
    // Enregistre la solution un fichier
    void SaveSolution();
    // Une étape du schéma en temps
    virtual void Advance(int n) = 0;
    // Permet de récupérer _sol
    const Eigen::VectorXd & GetIterateSolution() const;

   protected:
    // Pas de temps
    double _dt;
    // Temps en cours
    double _t;
    // Vecteur initial et vecteur solution
    Eigen::VectorXd _sol0, _sol;
    OdeSystem* _sys;
};

class EulerExp : public TimeScheme
{
 public:
  void Advance(int n);
};

class Runge3 : public TimeScheme
{
 public:
  void Advance(int n);
};

class Runge4 : public TimeScheme
{
 public:
  void Advance(int n);
};


class Adam : public TimeScheme
{ 
 public:
  Eigen::VectorXd _a;
  Eigen::VectorXd _b;
  //Adam(Eigen::VectorXd a, Eigen::VectorXd b);
  void Advance(int n);
};





#define _TIME_SCHEME_H
#endif
