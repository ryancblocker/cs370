//Dependencies
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <queue>
#include <sstream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Process {
    int id;
    int burstTime;
    int arrivalTime;
};

struct CompareBurstTime {
    bool operator()(Process const& p1, Process const& p2) {
        // Return true if p1 should come after p2
        return p1.burstTime > p2.burstTime;
    }
};

void firstComeFirstServe(vector<vector<int>> data) {

    //sort data table by arrive time
    sort(data.begin(), data.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1]; //set which var to sort by
    });

    vector<int> wt(data.size(), 0); //wait time
    vector<int> tat(data.size(), 0); //turnaround time

    float total_tat = 0; //total time
    float total_wt = 0; //total wait time

    int current_time = 0; //set current time

    for(size_t i = 0; i < data.size(); ++i) { //go from the first P in the list to the last P
        if(i == 0 || current_time < data[i][1]) { //if its the first process or the current time is less than new P's arrival time
            current_time = data[i][1]; //set current time equal to the current P arrvial time to account for gaps in arrival time
        }
        wt[i] = current_time - data[i][1]; //wait time for the new process is euqal to the current time - the new arrival time
        current_time += data[i][2]; // current time is equal to the current time + the amount of time the P runs for (burst)
        tat[i] = wt[i] + data[i][2]; //turnaround time is equal to the wait time + the amount of time the process runs for (wait + process time)
        total_wt += wt[i]; //the toal wait time is equal to the total wait time + and new wait times for each new process (total time += new wait times)
        total_tat += tat[i]; //turnaround time is eual to the total turnaround time plus any new turnaround times that come in (total tat += new tat times)
    }

    float avg_wt = total_wt / data.size(); //the average wait time is the total wait time divided by the total # of P's
    float avg_tat = total_tat / data.size(); //average turnaround time is the total turnaround time divided by the total # of P's

    int total_time = current_time - data[0][1]; //the total time is euqal to the current time minus the start of the first arrival time (getting rid of excess time where no process was running)
    float throughput = static_cast<float>(data.size()) / total_time; //throughput for each P or the time for each P to run is the total # of P's divided by the total time

    //set sig figs and return results
    cout << fixed << setprecision(3);
    cout << "\n--- FCFS ---\n";
    cout << "Average Turnaround Time (1098.400): " << avg_tat << "\n";
    cout << "Average Waiting Time (1075.100): " << avg_wt << "\n";
    cout << "Throughput (0.043): " << throughput << "\n\n";
}

void shortestJobFirst(const vector<vector<int>>& data) {
    
    sort(data.begin(), data.end(), [](const vector<int>& a, const vector<int>& b) {
        return a[1] < b[1];
    });

    priority_queue <int, vector<int>, greater<int>> pq;
    vector<int> remainingBurstTime;
    vector<int> arrivalTime;
    vector<int> completionTime;
    vector<int> totalWaitingTime;
    vector<bool> hasArrived;

    for(size_t i = 0; i < data.size(); ++i) {
        remainingBurstTime[i] = data[i][2];
        arrivalTime[i] = data[i][1];
        completionTime[i] = 0;
        totalWaitingTime[i] = 0;
        hasArrived[i] = false;
    }

    int currentTime = data[0][1];
    int currentProcessId = -1;

    // while there are unfinished processes:
    while(!data.empty()) {
            for(size_t i = 0; i < data.size()-1; ++i) {
                currentProcessId = i;    
                if(arrivalTime[i] <= currentTime && !hasArrived[i]) {
                    pq.push(data[currentProcessId]);
                    hasArrived[i] = true;
                } 
                if(currentProcessId != -1) {
                    remainingBurstTime[currentProcessId] -= 1;
                    if(remainingBurstTime[currentProcessId] == 0) {
                        completionTime[currentProcessId] = currentTime;
                        currentProcessId = -1;
                    }
                }
                if(!pq.empty()) {
                    data[currentProcessId + 1] = pq.top();
                    if (currentProcessId == -1 or remainingBurstTime[i + 1] < remainingBurstTime[currentProcessId]) {
                        if(currentProcessId != -1) {
                            pq.push({currentProcessId, arrivalTime[currentProcessId], remainingBurstTime[currentProcessId]});
                        }
                        currentProcessId = i + 1;
                    }
                }

            // Preemption check
            if (!pq.empty()) {
                currentProcessId + 1 = pq.top();
                if (currentProcessId == -1 || remainingBurstTime[i + 1] < remainingBurstTime[currentProcessId]) {
                    if(currentProcessId != -1) {
                        pq.push({currentProcessId, arrivalTime[currentProcessId], remainingBurstTime[currentProcessId]});
                    }
                    currentProcessId = i + 1;
                    pq.pop();
                }
            }
            }
            for(size_t i = 0; i < pq.size(); i ++) {
                totalWaitingTime[i] += 1;
            }
            currentTime += 1;
    }

    // // All processes are finished, calculate metrics
    float totalTurnaroundTime = 0;
    float totalWaitingTimeSum = 0;

    for(size_t i = 0; i < pq.size(); i ++) {
        float turnaroundTime = completionTime[i] - arrivalTime[i];
        totalTurnaroundTime += turnaroundTime;
        totalWaitingTimeSum += totalWaitingTime[i];
    }    

    float averageTurnaroundTime = totalTurnaroundTime / data.size()-1;
    float averageWaitingTime = totalWaitingTimeSum / data.size()-1;
    float throughput = data.size()-1; / (currentTime - arrivalTime[0]);

    cout << fixed << setprecision(3);
    cout << "\n--- SJF ---\n";
    cout << "Average Turnaround Time: " << averageTurnaroundTime << "\n";
    cout << "Average Waiting Time: " << averageWaitingTime << "\n";
    cout << "Throughput: " << throughput << "\n\n";

}

int main(int argc, char* argv[]) {
    
    //ERROR CHECK 1: Did not provide input file
    if(argc != 2 || argc > 3) {
        cerr << "\nERROR 1: You did not provide an input argument. Please provide only one file for testing.\n\n";
        exit(1);
    }
    
    //open given file
    ifstream inputFile;
    inputFile.open(argv[1]);

    //ERROR CHECK 2: Did not provide input file
    if(!inputFile.is_open()) {
        cerr << "\nERROR 2: The file (" << argv[1] << ") provided could not be opened.\n\n";
        exit(2);
    }

    //create data vector
    vector<vector<int>> data;
    string line;
    
    //read file into datalists
    while (getline(inputFile, line)) {
        vector<int> row;
        stringstream lineStream(line);
        string cell;

        while(getline(lineStream, cell, ',')) {
            row.push_back(stoi(cell));
        }

        data.push_back(row);
    }

    //ERROR CHECK 3: Data Table is Empty
    if(data.empty()) {
        cerr << "\nERROR 3: The data table is empty. Check your input file.\n\n";
        exit(3);
    }

    //run algorithms with data table
    firstComeFirstServe(data);
    //shortestJobFirst(data);
    //priorityScheduling(data);

    inputFile.close();
    return 0;

}