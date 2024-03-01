#include <iostream>
#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
using namespace std;

class ThreadPool {
public:
    static ThreadPool& getInstance() {
        static ThreadPool instance;
        return instance;
    }

    void init(size_t numThreads) {
        for (size_t i = 0; i < numThreads; ++i) {
            threads.emplace_back([this] {
                while (true) {
                    function<void()> task;
                    {
                        unique_lock<std::mutex> lock(mutex);
                        condition.wait(lock, [this] { return !tasks.empty() || stop; });
                        if (stop && tasks.empty()) {
                            return;
                        }
                        task = move(tasks.front());
                        tasks.pop();
                    }
                    task();
                }
            });
        }
    }

    void addTask(function<void()> task) {
        {
            unique_lock<std::mutex> lock(mutex);
            tasks.push(move(task));
        }
        condition.notify_one();
    }

    void shutdown() {
        {
            unique_lock<std::mutex> lock(mutex);
            stop = true;
        }
        condition.notify_all();
        for (thread& thread : threads) {
            if (thread.joinable()) {
                thread.join();
            }
        }
    }

private:
    ThreadPool() : stop(false) {}
    ~ThreadPool() { shutdown(); }

    ThreadPool(const ThreadPool&) = delete;
    ThreadPool& operator=(const ThreadPool&) = delete;

    vector<thread> threads;
    queue<function<void()>> tasks;
    mutex mutex;
    condition_variable condition;
    bool stop;
};

void sampleTask1() {
    cout << "\nSample Task 1 executed by thread " << this_thread::get_id() << endl;
}

void sampleTask2() {
    cout << "\n\nSample Task 2 executed by thread " << this_thread::get_id() << endl;
}

int main() {
    //Single instance of ThreadPool containing 4 threads is created.
    ThreadPool& threadPool = ThreadPool::getInstance();
    threadPool.init(4);

    threadPool.addTask(sampleTask1);
    threadPool.addTask(sampleTask2);

    this_thread::sleep_for(chrono::seconds(1));

    threadPool.shutdown();

    return 0;
}
