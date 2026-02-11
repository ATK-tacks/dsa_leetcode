
struct LazyTag {
    int add = 0;

    void merge(const LazyTag &other) {
        add += other.add;
    }

    bool isEmpty() const {
        return add == 0;
    }

    void clear() {
        add = 0;
    }
};

struct SegmentTreeNode {
    int minv = 0;   // minimum prefix sum
    int maxv = 0;   // maximum prefix sum
    LazyTag lazy;
};

class SegmentTree {
    int n;
    vector<SegmentTreeNode> tree;

    void build(const vector<int> &data, int l, int r, int idx) {
        if (l == r) {
            tree[idx].minv = tree[idx].maxv = data[l - 1];
            return;
        }

        int mid = (l + r) >> 1;
        build(data, l, mid, idx << 1);
        build(data, mid + 1, r, idx << 1 | 1);
        pullUp(idx);
    }

    void apply(int idx, const LazyTag &tag) {
        tree[idx].minv += tag.add;
        tree[idx].maxv += tag.add;
        tree[idx].lazy.merge(tag);
    }

    void pushDown(int idx) {
        if (!tree[idx].lazy.isEmpty()) {
            apply(idx << 1, tree[idx].lazy);
            apply(idx << 1 | 1, tree[idx].lazy);
            tree[idx].lazy.clear();
        }
    }

    void pullUp(int idx) {
        tree[idx].minv = min(tree[idx << 1].minv, tree[idx << 1 | 1].minv);
        tree[idx].maxv = max(tree[idx << 1].maxv, tree[idx << 1 | 1].maxv);
    }

    void rangeAdd(int ql, int qr, const LazyTag &tag, int l, int r, int idx) {
        if (ql <= l && r <= qr) {
            apply(idx, tag);
            return;
        }

        pushDown(idx);
        int mid = (l + r) >> 1;

        if (ql <= mid) rangeAdd(ql, qr, tag, l, mid, idx << 1);
        if (qr > mid)  rangeAdd(ql, qr, tag, mid + 1, r, idx << 1 | 1);

        pullUp(idx);
    }

    int query(int ql, int qr, int target, int l, int r, int idx) {
        if (tree[idx].minv > target || tree[idx].maxv < target)
            return -1;

        if (l == r) return l;

        pushDown(idx);
        int mid = (l + r) >> 1;

        // search right first
        if (qr > mid) {
            int res = query(ql, qr, target, mid + 1, r, idx << 1 | 1);
            if (res != -1) return res;
        }

        if (ql <= mid)
            return query(ql, qr, target, l, mid, idx << 1);

        return -1;
    }

public:
    SegmentTree(const vector<int> &prefix) {
        n = prefix.size();
        tree.resize(4 * n + 4);
        build(prefix, 1, n, 1);
    }

    void add(int l, int r, int value) {
        if (l > r) return;
        LazyTag tag;
        tag.add = value;
        rangeAdd(l, r, tag, 1, n, 1);
    }

    int findLast(int start, int value) {
        if (start > n) return -1;
        return query(start, n, value, 1, n, 1);
    }
};

class Solution {
    int parity(int x) {
        return (x & 1) == 0 ? 1 : -1;
    }

public:
    int longestBalanced(vector<int>& nums) {
        int n = nums.size();

        unordered_map<int, queue<int>> positions;
        vector<int> prefix(n);

        prefix[0] = parity(nums[0]);
        positions[nums[0]].push(1);

        for (int i = 1; i < n; i++) {
            prefix[i] = prefix[i - 1];

            auto &q = positions[nums[i]];
            if (q.empty()) {
                prefix[i] += parity(nums[i]);
            }
            q.push(i + 1);
        }

        SegmentTree segTree(prefix);
        int best = 0;

        for (int left = 0; left < n; left++) {

            int right = segTree.findLast(left + best + 1, 0);
            if (right != -1) {
                best = max(best, right - left);
            }

            auto &q = positions[nums[left]];
            q.pop();

            int nextPos = q.empty() ? n + 1 : q.front();
            segTree.add(left + 1, nextPos - 1, -parity(nums[left]));
        }

        return best;
    }
};
