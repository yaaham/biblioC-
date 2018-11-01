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

int di[4] = {-1,1,0,0};
int dj[4] = {0,0,-1,1};
int r,c;
int vis[10001], vid;

bool isValid(int i,int j){ return (i>=0 && i<r && j>=0 && j<c); }



void bfs(int si[], int sj[], int s,int res[])
{
    queue<int> q;
    vid++;
    for(int k=0;k<s;k++){
        int i = si[k];
        int j = sj[k];
        int id = i * c + j;
        q.push(id);
        vis[id] = vid;
        res[id] = 0;
    }
    while(q.size()){
        int id = q.front();
        q.pop();
        int i = id / c;
        int j = id % c;
        for(int k=0;k<4;k++){
            int ni = i + di[k];
            int nj = j + dj[k];
            int nid = ni * c + nj;
            if(!isValid(ni,nj) || vis[nid] == vid) continue;
            vis[nid] = vid;
            res[nid] = res[id] + 1;
            q.push(nid);
        }
    }
}

int pi[3] , pj[3];

int main()
{
    scanf("%d%d",&r,&c);
    int q;
    scanf("%d",&q);
    while(q--){
        int resM[r*c] , resC[r*c];
        for(int i=2;i>=0;i--){
            scanf("%d%d",&pi[i],&pj[i]);
            pi[i]--;
            pj[i]--;
        }
        bfs(pi+2,pj+2,1,resM);
        bfs(pi,pj,2,resC);
        bool b = 0;
        for(int i=0;i<r && !b;i++){
            for(int j=0;j<c && !b;j++){
                if(i == 0 || i == r-1 || j == 0 || j == c-1){
                    if(resM[i*c+j] < resC[i*c+j]){
                        puts("YES");
                        b = 1;
                    }
                }
            }
        }
        if(!b) puts("NO");
    }
    return 0;
}











