// First.cpp : Defines the entry point for the console application.
//
/*
2C Красиков Максим Эдуардович
C) список (std::list)
2. Разделить каждое число на полусумму первого отрицательного и K-го числа (K задается аргументом функции modify).
*/

#include "stdafx.h"
#include <list>
#include <clocale>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <time.h>
#include <vector>

int InputK(int begin, int end)
{	
	int k;
	std::cout << "Введите номер К\n";
	std::cin >> k;
	if ((k < begin) || (k > end)) throw ("Выход за границу значения k");
	return k;
}

double Findneg(std::list<double>::iterator begin, std::list<double>::iterator end)
{
	std::list<double>::iterator it = begin;
	double neg = 1;
	while ((neg == 1) && (it != end))
	{
		if (*it < 0) { neg = *it; }
		it++;
	}
	if (neg == 1) { throw "В списке нет отрицательных чисел\n"; }
	return neg;
}
//Найти элемент с номером К
double FindK(std::list<double>::iterator begin, std::list<double>::iterator end,int k)
{
	std::list<double>::iterator it = begin;
	for(int i = 1; i < k, it!=end ; i++,it++)
	return *it;
}
//Создание списка циклом
std::fstream CreateFileСycle(std::string fileName, int n, int M)
{	
	if ((M > 0)&&( n > 0))
	{
		std::fstream fout(fileName, std::ios::out);
		for (int i = 0; i < n; i++)
		{
			fout << (int)(rand() % (2 * M) + 2) - M - 2 << "\n";
		}
		fout.close();
		return fout;
	}
	else { throw "Значения не должны быть отрицательными\n"; }
}
//Создание списка алгаритмом generate
std::fstream CreateFileGenerate(std::string fileName, int n, int M)
{	
	if ((M > 0) && (n > 0))
	{
		std::vector<int> ad(n);
		std::fstream fout(fileName, std::ios::out);
		std::generate(ad.begin(),ad.end(), rand);
		for (int i = 0; i < n; i++)
		{
			fout << (ad[i] % (2 * M) + 1) - M << "\n";
		}
		fout.close();
		return fout;
	}
	else { throw "Значения не должны быть отрицательными\n"; }
}
// Считывание списка из файла
std::list<double> Getlist(std::string fileName)
{	
	std::list<double> list;
	double number;
	std::fstream fin(fileName, std::ios::in);
	while (fin >> number)
	{
		list.push_back(number);
	}
	fin.close();
	if (list.empty()) throw ("Пустой файл, загрузка не произведена");
	return list;
}
//Вывод в консоль
void OutputResultConsole(std::list<double> list)//std::string fileName = "")
{
	std::cout << "__________________________\n";
	if (list.empty()) std::cout << "Списрк пуст\n";
	else
	{
		for each (double number in list)
		{
			std::cout << number << "\n";
		}
	}
	std::cout << "__________________________\n";
}
//Вывод в файл
void OutputResultFile(std::list<double> list, std::string fileName)
{
	std::fstream fout(fileName, std::ios::out);
	for each (double number in list)
	{
		fout << number << "\n";
	}
	fout.close();
}
// Изменение мой способ
std::list<double> Modify(std::list<double> list, int k)
{
	if (list.empty()) throw ("Список пуст операцию произвести не возможно\n");
	double knum = FindK(list.begin(), list.end(), k);
	double neg = Findneg(list.begin(), list.end());
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{	
		for(std::list<double>::iterator it = list.begin();it != list.end();it++)
		{
			*it /= numToDel;
		}
		return list;
	}
	else { throw "Деление на 0\n"; }
	return list;
}
// Изменение через итераторы
void Modify(std::list<double>::iterator begin, std::list<double>::iterator end,int k)
{	

	double knum = FindK(begin,end, k);
	double neg = Findneg(begin,end);
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{
		for (std::list<double>::iterator it = begin; it != end; it++)
		{
			*it = *it / numToDel;
		}
	}
	else { throw "Деление на 0\n"; }
}
// Изменение через transform
std::list<double> ModifyTransform(std::list<double> list,int k)
{
	if (list.empty()) throw ("Список пуст операцию произвести не возможно\n");
	double knum = FindK(list.begin(), list.end(), k);
	std::list<double> newlist;
	newlist.resize(list.size());
	double neg = Findneg(list.begin(), list.end());
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{
		std::transform(list.begin(), list.end(), newlist.begin(), [numToDel](double num) -> double {return num / numToDel; });
	}
	else { throw "Деление на 0\n"; }
	return newlist;
}
//Изменение через for_each
std::list<double> ModifyForEach(std::list<double> list,int k)
{
	if (list.empty()) throw ("Список пуст операцию произвести не возможно\n");
	double knum = FindK(list.begin(), list.end(), k);
	std::list<double> newlist;
	newlist.resize(list.size());
	double neg = Findneg(list.begin(), list.end());
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{
	std::for_each(list.begin(), list.end(), [numToDel](double &num) -> void { num /= numToDel; });
	}
	else { throw "Деление на 0\n"; }
	return list;
}
// Сумма по списку
double listSum(std::list<double> list)
{
	if (list.empty()) throw ("Список пуст операцию произвести не возможно\n");
	double sum = 0;
	std::for_each(list.begin(), list.end(), [&sum](double num) -> void { sum+=num; });
	return sum;
}
// Среднее значение
double listAverage(std::list<double> list)
{
	return listSum(list) / list.size();
}
// Показать меню
int ShowMenu()
{
	std::string str;
	int res = 0;
	while ((res < 1)||(res > 10))
	{
		std::cout << "__________________________\n";
		std::cout << "1) выберите файл;\n";
		std::cout << "2) создать файл/список;\n";
		std::cout << "3) modify;\n";
		std::cout << "4) modify с итераторами;\n";
		std::cout << "5) modify с std::transform;\n";
		std::cout << "6) modify c std::for_each;\n";
		std::cout << "7) сумма и среднее арифметическое;\n";
		std::cout << "8) вывести список в консоль;\n";
		std::cout << "9) вывести список в файл;\n";
		std::cout << "10) выход;\n";
		std::cout << "__________________________\n";
		std::cin >> res;
		std::getline(std::cin, str);
	}
	return res;
}

