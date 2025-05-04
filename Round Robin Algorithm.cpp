#include<bits/stdc++.h>
using namespace std;

struct process
{
   int no , at , bt , ct, rt , tat , wt;
};

int main()
{
   int n , time_quant;
   cout << "Enter number of process : ";
   cin >> n;

   vector<process> p(n);
   float curr_time = 0 , avg_wt_time = 0 , avg_tat_time = 0;

   for (int i = 0; i < n; ++i)
   {
      p[i].no = i + 1;
      cout << "Enter arrival time for " << i + 1 << " process : ";
      cin >> p[i].at;
      cout << "Enter burst time for " << i + 1 << " process : ";
      cin >> p[i].bt;
      p[i].rt = p[i].bt;
   }

   cout << "Enter Time quantaum : ";
   cin >> time_quant;

   sort(p.begin(), p.end(), [](process a , process b) {
      return a.at < b.at;
   });

   cout << left << setw(12) << "Process no"
        << setw(8) << "AT"
        << setw(8) << "BT"
        << setw(8) << "CT"
        << setw(8) << "TAT"
        << setw(8) << "WT" << endl;

   queue<process> queue;
   vector<int> visited(n,0);
   int completed = 0;
   vector<process> gant;

   while(completed < n)
   {
       for(int i = 0; i < n; ++i)
       {
          if(p[i].at <= curr_time && !visited[i] && p[i].rt > 0)
          {
              queue.push(p[i]);
              visited[i] = 1;
          }
       }

       if(queue.empty())
       {
         ++curr_time;
         continue;
       }

       auto node = queue.front();
       queue.pop();

       int time = min(node.rt , time_quant);
       curr_time += time;
       node.rt -= time;

       for(int i = 0; i < n; ++i)
       {
          if(p[i].at <= curr_time && !visited[i] && p[i].rt > 0)
          {
             visited[i] = 1;
             queue.push(p[i]);
          }
       }

       if(node.rt == 0)
       {
           node.ct = curr_time;
           node.tat = curr_time - node.at;
           node.wt = node.tat - node.bt;
           avg_wt_time += node.wt;
           avg_tat_time += node.tat;
           ++completed;
           cout << left << setw(12) << node.no
           << setw(8) << node.at
           << setw(8) << node.bt
           << setw(8) << node.ct
           << setw(8) << node.tat
           << setw(8) << node.wt << endl;
           gant.push_back(node);
       } 
       else
       {
          queue.push(node);
       }
   }
  
   cout << endl;
   cout << "Average waiting Time : " << avg_wt_time / n << endl;
   cout << "Average Turn around Time : " << avg_tat_time / n << endl;
   cout << endl << endl;

   cout << "Gant chart" << endl;

   for (int i = 0; i < n; ++i)
   {
      cout << " ";
      for (int j = 0; j < gant[i].tat; ++j)
      {
         cout << "-";
      }
      // cout << " ";
   }

   cout << endl;

   for (int i = 0; i < n; ++i)
   {
      cout << "|";
      for (int j = 0; j < gant[i].tat; ++j)
      {
         if (j == gant[i].tat / 2)
         {
            cout << "P" << gant[i].no;
            ++j;
            continue;
         }
         cout << " ";
      }
   }

   cout << "|" << endl;

   for (int i = 0; i < n; ++i)
   {
      cout << " ";
      for (int j = 0; j < gant[i].tat; ++j)
      {
         cout << "-";
      }
   }

   cout << endl;
   
   int prev = 0;
   for(int i = 0; i < n; ++i)
   {
        cout << prev;
        for(int j = 0; j < gant[i].tat; ++j)
        {
            cout << " ";
        }

        prev += gant[i].ct;
   }

   cout << prev << endl;

   return 0;
}