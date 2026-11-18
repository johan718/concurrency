#include <cstdint>
#include <iostream>
#include <syncstream>
#include <thread>

using std::cout;
using std::endl;
using std::osyncstream;
using std::thread;

struct func 
{
    int i;
    func(int i_) : i(i_) {}

    void operator() () const
    {
        for (uint32_t j = 0; j < 100'000; ++j)
            // cout << i << ": " << j << '\n';
            // Use osyncstream to ensure that the output from different threads does not interleave
            std::osyncstream(std::cout) << i << ": " << j << '\n';

        // cout << endl;
        std::osyncstream(std::cout) << i << ": done" << endl;
    }
};

int main() 
{
    thread t1(func(1));
    thread t2(func(2));
    thread t3(func(3));
    thread t4(func(4));

    // When you detach, make sure you're not referencing any local variables in the thread function, 
    // as they may go out of scope before the thread finishes executing.
    // Also, if you detach a thread, you still need to ensure that the main thread doesn't exit before 
    // the detached thread has finished executing, as this can lead to undefined behavior.
    t1.join();
    t2.join();
    t3.join();
    t4.join();

    return 0;
}