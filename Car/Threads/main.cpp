#include<iostream>
#include<thread>

using namespace std::literals::chrono_literals;

static bool finish = false;

void What()
{
	while (!finish)
	{
		std::cout << "What a f*ck ";
		std::this_thread::sleep_for(1s);
	}
}

void Is()
{
	while (!finish)
	{
		std::cout << "is going on?\n";
		std::this_thread::sleep_for(1s);
	}
}

void main()
{
	std::thread thread_what(What);
	std::thread thread_is(Is);

	std::cout << thread_what.get_id() << std::endl;

	std::cin.get();	//������� ������� ������� Enter, ������� ��������� ������ - ����������.
	finish = true;

	thread_is.join();
	thread_what.join();

	std::thread thread;
	std::cout << thread.get_id() << std::endl;
	std::cout << thread.joinable() << std::endl;
}