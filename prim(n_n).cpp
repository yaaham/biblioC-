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

const int N = 128;
int A;
int cost[N][N];
int nvis[N];
int dist[N];

int prim(int sid)
{
    memset(dist, 0x3F, A*(sizeof dist[0]));
    dist[sid] = 0;
    iota(nvis,nvis+A,0);
    int sz = A;
    int nxt = sid;
    int res = 0;
    do{
        int cur = nvis[nxt];
        nvis[nxt] = nvis[--sz];
        nxt = -1;
        int best = 0x3f3f3f3f;
        for(int k=0;k<sz;k++){
            int j = nvis[k];
            int distj = cost[cur][j];
            if(dist[j] > distj){
                dist[j] = distj;
            }
            if(best > dist[j]){
                best = dist[j];
                nxt = k;
            }
        }
        if(best < 0x3f3f3f3f)
            res += best;
    }while(nxt != -1);
    return res;
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






