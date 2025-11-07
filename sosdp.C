const int m=(1ll<<20);
void solve(){
    int n;
    cin>>n;
    vector<int> dp(m,0);
    for(int i=0;i<n;i++){
        int a;
        cin>>a;
        dp[a]++;
    }
    for(int i=0;i<20;i++){
        for(int mask=0;mask<m;mask++){ //this is to iterate over supermast
            if((mask&(1ll<<i))==0){ //for submask we just need to negate the condition
                dp[mask]+=dp[mask^(1ll<<i)];
            }
        }
    }
    Z ans=0;
    int mx=(1ll<<20);
    for(int i=0;i<mx;i++){ //this is inclusion exclusion, just remember that such things can be done
        if(__builtin_parity(i)){//after all its just dp
            ans-=(P.pow(dp[i])-1);
        }
        else{
            ans+=(P.pow(dp[i])-1);
        }
    }
    cout<<ans<<"\n";
}

//this is to get random integer in range form [l,r] inclusive
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}