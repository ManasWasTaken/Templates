// gives the longest existing palindrome in a string
string longestPalindrome(const string &s){
    string t = "#"; for(char c:s) t += c, t += '#';
    int n = t.size(), C = 0, R = 0, best = 0, center = 0;
    vector<int> arr(n,0);
    for(int i=0; i<n; i++){
        int mirr = 2*C-i;
        if(i<R) arr[i]=min(R-i,arr[mirr]);
        while(i+arr[i]+1<n && i-arr[i]-1>=0 && t[i+arr[i]+1]==t[i-arr[i]-1]) arr[i]++;
        if(i+arr[i]>R) C=i,R=i+arr[i];
        if(arr[i]>best) best=arr[i], center=i;
    }
    return s.substr((center-best)/2,best);
}

// Gives and int array with value of prefix match lengths
/*	 Z-FUNCTION USECASES
   Pattern Search:     z of (pat + '#' + txt)
   Prefix = Suffix:    max z[i] where i + z[i] == n
   Period Check:       smallest i with i + z[i] == n
   Rotation Check:     z of (b + '#' + a + a)
   String Similarity:  sum(z) + n
   Prefix Palindrome:  z of (s + '#' + rev(s))
   Prefix count:       count z[i] values == k		*/
vector<int> z_function(string s){
    int n = s.size(), l = 0, r = 0;
    vector<int> z(n);
    for(int i = 1; i < n; i++){
        if(i <= r){ z[i] = min(r - i + 1, z[i - l]);}
        while(i + z[i] < n && s[z[i]] == s[i + z[i]]){ z[i]++;}
        if(i + z[i] - 1 > r){ l = i, r = i + z[i] - 1;}
    }
    return z;
}

// prefix KMP function
/*   KMP ALGORITHM USECASES
   Pattern Search:     Find all indices where pattern P occurs in text T
   Prefix = Suffix:    lps.back() → length of longest prefix also a suffix
   Period Check:       if n % (n - lps[n-1]) == 0 → string is periodic
   Minimal Rotation:   minimal repeating block = n - lps[n-1]
   Overlapping Match:  detects overlaps (like "aaa" in "aaaaa")	*/
vector<int> build_lps(string &p) {
    int m = p.size();
    vector<int> lps(m);
    for (int i = 1, len = 0; i < m;) {
        if (p[i] == p[len]) lps[i++] = ++len;
        else if (len) len = lps[len - 1];
        else lps[i++] = 0;
    }
    return lps;
}
// Finds all starting positions of pattern P in text T
vector<int> kmp_search(string &t, string &p) {
    vector<int> lps = build_lps(p), occ;
    int n = t.size(), m = p.size();
    for (int i = 0, j = 0; i < n;) {
        if (t[i] == p[j]) i++, j++;
        if (j == m) occ.push_back(i - m), j = lps[j - 1];
        else if (i < n && t[i] != p[j])
            j ? j = lps[j - 1] : i++;
    }
    return occ;
}


/* ---------- SUFFIX ARRAY TEMPLATE ----------
    1. Pattern Search           -> binary_search() in SA
    2. Count Distinct Substrings -> n*(n+1)/2 - sum(LCP)
    3. Longest Repeated Substr. -> max(LCP)
    4. Lexicographically Smallest Rotation -> min index in SA for s+s
    5. Compare Substrings / Suffixes -> LCP + RMQ (optional)	*/
vector<int> build_suffix_array(const string &s) {
    string str = s + "$";
    int n = str.size();
    vector<int> sa(n), rank(n);
    // Initial sorting by single character
    for (int i = 0; i < n; i++) sa[i] = i, rank[i] = str[i];
    // k = length of prefix compared (1,2,4,8,...)
    for (int k = 1; k < n; k <<= 1) {
        auto cmp = [&](int a, int b) {
            if (rank[a] != rank[b]) return rank[a] < rank[b];
            int ra = (a + k < n ? rank[a + k] : -1);
            int rb = (b + k < n ? rank[b + k] : -1);
            return ra < rb;
        };
        sort(sa.begin(), sa.end(), cmp);
        vector<int> tmp(n);
        tmp[sa[0]] = 0;
        for (int i = 1; i < n; i++)
            tmp[sa[i]] = tmp[sa[i - 1]] + cmp(sa[i - 1], sa[i]);
        rank = tmp;
        if (rank[sa.back()] == n - 1) break;
    }
    sa.erase(sa.begin()); // remove '$'
    return sa;
}
// ---------- BUILD LCP ARRAY (Kasai Algorithm) ----------
vector<int> build_lcp(const string &s, const vector<int> &sa) {
    int n = s.size(), k = 0;
    vector<int> rank(n, 0), lcp(n - 1, 0);
    for (int i = 0; i < n; i++) rank[sa[i]] = i;

    for (int i = 0; i < n; i++) {
        if (rank[i] == n - 1) { k = 0; continue; }
        int j = sa[rank[i] + 1];
        while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
        lcp[rank[i]] = k;
        if (k) k--;
    }
    return lcp;
}


// Booth returns index where lexographically minimal rotation string form
int booth(string s) {
    s += s;
    int n = s.size(), i = 0, j = 1, k = 0;
    while (i < n / 2 && j < n / 2 && k < n / 2) {
        if (s[i + k] == s[j + k]) k++;
        else if (s[i + k] > s[j + k]) {
            i = max(i + k + 1, j + 1);
            k = 0;
        } else {
            j = max(j + k + 1, i + 1);
            k = 0;
        }
    }
    return min(i, j);
}



