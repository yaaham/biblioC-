/*
TASK: schlnet
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

const int N = 1001, E = 10000;
int n,e;
int head[N], to[E], nxt[E];
int idx[N], low[N], st[N], stsz;
int compOf[N];
int nbrCmp, nxtIdx;
int nsrc[N], nsnk[N];

void init()
{
    e =0;
    memset(head,-1,n*(sizeof head[0]));
}

void addEdge(int f,int t)
{
    nxt[e] = head[f];
    head[f] = e;
    to[e++] = t;
}

void DFS(int u)
{
    idx[u] = low[u] = nxtIdx++;
    st[stsz++] = u;
    for(int k=head[u] ; ~k ; k = nxt[k]){
        int v = to[k];
        if(idx[v] == -1){ // Gray to White
            DFS(v);
            low[u] = min(low[u], low[v]);
        }else if(compOf[v] == -1){ // Gray to gray
            low[u] = min(low[u], low[v]);
        }
    }
    if(low[u] == idx[u]){
        do{
            compOf[ st[--stsz] ] = nbrCmp;
        }while(st[stsz] != u);
        nbrCmp++;
    }
}

void SCC()
{
    memset(idx, -1, n*(sizeof idx[0]));
    memset(compOf, -1, n*(sizeof compOf[0]));
    nbrCmp = nxtIdx = 0;
    for(int i=0;i<n;i++)
        if(idx[i] == -1)
            DFS(i);
}

int main()
{
    freopen("schlnet.in","r",stdin);
    freopen("schlnet.out","w",stdout);
    scanf("%d",&n);
    init();
    for(int i=0;i<n;i++){
        int a;
        while(scanf("%d",&a) && a){
            a--;
            addEdge(i,a);
        }
    }
    SCC();
    for(int i=0;i<n;i++){
        for(int k=head[i];~k;k=nxt[k]){
            int j = to[k];
            if(compOf[i] != compOf[j]){
                nsrc[ compOf[j] ] = 1;
                nsnk[ compOf[i] ] = 1;
            }
        }
    }
    int nbrsrc = count(nsrc, nsrc+nbrCmp,false);
    int nbrsnk = count(nsnk, nsnk+nbrCmp,false);
    cout << nbrsrc << endl << (nbrCmp == 1 ? 0 : max(nbrsrc, nbrsnk)) << endl;
    return 0;
}



