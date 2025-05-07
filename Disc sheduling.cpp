#include <bits/stdc++.h>
using namespace std;

int n, pos;
vector<int> seq;

void print(vector<int>& Seq) {
    cout << "Execution Sequence: ";
    for (auto x : Seq) {
        cout << x << " -> ";
    }
    cout << "end\n";
}

void FCFS() {
    cout << "\n[FCFS]\n";
    vector<int> ans = {pos};
    for (auto x : seq)
        ans.push_back(x);
    print(ans);
}

void SSTF() {
    cout << "\n[SSTF]\n";
    vector<int> pending = seq;
    vector<int> order = {pos};
    int curr = pos;

    while (!pending.empty()) {
        auto it = min_element(pending.begin(), pending.end(), [&](int a, int b) {
            return abs(a - curr) < abs(b - curr);
        });
        curr = *it;
        order.push_back(curr);
        pending.erase(it);
    }

    print(order);
}

void SCAN() {
    cout << "\n[SCAN]\n";
    vector<int> all = seq;
    all.push_back(pos);
    sort(all.begin(), all.end());

    vector<int> order;
    auto it = find(all.begin(), all.end(), pos);
    int index = distance(all.begin(), it);

    for (int i = index; i >= 0; --i)
        order.push_back(all[i]);

    for (int i = index + 1; i < all.size(); ++i)
        order.push_back(all[i]);

    print(order);
}

void C_SCAN() {
    cout << "\n[C-SCAN]\n";
    vector<int> all = seq;
    all.push_back(pos);
    sort(all.begin(), all.end());

    vector<int> order;
    auto it = find(all.begin(), all.end(), pos);
    int index = distance(all.begin(), it);

    for (int i = index; i < all.size(); ++i)
        order.push_back(all[i]);

    for (int i = 0; i < index; ++i)
        order.push_back(all[i]);

    print(order);
}

int main() {
    cout << "Size of queue: ";
    cin >> n;

    cout << "Enter the elements of the queue: ";
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        seq.push_back(x);
    }

    cout << "Enter initial head position: ";
    cin >> pos;

    FCFS();
    SSTF();
    SCAN();
    C_SCAN();

    return 0;
}
