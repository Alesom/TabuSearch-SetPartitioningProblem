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
const int BTMAX = 1 << 15;

struct solucao{
  set<int> P; // conjunto que armazena os elementos que estão na solução
  int Q; //representa a quantidade cobertos pela solução
  set<int> Next; // representa os possíveis elementos que ainda podem entrar na solução
  vector<int> Grau; // auxilia no controle do vetor next;
  ll FO; // valor da função objetivo;
  ll FO_semPen; //valor da função objetivo sem as penalizações

  solucao(int n, int m, ll MAXPriceValue){
    Q = 0;
    P.clear();
    for (int i = 0; i < m; i++){
      Next.insert(i);
      Grau.pb(0);
    }
    FO_semPen = 0;
    FO = FO_semPen + (n - Q)* MAXPriceValue;
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

  void AdicionaElemento(int n, int m, int e, int qtElementosCobertos, ll custo, set<int> viz, const ll MAXPriceValue){ // só adiciona elementos que podem ser adicionados
    P.insert(e);
    Q += qtElementosCobertos;
    set<int> aux;

    for (auto v: viz){
      Grau[v]++;
      if (Grau[v] == sz(P)){
        aux.insert(v);
      }
    }
    Next = aux;
    FO_semPen += custo;
    FO = FO_semPen + (n - Q)*MAXPriceValue;
  }

  void RemoveElemento(int n, int m, int e, int qtElementosCobertos, ll custo, const set<int> viz, const ll MAXPriceValue){ // só adiciona elementos que podem ser adicionados
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
    FO = FO_semPen + (n - Q) * MAXPriceValue;
  }

  void print(int n, int m){
    cout << "FO: " << FO << endl;
    cout << Q <<"/"<< n << " elementos cobertos" << endl;
    cout << "P->";
    for (auto v: P){
      cout << v << " ";
    }
    cout << endl;
    cout << "Next->";
    for (auto v: Next){
      cout << v << " ";
    }
    cout << endl;
  }
};

struct tabuList{
  map<int, int> tl; //o primeiro é
  queue<int> Q;

  tabuList(){
  }

  void rm(){
    int u = Q.front(); Q.pop();
    tl.erase(u);
  }

  void add(int x, int T, int iteracao){
    if (sz(tl) == T){
      int u = Q.front(); Q.pop();
      tl.erase(u);
    }
    Q.push(x);
    tl[x] = iteracao;
  }

  bool isTabu(int x){
    return tl.find(x) != tl.end();
  }

  void resize(int T){
    while (sz(tl) > T){
      int u = Q.front(); Q.pop();
      tl.erase(u);
    }
  }

  void clear(){
    tl.clear();
    while (!Q.empty()) Q.pop();
  }

  int getPosition(int u){
    return tl[u];
  }

  void print(){
    for (map<int, int>::iterator it = tl.begin(); it!=tl.end(); it++){
      cout << (*it).f <<" ";
    }
    cout << endl;
  }
};

solucao guloso();
int OrdenaPorIndice(const void *a, const void *b);
bool FuncaoDeAspiracao(int n, solucao s, solucao BestS, int &NoNewSolutionIteration, ll MAXPriceValue, int multiplicador);
void UpdatefAspiration(solucao s, solucao BestS, int m, map<int, int> &LoopControlol, int &T, int &NoNewSolutionIteration, tabuList &lt);
void chanceListaTabuSize(int m, int aumentaDiminui, int &T, tabuList &lt);
solucao melhorVizinho(int n, int m, vector< vector<int> > Dados, vector< set<int> > Grafo, tabuList LT, ll MAXPriceValue, ll &IteracoesSemDiversificacao, solucao sMin, int &mov);
bool conflito(int u, int v);
void carregaDados();
void printDadosSetPartitioning();
solucao BuscaTabu(int n, int m, int &T, ll MAXPriceValue, vector< vector<int> > Dados, vector < set<int> > Grafo);
int main();
