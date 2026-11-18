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
        for (uint32_t j = 0; j < 100; ++j)
            // cout << i << ": " << j << '\n';
            // Use osyncstream to ensure that the output from different threads does not interleave
            std::osyncstream(std::cout) << i << ": " << j << '\n';

        // cout << endl;
        std::osyncstream(std::cout) << i << ": done" << endl;
    }
};