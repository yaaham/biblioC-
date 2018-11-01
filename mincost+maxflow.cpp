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

char s[10001], t[10001];
const int N = 402, E = (9900 / 2 + 100 + 100) * 5;
int n,m,e,src,snk;
int head[N], to[E], nxt[E], cap[E], cost[E], from[E];
int dist[N], flow[N], par[E];
int inq[N], vid;
int a[128][128];

void init()
{
    e =0;
    memset(head,-1,n*(sizeof head[0]));
}

void addEdge(int f,int t,int ca,int co)
{
    nxt[e] = head[f];
    head[f] = e;
    cap[e] = ca;
    cost[e] = co;
    from[e] = f;
    to[e++] = t;
}

void addAugEdge(int f,int t,int ca,int co)
{
    addEdge(f,t,ca,co);
    addEdge(t,f,0,-co);
}

void bellman()
{
    memset(dist, 0x3f, n*(sizeof dist[0]));
    memset(flow, 0, n*(sizeof flow[0]));
    dist[src] = 0;
    flow[src] = 0x3f3f3f3f;
    vid++;
    queue<int> q;
    q.push(src);
    inq[src] = vid;
    int nn = n;
    while(q.size() && nn--){
        int s = q.size();
        while(s--){
            int cur = q.front();
            q.pop();
            inq[cur] = 0;
            for(int k=head[cur];~k;k=nxt[k]){
                int t = to[k];
                int c = cost[k] + dist[cur];
                if(cap[k] && dist[t] > c){
                    dist[t] = c;
                    flow[t] = min(flow[cur], cap[k]);
                    par[t] = k;
                    if(!nn) return;
                    if(inq[t] != vid){
                        q.push(t);
                        inq[t] = vid;
                    }
                }
            }
        }
    }
}

pair<int,int> minCostMaxFlow()
{
    pair<int,int> res = {0,0};
    while(1){
        bellman();
        if(!flow[snk]) break;
        res.first += flow[snk] * dist[snk];
        res.second += flow[snk];
        for(int i=snk ; i != src ; i = from[ par[i] ]){
            int k = par[i];
            cap[k] -= flow[snk];
            cap[k^1] += flow[snk];
        }
    }
    return res;
}

int main()
{
    int T;
    scanf("%d",&T);
    while(T--){
        scanf("%s%s",s,t);
        memset(a, 0x3f, sizeof a);
        int left = n = strlen(t);
        for(int i=strlen(s)-2;i>=0;i--)
            a[s[i]][ s[i+1] ] = (i+1)*(i+1);
        n += n;
        src = n++;
        snk = n++;
        init();
        for(int i=0;t[i];i++){
            addAugEdge(src,i,1,0);
            addAugEdge(i+left, snk,1,0);
            for(int j=i+1;t[j];j++){
                if(a[ t[i] ][ t[j] ] < 0x3f3f3f3f)
                    addAugEdge(i,j+left,1,a[ t[i] ][ t[j] ]);
            }
        }
        auto r = minCostMaxFlow();
        printf("%d %d\n", left - r.second, r.first);
    }
    return 0;
}



