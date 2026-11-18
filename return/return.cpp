// Returning threads and passing them
#include "func.h"

thread f()
{
    return thread(func(5));
}

thread g()
{
    thread t(func(6));
    return t;
}

void h(thread t)
{
    t.join();
    osyncstream(std::cout) << "Thread joined in h()" << endl;
}

void j()
{
    h(thread(func(7)));
    thread t(func(8));
    h(std::move(t));
}

int main()
{
    thread t1 = f();
    osyncstream(std::cout) << "t1 thread created in main()" << endl;
    thread t2 = g();
    osyncstream(std::cout) << "t2 thread created in main()" << endl;
    thread t3(func(9));
    osyncstream(std::cout) << "t3 thread created in main()" << endl;
    thread t4(func(10));
    osyncstream(std::cout) << "t4 thread created in main()" << endl;

    t1.join();
    osyncstream(std::cout) << "t1 Thread joined in main()" << endl;
    t2.join();
    osyncstream(std::cout) << "t2 Thread joined in main()" << endl;
    t3.join();
    osyncstream(std::cout) << "t3 Thread joined in main()" << endl;
    t4.join();
    osyncstream(std::cout) << "t4 Thread joined in main()" << endl;

    // We wait for t1 to t4 to finish before calling j().
    j();

    return 0;
}