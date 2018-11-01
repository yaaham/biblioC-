/*
TASK: comehome
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

const int A = 128;
int n;
int cost[A][A];
int nvis[A];
int dist[A];

void dij(int sid)
{
    memset(dist, 0x3F, A*(sizeof dist[0]));
    dist[sid] = 0;
    iota(nvis,nvis+A,0);
    int sz = A;
    int nxt = sid;
    do{
        int cur = nvis[nxt];
        nvis[nxt] = nvis[--sz];
        nxt = -1;
        int best = 0x3f3f3f3f;
        for(int k=0;k<sz;k++){
            int j = nvis[k];
            int distj = dist[cur] + cost[cur][j];
            if(dist[j] > distj){
                dist[j] = distj;
            }
            if(best > dist[j]){
                best = dist[j];
                nxt = k;
            }
        }

    }while(nxt != -1);
}

int main()
{
    freopen("comehome.in","r",stdin);
    freopen("comehome.out","w",stdout);
    int t;
    scanf("%d",&t);
    memset(cost, 0x3F,sizeof cost);
    while(t--){
        char a,b;
        int c;
        scanf(" %c %c%d",&a,&b,&c);
//        swap(a,b);
        cost[a][b] = min(cost[a][b], c);
        cost[b][a] = cost[a][b];
    }
    dij('Z');
//    for(int i='A';i<='Z';i++)
//        cout << dist[i] << " "; cout << endl;
    char c = min_element(dist+'A', dist+'Z') - dist;
    cout << c << " " << dist[c] << endl;
    return 0;
}