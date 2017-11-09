#include <bits/stdc++.h>

using namespace std;

#define f first
#define s second
#define pb push_back
#define sz(v) ((int)v.size())
#define rad(a) a * PI / 180

typedef long long ll;
typedef vector<int> vi;
typedef pair<ll,ll> ii;

const int MAX = 31;
const int LIM = 2000000;
const int MAXT = 270000;
const int P = 1000000007;
const int INF = (1 << 28);
const double EPS = 1e-6;
const double PI = 3.14159265358979;
const int partSz = 32; // tamanho da partição na solução(tamanho de um inteiro)
const int BTMAX = 1 << 10;
const int T = 5; // tamanho da lista tabu;

vector< vector<int> > Dados; // Matriz que armazena todos os dados do problema, exceto o número de partições m e o número de elementos n;
int MAXPriceValue; // Valor máximo de uma partição;
int n, m; // n representa a quantidade de elementos e m representa a quantidade de partições

struct solution{
    vector<unsigned> p; // vetor que representa quais partições estão ou não estão na solução
    int sizelast; // representa o tamanho do último inteiro adicionado a p;
    vector<char> e; /*vetor que representa quantas vezes um elemento foi "coberto";
                    Se e[i] = 0 o elemento não foi coberto;
                    Se e[i] = 1 o elemento foi coberto de forma perfeita;
                    Se e[i] > 1 existe mais de um partição cobrindo o elemento*/

    ll FO_Value; //Valor da função objetivo aplicada da solução com a adicão da penalidade;
    ll FO_P; //Valor da função objetivo aplicada da solução sem as penalidades;

    solution(int n, int m, vector<bool> v){ /* Método construtor;
                        n representa o número de elementos;
                        m representa o número de partições.
                        v representa o vetor 0's e 1's na solução*/
        FO_Value = INF;
        FO_P = 0;

        while (m >= partSz){
            m-=partSz;
            p.pb(0);
        }
        if (m > 0){
            sizelast = m;
            p.pb(0);
        }else sizelast = 0;

        for (int i = 0; i < n; i++) e.pb(0);
        if (sz(v) != m) return;
        for (int i = 0; i < sz(v); i++){
          setBit(n, i, v[i]);
        }
    }

    void operator =(solution &_s) { //sobreescreve o operador =
        FO_Value = _s.FO_Value;
        FO_P = _s.FO_P;
        sizelast = _s.sizelast;

        for (int i = 0 ; i < sz(e); i++){
          e[i] = _s.e[i];
        }

        for (int i = 0 ; i < sz(p); i++){
          p[i] = _s.p[i];
        }
    }

    bool operator <(const solution &_s) const { //sobreescreve o operador <
      return FO_Value < _s.FO_Value;
    }

    bool operator >(const solution &_s) const { //sobreescreve o operador >
      return FO_Value > _s.FO_Value;
    }

    bool operator ==(const solution &_s) const { //sobreescreve o operador ==
      return FO_Value == _s.FO_Value;
    }

    int getIntPart(int i){
        return i/partSz;
    }

    int getPosPart(int i){
        return i%partSz;
    }

    int getBit(int i){
        int integerPart = getIntPart(i);
        int bit = getPosPart(i);
        return (p[integerPart] & (1 << bit)) >> bit;
    }

    void setBit(int n, int i, int b){
        int integerPart = getIntPart(i);
        int bit = getPosPart(i);
        if (b){
            p[integerPart] = p[integerPart] | (1 << bit);
            FO_P+=Dados[i][0]; // atualiza a função objetivo;
            for(int j = 1; j < sz(Dados[i]); j++){
                e[Dados[i][j] - 1]++;
            }
        }else{
            p[integerPart] = p[integerPart] & ~(1 << bit);
            FO_P-=Dados[i][0]; // atualiza a função objetivo;
            for(int j = 1; j < sz(Dados[i]); j++){
                e[Dados[i][j] - 1]--;
            }
        }
        ll pen = 0;
        for (int i = 0; i < n; i++){
            if (e[i] == 0 || e[i] == 2) pen+=MAXPriceValue;
            else pen += (e[i] - 1) * MAXPriceValue;
        }
        FO_Value = FO_P + pen;
    }

    void print(int m){
        cout << FO_Value << endl;
        for (int i = 0; i < m; i++){
            cout << getBit(i);
        }
        cout << endl;
    }

    void print(int n, int m){
        cout << FO_P <<" "<< FO_Value << endl;


        for (int i = 0; i < sz(e); i++){
          cout << int(e[i]) <<" ";
        }

        cout << endl;

        for (int i = 0; i < m; i++){
            cout << getBit(i);
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
};

solution guloso(){
  vector<bool> v;
  return solution(n, m, v);
}

solution min(solution s1, solution s2){
  if (s1 < s2) return s1;
  return s2;
}

bool fAspiration(solution s, int mov, solution BestS){
  if (BestS > s) return true;
  return false;
}

solution tabu(){;
  solution s = guloso();
  solution BestS = s;

  int iter, Miter = 0;
  tabuList LT; // lista tabu

  for (iter = 0; iter - Miter < BTMAX; iter++) {
    solution sMin = s;
    sMin.FO_Value = INF;

    int mov = -1;
    for (int i = 0; i < m; i++){
      solution s1 = solution(s);
      s1.setBit(n, i, !s1.getBit(i));
      s1.print(n, m);
      if (!LT.isTabu(i) || fAspiration(s1, i, BestS)){
        if (sMin > s1){
          sMin = s1;
          mov = i;
        }
      }
    }
    LT.add(mov, T);
    cout << "Ganhou\n";
    sMin.print(n, m);
    cout << "end\n";
    s = sMin;

    if (sMin < BestS){
      BestS = sMin;
      Miter = iter;
      //BestS.print(n, m);
    }

  }

  return BestS;
}

void read(){ // oassando como parâmetro, precisa arrumar
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

vector<bool> makeVecBool(string s){
  vector<bool> v;
  for (int i = 0; i < sz(s); i++){
    v.pb(s.at(i) == '1');
  }
  return v;
}

int main(){
  read();
  tabu().print(n, m);
  return 0;
}
