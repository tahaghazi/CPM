#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <queue>
#include <optional>
using namespace std;

struct Task {
    string name;
    int duration;
    int earliestStart = 0;
    int earliestFinish = 0;
    int latestStart = 0;
    int latestFinish = 0;
};

class CPM {
private:
    map<string, Task> tasks;
    map<string, vector<string>> graph;
    map<string, vector<string>> predecessors;

public:
    void addTask(const string& name, int duration, const vector<string>& preds) {
        tasks[name] = {name, duration};
        predecessors[name] = preds;
        for (const string& pred : preds) {
            graph[pred].push_back(name);
        }
    }

    void calculate() {
        auto topoOrder = topologicalSort();

        // Calculate earliest start and finish times
        for (const string& taskName : topoOrder) {
            auto& task = tasks[taskName];
            for (const string& pred : predecessors[taskName]) {
                task.earliestStart = max(task.earliestStart, tasks[pred].earliestFinish);
            }
            task.earliestFinish = task.earliestStart + task.duration;
        }

        // Calculate latest start and finish times
        int projectDuration = tasks[topoOrder.back()].earliestFinish;
        for (auto it = topoOrder.rbegin(); it != topoOrder.rend(); ++it) {
            auto& task = tasks[*it];
            task.latestFinish = projectDuration;
            for (const string& succ : graph[*it]) {
                task.latestFinish = min(task.latestFinish, tasks[succ].latestStart);
            }
            task.latestStart = task.latestFinish - task.duration;
        }
    }

    vector<string> getCriticalPath() {
        vector<string> criticalPath;
        for (const auto& [name, task] : tasks) {
            if (task.earliestStart == task.latestStart) {
                criticalPath.push_back(name);
            }
        }
        return criticalPath;
    }

    void displayTasks() {
        cout << "Task\tDuration\tES\tEF\tLS\tLF\n";
        for (const auto& [_, task] : tasks) {
            cout << task.name << "\t   " << task.duration << "\t\t"
                 << task.earliestStart << "\t" << task.earliestFinish << "\t"
                 << task.latestStart << "\t" << task.latestFinish << "\n";
        }
    }

    void displayAllPaths() {
        vector<string> path;
        int totalDuration = 0;
        for (const auto &[name, _]: tasks) {
            if (predecessors[name].empty()) {
                findPaths(name, path, totalDuration);
            }
        }
    }

private:
    vector<string> topologicalSort() {
        map<string, int> inDegree;
        for (const auto& [name, _] : tasks) {
            inDegree[name] = 0;
        }
        for (const auto& [_, successors] : graph) {
            for (const string& succ : successors) {
                inDegree[succ]++;
            }
        }

        queue<string> q;
        for (const auto& [name, degree] : inDegree) {
            if (degree == 0) {
                q.push(name);
            }
        }

        vector<string> order;
        while (!q.empty()) {
            string task = q.front();
            q.pop();
            order.push_back(task);
            for (const string& succ : graph[task]) {
                if (--inDegree[succ] == 0) {
                    q.push(succ);
                }
            }
        }
        return order;
    }

    void findPaths(const string &current, vector<string> &path, int totalDuration) {
        path.push_back(current);
        totalDuration += tasks[current].duration;

        if (graph[current].empty()) {
            // Leaf node
            cout << "Path: ";
            for (size_t i = 0; i < path.size(); ++i) {
                cout << path[i];
                if (i < path.size() - 1) cout << " -> ";
            }
            cout << ", Duration: " << totalDuration << "\n";
        } else {
            for (const string &succ: graph[current]) {
                findPaths(succ, path, totalDuration);
            }
        }

        path.pop_back();
    }
};

int main() {
    CPM cpm;
    cout << "Enter activities, their predecessors (comma-separated), and duration.\n";
    cout << "Format: Activity, Predecessors, Duration\n";
    cout << "Example: a,,1 (activity 'a' with no predecessors and duration 1)\n";
    cout << "Enter 'done' to finish input.\n";

    string line;
    while (true) {
        cout << "Enter task details: ";
        getline(cin, line);
        if (line == "done") break;

        stringstream ss(line);
        string activity, preds, durationStr;
        getline(ss, activity, ',');
        getline(ss, preds, ',');
        getline(ss, durationStr, ',');

        vector<string> predecessors;
        stringstream predsStream(preds);
        string pred;
        while (getline(predsStream, pred, ' ')) {
            if (!pred.empty()) {
                predecessors.push_back(pred);
            }
        }

        try {
            int duration = stoi(durationStr);
            cpm.addTask(activity, duration, predecessors);
        } catch (exception&) {
            cerr << "Invalid input format. Please try again.\n";
        }
    }

    cpm.calculate();
    cpm.displayTasks();

    cout << "All Paths and their Durations:\n";
    cpm.displayAllPaths();

    auto criticalPath = cpm.getCriticalPath();
    cout << "Critical Path: ";
    for (size_t i = 0; i < criticalPath.size(); ++i) {
        cout << criticalPath[i];
        if (i < criticalPath.size() - 1) {
            cout << " -> ";
        }
    }
    cout << endl;

    return 0;
}
