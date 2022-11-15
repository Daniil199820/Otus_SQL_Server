#include <string>
#include <thread>
#include <atomic>
#include <mutex>
#include <condition_variable>
#include <queue>

class Client_require{
public:
    using TTask = std::function<void()>;
	using TCallback = std::function<void()>;

    Client_require():m_stopped{false}{
        worker_thread = std::thread(&Client_require::process,this);
    }

    void add_task(const std::string& str_){
        std::lock_guard<std::mutex> guard(worker_mutex);
    }


private:
    std::thread worker_thread;
    std::atomic<bool> m_stopped;
    std::mutex worker_mutex;
    std::condition_variable wait_worker;
    std::queue<std::pair<TTask, TCallback>> m_tasks;

    void process(){
        while(m_stopped==false){
            
        }   
    }
};