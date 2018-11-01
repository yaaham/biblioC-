/*
TASK: stall4
LANG: C++
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
 
const int N = 201, E = 40001;
int n,m,e,src,snk;
int R[N],L[N];
int head[N], to[E], nxt[E];
int vis[N], vid;
 
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
 
bool can(int u)
{
    if(vis[u] == vid) return false;
    vis[u] = vid;
    for(int k=head[u];~k;k=nxt[k]){
        int v = to[k];
        if(R[v] == -1 || can(R[v])){
            R[v] = u;
            L[u] = v;
            return true;
        }
    }
    return false;
}
 
int match()
{
    int res = 0;
    memset(R, -1, m*(sizeof R[0]));
    for(int i=0;i<n;i++){
        vid++;
        if(can(i)) res++;
    }
    return res;
}
 
int main()
{
    freopen("stall4.in","r",stdin);
    freopen("stall4.out","w",stdout);
    scanf("%d%d",&n,&m);
    init();
    for(int i=0;i<n;i++){
        int k; scanf("%d",&k);
        while(k--){
            int a; scanf("%d",&a);
            addEdge(i,--a);
        }
    }
    printf("%d\n", match());
    return 0;
}