#include "main.hpp"

solution tabuT_fixo(int n, int m, int &T, ll MAXPriceValue, vector< vector<int> > Dados){
  solution s = guloso();
  solution BestS = s;

  int iter, Miter = 0;
  tabuList LT; // lista tabu

  for (iter = 0; iter - Miter < BTMAX; iter++) {
    solution sMin = s;
    sMin.FO_Value = INF;

    int mov = -1;
    for (int i = 0; i < m; i++){ // percorre todos os vizinhos da solução s
      solution s1 = solution(s);
      s1.setBit(n, i, !s1.getBit(i), MAXPriceValue, Dados);
      int aux;
      if (!LT.isTabu(i) || fAspiration(m, s1, BestS, aux, 1)){
        if (sMin > s1){
          sMin = s1;
          mov = i;
        }
      }
    }
    LT.add(mov, T);

    s = sMin;

    if (sMin < BestS){
      BestS = sMin;
      Miter = iter;
      cout << "Ganhou\n";
      sMin.print(n, m);
      cout << "end\n";
    }

  }
  return BestS;
}
