/*Exemplo da busca tabu para o problema do caixeiro viajante*/


#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second
#define pb push_back
#define sz(v) ((int)v.size())
#define rad(a) a * PI / 180


#define nInterations 1 << 20

typedef long long ll;
typedef vector<int> vi;
typedef pair<int,int> ii;

const int MAX = 31;
const int LIM = 2000000;
const int MAXT = 270000;
const int P = 1000000007;
const int INF = (1 << 28);
const double EPS = 1e-6;
const double PI = 3.14159265358979;

const int BTMAX = 1123; // Número máximo de iterações sem melhora;

struct Edge{
    int u, v;
    int dist;

    Edge(int _u, int _v, int _dist) {u = _u, v = _v, dist = _dist;}

    bool operator <(const Edge &p) const {
        return dist < p.dist;
    }
};
vector<Edge> E;

struct Solucao{
  vector<bool> s;
  int FO;

  Solucao(vector<bool> _s){
    FO = 0;
    for (int i = 0; i < sz(_s); i++){
      s.pb(_s[i]);
      FO+=_s[i]*E[i].dist;
    }
  }
};

struct MUF{
  vector<int> mufp, mufrank;
  MUF(int n){
    for (int i = 0 ; i < n; i++){
      mufp.pb(i);
      mufrank.pb(1);
    }
  }

  int find(int x){
      return mufp[x] == x ? x : (mufp[x] = find(mufp[x]));
  }

  void un(int x, int y){
      x = find(x);
      y = find(y);
      if( x == y ){
          return;
      }

      if ( mufrank[x] < mufrank[y] ){
          mufp[x] = y;
      }
      else {
          mufp[y] = x;
          if (mufrank[x] == mufrank[y]) {
              mufrank[x]++;
          }
      }
  }
};


int n; // ordem do grafo
vector<ii> adj[MAX]; // matriz de adjacências do grafo

Solucao guloso(){
  vector<bool> s0;
  vector<int> dg;
  int qt = 0, i;

  for (i = 0; i < n; i++){
    dg.pb(0);
  }

  MUF uf(n);

  for (i = 0; i < sz(E) && qt < n - 1; i++){
    if (uf.find(E[i].v) != uf.find(E[i].u) && dg[E[i].v] < 2 && dg[E[i].u] < 2){
      dg[E[i].v]++;
      dg[E[i].u]++;
      uf.un(E[i].v, E[i].u);
      qt++;
      s0.pb(true);
    }else{
      s0.pb(false);
    }
  }

  for (; i < sz(E); i++){
    s0.pb(dg[E[i].v] < 2 && dg[E[i].u] < 2);
  }

  /* Solução inicial
  for (i = 0; i < sz(E); i++){
    cout << s0[i];
  }
  cout << endl;
  */

  return Solucao(s0);
}

void tabu(){
  Solucao s = guloso();
  int iter, Miter = 0;

  //cout << s.FO << endl;

  for (iter = 0; iter - Miter < BTMAX; iter++) {
    
  }


}

int main(void){
  int a, b, c, m;
  scanf("%d %d", &n, &m); // o grafo é completo

  for (int i = 0; i < m; i++){
    scanf("%d %d %d", &a, &b, &c);
    a--;
    b--;
    adj[a].pb(ii(c, b));
    adj[b].pb(ii(c, a));
    E.pb(Edge(min(a, b), max(a, b), c));
  }


  sort(E.begin(), E.end()); // ordem da solução

  for (int i =0 ; i < sz(E); i++){
    cout << E[i].u <<  " " << E[i].v << " " << E[i].dist << endl;
  }

  tabu();
  return 0;
}
