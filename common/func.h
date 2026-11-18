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
        for (uint32_t j = 0; j < 1'000'000; ++j)
            // cout << i << ": " << j << '\n';
            // Use osyncstream to ensure that the output from different threads does not interleave
            if (j % 1'000 == 0)
                std::osyncstream(std::cout) << i << ": " << j << '\n';

        // cout << endl;
        std::osyncstream(std::cout) << i << ": done" << endl;
    }
};