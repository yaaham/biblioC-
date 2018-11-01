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

const int A = 128, E = 20001;
int e;
int head[A], nxt[E], to[E], cost[E];

void init()
{
    e = 0;
    memset(head, -1, sizeof head);
}

void addEdge(int f,int t,int c)
{
    nxt[e] = head[f];
    head[f] = e;
    cost[e] = c;
    to[e++] = t;
}

void addBiEdge(int f,int t,int c)
{
    addEdge(f,t,c);
    addEdge(t,f,c);
}

int dist[A];

void dij(int sid)
{
    memset(dist, 0x3F, A*(sizeof dist[0]));
    dist[sid] = 0;
    priority_queue<pair<int,int> > q;
    q.push({0,sid});
    while(q.size()){
        int d = -q.top().first;
        int cur = q.top().second;
        q.pop();
        if(d != dist[cur]) continue;
        for(int k=head[cur]; ~k ; k= nxt[k]){
            int t = to[k];
            int c = cost[k] + d;
            if(dist[t] > c){
                dist[t] = c;
                q.push({-c,t});
            }
        }
    }
}

int main()
{
    freopen("agrinet.in","r",stdin);
    freopen("agrinet.out","w",stdout);
    scanf("%d",&A);
    for(int i=0;i<A;i++)
        for(int j=0;j<A;j++)
            scanf("%d",&cost[i][j]);
    printf("%d\n", prim(0));
    return 0;
}