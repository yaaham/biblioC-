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
int inq[A], inqid;

int bellman(int sid)
{
    memset(dist, 0x3F, A*(sizeof dist[0]));
    dist[sid] = 0;
    queue<int> q;
    q.push(sid);
    inqid++;
    inq[sid] = inqid;
    int x = A;
    while(q.size() && x--){
        int s = q.size();
        while(s--){
            int cur = q.front();
            inq[cur] = 0;
            q.pop();
            for(int k=head[cur]; ~k ; k= nxt[k]){
                int t = to[k];
                int c = cost[k] + dist[cur];
                if(dist[t] > c){
                    dist[t] = c;
                    if(!x) return false;
                    if(inq[t] != inqid){
                        inq[t] = inqid;
                        q.push(t);
                    }
                }
            }
        }
    }
    return true;
}

int main()
{
    freopen("comehome.in","r",stdin);
    freopen("comehome.out","w",stdout);
    int t;
    scanf("%d",&t);
    init();
    while(t--){
        char a,b;
        int c;
        scanf(" %c %c%d",&a,&b,&c);
        addBiEdge(a,b,c);
    }
    bellman('Z');
    char c = min_element(dist+'A', dist+'Z') - dist;
    cout << c << " " << dist[c] << endl;
    return 0;
}