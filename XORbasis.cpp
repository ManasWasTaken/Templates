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
int bits=20;
vector<int> basis(bits,-1);
int wasted=0;
void insert(int x,vector<int> &basis){
    for(int i=bits-1;i>=0;i--){
        if((x&(1ll<<i))==0) continue;
        if(basis[i]==-1){
            basis[i]=x;
            break;
        }
        x^=basis[i];
    }
    if(x==0) wasted++;
    return;
}
void merge(vector<int> basis1,vector<int> &basis2){
    for(int i=bits-1;i>=0;i--){
        if(basis1[i]==-1) continue;
        insert(basis1[i],basis2);
    }
    return;
}
bool check(int x,vector<int> &basis){
    int curr=0;
    for(int i=bits-1;i>=0;i--){
        if((x&(1ll<<i))!=(curr&(1ll<<i))){
            if(basis[i]==-1) return false;
            curr^=basis[i];
        }
    }
    if(curr==x) return true;
}
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