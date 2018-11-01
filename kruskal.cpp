/*
TASK: agrinet
LANG: C++11
*/
#include <bits/stdc++.h>
using namespace std;
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
typedef long long ll;
const int oo = (int) 1e9;
const int mod = (int) 1e9 + 7;
const double PI = acos(-1.0);
 
const int MAX = 100000;
 
int n;
int par[MAX], sz[MAX];
int nbr_sts;
 
int from[MAX], to[MAX], cost[MAX], sorted[MAX];
 
void init()
{
    nbr_sts = n;
    iota(par,par+n,0);
    fill(sz,sz+n,1);
}
 
int find(int x){
    return (x == par[x] ? x : par[x] = find(par[x]));
}
 
void join(int x,int y)
{
    x = find(x);
    y = find(y);
    if(x == y) return;
    if(sz[x] > sz[y]) swap(x,y);
    par[x]=y;
    sz[y] += sz[x];
    nbr_sts--;
}
 
int kruskal()
{
    int res = 0;
    sort(sorted, sorted+n*n,[](int x,int y){ return cost[x] < cost[y]; });
//    for(int i=0;i<n*n;i++) cout << sorted[i] << " ";
    for(int i=0;i<n*n;i++){
        int k = sorted[i];
        if(find(from[k]) != find(to[k])){
            join(from[k], to[k]);
            res += cost[k];
        }
    }
    return res;
}
 
int main()
{
    freopen("agrinet.in","r",stdin);
    freopen("agrinet.out","w",stdout);
    cin >> n;
    init();
    for(int i=0,k=0;i<n;i++){
        for(int j=0;j<n;j++){
            cin >> cost[k];
            sorted[k] = k;
            from[k] = i;
            to[k++] = j;
        }
    }
    cout << kruskal() << endl;
    return 0;
}