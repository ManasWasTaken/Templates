// JAI SHREE RAM //
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "../miscellaneous/Debug.h"
#else
#define debug(...) 8
#endif
const int M=1e9+7;
#define int long long
template<class Node, class Update>
struct Segtree {
    int n=0;
    vector<Node> st;
    vector<Update> lazy;
    vector<bool> pending;

    Segtree() {}

    Segtree(int n):Segtree(vector<long long>(n)) {}

    template<class T>
    Segtree(const vector<T> &a):n(a.size()),st(4*n),
        lazy(4*n),pending(4*n,false){
        if(n) build(0,0,n-1,a);
    }

    void pull(int p){
        st[p].merge(st[2*p+1],st[2*p+2]);
    }

    template<class T>
    void build(int p,int l,int r,const vector<T> &a){
        if(l==r){
            st[p]=Node(a[l]);
            return;
        }
        int m=(l+r)/2;
        build(2*p+1,l,m,a);
        build(2*p+2,m+1,r,a);
        pull(p);
    }

    void apply(int p,int l,int r,const Update &u){
        u.apply(st[p],l,r);
        if(l==r) return;
        lazy[p].merge(u,l,r);
        pending[p]=true;
    }

    void push(int p,int l,int r){
        if(!pending[p]) return;
        int m=(l+r)/2;
        apply(2*p+1,l,m,lazy[p]);
        apply(2*p+2,m+1,r,lazy[p]);
        lazy[p]=Update();
        pending[p]=false;
    }

    void update(int p,int l,int r,int ql,int qr,const Update &u){
        if(r<ql || qr<l) return;
        if(ql<=l && r<=qr){
            apply(p,l,r,u);
            return;
        }
        push(p,l,r);
        int m=(l+r)/2;
        update(2*p+1,l,m,ql,qr,u);
        update(2*p+2,m+1,r,ql,qr,u);
        pull(p);
    }

    Node query(int p,int l,int r,int ql,int qr){
        if(r<ql || qr<l) return Node();
        if(ql<=l && r<=qr) return st[p];
        push(p,l,r);
        int m=(l+r)/2;
        Node ans;
        ans.merge(query(2*p+1,l,m,ql,qr),
                  query(2*p+2,m+1,r,ql,qr));
        return ans;
    }

    void update(int l,int r,const Update &u){
        if(n && l<=r) update(0,0,n-1,l,r,u);
    }

    Node query(int l,int r){
        if(!n || l>r) return Node();
        return query(0,0,n-1,l,r);
    }
};

struct Node {
    long long val=LLONG_MIN;

    Node() {}
    Node(long long x):val(x) {}

    void merge(const Node &l,const Node &r){
        val=max(l.val,r.val);
    }
};

struct Update {
    long long add=0;

    Update() {}
    Update(long long x):add(x) {}

    // Existing update first, then u.
    void merge(const Update &u,int l,int r){
        add+=u.add;
    }

    void apply(Node &node,int l,int r) const{
        node.val+=add;
    }
};
void solve(){
    
}
int32_t main(){
    cout<<fixed;
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout<<setprecision(15)<<fixed;
    int t=1;
    while(t--){
       solve(); 
    }
    return 0;
}