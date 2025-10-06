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
using pii=pair<int,int>;
vector<pii> ds={{-1,0},{1,0},{0,1},{0,-1}};
void solve(){
    int n,m;
    cin>>n>>m;
    
    queue<pii> pq;
    vector<vector<int>> visited(n,vector<int> (m,0));
    auto bfs=[&]()->void{
        while(!pq.empty()){
            auto curr=pq.front();
            pq.pop();
            int x=curr.first;
            int y=curr.second;
            for(auto [dx,dy]:ds){
                int nx=x+dx;
                int ny=y+dy;
                if(nx<0 || nx>=n || ny<0 || ny>=m) continue;
                if(visited[nx][ny]==1) continue;
                visited[nx][ny]=1;
                pq.push({nx,ny});
            }
        }
    };
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