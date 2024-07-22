#include <iostream>
#include <thread>
#include <semaphore.h>
#include <vector>
#include <unistd.h>

sem_t semaphore;

void worker(int id) {
    std::cout << "Worker " << id << " waiting to access the resource.\n";
    sem_wait(&semaphore);  // Wait operation
    std::cout << "Worker " << id << " accessing the resource.\n";
    sleep(1);  // Simulate resource usage
    std::cout << "Worker " << id << " releasing the resource.\n";
    sem_post(&semaphore);  // Signal operation
}

int main() {
    const int num_workers = 5;
    sem_init(&semaphore, 0, 2);  // Initialize semaphore with value 2 (resource limit)

    std::vector<std::thread> workers;
    for (int i = 0; i < num_workers; ++i) {
        workers.emplace_back(worker, i);
    }

    for (auto& worker : workers) {
        worker.join();
    }

    sem_destroy(&semaphore);  // Destroy semaphore
    return 0;
}
