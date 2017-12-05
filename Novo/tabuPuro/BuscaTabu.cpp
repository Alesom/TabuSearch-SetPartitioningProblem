#include "main.hpp"

#define MaxRepetitionElement 500
#define MaxListSize 32384
#define MinT 2

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

void UpdatefAspiration(solucao s, solucao BestS, int m, map<int, int> &LoopControlol, int &T, int &NoNewSolutionIteration, tabuList &lt){
  void UpdatefAspiration(solucao s, solucao BestS, int m, map<int, int> &LoopControlol, int &T, int &NoNewSolutionIteration, tabuList &lt){
    if (LoopControlol.find(s.FO) != LoopControlol.end()){
      LoopControlol[s.FO]++;
      NoNewSolutionIteration++;
      if (NoNewSolutionIteration > MaxRepetitionElement){ // o programa está em um loop; -> Aumenta o tamanho da lista tabu para dar mais diversificação;
        chanceListaTabuSize(m, 1, T, lt); // aumenta lista tabu
        LoopControlol.clear();
        NoNewSolutionIteration = 1;
      }

      if (LoopControlol[s.FO] > MaxRepetitionElement){// o programa está em um loop; -> Aumenta o tamanho da lista tabu para dar mais diversificação;
        chanceListaTabuSize(m, 1, T, lt); // aumenta o tamanho da lista tabu
        LoopControlol.clear();
        NoNewSolutionIteration = 1;
      }
    }else{
      LoopControlol[s.FO] = 1;
      NoNewSolutionIteration = 1;
      if (sz(LoopControlol) > MaxListSize){
        chanceListaTabuSize(m, 0, T, lt);
        LoopControlol.clear();
      }
    }
  }
}

solucao BuscaTabu(int n, int m, int &T, ll MAXPriceValue, vector< vector<int> > Dados, vector < set<int> > Grafo){
  solucao s = guloso();
  solucao BestS = s;
  int IteracoesSemDiversificacao = 0;
  map<int, int> LoopControlol; // variável para controle de vezes que vamos considerar uma solução;
  unsigned iter, Miter = 0;
  tabuList LT; // lista tabu
  T = 5; // setando o tamanho da lista tabu para 2.
  //cout << "T, Iteração, FO\n";
  for (iter = 0; iter - Miter < BTMAX && iter < 0xf3f3f3f3; iter++){
    cout << T << "," << iter << "," << s.FO << endl;
    solucao sMin = s;
    sMin.FO = INF;

    int mov = -1;
    int multiplicador = 1;
    int aux = 0;

    while (mov == -1){
      int ultimoElemento;
      ll menor = INF;

      for (auto e: s.Next){ //pecorre todos possíveis candidatos a entrarem na solução
        solucao s1 = s;
        s1.AdicionaElemento(n, m, e, sz(Dados[e]) - 1, Dados[e][0], Grafo[e], MAXPriceValue);
        if (!LT.isTabu(e) || FuncaoDeAspiracao(n, s1, BestS, IteracoesSemDiversificacao, MAXPriceValue, multiplicador)){
          if (sMin > s1){
            sMin = s1;
            mov = e;
          }
        }else{
          int aux = LT.getPosition(e);
          if (menor > aux){
            menor = aux;
            ultimoElemento = e;
          }
        }
      }

      for (auto e: s.P){ //percorre todos elementos que estão na solução
        solucao s1 = s;
        s1.RemoveElemento(n, m, e, sz(Dados[e]) - 1, Dados[e][0], Grafo[e], MAXPriceValue);
        if (!LT.isTabu(e) || FuncaoDeAspiracao(n, s1, BestS, IteracoesSemDiversificacao, MAXPriceValue, multiplicador)){
          if (sMin > s1){
            sMin = s1;
            mov = e;
          }
        }else{
          int aux = LT.getPosition(e);
          if (menor > aux){
            menor = aux;
            ultimoElemento = e;
          }
        }
      }
      if (multiplicador == 1 && mov == -1){
        sMin = s;
        mov = ultimoElemento;
        if (sMin.Next.find(ultimoElemento) != sMin.Next.end()){
          sMin.AdicionaElemento(n, m, ultimoElemento, sz(Dados[ultimoElemento]) - 1, Dados[ultimoElemento][0], Grafo[ultimoElemento], MAXPriceValue);
        }else{
          sMin.RemoveElemento(n, m, ultimoElemento, sz(Dados[ultimoElemento]) - 1, Dados[ultimoElemento][0], Grafo[ultimoElemento], MAXPriceValue);
        }
      }
      multiplicador = 10;
      aux++;
    }

    UpdatefAspiration(sMin, BestS, m, LoopControlol, T, IteracoesSemDiversificacao, LT);

    LT.add(mov, T, iter);
    s = sMin;

    if (sMin < BestS){
      BestS = sMin;
      Miter = iter;
    /*  cout << "Ganhou\n";
      sMin.print(n, m);
      cout << "end\n";*/
      LoopControlol.clear();
      IteracoesSemDiversificacao = 0;
    }
  }
  return BestS;
}
