#include <iostream>
#include <mutex>
#include <thread>

// Multi-threaded counting towards a value

int g_i = 0;
int iterations = 5;
std::mutex g_i_mutex;  // protects g_i

static void safe_increment()
{
	std::lock_guard<std::mutex> lock(g_i_mutex);
	++g_i;

	std::cout << std::this_thread::get_id() << ": " << g_i << '\n';
}

static void increment() {
	std::lock_guard<std::mutex> lock(g_i_mutex);
	for (int i = 0; i < iterations; i++) {
		g_i++;
		std::cout << g_i << "\n";
	}
}

static void decrement() {
	std::lock_guard<std::mutex> lock(g_i_mutex);
	for (int i = 0; i < iterations; i++) {
		g_i--;
		std::cout << g_i << "\n";
	}

}

static void RunThread()
{
	std::cout << __func__ << ": " << g_i << '\n';

	std::thread t1(increment);
	std::thread t2(decrement);

	//t1.detach();
	//t2.detach();
	t1.join();
	t2.join();

	std::cout << __func__ << ": " << g_i << '\n';
}