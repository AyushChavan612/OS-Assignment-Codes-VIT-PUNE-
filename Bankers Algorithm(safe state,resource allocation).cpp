#include <bits/stdc++.h>
using namespace std;

int P, R;
vector<vector<int>> allocate, need, max_need;
vector<int> available;

bool issafe(vector<int> &safe_seq) {
    int completed = 0;
    vector<int> work = available;
    vector<int> finished(P, 0);
    safe_seq.clear();

    while (completed < P) {
        bool found = false;

        for (int i = 0; i < P; ++i) {
            if (!finished[i]) {
                bool can_allocate = true;
                for (int j = 0; j < R; ++j) {
                    if (need[i][j] > work[j]) {
                        can_allocate = false;
                        break;
                    }
                }

                if (can_allocate) {
                    for (int j = 0; j < R; ++j) {
                        work[j] += allocate[i][j];
                    }
                    safe_seq.push_back(i);
                    finished[i] = 1;
                    completed++;
                    found = true; 
                }
            }
        }

        if (!found) {
            return false;
        }
    }

    return true;
}

bool Request_Resources(vector<int> &req, int num) {
    --num; 

    for (int i = 0; i < R; ++i) {
        if (req[i] > need[num][i]) {
            cout << "Request exceeds maximum claim." << endl;
            return false;
        }
        if (req[i] > available[i]) {
            cout << "Resources not available right now." << endl;
            return false;
        }
    }

    for (int i = 0; i < R; ++i) {
        available[i] -= req[i];
        allocate[num][i] += req[i];
        need[num][i] -= req[i];
    }

    vector<int> safe_seq;
    if (issafe(safe_seq)) {
        return true;
    } else {
        for (int i = 0; i < R; ++i) {
            available[i] += req[i];
            allocate[num][i] -= req[i];
            need[num][i] += req[i];
        }
        return false;
    }
}

int main() {
    cout << "Enter the number of Processes: ";
    cin >> P;
    cout << "Enter the number of Resources: ";
    cin >> R;

    allocate.assign(P, vector<int>(R, 0));
    max_need.assign(P, vector<int>(R, 0));
    need.assign(P, vector<int>(R, 0));
    available.resize(R);

    for (int i = 0; i < P; ++i) {
        cout << "Enter allocated resources for process " << i + 1 << ": ";
        for (int j = 0; j < R; ++j) {
            cin >> allocate[i][j];
        }
    }

    for (int i = 0; i < P; ++i) {
        cout << "Enter maximum resources needed for process " << i + 1 << ": ";
        for (int j = 0; j < R; ++j) {
            cin >> max_need[i][j];
        }
    }

    cout << "Enter the available resources: ";
    for (int i = 0; i < R; ++i) {
        cin >> available[i];
    }

    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < R; ++j) {
            need[i][j] = max_need[i][j] - allocate[i][j];
        }
    }

    vector<int> safe_seq;
    if (issafe(safe_seq)) {
        cout << "The system is in a safe state.\nSafe sequence: ";
        for (auto &p : safe_seq)
            cout << "P" << p + 1 << " ";
        cout << endl;
    } else {
        cout << "The system is not in a safe state." << endl;
        return 0;
    }

    while (true) {
        int choice;
        cout << "\n1. Request Resources\n2. Exit\nEnter choice: ";
        cin >> choice;

        if (choice == 2)
            break;

        int proc;
        cout << "Enter process number (1-based): ";
        cin >> proc;

        vector<int> req(R);
        cout << "Enter resource request: ";
        for (int i = 0; i < R; ++i) {
            cin >> req[i];
        }

        if (Request_Resources(req, proc)) {
            cout << "Resources have been allocated successfully." << endl;
        } else {
            cout << "Resources cannot be allocated. Request denied." << endl;
        }
    }

    return 0;
}
