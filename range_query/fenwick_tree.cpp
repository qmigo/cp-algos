#include<bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
const string kInputFilename = "../io/input.txt";
const string kOutputFilename = "../io/output.txt";
ifstream fin(kInputFilename);
ofstream fout(kOutputFilename);

class FenwickTree {
    
    public:
    vector<int> A;
    
    void create_tree(vector<int>&v) {
        int n = v.size();
        A.resize(n+1,0);
        
        for(int i=1;i<=n;i++) {
            add(i,v[i-1]);
        }
    }

    void add(int idx, int val) {
        int n = A.size();
        for(int j=idx;j<n;j+=(j&-j)) {
                A[j] += val;
            }
    }

    int query(int r) {
        int sum = 0;
        for(;r>0;r-=(r&-r)) {
            sum+=A[r];
        }
        return sum;
    }

    void show() {
        for(int i=1;i<A.size();i++)cout<<A[i]<<" ";
        cout<<"\n";
    }
};

int main() {
    int n;
    cin>>n;
    vector<int> A(n);
    for(int i=0;i<n;i++)cin>>A[i];
    FenwickTree ft = FenwickTree();
    ft.create_tree(A);
    ft.show();
    int q;
    cin>>q;
    while(q--) {
        int ty;
        cin>>ty;
        if(ty==0) {
            int pos, val;
            cin>>pos>>val;
            ft.add(pos+1, -A[pos]);
            ft.add(pos+1, val);
        }
        else {
            int l,r;
            cin>>l>>r;
            cout<<ft.query(r+1)-ft.query(l)<<"\n";
        }
    }
}