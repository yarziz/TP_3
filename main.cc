#include "TimeScheme.h"
#include <string>
#include <iostream>
using namespace std;
using namespace Eigen;




int main()
{
  double t0(0.), tfinal(5.), dt(0.005); // temps initial, final, pas de temps
  int nb_iterations = int(ceil(tfinal/dt)); // Définition du nombre d’itérations
  dt = tfinal / nb_iterations; // Recalcul de dt
  string results; // nom du fichier résultat
  int userChoiceSys; // Choix de l’utilisateur
  int userChoiceShema;
  VectorXd sol0, exactSol; // Condition initiale et Solution exacte
  cout << "------------------------------------" << endl;
  cout << "Choississez le système : " << endl;
  cout << "1) X’ = X"<< endl;
  cout << "2) x’ = -y et y’ = x" << endl;
  cout << "3) x’ = x^2 t" << endl;
  cout << "4) x’ = x(a-by) et y' =y(cx-d)" << endl;
  cout << "5) pondule" << endl;
  cout << "6) Chute" << endl;
  cin >> userChoiceSys;
  OdeSystem* sys(0);
  switch(userChoiceSys)
    {
    case 1:
      sys = new FirstExampleOdeSystem();
      sol0.resize(4);
      sol0(0) = 2.; sol0(1) = 3.1; sol0(2) = -5.1; sol0(3) = 0.1;
      exactSol = sol0*exp(tfinal);
      results = "first_ex.txt";
      break;
    case 2:
      sys = new SecondExampleOdeSystem();
      sol0.resize(2); exactSol.resize(2); sol0(0) = 1; sol0(1) = -1;
      exactSol(0) = sol0(0)*cos(tfinal)-sol0(1)*sin(tfinal);
      exactSol(1) = sol0(1)*cos(tfinal)+sol0(0)*sin(tfinal);
      results = "second_ex.txt";
      break;
    case 3:
      sys = new ThirdExampleOdeSystem();
      sol0.resize(1); exactSol.resize(1); sol0(0) = -2;
      exactSol(0) = 2*sol0(0)/(2-tfinal*tfinal*sol0(0));
      results = "third_ex.txt";
      break;
    case 4:
      sys = new LotkaVolterraOdeSystem(2,1,2,10);
      sol0.resize(2); sol0(0) = 1;sol0(1)=1;
      results = "Lotka.txt";
      break;
    case 5:
      int userChoiceK;
      cout<<"1) k=0"<<endl;
      cout<<"2) k different de zero"<<endl;
      cin >> userChoiceK;
      if(userChoiceK==1){
	sys = new PendulumOdeSystem(0.1,1);
      }else{
	sys = new PendulumOdeSystem(0.1,1,2);
      }
      sol0.resize(2); sol0(0) = 0;sol0(1)=M_PI;
      results = "pendule.txt";
      break;
    case 6:
      double g;
      double m;
      cout<<"donnez la masse m"<<endl;
      cin >> m;
      double k;
      cout<<"donnez la raideur k "<<endl;
      cin >> k;
      double v_0;
      cout<<"donnez la donnee initial v_0"<<endl;
      cin >> v_0;
      double tho;
      sys=new Chute(m,k);
      sol0.resize(1);
      sol0(0)=v_0;
      g=9.81;
      tho=m/k;
      exactSol.resize(1);
      exactSol(0) =g*tho*(exp(-tfinal/tho)-1)+v_0*exp(-tfinal/tho);
      results = "chute";
      break;
    default:
      cout << "Ce choix n’est pas possible ! Veuillez recommencer !" << endl;
      exit(0);
    }


  cout << "------------------------------------" << endl;
  cout << "Choississez le schemas en temps  : " << endl;
  cout << "1) euler explicite"<< endl;
  cout << "2) runge kutta_3" << endl;
  cout << "3) runge kutta_4" << endl;
  cout << "4) adam " << endl;
  cin>>userChoiceShema;
  TimeScheme* time_scheme;

  switch(userChoiceShema){
  case(1):
    time_scheme = new EulerExp();
    break;
  case(2):
    time_scheme = new Runge3();
    break;
  case(3):
    time_scheme = new Runge4();
    break;
  case(4):
    time_scheme = new Adam();
    break;
    
  }
  
  time_scheme->Initialize(t0, dt, sol0, results, sys); // Initialisation
  time_scheme->SaveSolution(); // Sauvegarde condition initiale

  for (int n = 0; n < nb_iterations; n++)
    { // Boucle en temps
      time_scheme->Advance(n);
      time_scheme->SaveSolution();
    }

  if ((userChoiceSys == 1) || (userChoiceSys == 2) || (userChoiceSys == 3)||(userChoiceSys == 6))
    {
      VectorXd approxSol = time_scheme->GetIterateSolution(); // Temps final
      double error = ((approxSol-exactSol).array().abs()).sum();
      cout << "Erreur = " << error<< " pour dt = " << dt << endl;
      time_scheme->Initialize(t0, dt/2., sol0, results, sys);
      for (int n = 0; n < nb_iterations*2; n++){
	time_scheme->Advance(n);
      }
      approxSol = time_scheme->GetIterateSolution(); // Temps final
      double error2 = ((approxSol-exactSol).array().abs()).sum();
      cout << "Erreur = " << error2<< " pour dt = " << dt/2. << endl;
      cout << "Ordre de la méthode = " << log2(error/error2) << endl;
    }
  delete sys;
  return 0;
}




 

