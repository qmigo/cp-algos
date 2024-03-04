#include<bits/stdc++.h>
using namespace std;

#define cin fin
#define cout fout
const string kInputFilename = "../io/input.txt";
const string kOutputFilename = "../io/output.txt";
ifstream fin(kInputFilename);
ofstream fout(kOutputFilename);


// Implemented a Segment tree
// set **def_val** as
// 1. INT_MIN max query
// 2. INT_MAX min query
// 3. 0       sum query
class SegmentTree {
    public:
    vector<int> seg;
    vector<int> v;
    int def_val;
    SegmentTree(vector<int>&v, int def_val) {
        int n = v.size();
        this->v = v;
        this->def_val = def_val;
        seg.resize(4*n, def_val);
        build(0, 0, n-1);
    }
    void build(int idx, int l, int r) {
        if(l==r) {
            seg[idx] = v[l];
            return;
        }
        int m = l+(r-l)/2;
        build(idx*2+1, l,m);
        build(idx*2+2,m+1,r);

        // max query
        if(def_val==INT_MIN)
        seg[idx] = max(seg[idx*2+1], seg[idx*2+2]);

        // min query
        else if(def_val==INT_MAX) 
        seg[idx] = min(seg[idx*2+1], seg[idx*2+2]);

        // sum query
        else 
        seg[idx] = seg[idx*2+1]+ seg[idx*2+2];

    }
    void update(int idx, int low, int high, int pos, int val) {
        if(low==high) {
            seg[idx] = val;
            return;
        }
        int mid = low+(high-low)/2;
        if(pos<=mid) {
            update(idx*2+1, low, mid, pos, val);
        } else {
            update(idx*2+2, mid+1, high, pos, val);
        }

        // max query
        if(def_val==INT_MIN)
        seg[idx] = max(seg[idx*2+1], seg[idx*2+2]);

        // min query
        else if(def_val==INT_MAX) 
        seg[idx] = min(seg[idx*2+1], seg[idx*2+2]);

        // sum query
        else 
        seg[idx] = seg[idx*2+1]+ seg[idx*2+2];
        
    }
    int query(int idx, int low, int high, int l, int r) {
        
        if(l<=low and high<=r) return seg[idx];
        
        if(r<low or high<l)return def_val;
        
        int mid = low+(high-low)/2;
        
        int left = query(idx*2+1, low, mid, l,r);
        int right = query(idx*2+2, mid+1, high, l, r);
        
        // max query
        if(def_val==INT_MIN)
        return max(left, right);

        // min query
        else if(def_val==INT_MAX)
        return min(left, right);

        // sum query
        return left+right;
    }

    void show() {
        for(auto&i:seg)cout<<i<<" ";
        cout<<"\n";
    }
};

int main() {
    int n;
    cin>>n;
    vector<int> arr(n);
    for(int i=0;i<n;i++)cin>>arr[i];
    SegmentTree st = SegmentTree(arr, INT_MIN);
    st.show();
    int q;
    cin>>q;
    while(q--) {
        // t=0 update
        // t=1 query
        int t;
        cin>>t;
        if(t==0) {
            int pos, val;
            cin>>pos>>val;
            st.update(0,0,n-1,pos,val);
        } else {
            int l, r;
            cin>>l>>r;
            cout<<st.query(0, 0, n-1, l, r)<<"\n";
        }
    }
}