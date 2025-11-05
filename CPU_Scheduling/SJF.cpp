
#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt;
};

vector<process> p;
vector<int> gantt_chat;
int n;

void SJF_Algo()
{
    sort(p.begin(), p.end(), [](process a, process b)
         { return a.at < b.at; });

    vector<int> ct(n), tat(n), wt(n);
    vector<bool> done(n, false);

    // gantt_chat.resize(n);
    int total_tat = 0, total_wt = 0, curr_time = 0;
    int com = 0;

    cout << "PID\tAT\tBT\tCT\tTAT\tWT\n";

    while (com < n)
    {
        int idx = -1;
        int min_bt = INT_MAX;

        for (int i = 0; i < n; i++)
        {
            if (!done[i] && p[i].at <= curr_time && p[i].bt < min_bt)
            {
                min_bt = p[i].bt;
                idx = i;
            }
        }

        if (idx == -1)
        {
            curr_time++;
            continue;
        }
        gantt_chat.push_back(p[idx].pid);

        curr_time += p[idx].bt;
        ct[idx] = curr_time;
        tat[idx] = ct[idx] - p[idx].at;
        wt[idx] = tat[idx] - p[idx].bt;

        total_tat += tat[idx];
        total_wt += wt[idx];

        cout << p[idx].pid << "\t" << p[idx].at << "\t" << p[idx].bt << "\t" << ct[idx] << "\t" << tat[idx] << "\t" << wt[idx] << "\n";
        com++;
        done[idx] = true;
    }

    cout << "The avg TAT is: " << (double)total_tat / n << "\n";
    cout << "The avg WT is: " << (double)total_wt / n << "\n\n";

    cout << "Gnatt Chat is: | ";
    for (int i : gantt_chat)
    {
        cout << i << ", ";
    }
    cout << "|\n";
}
int main()
{
    cout << "Enter the number of process:\n";
    cin >> n;
    cout << "Enter process id,at,bt:\n";
    p.resize(n);
    for (int i = 0; i < n; i++)
    {
        cin >> p[i].pid >> p[i].at >> p[i].bt;
    }

    SJF_Algo();
}