#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

void threadFunctionJoin()
{
	cout << "Thread with join started.\n";
	this_thread::sleep_for(chrono::seconds(2));
	cout << "Thread with join finished.\n";
}

void threadFunctionDetach()
{
	cout << "Thread with detach started.\n";
	this_thread::sleep_for(chrono::seconds(3));
	cout << "Thread with detach finished.\n";
}

int main()
{
	cout << "Main thread starts.\n";

	thread t1(threadFunctionJoin);
	thread t2(threadFunctionDetach);

	if (t1.joinable())
	{
		t1.join();
	}

	if (t2.joinable())
	{
		t2.detach();
	}

	cout << "Main thread ends.\n";
	this_thread::sleep_for(chrono::seconds(4));

	return 0;
}
