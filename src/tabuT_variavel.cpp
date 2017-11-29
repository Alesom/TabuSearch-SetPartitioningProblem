#include "main.hpp"

#define MaxRepetitionElement 500
#define MaxListSize 8096
#define MinT 2
#define RandomConstant 48

void chanceListaTabuSize(int m, int aumentaDiminui, int &T, tabuList &lt){
  if (aumentaDiminui){
    T = T << 1;
    if (T >= m){
      T = m;
    }
  }else{
    T = T >> 1;
    if (T < MinT){
      T = 2;
    }
    lt.resize(T);
  }
}

void UpdatefAspiration(solution s, solution BestS, int m, map<int, int> &LoopControlol, int &T, int &NoNewSolutionIteration, tabuList &lt){
  if (LoopControlol.find(s.FO_Value) != LoopControlol.end()){
    LoopControlol[s.FO_Value]++;
    NoNewSolutionIteration++;
    if (NoNewSolutionIteration > MaxRepetitionElement){ // o programa está em um loop; -> Aumenta o tamanho da lista tabu para dar mais diversificação;
      cout << "NoNewSolutionIteration" << endl;
      chanceListaTabuSize(m, 1, T, lt); // aumenta lista tabu
      cout << "T->" << T<< endl;
    }

    if (LoopControlol[s.FO_Value] > MaxRepetitionElement){// o programa está em um loop; -> Aumenta o tamanho da lista tabu para dar mais diversificação;
      chanceListaTabuSize(m, 1, T, lt); // aumenta o tamanho da lista tabu
      cout << "T->" << T <<"    " << s.FO_Value << " " << LoopControlol[s.FO_Value]  << endl;
    }
  }else{
    LoopControlol[s.FO_Value] = 1;
    NoNewSolutionIteration = 1;
    if (sz(LoopControlol) > MaxListSize){
      chanceListaTabuSize(m, 0, T, lt);
      cout << "T->" << T << " " << LoopControlol.size()<< endl;
      LoopControlol.clear();
    }
  }
}

bool fAspiration(int m, solution s, solution BestS, int &NoNewSolutionIteration, ll MAXPriceValue){
  if (BestS > s) return true;

  random_device rd;  //Will be used to obtain a seed for the random number engine
  mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  uniform_int_distribution<> dis(1, 100);
  int r1 = dis(gen);
  int r2 = dis(gen);
  ll pen = (s.FO_Value - s.FO_P) / MAXPriceValue;

  if ((200.0*pen/m) < r1 && (NoNewSolutionIteration*100 / (RandomConstant*MaxRepetitionElement)) > r2){
    cout << NoNewSolutionIteration << "  Sorteou "<< pen << " " << r1 << " " << r2 << endl;
    s.print(17, m);
    NoNewSolutionIteration = 1;
  }

  return (100.0*pen/m) < r1 && (NoNewSolutionIteration*100 / (RandomConstant*MaxRepetitionElement)) > r2;
}

solution tabuT_variavel(int n, int m, int &T, ll MAXPriceValue, vector< vector<int> > Dados){
  solution s = guloso();
  solution BestS = s;
  s.print(n, m);

  int NoNewSolutionIteration = 1;
  map<int, int> LoopControlol; // variável para controle de vezes que vamos considerar uma solução;
  int iter, Miter = 0;
  tabuList LT; // lista tabu
  T = m >> 1; // setando o tamanho da lista tabu para 2.

  for (iter = 0; iter - Miter < BTMAXITERSEMMELHORA && iter < BTMAX; iter++){
  //  cout << iter << " " <<  Miter << endl;
    solution sMin = s;
    sMin.FO_Value = INF;

    int mov = -1;
    for (int i = 0; i < m; i++){ // percorre todos os vizinhos da solução s
      solution s1 = s;
      s1.setBit(n, i, !s1.getBit(i), MAXPriceValue, Dados);
      if (!LT.isTabu(i) || fAspiration(m, s1, BestS, NoNewSolutionIteration, MAXPriceValue)){
        if (sMin > s1){
          sMin = s1;
          mov = i;
        }
      }
    }

    if (mov == -1){
      random_device rd;  //Will be used to obtain a seed for the random number engine
      mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
      uniform_int_distribution<> dis(0, m - 1);
      int mov = dis(gen);
      sMin = s;
      sMin.setBit(n, mov, !sMin.getBit(mov), MAXPriceValue, Dados);
    }
  //  sMin.print(n, m);
    UpdatefAspiration(sMin, BestS, m, LoopControlol, T, NoNewSolutionIteration, LT);
/*    for (map<int, int>::iterator it = LoopControlol.begin(); it!=LoopControlol.end(); it++){
      cout << "("<< (*it).f << ","<< (*it).s << ") ";
    }
    cout << endl;
*/
    LT.add(mov, T);
  //  LT.print();
    s = sMin;


    if (sMin < BestS){
      BestS = sMin;
      Miter = iter;
  //    cout << T << endl;
      cout << "Ganhou\n";
      sMin.print(n, m);
      cout << "end\n";
    }
  }
  return BestS;
}
