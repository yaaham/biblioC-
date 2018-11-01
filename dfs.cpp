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

const int N = 10001, E = 40001;

int n,m,e;
int head[N], to[E], nxt[E];
int vis[N], vid;

void init()
{
    e = 0;
    vid++;
    memset(head, -1,n* (sizeof head[0]));
    memset(vis, 0,n* (sizeof vis[0]));
}

void addEdge(int f,int t)
{
    nxt[e] = head[f];
    to[e] = t;
    head[f] = e++;
}

void addBiEdge(int f,int t)
{
    addEdge(f,t);
    addEdge(t,f);
}

int dfs(int u)
{
    if(vis[u] == vid)
        return 0;
    vis[u] = vid;
    int ret = 1;
    for(int k = head[u] ; ~k ; k = nxt[k]){
        int v = to[k];
        ret += dfs(v);
    }
    return ret;
}

int main()
{
    scanf("%d%d",&n,&m);
    init();
    while(m--){
        int u,v;
        scanf("%d%d",&u,&v);
        --u, --v;
        addBiEdge(u,v);
    }
    if(e / 2 == n-1 && dfs(0) == n) puts("YES");
    else puts("NO");
    return 0;
}
