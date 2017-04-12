// First.cpp : Defines the entry point for the console application.
//
/*
2C Красиков Максим Эдуардович
C) список (std::list)
2. Разделить каждое число на полусумму первого отрицательного и K-го числа (K задается аргументом функции modify).
*/

#include "stdafx.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <time.h>
#include <vector>
//Найти первое отрицательное
double Findneg(std::list<double> list)
{
	if (list.empty())
	{
		throw "Список пуст";
	}
	else
	{
		std::list<double>::iterator it = list.begin();
		int neg = 1;
		while ((neg == 1) && (it != list.end()))
		{
			if (*it < 0) { neg = *it; }
			it++;
		}
		if (neg == 1) { throw "Нет отрицательных чисел"; }
		return neg;
	}
}
//Найти элемент с номером К
double FindK(std::list<double> list,int k)
{
	if (list.empty())
	{
		throw "Список пуст";
	}
	if ((k >= 1)&&(k <= (list.size())))
	{
		std::list<double>::iterator it = list.begin();
		for(int i = 0; i < k; i++) 
			it++;
		return *it;
	}
	else { throw "В списке меньше, чем k элементов"; }
}
//Создание списка циклом
std::fstream CreateFileСycle(std::string fileName, int n, int M)
{	
	if ((M > 0)||( n > 0))
	{
		srand(time(NULL));
		std::fstream fout(fileName, std::ios::out);
		for (int i = 0; i < n; i++)
		{
			fout << (rand() % (2 * M) + 1) - M << "\n";
		}
		fout.close();
		return fout;
	}
	else { throw "Значения не должны быть отрицательными"; }
}
//Создание списка алгаритмом generate
std::fstream CreateFileGenerate(std::string fileName, int n, int M)
{	
	if ((M > 0) || (n > 0))
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
	else { throw "Значения не должны быть отрицательными"; }
}
// Считывание списка из файла
std::list<double> Getlist(std::string fileName)
{	
	std::list<double> list;
	int number;
	std::fstream fin(fileName, std::ios::in);
	while (fin)
	{
		fin >> number;
		list.push_back(number);
	}
	fin.close();
	list.pop_back();
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
	int neg = Findneg(list);
	double knum = FindK(list,k);
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{	
		for(std::list<double>::iterator it = list.begin();it != list.end();it++)
		{
			*it /= numToDel;
		}
		return list;
	}
	else { throw "Деление на 0"; }
	return list;
}
// Изменение через итераторы
std::list<double> Modify(std::list<double> list, int k, std::list<double>::iterator begin, std::list<double>::iterator end)
{
	std::list<double> newlist;
	int neg = Findneg(list);
	double knum = FindK(list, k); // Проверка k на пригодность проходит здесь, надо ли дублировать?
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{
		for (std::list<double>::iterator it = begin; it != end; it++)
		{
			newlist.push_back(*it / numToDel);
		}
		return newlist;
	}
	else { throw "Деление на 0"; }
	return newlist;
}
// Изменение через transform
std::list<double> ModifyTransform(std::list<double> list, int k)
{
	std::list<double> newlist;
	newlist.resize(list.size());
	int neg = Findneg(list);
	double knum = FindK(list, k);
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{
		std::transform(list.begin(), list.end(), newlist.begin(), [numToDel](int num) -> int {return num / numToDel; });
	}
	else { throw "Деление на 0"; }
	return newlist;
}
//Изменение через for_each
std::list<double> ModifyForEach(std::list<double> list, int k)
{
	std::list<double> newlist;
	newlist.resize(list.size());
	double neg = Findneg(list);
	double knum = FindK(list, k);
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{
	std::for_each(list.begin(), list.end(), [numToDel](double &num) -> void { num /= numToDel; });
	}
	else { throw "Деление на 0"; }
	return list;
}
// Сумма по списку
double listSum(std::list<double> list)
{
	int sum = 0;
	for (int x : list)
	{
		sum += x;
	}
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
	int res = 0;
	while ((res < 1)||(res > 10))
	{
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
		std::cin >> res;
	}
	return res;
}

int main()
{	
	setlocale(LC_ALL, "rus");
	bool exite = false;
	int option = ShowMenu();
	std::list<double> list;
	std::fstream file;
	std::string fileName;
	int k,o;

	while (!exite)
	{
		switch (option)
		{
		case 1:
			std::cout << "Введите имя файла\n";
			std::cin >> fileName;
			file.open(fileName);
			/*while (!file.is_open())
			{
				std::cout << "некорректное имя, повторите ввод\n";
				std::cin >> fileName;
				file.open(fileName);
			}*/
			option = ShowMenu();
			break;
		case 2:
			int n, M;
			o = 0;
			std::cout << "Введите n\n";
			std::cin >> n;
			std::cout << "Введите M\n";
			std::cin >> M;
			while ((o < 1) || (o > 3))
			{
				std::cout << "1) Через свою функцию\n";
				std::cout << "2) Через std::Generate\n";
				std::cout << "3) Отмена\n";
				std::cin >> o;
			}
			fileName = "Что-то что никто не наберет.txt";
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
			}
			list= Getlist(fileName);
			option = ShowMenu();
			break;
		case 3:
			std::cout << "Введите номер К\n";
			std::cin >> k;
			list = Modify(list, k);
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 4:
			std::cout << "Введите номер К\n";
			std::cin >> k;
			list = Modify(list, k, list.begin(),list.end());
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 5:
			std::cout << "Введите номер К\n";
			std::cin >> k;
			list = ModifyTransform(list, k);
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 6:
			std::cout << "Введите номер К\n";
			std::cin >> k;
			list = ModifyForEach(list, k);
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 7:
			std::cout << "Сумма = " << listSum << "\n";
			std::cout << "Среднеее арифмитическое = " << listAverage << "\n";
			break;
		case 8:
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 9:
			std::cout << "Введите имя файла\n";
			std::cin >> fileName;
			OutputResultFile(list, fileName);
			option = ShowMenu();
			break;
		case 10:
			exite = true;
			break;
		}
	}
    return 0;
}

