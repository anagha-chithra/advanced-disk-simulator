#include <iostream>
#include <vector>
#include "DiskScheduler.h"

int main() {
    int num_requests, head, disk_size;
    std::cout << "Enter the number of disk requests: ";
    std::cin >> num_requests;

    std::vector<int> requests(num_requests);
    std::cout << "Enter the disk request sequence: ";
    for (int i = 0; i < num_requests; i++) {
        std::cin >> requests[i];
    }

    std::cout << "Enter the initial head position: ";
    std::cin >> head;

    std::cout << "Enter the total disk size: ";
    std::cin >> disk_size;

    DiskScheduler scheduler(requests, head, disk_size);

    std::cout << "\n--- Running Disk Scheduling Algorithms ---\n";
    scheduler.FCFS();
    scheduler.SSTF();
    scheduler.SCAN();
    scheduler.CSCAN();

    return 0;
}
#include <iostream>
#include <vector>
#include "DiskScheduler.h"

int main() {
    int num_requests, head, disk_size;
    std::cout << "Enter the number of disk requests: ";
    std::cin >> num_requests;

    std::vector<int> requests(num_requests);
    std::cout << "Enter the disk request sequence: ";
    for (int i = 0; i < num_requests; i++) {
        std::cin >> requests[i];
    }

    std::cout << "Enter the initial head position: ";
    std::cin >> head;

    std::cout << "Enter the total disk size: ";
    std::cin >> disk_size;

    DiskScheduler scheduler(requests, head, disk_size);

    std::cout << "\n--- Running Disk Scheduling Algorithms ---\n";
    scheduler.FCFS();
    scheduler.SSTF();
    scheduler.SCAN();
    scheduler.CSCAN();

    return 0;
}

