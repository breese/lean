#include "test_assert.hpp"
#include <thread>
#include <lean/atomic.hpp>

#if LEAN_CXX <= LEAN_LIB_ATOMIC_WAIT

//-----------------------------------------------------------------------------

namespace atomic_wait_suite
{

void wait_ready()
{
    bool old = false;
    lean::atomic<bool> shared{ old };

    shared.store(true);
    shared.notify_one();

    shared.wait(old);
    assert(shared.load() == true);
}

void threaded_wait()
{
    bool old = false;
    lean::atomic<bool> shared{ old };

    std::thread thread(
        [&] {
            std::this_thread::yield();
            shared.store(true);
            shared.notify_one();
        });

    shared.wait(old);
    assert(shared.load() == true);

    thread.join();
}

void threaded_wait_post_join()
{
    bool old = false;
    lean::atomic<bool> shared{ old };

    std::thread thread(
        [&] {
            shared.store(true);
            shared.notify_one();
        });
    thread.join();

    shared.wait(old);
    assert(shared.load() == true);
}

void run()
{
    wait_ready();
    threaded_wait();
    threaded_wait_post_join();
}

} // namespace atomic_wait_suite

//-----------------------------------------------------------------------------

int main()
{
    atomic_wait_suite::run();
    return 0;
}

#else

int main () { return 0; }

#endif
