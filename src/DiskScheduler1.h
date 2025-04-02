#ifndef DISKSCHEDULER_H
#define DISKSCHEDULER_H

#include <vector>

class DiskScheduler {
public:
    std::vector<int> requests;
    int head, disk_size;

    DiskScheduler(std::vector<int> req, int h, int ds);

    void FCFS();
    void SSTF();
    void SCAN();
    void CSCAN();
};

#endif