int main()
{	
	setlocale(LC_ALL, "rus");
	srand(time(NULL));
	std::string str;
	bool exite = false;
	int option = ShowMenu();
	std::list<double> list;
	std::fstream file;
	std::string fileName;
	int o,k;
	auto begin = list.begin();
	auto end = list.begin();

	while (!exite)
	{
		switch (option)
		{
		case 1:
			std::cout << "Введите имя файла\n";
			std::cin >> fileName;
			std::getline(std::cin, str);
			try
			{
				list = Getlist(fileName);
			}
			catch (char* str)
			{
				std::cout << str;
				option = ShowMenu();
			}
			option = ShowMenu();
			break;
		case 2:
			try {
				int n, M;
				o = 0;
				std::cout << "Введите имя файла\n";
				std::cin >> fileName;
				std::cout << "Введите n\n";
				std::cin >> n;
				std::cout << "Введите M\n";
				std::cin >> M;
				std::getline(std::cin, str);
				while ((o < 1) || (o > 3))
				{
					std::cout << "1) Через свою функцию\n";
					std::cout << "2) Через std::Generate\n";
					std::cout << "3) Отмена\n";
					std::cin >> o;
					std::getline(std::cin, str);
				}
				switch (o)
				{
				case 1:
					file = CreateFileСycle(fileName, n, M);
					break;
				case 2:
					file = CreateFileGenerate(fileName, n, M);
					break;
				case 3:
					break;
				default:
					throw ("Неопределенный ввод");
				}
				list = Getlist(fileName);
				option = ShowMenu();
			}
			catch (char* str)
			{
				std::cout << str;
				option = ShowMenu();
			}
			break;
		case 3:
			try {
				k = InputK(1, list.size());
				list = Modify(list, k);
				OutputResultConsole(list);
				option = ShowMenu();
			}
			catch (char* str)
			{
				std::cout << str;
				option = ShowMenu();
			}
			break;
		case 4:
			try {
				int a, b, o;
				a = b = o = 0;
				if (list.empty()) throw ("Список пуст операцию произвести не возможно\n");
				if (!list.empty()) {
					OutputResultConsole(list);
					while ((o < 1) || (o > 3))
					{
						std::cout << " 1)[list.begin(), list.end())\n";
						std::cout << " 2)[a, b]\n";
						std::cout << " 3)Отмена\n";
						std::cout << " >> ";
						std::cin >> o;
						std::getline(std::cin, str);
					}
					switch (o)
					{
					case 1:
						k = InputK(1, list.size());
						Modify(list.begin(), list.end(),k);
						OutputResultConsole(list);
						break;
					case 2:
						std::cout << "a: ";
						std::cin >> a;
						std::cout << "b: ";
						std::cin >> b;
						while (a < 1 || a > list.size())
						{
							std::cout << "Повторите ввод a: ";
							std::cin >> a;
						}
						while (b < 1 || b > list.size())
						{
							std::cout << "Повторите ввод b: ";
							std::cin >> b;
						}
						std::getline(std::cin, str);
						if (b < a)
						{
							int tmp = a;
							a = b;
							b = tmp;
						}
						begin = list.begin();
						end = list.begin();
						std::advance(begin, a-1);
						std::advance(end, b);
						k = InputK(a, b);
						Modify(begin, end, k);
						OutputResultConsole(list);
						break;
					case 3:
						break;
					default:
						throw ("Неопределенный ввод");
					}
				
				}
				option = ShowMenu();
			}
			catch (char* str)
			{
				std::cout << str;
				option = ShowMenu();
			}
			break;
		case 5:
			try {
				k = InputK(1,list.size());
				list = ModifyTransform(list,k);
				OutputResultConsole(list);
				option = ShowMenu();
				break;
			}
			catch (char* str)
			{
				std::cout << str;
				option = ShowMenu();
			}
		case 6:
			try {
				k = InputK(1,list.size());
				list = ModifyForEach(list,k);
				OutputResultConsole(list);
				option = ShowMenu();
			}
			catch (char* str)
			{
				std::cout << str;
				option = ShowMenu();
			}
			break;
		case 7:
			std::cout << "Сумма = " << listSum(list) << "\n";
			std::cout << "Среднеее арифмитическое = " << listAverage(list) << "\n";
			option = ShowMenu();
			break;
		case 8:
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 9:
			std::cout << "Введите имя файла\n";
			std::cin >> fileName;
			std::getline(std::cin, str);
			OutputResultFile(list, fileName);
			option = ShowMenu();
			break;
		case 10:
			exite = true;
			break;
		default:
			option = ShowMenu();
		}
	}
    return 0;
}

