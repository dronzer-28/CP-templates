class ST{
    vector<int> seg, lazy;
public:
    ST(int n){
        seg.resize(4*n);
        lazy.resize(4*n);
    }

    void build(int ind, int low, int high, int arr[]){
        if(low == high){
            seg[ind] = arr[low];
            return;
        }

        int mid = (low+high) >> 1;
        build(2*ind+1, low, mid, arr);
        build(2*ind+2, mid+1, high, arr);

        seg[ind] = seg[2*ind+1] + seg[2*ind+2];
    }

    void update(int ind, int low, int high, int l, int r, int val){
        //update previous remaining updates and propagate down
        if(lazy[ind] != 0){
            seg[ind] += (high - low + 1)*lazy[ind];
            if(low !=high){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        //no overlap low high l r or l r low high
        if(high < l || r < low){
            return;
        }
        //complete overlap  l low high r
        if(l<=low && high<=r){
            seg[ind] += (high-low+1)*val;
            if(low!=high){
                lazy[2*ind+1] += val;
                lazy[2*ind+2] += val;
            }
            return;
        }
        //partial overlap
        int mid = (low+high) >> 1;
        update(2*ind+1, low, mid, l, r, val);
        update(2*ind+2, mid+1, high, l, r, val);
        seg[ind] = seg[2*ind+1] + seg[2*ind+2];
    }

    int query(int ind, int low, int high, int l, int r){
         //update previous remaining updates and propagate down
        if(lazy[ind] != 0){
            seg[ind] += (high - low + 1)*lazy[ind];
            if(low !=high){
                lazy[2*ind+1] += lazy[ind];
                lazy[2*ind+2] += lazy[ind];
            }
            lazy[ind] = 0;
        }

        // no overlap
        if(high < l || r < low){
            return 0;
        }
        // complete overlap
        if(l<=low && high<=r){
            return seg[ind];
        }
        // partial overlap
        int mid = (low+high) >> 1;
        int left = query(2*ind+1, low, mid, l, r);
        int right = query(2*ind+2, mid+1, high, l, r);
        return left+right;
    }
};
