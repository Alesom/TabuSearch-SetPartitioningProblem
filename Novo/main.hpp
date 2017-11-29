#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second
#define pb push_back
#define sz(v) ((int)v.size())
#define rad(a) a * PI / 180

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;

const int MAX = 31;
const int LIM = 2000000;
const int MAXT = 270000;
const int P = 1000000007;
const ll INF = 0x3F3F3F3F3F3F3F3FLL;
const double EPS = 1e-6;
const double PI = 3.14159265358979;
const int partSz = 32; // tamanho da partição na solução(tamanho de um inteiro)
const int BTMAX = 1 << 10;

struct solucao{
  set<int> P;
  int Q;
  set<int> Next;
  vector<int> Grau;
  ll FO;
  ll FO_semPen;

  solucao(int m, ll MAXPriceValue){
    Q = 0;
    P.clear();
    for (int i = 0; i < m; i++){
      Next.insert(i);
      Grau.pb(0);
    }
    FO_semPen = 0;
    FO = FO_semPen + (m - Q)* MAXPriceValue;
  }

  void operator =(solucao &_s) { //sobreescreve o operador =
    P = _s.P;
    Q = _s.Q;
    Next = _s.Next;
    Grau = _s.Grau;
    FO = _s.FO;
    FO_semPen = _s.FO_semPen;
  }

  bool operator <(const solucao &_s) const { //sobreescreve o operador <
    return FO < _s.FO;
  }

  bool operator >(const solucao &_s) const { //sobreescreve o operador >
    return FO > _s.FO;
  }

  bool operator ==(const solucao &_s) const { //sobreescreve o operador ==
    return FO == _s.FO;
  }

  void AdicionaElemento(int m, int e, int qtElementosCobertos, ll custo, set<int> viz, const ll MAXPriceValue){ // só adiciona elementos que podem ser adicionados
    P.insert(e);
    Q += qtElementosCobertos;
    set<int> aux;

    for (auto v: viz){
      Grau[v]++;
      if (Grau[v] == sz(P)){
        aux.insert(v);
      }
    }
    cout << endl;
    Next = aux;
    FO_semPen += custo;
    FO = FO_semPen + (m - Q)*MAXPriceValue;
  }

  void RemoveElemento(int m, int e, int qtElementosCobertos, ll custo, const set<int> viz, const ll MAXPriceValue){ // só adiciona elementos que podem ser adicionados
    P.erase(e);
    Q -= qtElementosCobertos;
    for (auto v: viz){
      Grau[v]--;
    }
    set<int> aux;
    for (int i = 0; i < m; i++){
      if (Grau[i] == sz(P)){
        aux.insert(i);
      }
    }
    Next = aux;
    FO_semPen -= custo;
    FO = FO_semPen + (m - Q) * MAXPriceValue;
  }

  void print(int m){
    cout << "FO: " << FO << endl;
    cout << Q << " elementos cobertos" << endl;
    for (auto v: P){
      cout << v << " ";
    }
    cout << endl;
  }
};

struct tabuList{
  set<int> tl; // como cada movimento é apenas a troca de um bit, podemos representar usando um set;
  queue<int> Q;

  tabuList(){
  }

  void rm(){
    int u = Q.front(); Q.pop();
    tl.erase(u);
  }

  void add(int x, int T){
    if (sz(tl) == T){
      int u = Q.front(); Q.pop();
      tl.erase(u);
    }
    Q.push(x);
    tl.insert(x);
  }

  bool isTabu(int x){
    return tl.find(x) != tl.end();
  }

  void clear(){
    tl.clear();
    while (!Q.empty()) Q.pop();
  }

  void print(){
    for (set<int>::iterator it = tl.begin(); it!=tl.end(); it++){
      cout << *it <<" ";
    }
    cout << endl;
  }
};

solucao guloso();
int OrdenaPorIndice(const void *a, const void *b);
bool FuncaoDeAspiracao(solucao s, int mov, solucao BestS);
bool conflito(int u, int v);
void carregaDados();
void printDadosSetPartitioning();
int main();
