#ifndef _ODE_SYSTEM_H

#include "Dense"
#include <fstream>

class OdeSystem
{
 private:
  // Écriture du fichier
  std::ofstream _file_out;
 public:
  // Constructeur par défaut
  OdeSystem();
  // Destructeur par défaut
  virtual ~OdeSystem();
  // Initialiser le nom du fichier solution
  void InitializeFileName(const std::string file_name);
  // Sauvegarde la solution
  void SaveSolution(const double t, const Eigen::VectorXd & sol);
  // Pour récupérer _f
  const Eigen::VectorXd &  GetF()  const;
  // Pour construire _f en fonction de votre système
  virtual void BuildF(const double t, const Eigen::VectorXd & sol)=0;

 protected:
  // Votre fonction f
  Eigen::VectorXd _f;

};


class FirstExampleOdeSystem : public OdeSystem
{
 public:
  void BuildF(const double t, const Eigen::VectorXd & sol); //f(X,t) = X
};


class SecondExampleOdeSystem : public OdeSystem
{
 public:
  void BuildF(const double t, const Eigen::VectorXd & sol); //f(X,t) = X
};

class ThirdExampleOdeSystem : public OdeSystem
{
 public:
  void BuildF(const double t, const Eigen::VectorXd & sol); //f(X,t) = X
};

class LotkaVolterraOdeSystem : public OdeSystem
{
 private:
  double _a;
  double _b;
  double _c;
  double _d;
 public:
  LotkaVolterraOdeSystem(double a, double b, double c, double d);
  void BuildF(const double t, const Eigen::VectorXd & sol); 
};


class PendulumOdeSystem : public OdeSystem
{
 private:
  double _m;
  double _l;
  double _k;
 public:
  PendulumOdeSystem(double m, double l);
  PendulumOdeSystem(double m, double l, double k);
  void BuildF(const double t, const Eigen::VectorXd & sol); 
};


#define _ODE_SYSTEM_H
#endif
