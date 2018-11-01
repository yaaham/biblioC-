
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

const int N = 202, E = 401;
int n,m,e,src,snk;
int head[N], to[E], nxt[E], cap[E];
int vis[N], vid;

void init()
{
    e =0;
    memset(head,-1,n*(sizeof head[0]));
}

void addEdge(int f,int t,int c)
{
    nxt[e] = head[f];
    head[f] = e;
    cap[e] = c;
    to[e++] = t;
}

void addAugEdge(int f,int t,int c)
{
    addEdge(f,t,c);
    addEdge(t,f,0);
}

int dfs(int minEdge,int cur = src, int flow = INT_MAX)
{
    if(cur == snk) return flow;
    if(vis[cur] == vid || flow < minEdge) return 0;
    vis[cur] = vid;
    for(int k=head[cur];~k;k=nxt[k]){
        int t = to[k];
        int f;
        if(!(f=dfs(minEdge,t,min(flow, cap[k])))) continue;
        cap[k] -= f;
        cap[k^1] += f;
        return f;
    }
    return 0;
}


int maxFlow()
{
    if(src == snk) return oo;
    int res = 0, f;
    for(int edge = 1<<30 ; edge ; edge >>= 1)
        while(vid++, f=dfs(edge)) res += f;
    return res;
}

int main()
{
    freopen("ditch.in","r",stdin);
    freopen("ditch.out","w",stdout);
    scanf("%d%d",&m,&n);
    init();
    while(m--){
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        addAugEdge(--a,--b,c);
    }
    src = 0, snk = n-1;
    cout << maxFlow() << endl;
    return 0;
}
