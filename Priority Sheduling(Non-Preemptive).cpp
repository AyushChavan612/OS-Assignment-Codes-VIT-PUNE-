#include<bits/stdc++.h>
using namespace std;

struct process
{
   int no , at , bt , prio, ct , tat , wt;
};

int main()
{
   int n;
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
      cout << "Enter Priority for " << i + 1 << " process : ";
      cin >> p[i].prio;
   }

   sort(p.begin(), p.end(), [](process a , process b) {
      return a.prio < b.prio;
   });


   for (int i = 0; i < n - 1; ++i)
   {
      if (curr_time < p[i].at)
      {
         curr_time = p[i].at;
      }

      curr_time += p[i].bt;
      p[i].ct = curr_time;
      p[i].tat = p[i].ct - p[i].at;
      p[i].wt = p[i].tat - p[i].bt;
      avg_wt_time += p[i].wt;
      avg_tat_time += p[i].tat;
   }


   cout << left << setw(12) << "Process no"
        << setw(8) << "AT"
        << setw(8) << "BT"
        << setw(8) << "CT"
        << setw(8) << "TAT"
        << setw(8) << "WT" << endl;

   for (int i = 0; i < n; ++i) {
      if (curr_time < p[i].at) {
         curr_time = p[i].at;
      }

      curr_time += p[i].bt;
      p[i].ct = curr_time;
      p[i].tat = p[i].ct - p[i].at;
      p[i].wt = p[i].tat - p[i].bt;

      avg_wt_time += p[i].wt;
      avg_tat_time += p[i].tat;

      cout<<left<<setw(12)<<p[i].no<<setw(8)<<p[i].at<<setw(8)<<p[i].bt<<setw(8)<<p[i].ct<<setw(8)<<p[i].tat<<setw(8)<<p[i].wt<<endl;
   }

   cout << endl;
   cout << "Average waiting Time : " << avg_wt_time / n << endl;
   cout << "Average Turn around Time : " << avg_tat_time / n << endl;
   cout << endl << endl;

   cout << "Gant chart" << endl;

   for (int i = 0; i < n; ++i)
   {
      cout << " ";
      for (int j = 0; j < p[i].tat; ++j)
      {
         cout << "-";
      }
      // cout << " ";
   }

   cout << endl;

   for (int i = 0; i < n; ++i)
   {
      cout << "|";
      for (int j = 0; j < p[i].tat; ++j)
      {
         if (j == p[i].tat / 2)
         {
            cout << "P" << p[i].no;
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
      for (int j = 0; j < p[i].tat; ++j)
      {
         cout << "-";
      }
   }

   return 0;
}