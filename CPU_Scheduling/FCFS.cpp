
#include <bits/stdc++.h>
using namespace std;
int n;

struct process
{
    int pid, at, bt;
};

void FCFS_Algo(vector<process> &proc)
{
    sort(proc.begin(), proc.end(), [](process a, process b)
         { return a.at < b.at; });

    vector<int> wt(n), tat(n), ct(n);
    int total_wt = 0, total_tat = 0, curr_time = 0;

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++)
    {
        if (curr_time < proc[i].at)
            curr_time = proc[i].at;

        curr_time += proc[i].bt;
        ct[i] = curr_time;
        tat[i] = ct[i] - proc[i].at;
        total_tat += tat[i];

        wt[i] = tat[i] - proc[i].bt;
        total_wt += wt[i];

        cout << proc[i].pid << "\t" << proc[i].at << "\t" << proc[i].bt << "\t" << ct[i] << "\t" << tat[i] << "\t" << wt[i] << "\n";
    }

    cout << "Average TAT is: " << (float)total_tat / n << "\n";
    cout << "Average WT is: " << (float)total_wt / n << "\n";
}

int main()
{
    cout << "Enter the number of processes:\n";
    cin >> n;
    vector<process> proc(n);

    cout << "PID, AT, BT:\n";
    for (int i = 0; i < n; i++)
    {
        cin >> proc[i].pid >> proc[i].at >> proc[i].bt;
    }

    FCFS_Algo(proc);
}