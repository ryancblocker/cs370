#include <iostream>
using namespace std;

//non-preemtive scheduling

// Algorithm for FCFS Scheduling
// The waiting time for the first process is 0 as it is executed first.
// The waiting time for the upcoming process can be calculated by:
// wt[i] =  ( at[i – 1] + bt[i – 1] + wt[i – 1] ) – at[i]

// where 

// wt[i] = waiting time of current process 
// at[i-1] = arrival time of previous process 
// bt[i-1] = burst time of previous process 
// wt[i-1] = waiting time of previous process 
// at[i] = arrival time of current process 

//So

//waiting time of currProcess = (arrival time of previous process + burst time of previous process + waiting time of previous process) - arrival time of current process

//Average Waiting Time = (sum of all waiting time)/(Number of processes)

// 0. <process id>, 1. <arrival time>, 2. <burst duration>, 3. <priority>


void firstComeFirstServe( vector<vector<int> > data) {

    int wt[100]; //waiting time array
    wt[0] = 0; //set first process wait to 0

    //calculate wait time for each process
    for(size_t i = 0; i < data.size(); i++) {
        
        if(i == 0) { //for the first process
            wt[i] = (data[i][1] + data[i][2] + wt[i]) - data[i][1];  //waiting time = (p_arrivetime + p_bursttime + p_waittime) - curr_arrivetime
        }
        else {
            wt[i] = (data[i - 1][1] + data[i - 1][2] + wt[i - 1]) - data[i][1];  //waiting time = (p_arrivetime + p_bursttime + p_waittime) - curr_arrivetime
        }
        
    }

    float averageWait;
    float totalWaitTime = 0;
    float totalTime;
    float throughput;

    //calculate average wait time
    for(size_t i = 0; i < data.size(); i++) {
        totalWaitTime = totalWaitTime + wt[i];
    }

    averageWait = totalWaitTime / data.size();

    //Calculate turnaround
    totalTime = data[data.size()-1][1] + data[data.size()-1][2];

    //calculate process throughput
    throughput = data.size() / totalTime;

    //print out results
    cout << fixed;
    cout << "\n\n--- FCFS ---\n";
    cout << setprecision(3) << "Average Turnaround Time (4.200): " << totalTime << "\n";
    cout << setprecision(3) << "Average Waiting Time (1.200): " << averageWait << "\n";
    cout << setprecision(3) << "Throughput (0.333): " << throughput << "\n\n";
}
