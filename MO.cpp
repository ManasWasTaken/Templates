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
const int block; //use this as const only else your cooked
#pragma GCC optimize("O3,unroll-loops")
struct query{
    int l,r,idx;
    query(int l,int r,int idx) : l(l),r(r),idx(idx){

    }
    bool operator <(const query other) const{
        int a=l/block;
        int b=other.l/block;
        if(a!=b) return a<b;
        return r<other.r;
    }
};

void solve(){
    int q;
    cin>>q;
    vector<query> queries;
    for(int i=0;i<q;i++){
        int l,r;
        cin>>l>>r;
        queries.push_back(query(l,r,i));
    }
    sort(queries.begin(),queries.end());
    int l=0,r=-1;
    int ans=0;
    vector<int> res(q,0);
    auto add=[&](int idx){ //just need to add given index
        
    };
    auto remove=[&](int idx){ //remove the given index

    };
    for(query q:queries){
        while(l>q.l){
            l--;
            add(l);
        }
        while(r<q.r){
            r++;
            add(r);
        }
        while(l<q.l){
            remove(l);
            l++;
        }
        while(r>q.r){
            remove(r);
            r--;
        }
        res[q.idx]=ans;
    }
    return;
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