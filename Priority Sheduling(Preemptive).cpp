#include<bits/stdc++.h>
using namespace std;

struct process
{
   int no , at , bt , prio, rt, ct , tat , wt;
};

int main()
{
   int n;
   cout << "Enter number of process : ";
   cin >> n;

   vector<process> p(n);
   int curr_time = 0 ;

   for (int i = 0; i < n; ++i)
   {
      p[i].no = i + 1;
      cout << "Enter arrival time for " << i + 1 << " process : ";
      cin >> p[i].at;
      cout << "Enter burst time for " << i + 1 << " process : ";
      cin >> p[i].bt;
      cout << "Enter Priority for " << i + 1 << " process : ";
      cin >> p[i].prio;
      p[i].rt = p[i].bt;
   }

   sort(p.begin(), p.end(), [](process a , process b) {
      return a.at < b.at;
   });

   cout << left << setw(12) << "Process no"
        << setw(8) << "AT"
        << setw(8) << "BT"
        << setw(8) << "CT"
        << setw(8) << "TAT"
        << setw(8) << "WT" << endl;


   int completed = 0 , avg_tat_time = 0 , avg_wt_time = 0;
   while (completed < n)
   {
      bool found = false;
      int min_index = -1 , min_value = 1e9;
      for (int i = 0; i < n; ++i)
      {
         if (p[i].at <= curr_time && p[i].rt > 0 && p[i].prio < min_value)
         {
            min_index = i;
            min_value = p[i].prio;
            found = true;
         }
      }

      if (!found)
      {
         curr_time++;
         continue;
      }

      curr_time++;
      p[min_index].rt--;

      if (p[min_index].rt == 0)
      {
         ++completed;
         p[min_index].ct = curr_time;
         p[min_index].tat = p[min_index].ct - p[min_index].at;
         p[min_index].wt = p[min_index].tat - p[min_index].bt;
         avg_wt_time += p[min_index].wt;
         avg_tat_time += p[min_index].tat;
         cout << left << setw(12) << p[min_index].no << setw(8) << p[min_index].at << setw(8) << p[min_index].bt << setw(8) << p[min_index].ct 
                                                                                   << setw(8) << p[min_index].tat << setw(8) << p[min_index].wt << endl;
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