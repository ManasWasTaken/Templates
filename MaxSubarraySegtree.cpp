// JAI SHREE RAM //
#include <bits/stdc++.h>
using namespace std;
#ifndef ONLINE_JUDGE
#include "debug.h"
#else
#define debug(...) 8
#endif
const int M=1e9+7;
#define int long long

const int N=1<<18; // Power of two; for 1-based indexing, n < N.
struct Node{
    int sum;
    int max_sum;
    int max_sum_left;
    int max_sum_right;
} tree[2*N];

Node merge(const Node &l,const Node &r){
    return {
        l.sum+r.sum,
        max({l.max_sum,r.max_sum,l.max_sum_right+r.max_sum_left}),
        max(l.max_sum_left,l.sum+r.max_sum_left),
        max(r.max_sum_right,r.sum+l.max_sum_right)
    };
}

void update(int i,int x){
    i+=N;
    tree[i]={x,max(x,0LL),max(x,0LL),max(x,0LL)};
    while(i>1){
        i/=2;
        tree[i]=merge(tree[2*i],tree[2*i+1]);
    }
}

Node query(int l,int r){ // Inclusive [l,r]; empty subarrays are allowed.
    Node left{},right{};
    l+=N;
    r+=N;
    while(l<=r){
        if(l&1) left=merge(left,tree[l++]);
        if(!(r&1)) right=merge(tree[r--],right);
        l/=2;
        r/=2;
    }
    return merge(left,right); // Preserve left-to-right merge order.
}

void solve(){
    int n,q;
    cin>>n>>q;
    for(int i=1;i<=n;i++){
        int x;
        cin>>x;
        update(i,x);
    }
    while(q--){
        int k,x;
        cin>>k>>x;
        update(k,x);
        cout<<tree[1].max_sum<<'\n';
        // query(l,r).max_sum gives the maximum subarray sum on [l,r].
    }
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