/*
  int main()
  {
  // Définition du temps initial, du temps final et du pas de temps
  double t0(0.), tfinal(10.), dt(0.01);
  // Définition du nombre d'itérations à partir du temps final et du pas de temps
  int nb_iterations = int(ceil(tfinal/dt));
  // Recalcul de dt
  dt = tfinal / nb_iterations;
  // Nom du fichier solution
  string results = "solution.txt";

	
  // Définition du vecteur initial (vecteur de Eigen)
  // Ici dans R^2
  /*
  VectorXd sol0(4);
  // Initialisation des valeurs
  sol0(0) = 2.;
  sol0(1) = 3.1;
  sol0(2) = -5.1;
  sol0(3) = 0.1;
	
	
  // Définition d'un pointeur de OdeSystem
  OdeSystem* sys = new LotkaVolterraOdeSystem(2,1,2,10);

  VectorXd sol0(2);
  sol0(0)=1;
  sol0(1)=1;
	



  // Définition d'un objet de TimeScheme
  TimeScheme time_scheme;

  /*
  cout << "------------------------------------" << endl;
  cout << "Euler Explicite" << endl;
  cout << "------------------------------------" << endl;
  cout << "Système : X' = X avec X0 = " << endl;
  cout << sol0 << endl;
  cout << "------------------------------------" << endl;
	


  // Initialisation
  time_scheme.Initialize(t0, dt, sol0, results, sys);
  // On sauvegarde la solution
  time_scheme.SaveSolution();

  // Boucle en temps
  for (int n = 0; n < nb_iterations; n++)
  {
  time_scheme.Advance();
  time_scheme.SaveSolution();
  }

	
  // On récupère la solution approchée au temps final
	
  VectorXd approxSol = time_scheme.GetIterateSolution();

  /*
  // Définition de la solution exacte au temps final
  VectorXd exactSol = sol0*exp(tfinal);
  double error = ((approxSol-exactSol).array().abs()).sum();
  cout << "Erreur = " << error << " pour dt = " << dt << endl;
  cout << "------------------------------------" << endl;


  time_scheme.Initialize(t0, dt/2., sol0, results, sys);
  for (int n = 0; n < nb_iterations*2; n++)
  {
  time_scheme.Advance();
  }

  // On récupère la solution approchée au temps final
  approxSol = time_scheme.GetIterateSolution();
  double error2 = ((approxSol-exactSol).array().abs()).sum();
  cout << "Erreur = " << error2<< " pour dt = " << dt/2. << endl;
  cout << "------------------------------------" << endl;

  cout << "Ordre de la méthode = " << log2(error/error2) << endl;
  cout << "------------------------------------" << endl;
  delete sys;

  return 0;
}
//*/



