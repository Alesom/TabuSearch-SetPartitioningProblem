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
const unsigned full = 0xffffffff;

struct Edge{
    int u, v;
    int dist;

    Edge(int _u, int _v, int _dist) {u = _u, v = _v, dist = _dist;}

    bool operator <(const Edge &p) const {
        return dist < p.dist;
    }
};


int main(){
	printf("%u\n", full - (1 << 31));
	return 0;
}
