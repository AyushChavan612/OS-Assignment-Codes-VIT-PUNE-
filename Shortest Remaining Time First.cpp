#include<bits/stdc++.h>
using namespace std;

struct process
{
	int no, at, bt, rt, ct, tat, wt;
};

int main()
{
	int n;
	cout << "Enter the nuber of process : ";
	cin >> n;

	vector<process> p(n);

	for (int i = 0; i < n; ++i)
	{
		cout << "Enter the arrival time of process " << i+1 << " : ";
		cin >> p[i].at;
		cout << "Enter the burst time of process " << i+1 << " : ";
		cin >> p[i].bt;
		p[i].rt = p[i].bt;
		p[i].no = i + 1;
	}

	int curr_time = 0 , completed = 0 , avg_tat_time = 0 , avg_wt_time = 0;
	while (completed < n)
	{
		bool found = false;
		int min_index = -1 , min_value = 1e9;
		for (int i = 0; i < n; ++i)
		{
			if (p[i].at <= curr_time && p[i].rt > 0 && p[i].rt < min_value)
			{
				found = true;
				min_index = i;
				min_value = p[i].rt;
			}
		}

		if (!found)
		{
			curr_time++;
			continue;
		}

		p[min_index].rt--;
		curr_time++;

		if (p[min_index].rt == 0)
		{
			++completed;
			p[min_index].ct = curr_time;
			p[min_index].tat = p[min_index].ct - p[min_index].at;
			p[min_index].wt = p[min_index].tat - p[min_index].bt;
			avg_wt_time += p[min_index].wt;
			avg_tat_time += p[min_index].tat;
		}
	}

	cout << "Average waiting time : " << avg_wt_time << endl;
	cout << "Average turn around time : " << avg_tat_time << endl;

	cout << left << setw(12)  << "Process No." << setw(8) << "AT" << setw(8) << "BT" << setw(8) << "CT" << setw(8) << "TAT" << setw(8) << "WT" << endl;

	for (int i = 0; i < n; ++i)
	{
		cout << left << setw(12) << p[i].no << setw(8) << p[i].at << setw(8) << p[i].bt << setw(8) << p[i].ct << setw(8) << p[i].tat << setw(8) << p[i].wt << endl;
	}

	for (int i = 0; i < n; ++i)
	{
		cout << " ";
		for (int j = 0; j < p[i].tat; ++j)
		{
			cout << "-";
		}
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

	cout << endl;
    int prev = 0;
	for(int i = 0; i < n; ++i)
	{
        cout << prev;
        for(int j = 0; j < p[i].tat; ++j)
        {
        	cout << " ";
        }

        prev += p[i].tat;
	}
    
    cout << prev << endl;


	return 0;
}