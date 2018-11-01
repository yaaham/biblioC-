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

void floyd()
{
    for(int k=0;k<A;k++){
        for(int i=0;i<A;i++)
        for(int j=0;j<A;j++){
            int dist = cost[i][k] + cost[k][j];
            cost[i][j] = min(cost[i][j], dist);
        }
    }
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
        cost[a][b] = min(cost[a][b], c);
        cost[b][a] = cost[a][b];
    }
    floyd();
    char c = min_element(cost['Z']+'A', cost['Z']+'Z') - cost['Z'];
    cout << c << " " << cost['Z'][c] << endl;
    return 0;
}