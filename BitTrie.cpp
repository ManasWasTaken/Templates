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
    int cnt;
    Tnode* arr[2];
};
Tnode *root; //needs to be initialised
int BITS=31;
Tnode *new_node(){
    Tnode *node=new Tnode;
    node->val=0;
    node->cnt=0;
    node->arr[0]=NULL;
    node->arr[1]=NULL;
    return node;
}
void insertNode(int val){
    Tnode *node=root;
    for(int i=BITS;i>=0;i--){
        int z=(val>>i)&1;
        if(node->arr[z]==NULL){
            node->arr[z]=new_node();
        }
        node=node->arr[z];
        node->cnt++;
    }
    node->val=val;
    return;
}
void deleteNode(Tnode* &node,int val,int bit){
    if(bit==-1){
        node->cnt--;
        if(node->cnt==0){
            delete node;
            node=NULL;
        }
        return;
    }
    int z = (val >> bit) & 1;
    deleteNode(node->arr[z],val,bit-1);
    if(node->arr[z]==NULL && node->arr[1-z]==NULL){
        delete node;
        node=NULL;
    }
    return;
}
int get(int val){
    Tnode *node=root;
    for(int i=BITS;i>=0;i--){
        int z=(val>>i)&1;
        if(node->arr[1-z]!=NULL){
            node=node->arr[1-z];
        }
        else{
            node=node->arr[z];
        }
    }
    return (node->val)^val;
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