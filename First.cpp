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


int kAndNeg(int k, int& Neg, std::list<int> List)
{
	if (List.empty())
	{
		throw "Список пуст";
	}
	else
	{
		int neg = 1;
		int kNum;
		int i = 1;
		if (k <= List.size())
		{
			std::list<int>::iterator it = List.begin();
			while (i != k)
			{
				i++;
				if ((neg == 1) && (*it < 0)) { neg = *it; }
				it++;
			}
			kNum = *it;
			while ((neg == 1) && (it != List.end()))
			{
				if (*it < 0) { neg = *it; }
				it++;
			}
			if (neg == 1) { throw "Нет отрицательных чисел"; }
			return kNum;
		}
		else { throw "В списке меньше, чем k элементов"; }
	}
}

std::fstream CreateFileСycle(std::string fileName, int N, int M)
{	
	srand(time(NULL));
	std::fstream fout(fileName, std::ios::out);
	for (int i = 0; i < N; i++)
	{
		fout << (rand() % (2 * M) + 1) - M << "\n";
	}
	fout.close();
	return fout;
}

std::fstream CreateFileGenerate(std::string fileName, int N, int M)
{	
	std::vector<int> ad(N);
	std::fstream fout(fileName, std::ios::out);
	std::generate(ad.begin(),ad.end(), rand);
	for (int i = 0; i < N; i++)
	{
		fout << (ad[i] % (2 * M) + 1) - M << "\n";
	}
	fout.close();
	return fout;
}

std::list<int> GetList(std::string fileName)
{	
	std::list<int> List;
	int number;
	std::fstream fin(fileName, std::ios::in);
	while (fin)
	{
		fin >> number;
		List.push_back(number);
	}
	fin.close();
	List.pop_back();
	return List;
}

/*std::list<int> GetList(std::fstream &fin)
{
	std::list<int> List;
	int number;
	while (fin)
	{
		fin >> number;
		List.push_back(number);
	}
	fin.close();
	List.pop_back();
	return List;
}*/

void OutputResult(std::list<int> List, bool onConsole, std::string fileName = "")
{	
	if (onConsole)
	{
		for each (int number in List)
		{
			std::cout << number << "\n";
		}
	}
	else
	{
		std::fstream fout(fileName, std::ios::out);
		for each (int number in List)
		{
			fout << number << "\n";
		}
		fout.close();
	}
}

std::list<int> Modify(std::list<int> List, int k)
{	
	int neg = 1;
	int kNum = kAndNeg(k, neg, List);
	kNum = (kNum + neg) / 2;
	if (kNum != 0)
	{	
		std::list<int>::iterator it = List.begin();
		for(;it != List.end();it++)
		{
			*it /= kNum;
		}
		return List;
	}
	else { throw "Деление на 0"; }
	return List;
}

std::list<int> Modify(std::list<int> List, int k, std::list<int>::iterator begin, std::list<int>::iterator end)
{
	/*std::list<int> list;
	for (auto it = begin; it != end; it++)
	{
		list.push_back(*it);
	}
	list = modify(list);
	return list;*/
	std::list<int> newList;
	int neg = 1;
	int kNum = kAndNeg(k, neg, List);
	kNum = (kNum + neg) / 2;
	if (kNum != 0)
	{
		std::list<int>::iterator it = begin;
		for (; it != end; it++)
		{
			newList.push_back(*it / kNum);
		}
		return newList;
	}
	else { throw "Деление на 0"; }
	return newList;
}

std::list<int> ModifyTransform(std::list<int> List, int k)
{
	std::list<int> newList;
	newList.resize(List.size());
	int neg = 1;
	int kNum = kAndNeg(k, neg, List);
	kNum = (kNum + neg) / 2;
	std::transform(List.begin(), List.end(), newList.begin(), [kNum](int num) -> int {return num / kNum;});
	return newList;
}

std::list<int> ModifyForEach(std::list<int> List, int k)
{
	std::list<int> newList;
	newList.resize(List.size());
	int neg = 1;
	int kNum = kAndNeg(k, neg, List);
	kNum = (kNum + neg) / 2;
	std::for_each(List.begin(), List.end(), [kNum](int &num) -> void { num /= kNum; });
	return List;
}

int ListSum(std::list<int> List)
{
	int sum = 0;
	for (int x : List)
	{
		sum += x;
	}
	return sum;
}

double ListAverage(std::list<int> List)
{
	return ListSum(List) / List.size();
}

int ShowMenu()
{
	int res = 0;
	while ((res < 1)||(res > 9))
	{
		std::cout << "1) выберите файл;\n";
		std::cout << "2) создать файл/список;\n";
		std::cout << "3) modify;\n";
		std::cout << "4) modify с итераторами;\n";
		std::cout << "5) modify с std::transform;\n";
		std::cout << "6) modify c std::for_each;\n";
		std::cout << "7) сумма и среднее арифметическое;\n";
		std::cout << "8) вывести список;\n";
		std::cout << "9) выход;\n";
		std::cin >> res;
	}
	return res;
}

int main()
{	
	setlocale(LC_ALL, "rus");
	bool exite = false;
	int option = ShowMenu();
	std::list<int> List;
	std::fstream file;
	std::string filename;
	int k,o;

	while (!exite)
	{
		switch (option)
		{
		case 1:
			std::cout << "Введите имя файла\n";
			std::cin >> filename;
			file.open(filename);
			/*while (!file.is_open())
			{
				std::cout << "некорректное имя, повторите ввод\n";
				std::cin >> filename;
				file.open(filename);
			}*/
			option = ShowMenu();
			break;
		case 2:
			int N, M;
			o = 0;
			std::cout << "Введите N\n";
			std::cin >> N;
			std::cout << "Введите M\n";
			std::cin >> M;
			while ((o < 1) || (o > 3))
			{
				std::cout << "1) Через свою функцию\n";
				std::cout << "2) Через std::Generate\n";
				std::cout << "3) Отмена\n";
				std::cin >> o;
			}
			switch (o)
			{
			case 1:
				file = CreateFileСycle(filename, N, M);
				break;
			case 2:
				file = CreateFileGenerate(filename, N, M);
				break;
			case 3:
				break;
			}
			List= GetList(filename);
			option = ShowMenu();
			break;
		case 3:
			std::cin >> k;
			List = Modify(List, k);
			option = ShowMenu();
			break;
		case 4:
			std::cin >> k;
			List = Modify(List, k, List.begin(),List.end());
			option = ShowMenu();
			break;
		case 5:
			std::cin >> k;
			List = ModifyTransform(List, k);
			option = ShowMenu();
			break;
		case 6:
			std::cin >> k;
			List = ModifyForEach(List, k);
			option = ShowMenu();
			break;
		case 7:
			std::cout << "Сумма = " << ListSum << "\n";
			std::cout << "Среднеее арифмитическое = " << ListAverage << "\n";
			break;
		case 8:
			std::cout << "1) консоль\n2) в файл\n";
			std::cin >> o;
			switch (o)
			{
			case 1: OutputResult(List, true);
				break;
			case 2: OutputResult(List, false, filename);
				break;
			}
			option = ShowMenu();
			break;
		case 9:
			exite = true;
			break;
		}
	}
    return 0;
}

