#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt;
};

vector<process> p;
int n;

void SRTF_Algo()
{
    sort(p.begin(), p.end(), [](process a, process b)
         { return a.at < b.at; });

    vector<int> rt(n), ct(n), tat(n), wt(n);
    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    int complete = 0, curr_time = 0, idx = -1, min_rt = INT_MAX;
    vector<int> gantt;

    while (complete < n)
    {
        idx = -1;
        min_rt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= curr_time && rt[i] > 0 && rt[i] < min_rt)
            {
                min_rt = rt[i];
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

        // Execute process for 1 unit of time
        rt[idx]--;
        curr_time++;

        // If completed
        if (rt[idx] == 0)
        {
            complete++;
            ct[idx] = curr_time;
            tat[idx] = ct[idx] - p[idx].at;
            wt[idx] = tat[idx] - p[idx].bt;
        }
    }

    double total_tat = 0, total_wt = 0;
    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        total_tat += tat[i];
        total_wt += wt[i];
        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
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

    cout << "Enter PID AT BT:\n";
    for (int i = 0; i < n; i++)
        cin >> p[i].pid >> p[i].at >> p[i].bt;

    SRTF_Algo();
}
