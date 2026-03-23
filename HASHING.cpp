#include "bits/stdc++.h"

#pragma GCC optimize("Ofast")

using namespace std;

#define int long long

vector<int>mods = {(int)1e9 + 7,998244353,100'000'037,(int)1e9 + 9};
vector<int>bases = {67,71,17,41,43,57};

int N = mods.size();

vector<vector<int>>P,R,deg;

void build1(int &mod,int &base,string &s,int &n){

    vector<int>p(n),r(n),d(n+1);

    d[0] = 1;

    for(int i=1;i<=n;i++)
        d[i] = d[i-1] * base % mod;

    auto build = [&](vector<int>&p){
        p[0] = s[0] - 'a' + 1;

        for(int i=1;i<n;++i)
            p[i] = (p[i-1] * base + s[i] - 'a' + 1)%mod;
    };

    build(p);
    reverse(s.begin(),s.end());
    build(r);

    P.push_back(p);
    R.push_back(r);
    deg.push_back(d);

}

int get_c(int l,int r,int &mod,int &ind_base){

    if(!l)return P[ind_base][r];

    return (P[ind_base][r] - P[ind_base][l-1] * deg[ind_base][r - l + 1] % mod + mod) % mod;
}

int get_r(int l,int r,int &mod,int &ind_base){

    if(!l)return R[ind_base][r];

    return (R[ind_base][r] - R[ind_base][l-1] * deg[ind_base][r - l + 1] % mod + mod) % mod;
}

bool check(int &n,int &l,int &r,int &mod,int &ind_base){
    return get_c(l,r,mod,ind_base) == get_r(n-r-1,n-l-1,mod,ind_base);
}

void build(int &n,string &s){
    
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    shuffle(bases.begin(),bases.end(),rng);

    P.clear();
    R.clear();
    deg.clear();


    for(int i=0;i<N;i++)
        build1(mods[i],bases[i],s,n);
}

bool CHECK(int l,int r,int n){
    bool ok = 1;

    for(int i=0;i<N;i++)
        ok &= check(n,l,r,mods[i],i);

    return ok;
}