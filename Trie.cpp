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
struct Tnode{
    int val;
    Tnode* arr[26];
};
Tnode *root; //needs to be initialised
Tnode *new_node(){
    Tnode *node=new Tnode;
    node->val=0;
    for(int i=0;i<26;i++) node->arr[i]=NULL;
    return node;
}
void insertNode(string s){
    Tnode *node=root;
    for(auto x:s){
        int val=x-'a';
        if(node->arr[val]==NULL){
            node->arr[val]=new_node();
        }
        node=node->arr[val];
        node->val+=1;
    }
    return;
}
int get(string s){
    Tnode *node=root;
    int sub=0;
    for(auto x:s){
        int val=x-'a';
        if(node->arr[val]==NULL) break;
        node=node->arr[val];
        sub+=node->val;
    }
    return sub;
}
//can be made better
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