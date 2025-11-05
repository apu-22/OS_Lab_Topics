#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt, pr;
};

vector<process> p;
int n;

void Priority_Preemptive()
{
    sort(p.begin(), p.end(), [](process a, process b)
         { return a.at < b.at; });

    vector<int> rt(n), ct(n), tat(n), wt(n);
    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;  

    vector<int> gantt; 
    int completed = 0, curr_time = 0;

    while (completed < n)
    {
        int idx = -1;
        int best_pr = INT_MAX;

        // Pick the highest priority process among arrived ones
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= curr_time && rt[i] > 0 && p[i].pr < best_pr)
            {
                best_pr = p[i].pr;
                idx = i;
            }
        }

        if (idx == -1)
        {
            curr_time++;
            continue;
        }

        gantt.push_back(p[idx].pid);

        // Execute selected process for 1 unit
        rt[idx]--;
        curr_time++;

        // If finished
        if (rt[idx] == 0)
        {
            completed++;
            ct[idx] = curr_time;
            tat[idx] = ct[idx] - p[idx].at;
            wt[idx] = tat[idx] - p[idx].bt;
        }
    }

    double total_tat = 0, total_wt = 0;

    cout << "PID\tAT\tBT\tPR\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        total_tat += tat[i];
        total_wt += wt[i];

        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t" << p[i].pr
             << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "Average TAT: " << total_tat / n << "\n";
    cout << "Average WT: " << total_wt / n << "\n";

    // Gantt Chart Print
    cout << "\nGantt Chart (Timeline):\n";
    for (int x : gantt)
        cout << "P" << x << " ";
    cout << "\n";
}

int main()
{
    cout << "Enter number of processes:\n";
    cin >> n;
    p.resize(n);

    cout << "Enter PID AT BT PRIORITY (lower value = higher priority):\n";
    for (int i = 0; i < n; i++)
        cin >> p[i].pid >> p[i].at >> p[i].bt >> p[i].pr;

    Priority_Preemptive();
}
