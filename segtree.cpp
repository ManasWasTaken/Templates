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
struct segtree{
    vector<int> arr; //the array
    int n; //size of the array
    int identity_element; 
    vector<int> st;
    segtree(vector<int> arr, int n, int identity_element) : arr(arr), n(n), identity_element(identity_element), st(4 * n, identity_element) {
        build(0, 0, n - 1);
    }
    int combine(int a,int b){ //change here for different operations
        return max(a,b);
    }
    void build(int node,int l,int r){
        if(l==r){
            st[node]=arr[l];
            return;
        }
        int left=2 * node + 1;
        int right=2 * node + 2;
        int mid= (l + r)/2;
        build(left,l,mid);
        build(right,mid+1,r);
        st[node]=combine(st[left],st[right]);
    }
    void update(int node,int l,int r,int index,int val){
        if(l==r){
            st[node]=val;
            return;
        }
        int left=2 * node + 1;
        int right=2 * node + 2;
        int mid= (l + r)/2;
        if(index<=mid){
            update(left,l,mid,index,val);
        }
        else{
            update(right,mid+1,r,index,val);
        }
        st[node]=combine(st[left],st[right]);
    }
    int query(int node,int l,int r,int lx,int rx){
        if (r < lx || l > rx) {
            return identity_element;
        }
        if (l >= lx && r <= rx) {
            return st[node];
        }
        int left= (2 * node) + 1;
        int right= (2 * node) + 2;
        int mid= (l + r)/2;
        int a=query(left,l,mid,lx,rx);
        int b=query(right,mid+1,r,lx,rx);
        return combine(a,b);
    }
    int walk(int node,int l,int r,int k){
        if(st[node]<k) return -1;
        if(l==r){
            return l;
        }
        int left=2 * node + 1;
        int right=2 * node + 2;
        int mid= (l + r)/2;
        if(k<=st[left]){
            return walk(left,l,mid,k);
        }
        else{
            return walk(right,mid+1,r,k);
        }
    }
 
    void update_point(int index, int val){
        update(0,0,n-1,index,val);
    }
 
    int range_query(int l, int r){
        return query(0, 0, n - 1, l, r);
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