#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "DiskScheduler.h"

DiskScheduler::DiskScheduler(std::vector<int> req, int h, int ds) {
    requests = req;
    head = h;
    disk_size = ds;
}

// FCFS Algorithm
void DiskScheduler::FCFS() {
    int seek_time = 0, current_head = head;
    std::cout << "\nFCFS Order: " << current_head;
    for (int req : requests) {
        seek_time += std::abs(current_head - req);
        current_head = req;
        std::cout << " -> " << req;
    }
    std::cout << "\nTotal Seek Time: " << seek_time << " cylinders\n";
}

// SSTF Algorithm
void DiskScheduler::SSTF() {
    std::vector<int> remaining_requests = requests;
    int seek_time = 0, current_head = head;
    std::cout << "\nSSTF Order: " << current_head;

    while (!remaining_requests.empty()) {
        auto it = std::min_element(remaining_requests.begin(), remaining_requests.end(),
            [current_head](int a, int b) { return std::abs(a - current_head) < std::abs(b - current_head); });
        seek_time += std::abs(current_head - *it);
        current_head = *it;
        std::cout << " -> " << *it;
        remaining_requests.erase(it);
    }
    std::cout << "\nTotal Seek Time: " << seek_time << " cylinders\n";
}

// SCAN Algorithm
void DiskScheduler::SCAN() {
    int seek_time = 0, current_head = head;
    std::vector<int> left, right;
    
    for (int req : requests) {
        if (req < head) left.push_back(req);
        else right.push_back(req);
    }
    
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    
    std::cout << "\nSCAN Order: " << current_head;
    for (int req : right) {
        seek_time += std::abs(current_head - req);
        current_head = req;
        std::cout << " -> " << req;
    }
    if (current_head < disk_size - 1) {
        seek_time += std::abs(current_head - (disk_size - 1));
        std::cout << " -> " << (disk_size - 1);
        current_head = disk_size - 1;
    }
    for (auto it = left.rbegin(); it != left.rend(); ++it) {
        seek_time += std::abs(current_head - *it);
        current_head = *it;
        std::cout << " -> " << *it;
    }
    std::cout << "\nTotal Seek Time: " << seek_time << " cylinders\n";
}

// C-SCAN Algorithm
void DiskScheduler::CSCAN() {
    int seek_time = 0, current_head = head;
    std::vector<int> left, right;
    
    for (int req : requests) {
        if (req < head) left.push_back(req);
        else right.push_back(req);
    }
    
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());
    
    std::cout << "\nC-SCAN Order: " << current_head;
    for (int req : right) {
        seek_time += std::abs(current_head - req);
        current_head = req;
        std::cout << " -> " << req;
    }
    if (current_head < disk_size - 1) {
        seek_time += std::abs(current_head - (disk_size - 1));
        std::cout << " -> " << (disk_size - 1);
        current_head = disk_size - 1;
    }
    seek_time += (disk_size - 1);
    std::cout << " -> 0";
    current_head = 0;
    for (int req : left) {
        seek_time += std::abs(current_head - req);
        current_head = req;
        std::cout << " -> " << req;
    }
    std::cout << "\nTotal Seek Time: " << seek_time << " cylinders\n";
}

