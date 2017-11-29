#include "main.hpp"

vector< vector<int> > Dados; // Matriz que armazena todos os dados do problema, exceto o número de partições m e o número de elementos n;
int MAXPriceValue; // Valor máximo de uma partição;
int n, m; // n representa a quantidade de elementos e m representa a quantidade de partições
int T = 10; // tamanho da lista tabu;
vector < set<int> > Grafo;

solucao guloso(){
  solucao s = solucao(m, MAXPriceValue);

  while (sz(s.Next)){
    set<int>:: iterator it, best;
    bool ff = true;

    for (it = s.Next.begin(); it != s.Next.end(); it++){
      if (ff){
        best = it;
        ff = false;
      }else{
        if (Dados[*it][0] < Dados[*best][0]){
          best = it;
        }
      }
    }
    s.AdicionaElemento(m, *best, sz(Dados[*best]) - 1, Dados[*best][0], Grafo[*best], MAXPriceValue);

  }
  return s;
}

bool FuncaoDeAspiracao(solucao s, int mov, solucao BestS){
  if (BestS > s) return true;
  return false;
}

bool conflito(int u, int v){
  //cout << u << " " << v << endl;

  for (int i = 1; i < sz(Dados[u]); i++){
    for (int j = 1; j < sz(Dados[v]); j++){
      if (Dados[u][i] == Dados[v][j]) return true;
    }
  }
  return false;
}

void carregaDados(){
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

  for (int i = 0; i < m; i++){
    set<int> s;
    for (int j = 0; j < m; j++){
      if (i != j && !conflito(i, j)){
        s.insert(j);
      }
    }
    Grafo.pb(s);
  }
  MAXPriceValue*=m;
}

void printDadosSetPartitioning(){
  cout << n << " " << m << endl;
  for (int i = 0; i < sz(Dados); i++){
    for (int j = 0; j < sz(Dados[i]); j++){
      cout << Dados[i][j] << " ";
    }
    cout << endl;
  }
}

int main(){
  carregaDados();
  for (int i = 0; i < m; i++){
    cout << i <<"->";
    for (auto u: Grafo[i]){
      cout << u << " ";
    }
    cout << endl;
  }
  /*solucao s = guloso();
  s.RemoveElemento(m, 6, sz(Dados[6]) - 1, Dados[6][0], Grafo[6], MAXPriceValue);
  s.print(m);*/
  //cout << "max->" << MAXPriceValue << endl;
  //tabuT_variavel(n, m, T, MAXPriceValue, Dados).print(n, m);
  return 0;
}
