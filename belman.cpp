#include <bits/stdc++.h>
#define ll long long
#define mp make_pair
#define pb push_back
#define pp pair <int ,int >
#define ppi pair < int , pair <int ,int > >
#define ull unsigned long long
#define oo (int)(1e9+7)
#define PI acos(-1)
#define s second
#define f first

const int N = 128, E = 20001;
int n,m;
int e;
int head[N], nxt[E], to[E], cost[E];

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

int dist[N];
int inq[N], inqid;

int bellman()
{
    memset(dist, 0, n*(sizeof dist[0]));
    queue<int> q;
    inqid++;
    for(int i=0;i<n;i++) q.push(i), inq[i] = inqid;
    int x = n;
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

  #ifndef ONLINE_JUDGE
    freopen("/home/yaham/Documents/in"   , "r" ,stdin  ) ;
	//freopen("/home/hatem/Documents/out" , "w" ,stdout ) ;
	#endif
    while(cin >> n && n){
        n++;
        cin >> m;
        init();
        while(m--){
            int a,b,k;
            char op[5];
            cin >> a >> b >> op >> k;
            b += a;
            a--;
            if(op[0] == 'g'){
                swap(a,b);
                k *= -1;
            }
            k--;
            addEdge(a,b,k);
        }
        if(bellman()) puts("lamentable kingdom");
        else puts("successful conspiracy");
    }
    return 0;
}
