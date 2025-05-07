#include <bits/stdc++.h>
#include <sstream>
using namespace std;

int f;
string line;

void print(int ref, bool fault, vector<int>& frames) {
   cout << left << setw(12) << ref << setw(12) << (fault ? "YES" : "NO");
   for (auto& fr : frames) cout << fr << " ";
   cout << "\n";
}

void fifo(vector<int>& refs) {
   queue<int> q;
   unordered_set<int> st;
   vector<int> frames;
   int faults = 0;

   cout << "\nFIFO Page Replacement:\n";
   cout << left << setw(12) << "Reference" << setw(12) << "Page Fault" << "Frames\n";

   for (auto& page : refs) {
      bool fault = !st.count(page);
      if (fault) {
         if (frames.size() == f) {
            int removed = q.front(); q.pop();
            st.erase(removed);
            frames.erase(frames.begin());
         }
         ++faults;
         q.push(page);
         st.insert(page);
         frames.push_back(page);
      }
      print(page, fault, frames);
   }
   cout << "Total Page Faults: " << faults << "\n";
}

void lru(vector<int>& refs) {
   vector<int> frames;
   int faults = 0;

   cout << "\nLRU Page Replacement:\n";
   cout << left << setw(12) << "Reference" << setw(12) << "Page Fault" << "Frames\n";

   for (auto& page : refs) {
      auto it = find(frames.begin(), frames.end(), page);
      bool fault = (it == frames.end());
      if (fault) {
         if (frames.size() == f)
            frames.erase(frames.begin());
         ++faults;
         frames.push_back(page);
      } else {
         frames.erase(it);
         frames.push_back(page);
      }
      print(page, fault, frames);
   }
   cout << "Total Page Faults: " << faults << "\n";
}

void optimal(vector<int>& refs) {
   vector<int> frames;
   int faults = 0;

   cout << "\nOptimal Page Replacement:\n";
   cout << left << setw(12) << "Reference" << setw(12) << "Page Fault" << "Frames\n";

   for (int i = 0; i < refs.size(); ++i) {
      int page = refs[i];
      auto it = find(frames.begin(), frames.end(), page);
      bool fault = (it == frames.end());

      if (fault) {
         if (frames.size() == f) {
            int farthest = -1, index = -1;
            for (int j = 0; j < frames.size(); ++j) {
               int k;
               for (k = i + 1; k < refs.size(); ++k) {
                  if (refs[k] == frames[j]) break;
               }
               if (k > farthest) {
                  farthest = k;
                  index = j;
               }
            }
            frames[index] = page;
         } else {
            frames.push_back(page);
         }
         ++faults;
      }
      print(page, fault, frames);
   }
   cout << "Total Page Faults: " << faults << "\n";
}

void secondchance(vector<int>& refs) {
   cout << "\nSecond Chance Page Replacement:\n";
   cout << left << setw(12) << "Reference" << setw(12) << "Page Fault" << "Frames\n";

   queue<int> q;
   vector<int> frames;
   unordered_map<int, bool> refBit;
   int faults = 0;

   for (auto& page : refs) {
      bool fault = !refBit.count(page);
      if (fault) {
         while (1) {
            int front = q.front(); q.pop();
            if (refBit[front]) {
               refBit[front] = false;
               q.push(front);
            } else {
               refBit.erase(front);
               frames.erase(find(frames.begin(), frames.end(), front));
               break;
            }
         }
         q.push(page);
         refBit[page] = false;
         frames.push_back(page);
         ++faults;
      } else
      {
         refBit[page] = true;
      }
      print(page, fault, frames);
   }

   cout << "Total Page Faults: " << faults << "\n";
}

int main() {
   cout << "Enter the number of frames: ";
   cin >> f;
   cin.ignore();

   cout << "Enter the reference string (space separated): ";
   getline(cin, line);
   istringstream iss(line);

   vector<int> refs;
   int x;
   while (iss >> x) refs.push_back(x);

   fifo(refs);
   lru(refs);
   optimal(refs);
   secondchance(refs);

   return 0;
}
