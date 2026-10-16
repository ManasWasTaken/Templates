#include <iostream>
#include <set>
using namespace std;

struct Trie {
	Trie *children[2] = {};
	int cnt = 0;  // # of numbers with this bit
};

void add(Trie *root, int x) {
	Trie *cur = root;
	for (int i = 30; i >= 0; i--) {
		bool has_bit = x & (1 << i);
		if (cur->children[has_bit] == NULL) {
			cur->children[has_bit] = new Trie;
		}
		cur->children[has_bit]->cnt++;
		cur = cur->children[has_bit];
	}
}

void remove(Trie *root, int x) {
	Trie *cur = root;
	for (int i = 30; i >= 0; i--) {
		bool has_bit = x & (1 << i);
		cur->children[has_bit]->cnt--;
		cur = cur->children[has_bit];
	}
}

int query(Trie *root, int x) {
	Trie *cur = root;
	int res = 0;
	for (int i = 30; i >= 0; i--) {
		bool has_bit = x & (1 << i);
		if (cur->children[has_bit] != NULL && cur->children[has_bit]->cnt > 0) {
			// we go down the same bit
			cur = cur->children[has_bit];
		} else {
			/*
			 * we go down a different bit,
			 * xor increases by 2^i
			 */
			cur = cur->children[!has_bit];
			res += 1 << i;
		}
	}
	return res;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	Trie tr;
	int q;
	cin >> q;
	set<int> s;
	for (int qry = 0; qry < q; qry++) {
		int t, x;
		cin >> t >> x;
		if (t == 0) {
			if (!s.count(x)) {
				s.insert(x);
				add(&tr, x);
			}
		} else if (t == 1) {
			if (s.count(x)) {
				s.erase(x);
				remove(&tr, x);
			}
		} else {
			cout << query(&tr, x) << "\n";
		}
	}
}