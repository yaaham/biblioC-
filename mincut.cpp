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
 
const int N = 2502, E = (2500 * 4 + 2500) * 2 + 10;
int n,m,e,src,snk;
int head[N], to[E], nxt[E], cap[E];
int vis[N], vid;
int r,c, d,f,b;
string grid[55];
int di[4] = {-1,1,0,0};
int dj[4] = {0,0,-1,1};
 
bool isValid(int i,int j)
{
    return (i>=0 && i<r && j>=0 && j<c);
}
 
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
 
int dfs(int lo, int cur = src, int flow = INT_MAX)
{
    if(cur == snk) return flow;
    if(vis[cur] == vid || flow < lo) return 0;
    vis[cur] = vid;
    for(int k=head[cur];~k;k=nxt[k]){
        int t = to[k];
        int f;
        if(!(f=dfs(lo, t,min(flow, cap[k])))) continue;
        cap[k] -= f;
        cap[k^1] += f;
        return f;
    }
    return 0;
}
 
bool isBoundary(int i,int j)
{
    return (i == 0 || i == r-1 || j == 0 || j == c-1);
}
 
int maxFlow()
{
    if(src == snk) return oo;
    int res = 0, f;
    for(int lo = 1<<30 ; lo ; lo >>= 1)
        while(vid++, f=dfs(lo)) res += f;
    return res;
}
 
int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%d%d",&c,&r);
        scanf("%d%d%d",&d,&f,&b);
        int sol = 0;
        n = r * c;
        src = n++;
        snk = n++;
        init();
        for(int i=0;i<r;i++){
            for(int j=0;j<c;j++){
                char ch;
                scanf(" %c",&ch);
                int id = i * c + j;
                if(isBoundary(i,j)){
                    if(ch == '.'){
                        sol += f;
                    }
                    addAugEdge(src, id, INT_MAX);
                }else{
                    if(ch == '.'){
                        addAugEdge(id, snk, f);
                    }else{
                        addAugEdge(src, id, d);
                    }
                }
                for(int k=0;k<4;k++){
                    int ni = i + di[k];
                    int nj = j + dj[k];
                    if(!isValid(ni,nj)) continue;
                    int nid = ni * c + nj;
                    addAugEdge(id, nid, b);
                }
            }
        }
        printf("%d\n",sol+maxFlow());
    }
    return 0;
}