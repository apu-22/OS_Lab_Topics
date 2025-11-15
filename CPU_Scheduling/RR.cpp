
#include <bits/stdc++.h>
using namespace std;

struct process
{
    int pid, at, bt;
};

vector<process> p;
int n, tq;

void Round_Robin()
{
    vector<int> rt(n), ct(n), tat(n), wt(n), start(n, -1);
    for (int i = 0; i < n; i++)
        rt[i] = p[i].bt;

    queue<int> q;
    vector<bool> inQueue(n, false);
    vector<tuple<int,int,int>> gantt; // {pid, start, end}

    int curr_time = 0, completed = 0;

    sort(p.begin(), p.end(), [](process a, process b){
        return a.at < b.at;
    });

    q.push(0);
    inQueue[0] = true;

    while (completed < n)
    {
        if (q.empty())
        {
            curr_time++;
            for (int i = 0; i < n; i++)
            {
                if (!inQueue[i] && rt[i] > 0 && p[i].at <= curr_time)
                {
                    q.push(i);
                    inQueue[i] = true;
                }
            }
            continue;
        }

        int idx = q.front();
        q.pop();

        if (start[idx] == -1)
            start[idx] = curr_time;

        int exec_time = min(rt[idx], tq);
        gantt.push_back({p[idx].pid, curr_time, curr_time + exec_time});

        rt[idx] -= exec_time;
        curr_time += exec_time;

        for (int i = 0; i < n; i++)
        {
            if (!inQueue[i] && rt[i] > 0 && p[i].at <= curr_time)
            {
                q.push(i);
                inQueue[i] = true;
            }
        }

        if (rt[idx] == 0)
        {
            completed++;
            ct[idx] = curr_time;
            tat[idx] = ct[idx] - p[idx].at;
            wt[idx] = tat[idx] - p[idx].bt;
        }
        else
            q.push(idx);
    }

    vector<int> resp(n);
    for (int i = 0; i < n; i++)
        resp[i] = start[i] - p[i].at;

    double total_tat = 0, total_wt = 0, total_rt = 0;

    cout << "\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n";
    for (int i = 0; i < n; i++)
    {
        total_tat += tat[i];
        total_wt += wt[i];
        total_rt += resp[i];

        cout << p[i].pid << "\t" << p[i].at << "\t" << p[i].bt << "\t"
             << ct[i] << "\t" << tat[i] << "\t" << wt[i]
             << "\t" << resp[i] << "\n";
    }

    cout << "\nAverage TAT: " << total_tat / n << "\n";
    cout << "Average WT:  " << total_wt / n << "\n";
    cout << "Average RT:  " << total_rt / n << "\n";

    // Gantt Chart Print
    cout << "\nGantt Chart:\n";
    cout << "-------------------------------------------------\n";
    for (auto &g : gantt)
        cout << "|  P" << get<0>(g) << "  ";
    cout << "|\n";

    cout << "0";
    for (auto &g : gantt)
        cout << "      " << get<2>(g);
    cout << "\n-------------------------------------------------\n";
}

int main()
{
    cout << "Enter number of processes:\n";
    cin >> n;
    p.resize(n);

    cout << "Enter PID AT BT:\n";
    for (int i = 0; i < n; i++)
        cin >> p[i].pid >> p[i].at >> p[i].bt;

    cout << "Enter Time Quantum:\n";
    cin >> tq;

    Round_Robin();
}
