#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt, pr;
};

vector<process> p;
int n;

void Priority_NonPreemptive()
{
    sort(p.begin(), p.end(), [](process a, process b)
         { return a.at < b.at; });

    vector<int> ct(n), tat(n), wt(n);
    vector<bool> done(n, false);
    vector<int> gantt; // To store the process id for Gantt chart

    int completed = 0, curr_time = 0;

    while (completed < n)
    {
        int idx = -1;
        int best_pr = INT_MAX; // lower priority number means higher priority

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && p[i].at <= curr_time && p[i].pr < best_pr)
            {
                best_pr = p[i].pr;
                idx = i;
            }
        }

        // If no process arrived yet, increase time
        if (idx == -1)
        {
            curr_time++;
            continue;
        }

            gantt.push_back(p[idx].pid);

        // Execute whole burst at once (non-preemptive)
        curr_time += p[idx].bt;
        ct[idx] = curr_time;
        tat[idx] = ct[idx] - p[idx].at;
        wt[idx] = tat[idx] - p[idx].bt;

        done[idx] = true;
        completed++;
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

    cout << "Enter PID AT BT PRIORITY (lower = higher priority):\n";
    for (int i = 0; i < n; i++)
        cin >> p[i].pid >> p[i].at >> p[i].bt >> p[i].pr;

    Priority_NonPreemptive();
}
