/*
TASK: mining your own business
uva
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

const int N = 100002, E = 100001;
int n,m,e;
int head[N], to[E], nxt[E];
int idx[N], low[N], st[E], stsz;
int vis[N];
int compOf[E];
int nbrCmp, nxtIdx;
int isArt[N], isBridge[E], vid;
int rootid, rootchildren;
// this code mouch bi tala3 isolated nodes

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

void addBiEdge(int f,int t)
{
    addEdge(f,t);
    addEdge(t,f);
}

void extractComp(int k)
{
    do{
        int a = st[--stsz];
        compOf[ a^1 ] = compOf[ a ] = nbrCmp;
    }while(st[stsz] != k);
    nbrCmp++;
}

void DFS(int u,int id)
{
    idx[u] = low[u] = nxtIdx++;
    vis[u] = vid;
    for(int k=head[u];~k;k=nxt[k]){
        if(k == id) continue;
        int v = to[k];
        if(vis[v] != vid){ // v is white
            st[stsz++] = k;
            DFS(v, k^1);
            low[u] = min(low[u], low[v]);
            if(u == rootid){
                if(rootchildren++)
                    isArt[rootid] = vid;
                extractComp(k);
            }else if(low[v] >= idx[u]) {
                isArt[u] = vid;
                extractComp(k);
            }
            if(low[v] > idx[u]){
                isBridge[k] = vid;
                isBridge[k^1] = vid;
            }
        }else{ // v is gray or black
            low[u] = min(low[u], idx[v]);
            if(idx[v] < idx[u])
                st[stsz++] = k; // v is gray
        }
    }
}

void BiConnComp()
{
    vid++;
    nbrCmp = nxtIdx = 0;
    for(int i=0;i<n;i++){
        if(vis[i] != vid){
            rootid = i;
            rootchildren = 0;
            DFS(rootid, -1);
        }
    }
}

int main()
{
    int tc(1);
    while(cin >> m && m){
        n = 100001;
        init();
        n = 0;
        while(m--){
            int a,b;
            cin >> a >> b;
            n = max(n, max(a--,b--));
            addBiEdge(a,b);
        }
        BiConnComp();
    //    for(int i=0;i<n;i++)
    //        if(isArt[i] == vid)
    //            cout << i << " ";
    //    cout << endl;
    //    for(int i=0;i<e;i++)
    //        if(isBridge[i] == vid)
    //            cout << i << " ";
    //    cout << endl << endl;
    //    for(int i=0;i<e;i++){
    //        cout << i << " " << compOf[i] << endl;
    //    }
        vector<set<int> > compNodes(nbrCmp), compArt(nbrCmp);
        for(int i=0;i<n;i++)
            for(int k=head[i];~k;k=nxt[k]){
                compNodes[ compOf[k] ].insert(i);
                if(isArt[i] == vid) compArt[ compOf[k] ].insert(i);
            }
        int ans = 0;
        long long ways = 1;
        for(int i=0;i<nbrCmp;i++){
            if(compArt[i].size() != 1) continue;
            ans ++;
            ways *= (compNodes[i].size() - compArt[i].size());
        }
        if(nbrCmp == 1){
            ans = 2;
            ways = n * (n-1LL)/2;
        }
        cout << "Case " << tc++ << ": " << ans << " " << ways << endl;
    }
    return 0;
}
/*
6 7
0 1
1 2
2 3
3 1
0 4
0 5
5 4
*/





