#include "main.hpp"

#define MaxRepetitionElement 110
#define MaxListSize 1024
#define MinT 2

solucao BuscaTabu(int n, int m, int &T, ll MAXPriceValue, vector< vector<int> > Dados){
  solution s = guloso();
  solution BestS = s;

  int NoNewSolutionIteration = 0;
  map<int, int> LoopControlol; // variável para controle de vezes que vamos considerar uma solução;
  int iter, Miter = 0;
  tabuList LT; // lista tabu
  T = m>>2; // setando o tamanho da lista tabu para 2.


  for (iter = 0; iter - Miter < BTMAX; iter++){
    solution sMin = s;
    sMin.FO_Value = INF;

    int mov = -1;
    for (int i = 0; i < m; i++){ // percorre todos os vizinhos da solução s
      solution s1 = s;
      s1.setBit(n, i, !s1.getBit(i), MAXPriceValue, Dados);
      if (!LT.isTabu(i) || fAspiration(s1, i, BestS)){
        if (sMin > s1){
          sMin = s1;
          mov = i;
        }
      }
    }


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

    if (LoopControlol.find(sMin.FO_Value) != LoopControlol.end()){
      LoopControlol[sMin.FO_Value]++;
      NoNewSolutionIteration++;
      if (NoNewSolutionIteration > MaxRepetitionElement){ // o programa está em um loop; -> Aumenta o tamanho da lista tabu para dar mais diversificação;
        T = T << 1;
        if (T >= m){
          T = m >> 1;
        }
        cout << "T->" << T<< endl;
        //LoopControlol.clear();
        NoNewSolutionIteration = 0;
        s = BestS;
        LT.clear();
      }

      if (LoopControlol[sMin.FO_Value] > MaxRepetitionElement){// o programa está em um loop; -> Aumenta o tamanho da lista tabu para dar mais diversificação;
        //LoopControlol.clear();
        T = T << 1;
        if (T >= m){
          T = m >> 1;
        }
        NoNewSolutionIteration = 0;
        cout << "T->" << T << endl;
        s = BestS;
        LT.clear();
      }
    }else{
      LoopControlol[sMin.FO_Value] = 1;
      if (sz(LoopControlol) > MaxListSize){
        //LoopControlol.clear();
        T = T >> 1;
        if (T < MinT){
          T = 2;
        }
        cout << "T->" << T<< endl;
        s = BestS;
        LT.clear();
      }
    }
  }
  return BestS;
}
