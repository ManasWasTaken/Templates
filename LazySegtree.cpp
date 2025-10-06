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
struct LazySegmentTree {
    int n;
    vector<int> arr;
    vector<int> st;
    vector<int> lazy;
    const int IDENTITY_ELEMENT = 1e18; 
    const int IDENTITY_UPDATE = 0;    

    LazySegmentTree(const std::vector<int>& x) {
        arr = x;
        n = arr.size();
        st.resize(4 * n, IDENTITY_ELEMENT);
        lazy.assign(4 * n, IDENTITY_UPDATE);
        build(0, 0, n - 1);
    }

    int combine(int a, int b) { //the operation
        return min(a,b);
    }

    void apply_update(int node,int Size) { //applying updates
        st[node] += (lazy[node]); 
    }

    void combine_lazy(int node, int new_update) { //combining updates
        lazy[node] += new_update;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            st[node] = arr[l];
            return;
        }
        int mid = l + (r - l) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;

        build(left_child, l, mid);
        build(right_child, mid + 1, r);

        st[node] = combine(st[left_child], st[right_child]);
    }

    void push(int node, int l, int r) {
        if (lazy[node] == IDENTITY_UPDATE) {
            return;
        }

        apply_update(node,r-l+1);

        if (l != r) {
            int left_child = 2 * node + 1;
            int right_child = 2 * node + 2;
            combine_lazy(left_child, lazy[node]);
            combine_lazy(right_child, lazy[node]);
        }

        lazy[node] = IDENTITY_UPDATE;
    }

    void update(int node, int l, int r, int lq, int rq, int val) {
        push(node, l, r);

        if (r < lq || l > rq) {
            return;
        }

        if (l >= lq && r <= rq) {
            combine_lazy(node, val); 
            push(node, l, r);        
            return;
        }

        int mid = l + (r - l) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        update(left_child, l, mid, lq, rq, val);
        update(right_child, mid + 1, r, lq, rq, val);

        push(left_child, l, mid);
        push(right_child, mid + 1, r);
        st[node] = combine(st[left_child], st[right_child]);
    }

    int query(int node, int l, int r, int lq, int rq) {
        push(node, l, r);

        if (r < lq || l > rq) {
            return IDENTITY_ELEMENT; 
        }

        if (l >= lq && r <= rq) {
            return st[node]; 
        }

        int mid = l + (r - l) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        int left_result = query(left_child, l, mid, lq, rq);
        int right_result = query(right_child, mid + 1, r, lq, rq);

        return combine(left_result, right_result);
    }

    int walk(int node, int l, int r, int k) {
        push(node, l, r);
        if (st[node] > k) return -1;
        if (l == r) return l;
        int mid = l + (r - l) / 2;
        int left_child = 2 * node + 1;
        int right_child = 2 * node + 2;
        push(left_child, l, mid);
        push(right_child, mid + 1, r);
        if (st[left_child] <= k)
            return walk(left_child, l, mid, k);
        else
            return walk(right_child, mid + 1, r, k);
    }

public:

    void range_update(int l, int r, int val) {
        if (l > r) return;
        update(0, 0, n - 1, l, r, val);
    }

    int range_query(int l, int r) {
        if (l > r) return IDENTITY_ELEMENT;
        return query(0, 0, n - 1, l, r);
    }

    int walker(int k) {
        return walk(0, 0, n - 1, k);
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