#include <iostream>
#include <windows.h>
#include <iomanip>
#include <fstream>
using namespace std;
class Time
{

	int hours;
	int minutes;
	int seconds;
public:
	Time()
	{
		hours = 0;
		minutes = 0;
		seconds = 0;
	}
	Time(int hours, int minutes, int seconds)
	{
		cout << "Вызван конструктор" << endl;
		this->hours = hours;
		this->minutes = minutes;
		this->seconds = seconds;
	}
	Time(const Time& other)
	{
		this->hours = other.hours;
		this->minutes = other.minutes;
		this->seconds = other.seconds;
		cout << "Вызван конструктор копирования" << endl;
	}
	void Timecheck()
	{
		hours = (hours >= 0 && hours < 24) ? hours : 12;
		minutes = (minutes >= 0 && minutes < 60) ? minutes : 12;
		seconds = (seconds >= 0 && seconds < 60) ? seconds : 12;
	}
	void printTime()
	{
		cout << "Выберите способ представления времени" << endl;
		cout << "1-часы,мин,сек" << endl;
		cout << "2-AM,PM" << endl;

		int choose;

		cin >> choose;
		if (choose == 1)
		{
			cout << ((hours == 0 || hours == 12) ? 12 : hours % 12) << " часов "
				<< (minutes < 10 ? "0" : "") << minutes
				<< " минут " << (seconds < 10 ? "0" : "") << seconds
				<< " секунд " << endl;
		}
		else
		{
			if (choose == 2)
			{
				cout << ((hours == 0 || hours == 12) ? 12 : hours % 12)
					<< ":" << (minutes < 10 ? "0" : "") << minutes
					<< ":" << (seconds < 10 ? "0" : "") << seconds
					<< (hours < 12 ? " AM" : " PM") << endl;
			}
			else
			{
				cout << "Некорретно введено значение" << endl;
			}
		}
	}
	~Time()
	{

		cout << "Вызван деструктор" << endl;
	}
};

int menu()
{
	int sw;
	cout << "Введите:\n";
	cout << "1-для ввода массива времен\n";
	cout << "2-для установки времени по умолчанию(12:00:00 PM)\n";
	cout << "3-для ввода времени\n";
	cout << "4- для записи данных в файл\n";
	cout << "5-для выхода из программы\n";

	cin >> sw;
	return sw;
}
void timemas()
{
	int hour, min, sec;
	int size;
	cout << "Введите размер массива" << endl;
	cin >> size;
	Time* arr = new Time[size];
	for (int i = 0; i < size; i++)
	{
		cout << "Введите часы" << endl;
		cin >> hour;
		cout << "Введите минуты" << endl;
		cin >> min;
		cout << "Введите секунды" << endl;
		cin >> sec;
		arr[i] = Time(hour, min, sec);

	}

	for (int i = 0; i < size; i++)
	{
		arr[i].Timecheck();
		arr[i].printTime();
	}

	delete[] arr;

}
void time()
{
	int hour, min, sec;
	cout << "Введите часы" << endl;
	cin >> hour;
	cout << "Введите минуты" << endl;
	cin >> min;
	cout << "Введите секунды" << endl;
	cin >> sec;
	Time one(hour, min, sec);
	one.Timecheck();
	one.printTime();
	Time two(one);
	two.printTime();


}
void timedefault()
{
	Time three;
	three.Timecheck();
	three.printTime();
}
void fileinput()
{
	cout << "Введите данные для записи в файл" << endl;
	int hour, min, sec;
	cout << "Введите часы" << endl;
	cin >> hour;
	cout << "Введите минуты" << endl;
	cin >> min;
	cout << "Введите секунды" << endl;
	cin >> sec;
	Time four(hour, min, sec);
	four.Timecheck();
	ofstream fout;
	fout.open("Myfile.txt", ofstream::app);
	if (!fout.is_open())
	{
		cout << "Ошибка открытия файла" << endl;
	}
	else
	{
		cout << "Файл открыт" << endl;
		fout.write((char*)&four, sizeof(Time));

	}
	fout.close();
}
int  main()
{
	setlocale(LC_ALL, "rus");
	while (1)
	{
		switch (menu())
		{
		case 1:timemas(); break;
		case 2:timedefault(); break;
		case 3:time(); break;
		case 4:fileinput(); break;
		case 5:return 0;
		default:cout << "Введены некорректные данные" << endl;
		}
	}
	return 0;
}