// First.cpp : Defines the entry point for the console application.
//
/*
2C �������� ������ ����������
C) ������ (std::list)
2. ��������� ������ ����� �� ��������� ������� �������������� � K-�� ����� (K �������� ���������� ������� modify).
*/

#include "stdafx.h"
#include <list>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm> 
#include <time.h>
#include <vector>
//����� ������ �������������
double Findneg(std::list<double> list)
{
	if (list.empty())
	{
		throw "������ ����\n";
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
		if (neg == 1) { throw "� ������ ��� ������������� �����\n"; }
		return neg;
	}
}
//����� ������� � ������� �
double FindK(std::list<double> list,int k)
{
	if (list.empty())
	{
		throw "������ ����\n";
	}
	if ((k >= 1)&&(k <= (list.size())))
	{
		std::list<double>::iterator it = list.begin();
		for(int i = 1; i < k; i++) 
			it++;
		return *it;
	}
	else { throw "������������ �������� k, k > 0, k < length\n"; }
}
//�������� ������ ������
std::fstream CreateFile�ycle(std::string fileName, int n, int M)
{	
	if ((M > 0)&&( n > 0))
	{
		srand(time(NULL));
		std::fstream fout(fileName, std::ios::out);
		for (int i = 0; i < n; i++)
		{
			fout << (int)(rand() % (2 * M) + 2) - M - 2 << "\n";
		}
		fout.close();
		return fout;
	}
	else { throw "�������� �� ������ ���� ��������������\n"; }
}
//�������� ������ ���������� generate
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
	else { throw "�������� �� ������ ���� ��������������\n"; }
}
// ���������� ������ �� �����
std::list<double> Getlist(std::string fileName)
{	
	std::list<double> list;
	int number;
	std::fstream fin(fileName, std::ios::in);
	while (fin >> number)
	{
		list.push_back(number);
	}
	fin.close();
	Findneg(list);
	return list;
}
//����� � �������
void OutputResultConsole(std::list<double> list)//std::string fileName = "")
{
	std::cout << "__________________________\n";
	if (list.empty()) std::cout << "������ ����\n";
	else
	{
		for each (double number in list)
		{
			std::cout << number << "\n";
		}
	}
	std::cout << "__________________________\n";
}
//����� � ����
void OutputResultFile(std::list<double> list, std::string fileName)
{
	std::fstream fout(fileName, std::ios::out);
	for each (double number in list)
	{
		fout << number << "\n";
	}
	fout.close();
}
// ��������� ��� ������
std::list<double> Modify(std::list<double> list)
{	
	int k;
	std::cout << "������� ����� �\n";
	std::cin >> k;
	double knum = FindK(list, k);
	double neg = Findneg(list);
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{	
		for(std::list<double>::iterator it = list.begin();it != list.end();it++)
		{
			*it /= numToDel;
		}
		return list;
	}
	else { throw "������� �� 0\n"; }
	return list;
}
// ��������� ����� ���������
std::list<double> Modify(std::list<double> list, std::list<double>::iterator begin, std::list<double>::iterator end)
{	
	int k;
	std::cout << "������� ����� �\n";
	std::cin >> k;
	double knum = FindK(list, k); // �������� k �� ����������� �������� �����, ���� �� �����������?
	std::list<double> newlist;
	double neg = Findneg(list);
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{
		for (std::list<double>::iterator it = begin; it != end; it++)
		{
			newlist.push_back(*it / numToDel);
		}
		return newlist;
	}
	else { throw "������� �� 0\n"; }
	return newlist;
}
// ��������� ����� transform
std::list<double> ModifyTransform(std::list<double> list)
{
	int k;
	std::cout << "������� ����� �\n";
	std::cin >> k;
	double knum = FindK(list, k);
	std::list<double> newlist;
	newlist.resize(list.size());
	double neg = Findneg(list);
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{
		std::transform(list.begin(), list.end(), newlist.begin(), [numToDel](int num) -> int {return num / numToDel; });
	}
	else { throw "������� �� 0\n"; }
	return newlist;
}
//��������� ����� for_each
std::list<double> ModifyForEach(std::list<double> list)
{
	int k;
	std::cout << "������� ����� �\n";
	std::cin >> k;
	double knum = FindK(list, k);
	std::list<double> newlist;
	newlist.resize(list.size());
	double neg = Findneg(list);
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{
	std::for_each(list.begin(), list.end(), [numToDel](double &num) -> void { num /= numToDel; });
	}
	else { throw "������� �� 0\n"; }
	return list;
}
// ����� �� ������
double listSum(std::list<double> list)
{
	double sum = 0;
	for (int x : list)
	{
		sum += x;
	}
	return sum;
}
// ������� ��������
double listAverage(std::list<double> list)
{
	return listSum(list) / list.size();
}
// �������� ����
int ShowMenu()
{
	int res = 0;
	while ((res < 1)||(res > 10))
	{
		std::cout << "__________________________\n";
		std::cout << "1) �������� ����;\n";
		std::cout << "2) ������� ����/������;\n";
		std::cout << "3) modify;\n";
		std::cout << "4) modify � �����������;\n";
		std::cout << "5) modify � std::transform;\n";
		std::cout << "6) modify c std::for_each;\n";
		std::cout << "7) ����� � ������� ��������������;\n";
		std::cout << "8) ������� ������ � �������;\n";
		std::cout << "9) ������� ������ � ����;\n";
		std::cout << "10) �����;\n";
		std::cout << "__________________________\n";
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
			std::cout << "������� ��� �����\n";
			std::cin >> fileName;
			/*while (!file.is_open())
			{
				std::cout << "������������ ���, ��������� ����\n";
				std::cin >> fileName;
				file.open(fileName);
			}*/
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
				std::cout << "������� ��� �����\n";
				std::cin >> fileName;
				std::cout << "������� n\n";
				std::cin >> n;
				std::cout << "������� M\n";
				std::cin >> M;
				while ((o < 1) || (o > 3))
				{
					std::cout << "1) ����� ���� �������\n";
					std::cout << "2) ����� std::Generate\n";
					std::cout << "3) ������\n";
					std::cin >> o;
				}
				switch (o)
				{
				case 1:
					file = CreateFile�ycle(fileName, n, M);
					break;
				case 2:
					file = CreateFileGenerate(fileName, n, M);
					break;
				case 3:
					break;
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
				list = Modify(list);
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
				std::cout << "������� ����� �\n";
				std::cin >> k;
				list = Modify(list,list.begin(),list.end());
				OutputResultConsole(list);
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
				std::cout << "������� ����� �\n";
				std::cin >> k;
				list = ModifyTransform(list);
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
				std::cout << "������� ����� �\n";
				std::cin >> k;
				list = ModifyForEach(list);
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
			std::cout << "����� = " << listSum(list) << "\n";
			std::cout << "�������� �������������� = " << listAverage(list) << "\n";
			option = ShowMenu();
			break;
		case 8:
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 9:
			std::cout << "������� ��� �����\n";
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

