#include<iostream>
#include<conio.h>
#include<thread>
#include<Windows.h>

class Car
{
	class Tank
	{
		unsigned int volume;//Объем бака.
		double fuel;	//Уровень топлива.
	public:
		unsigned int get_volume()const
		{
			return this->volume;
		}
		double get_fuel()const
		{
			return this->fuel;
		}
		Tank(unsigned int volume) :volume(volume >= 20 && volume <= 100 ? volume : throw std::exception("Error: Bad tank volume")), fuel(0)
		{
			std::cout << "Tank is ready:\t" << this << std::endl;
		}
		~Tank()
		{
			std::cout << "Tank crashed:\t" << this << std::endl;
		}
		void fill(double fuel)
		{
			if (fuel >= 0)
			{
				this->fuel += fuel;
				if (this->fuel >= volume)this->fuel = volume;
			}
		}
		double give_fuel(double amount)
		{
			fuel -= amount;
			if (fuel < 0)fuel = 0;
			return fuel;
		}
		void info()const
		{
			std::cout << "Tank volume:\t" << volume << " liters.\n";
			std::cout << "Fuel level:\t" << fuel << " liters.\n";
		}
	}tank;
	class Engine
	{
		bool started;
		double consumption;
		double consumption_per_second;
	public:
		bool Started()const
		{
			return started;
		}
		double get_consumption()const
		{
			return consumption;
		}
		double get_consumption_per_second()const
		{
			return consumption_per_second;
		}
		/*void set_consumption(double consumption)
		{
			this->consumption = consumption >= 3 && consumption <= 30 ? consumption : throw std::exception("Error:Bad consumption");
		}*/
		Engine(double consumption) :
			consumption(consumption >= 3 && consumption <= 30 ? consumption : throw std::exception("Error:Bad consumption")),
			consumption_per_second(consumption / 10000),
			started(false)
		{
			std::cout << "Engine installed" << this << std::endl;
		}
		~Engine()
		{
			std::cout << "Engine crashed" << this << std::endl;
		}

		void start()
		{
			started = true;
		}
		void stop()
		{
			started = false;
		}

		void info()const
		{
			std::cout << "Engine is " << (started ? "started" : "stopped") << ".\n";
			std::cout << "Consumption is:\t" << consumption << " liter/100km\n";
			std::cout << "Consumption per second is " << consumption_per_second << " liter/1s\n";
		}
	}engine;
	/*Engine engine;
	Tank tank;*/
	struct Control
	{
		std::thread panel_thread;
		std::thread engine_idle_thread;

		std::thread main_thread;
		std::thread acceleration_thread;	//speed inrease
		std::thread free_wheeling_thread;	//car move

	}control;
	struct Delay
	{
		double panel = 1;
		double engine_idle = 1;
		double main = 1;
		double acceleration = 1;
		double free_wheeling = 1;
	}delay;
	bool driver_inside;

	bool gas_pedal;
	bool break_pedal;
	unsigned int speed;
	unsigned int max_speed;
public:
	const Engine& get_engine()const
	{
		return this->engine;
	}
	const Tank& get_tank()const
	{
		return this->tank;
	}
	Car(double engine_consumption, unsigned int tank_volume, unsigned int max_speed = 250) :engine(engine_consumption), tank(tank_volume)
	{
		driver_inside = false;
		gas_pedal = false;
		break_pedal = false;
		speed = 0;
		this->max_speed = max_speed <= 350 ? max_speed : 250;

		control.main_thread = std::thread(&Car::ControlCar, this);

		std::cout << "Your car is ready to go :-)\n";
	}
	~Car()
	{
		if (control.main_thread.joinable())control.main_thread.join();
		std::cout << "Don't leave me alone.\n";
	}

	void ControlCar()
	{
		using namespace std::literals::chrono_literals;
		char key;
		do
		{
			key = _getch();
			switch (key)
			{
			case 13:
				if (driver_inside)this->get_out();
				else this->get_in();
				break;
			case 'i':case 'I'://Ignition
				if (!this->get_engine().Started())this->start();
				else this->stop();
				break;
			case 'f':
				double amount;
				std::cout << "How mach?"; std::cin >> amount;
				this->fill(amount);
				break;
			case 27:
				this->stop();
				this->get_out();
				break;
				/////////////////////////////////
			case 'w':case 'W':
				//std::this_thread::sleep_for(1s);
				if (engine.Started())
				{
					if (speed < max_speed)speed += 1;
					else speed = max_speed;
				}
				break;
			case 's':case 'S':
				if (speed>5)speed-=2;
				else speed = 0;
				break;
			}
			std::this_thread::sleep_for(0.1s);
			if (speed > 0 && !control.free_wheeling_thread.joinable())control.free_wheeling_thread = std::thread(&Car::free_wheeling, this);
			else if (speed == 0 && control.free_wheeling_thread.joinable())control.free_wheeling_thread.join();
		} while (key != 27);
	}

	void fill(double fuel)
	{
		tank.fill(fuel);
	}
	void info()const
	{
		engine.info();
		tank.info();
	}

	void get_in()
	{
		driver_inside = true;
		control.panel_thread = std::thread(&Car::panel, this);
	}
	void get_out()
	{
		driver_inside = false;
		if (control.panel_thread.joinable())control.panel_thread.join();
	}
	void panel()
	{
		using namespace std::literals::chrono_literals;
		while (driver_inside)
		{
			system("CLS");
			for (int i = 0; i < speed / 2; i++)std::cout << "|"; std::cout << std::endl;
			std::cout << "Engine is  " << (engine.Started() ? "started" : "stopped") << ".\n";
			std::cout << "Fuel level:" << tank.get_fuel() << std::endl;
			std::cout << "Speed:     " << speed << " km/h" << std::endl;
			if (tank.get_fuel() < 5)
			{
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 12);
				std::cout << "LOW FUEL!" << std::endl;
				SetConsoleTextAttribute(hConsole, 7);
			}
			std::this_thread::sleep_for(0.5s);

			if (tank.get_fuel() == 0)
			{
				//if (control.engine_idle_thread.joinable())control.engine_idle_thread.join();
				stop();
			}
		}
	}

	void start()
	{
		if (tank.get_fuel())
		{
			engine.start();
			control.engine_idle_thread = std::thread(&Car::engine_idle, this);
		}
		else
		{
			std::cout << "No fuel\a\n";
		}
	}
	void stop()
	{
		engine.stop();
		if (control.engine_idle_thread.joinable())
			control.engine_idle_thread.join();
	}
	void engine_idle()
	{
		using namespace std::literals::chrono_literals;
		while (engine.Started() && tank.give_fuel(engine.get_consumption_per_second()))
		{
			std::this_thread::sleep_for(1s);
		}
		engine.stop();
	}

	void free_wheeling()
	{
		using namespace std::literals::chrono_literals;
		while (speed > 0)
		{
			speed--;
			std::this_thread::sleep_for(1s);
		}
	}
};

void main()
{
	/*Tank tank(40);
	tank.fill(20);
	tank.fill(30);
	tank.info();

	Engine engine(8);
	engine.info();*/

	Car car(8, 40);
	//car.info();

	std::cout << "Press Enter to get in";
	//std::cin.get();
	//car.get_in();

	/*char key;
	do
	{
		key = _getch();
		switch (key)
		{
		case 13:
			if (!car.get_engine().Started())car.start();
			else car.stop();
			break;
		case 'f':
			double amount;
			std::cout << "How mach?"; std::cin >> amount;
			car.fill(amount);
			break;
		case 27:
			car.stop();
			car.get_out();
		}
	} while (key != 27);*/
}