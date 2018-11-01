#include <iostream>
#include <cstdio>
using namespace std;
#define mp make_pair
#define pb push_back
#define F first
#define S second
#define sz(x) (int)(x).size()
//#define all(x) (x).begin(),(x).end()
typedef long long ll;
const int oo = (int) 1e9;
const int mod = (int) 1e9 + 7;

const int MAX = (1<<17);
struct node{
    int pref, suff, all;
    int lazy;
    node(){ lazy = -1; }
    node(int p,int s,int a): pref(p),suff(s),all(a){
        lazy = -1;
    }
};

node st[MAX];
int n,m;

void merge(const node& l,const node& r,node& p,int szl,int szr)
{
    p.pref = l.pref;
    if(szl == l.pref) p.pref = szl + r.pref;
    p.suff = r.suff;
    if(szr == r.suff) p.suff = szr + l.suff;
    p.all = max(l.all, max(r.all, l.suff + r.pref));
}

void push_down(node& l, node& r, node& p,int szl,int szr)
{
    if(p.lazy == -1 || szl+szr == 1) return;
    if(p.lazy == 0){
        l.all = l.suff = l.pref = szl;
        r.all = r.suff = r.pref = szr;
    }else{
        l.all = l.suff = l.pref = 0;
        r.all = r.suff = r.pref = 0;
    }
    l.lazy = r.lazy = p.lazy;
    p.lazy = -1;
}

void update(int cur, int ns,int ne,int qs,int qe,int val)
{
    if(ns > qe || ne < qs) return;
    if(ns >= qs && ne <= qe){
        st[cur].lazy = val;
        st[cur].pref = st[cur].suff =
        st[cur].all = val ? 0 : ne - ns + 1;
        return;
    }
    int mid = (ns+ne)/2;
    push_down(st[2*cur+1], st[2*cur+2], st[cur], mid-ns+1, ne-mid);
    update(2*cur+1, ns, mid, qs, qe, val);
    update(2*cur+2, mid+1, ne, qs, qe, val);
    merge(st[2*cur+1], st[2*cur+2], st[cur], mid-ns+1, ne-mid);
}

int find(int cur, int ns,int ne,int sz)
{
    if(st[cur].all < sz) return -1;
    if(st[cur].pref >= sz) return ns;
    int mid = (ne + ns) >> 1;
    int szl = mid - ns + 1,
    szr = ne - mid;
    push_down(st[2*cur+1], st[2*cur+2], st[cur], szl, szr);
    if(st[2*cur+1].all >= sz) return find(2*cur+1,ns,mid,sz);
    if(st[2*cur+1].suff+st[2*cur+2].pref >= sz)
        return mid - st[cur*2+1].suff + 1;
    return find(2*cur+2,mid+1,ne,sz);
}

void print(int cur,int ns,int ne)
{
    printf("cur = %d ns = %d ne = %d ", cur, ns, ne);
    printf("suff = %d all = %d pref = %d lazy = %d\n", st[cur].suff, st[cur].all, st[cur].pref, st[cur].lazy);
    if(st[cur].lazy != -1 || ns == ne) return;
    int mid = (ns+ne) >> 1;
    print(2*cur+1, ns, mid);
    print(2*cur+2, mid+1, ne);
}

int main()
{
    scanf("%d%d",&n,&m);
    st[0].pref = st[0].suff = st[0].all = n;
    st[0].lazy = 0;
    while(m--){
        int op,a,b;
        scanf("%d",&op);
        if(op == 1){
            scanf("%d",&a);
            int v = find(0,0,n-1,a);
            if(v != -1)
                update(0,0,n-1,v,v+a-1,1);
            printf("%d\n", v+1);
        }else{
            scanf("%d%d",&a,&b);
            --a;
            b--;
            b += a;
            update(0,0,n-1,a,b,0);
        }
//        print(0,0,n-1);
//        printf("--------\n");
    }
    return 0;
}
