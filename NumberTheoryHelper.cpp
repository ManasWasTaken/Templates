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
struct numbertheory{
    int n;
    vector<int> spf; //spf is smallest prime factor for each number
    vector<int> primes; 
    numbertheory(int x) : n(x), spf(n+1,-1){
        build();
    }

    void build(){
        spf[1]=1;
        for(int i=2;i<=n;i++){
            if(spf[i]!=-1) continue;
            primes.push_back(i);
            for(int j=1;i*j<=n;j++){
                if(spf[i*j]==-1) spf[i*j]=i;
            }
        }
    }

    map<int,int> factorise(int x){
        map<int,int> mp;
        int z=x;
        while(z>1){
            mp[spf[z]]++;
            z/=spf[z];
        }
        if(z>1) mp[z]++;
        return mp;
    }

    bool isPrime(int n){
        if(n==1) return false;
        if(spf[n]==n) return true;
        return false;
    }
    map<int,int> sqrtF(int n){ //use this is number is greater than n
        map<int,int> mp;
        for(auto x:primes){
            if(x>n) break;
            while(n%x==0){
                mp[x]++;
                n/=x;
            }
        }
        if(n>1) mp[n]++;
        return mp;
    }
    vector<int> getFactors(int z){
        vector<int> sol;
        for(int i=1;i*i<=z;i++){
            if(z%i==0){
                sol.push_back(i);
                if((z/i)!=i)sol.push_back(z/i);
            }
        }
        sort(sol.begin(),sol.end());
        return sol;
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