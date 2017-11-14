#include "main.hpp"

solution guloso(){
  vector<bool> v;
  return solution(n, m, v);
}

bool fAspiration(solution s, int mov, solution BestS){
  if (BestS > s) return true;
  return false;
}

solution tabu(){
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
      s1.setBit(n, i, !s1.getBit(i));
    //  s1.print(n, m);
      if (!LT.isTabu(i) || fAspiration(s1, i, BestS)){
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
      //BestS.print(n, m);
    }

  }

  return BestS;
}

void read(){ // passando como parâmetro, precisa arrumar
  scanf("%d %d", &n, &m);
  vi partition;
  int qt, aux;
  MAXPriceValue = 0;
  for (int i = 0; i < m; i++){
    scanf("%d", &aux);
    partition.pb(aux); // o primeiro elemento da partição é representa o custo da partição.
    MAXPriceValue = max(MAXPriceValue, aux); // MAXPriceValue recebe o máximo valor possível que uma partição pode custar.

    scanf("%d", &qt);
    for(int i = 0; i < qt; i++){ // os próximos qt elementos são os elementos que estão na partição.
      scanf("%d", &aux);
      partition.pb(aux);
    }

    Dados.pb(partition); // a matriz dados é um vetor, onde cada elemento é uma novo vetor que armazena as informações sobre as partições.
    partition.clear();
  }
  MAXPriceValue*=m;
}

void printDadosSetPartitioning(){
  cout << n << " " << m <<endl;
  for (int i = 0; i < sz(Dados); i++){
    for (int j = 0; j < sz(Dados[i]); j++){
      cout << Dados[i][j] << " ";
    }
    cout << endl;
  }
}

vector<bool> makeVecBool(string s){
  vector<bool> v;
  for (int i = 0; i < sz(s); i++){
    v.pb(s.at(i) == '1');
  }
  return v;
}

int main(){
  read();
  cout << "max->" << MAXPriceValue << endl;
  tabu().print(n, m);
  return 0;
}
