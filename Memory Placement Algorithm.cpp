#include<bits/stdc++.h>
using namespace std;

void print(vector<int> allocate,vector<int> process)
{
    int n = process.size();
     for(int i = 0; i < n; ++i)
     {
         cout << "Process " << i+1 << " of size " << process[i] << " alloctaed at block : " << allocate[i] << endl;
     }
}

vector<int> firstFit(vector<int> process , vector<int> blocks)
{
   int n = process.size() , m = blocks.size();;
   vector<int> allocate(n,-1);
   for(int i = 0; i < n; ++i)
   {
      for(int j = 0; j < m; ++j)
      {
          if(process[i] <= blocks[j])
          {
             allocate[i] = j;
             blocks[j] -= process[i];
             break;
          }
      }
   }
   return allocate;
}

vector<int> nextFit(vector<int> process , vector<int> blocks)
{
    vector<int> alloc(process.size(), -1);
    int last = 0, n = blocks.size();
    for (int i = 0; i < process.size(); ++i) {
        int cnt = 0, j = last;
        while (cnt++ < n) {
            if (blocks[j] >= process[i]) {
                alloc[i] = j;
                blocks[j] -= process[i];
                last = j;
                break;
            }
            j = (j + 1) % n;
        }
    }
    return alloc;
}

vector<int> bestFit(vector<int> process , vector<int> blocks)
{
   int n = process.size() , m = blocks.size();;
   vector<int> allocate(n,-1);
   for(int i = 0; i < n; ++i)
   {
      int best = -1;
      for(int j = 0; j < m; ++j)
      {
          if(process[i] <= blocks[j] && (best == -1 || blocks[best] > blocks[j]))
          {
             best = j;
          }
      }

      if(best != -1)
      {
         allocate[i] = best;
         blocks[best] -= process[i];
      }
   }
   return allocate;
}

vector<int> worstFit(vector<int> process , vector<int> blocks)
{
   int n = process.size() , m = blocks.size();;
   vector<int> allocate(n,-1);
   for(int i = 0; i < n; ++i)
   {
      int worst = -1;
      for(int j = 0; j < m; ++j)
      {
          if(process[i] <= blocks[j] && (worst == -1 || blocks[worst] < blocks[j]))
          {
             worst = j;
          }
      }

      if(worst != -1)
      {
         allocate[i] = worst;
         blocks[worst] -= process[i];
      }
   }
   return allocate;
}

int main()
{
   vector<int> process , blocks;
   int n , m;
   cout << "Enter the number of process : ";
   cin >> n;
   cout << "Enter the numbers of memory blocks : ";
   cin >> m;

   cout << "Enter process size : ";
   for(int i = 0; i < n; ++i)
   {
      int x; cin >> x;
      process.push_back(x);
   }

   cout << "Enter memory blocks sizes : ";
   for(int i = 0; i < m; ++i)
   {
      int x; cin >> x;
      blocks.push_back(x);
   }

   cout << "First Fit allcoation : " << endl;
   print(firstFit(process,blocks),process);
   cout << "Next Fit allcoation : " << endl;
   print(nextFit(process,blocks),process);
   cout << "Best Fit allcoation : " << endl;
   print(bestFit(process,blocks),process);
   cout << "Worst Fit allcoation : " << endl;
   print(worstFit(process,blocks),process);


   return 0;
}