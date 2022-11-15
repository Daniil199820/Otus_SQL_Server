#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class Client_require{
public:
    using TTask = std::function<void()>;
	using TCallback = std::function<void()>;

    Client_require():m_stopped{false}{
        worker_thread = std::thread(&Client_require::process,this);
    }


    void add_task(const std::string& command_str){
        {
        std::lock_guard<std::mutex> guard(worker_mutex);
        m_tasks.push(command_str);
        }
        wait_worker.notify_all();
    }


private:
    std::thread worker_thread;
    std::atomic<bool> m_stopped;
    std::mutex worker_mutex;
    std::condition_variable wait_worker;
    std::queue<std::string> m_tasks;

    void process(){
        while(m_stopped==false){
            std::unique_lock<std::mutex> locker(worker_mutex);
            wait_worker.wait(locker,[&](){return !m_tasks.empty()||m_stopped==true;});
            std::string temp_command = m_tasks.front();
            m_tasks.pop();
            locker.unlock();
        }   
    }
};