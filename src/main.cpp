#include "main.hpp"

vector< vector<int> > Dados; // Matriz que armazena todos os dados do problema, exceto o número de partições m e o número de elementos n;
int MAXPriceValue; // Valor máximo de uma partição;
int n, m; // n representa a quantidade de elementos e m representa a quantidade de partições
int T = 100; // tamanho da lista tabu;

int sortByIndex(const void *a, const void *b){
  int i = *(int *)a;
  int j = *(int *)b;
  return Dados[i][0] - Dados[j][0];
}

solution guloso(){
  int I[m];
  vector<bool> v;
  solution s = solution(n, m, v, MAXPriceValue, Dados);

  for (int i = 0; i < m; i++){
    I[i] = i;
  }
  qsort(I, m, sizeof(int), sortByIndex);

  /*for (int i = 0; i < m; i++){
    for (int j = 0; j < sz(Dados[i]); j++){
      cout << Dados[I[i]][j] << " ";
    }
    cout << endl;
  }
  s.print(n, m);
  */

  for (int i = 0; i < m; i++){
    int ff = true;
    for (int j = 1; j < sz(Dados[I[i]]) && ff; j++){
      if (s.e[Dados[I[i]][j] - 1]) ff = false;
    }

    if (ff){
      s.setBit(n, I[i], 1, MAXPriceValue, Dados);
    //  s.print(n, m);
    }
  }

  return s;
}

bool fAspiration(solution s, int mov, solution BestS){
/*  if (BestS > s) return true;
  default_random_engine generator;
  uniform_int_distribution<int> distribution(1, 100);
  int dice_roll = distribution(generator);  // generates number in the range 1..6*/
  if (BestS > s) return true;
  return false;
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
  tabuT_fixo(n, m, T, MAXPriceValue, Dados).print(n, m);
  return 0;
}
