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
		throw "������ ����";
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
		if (neg == 1) { throw "��� ������������� �����"; }
		return neg;
	}
}
//����� ������� � ������� �
double FindK(std::list<double> list,int k)
{
	if (list.empty())
	{
		throw "������ ����";
	}
	if ((k >= 1)&&(k <= (list.size())))
	{
		std::list<double>::iterator it = list.begin();
		for(int i = 0; i < k; i++) 
			it++;
		return *it;
	}
	else { throw "� ������ ������, ��� k ���������"; }
}
//�������� ������ ������
std::fstream CreateFile�ycle(std::string fileName, int n, int M)
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
	else { throw "�������� �� ������ ���� ��������������"; }
}
//�������� ������ ���������� generate
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
	else { throw "�������� �� ������ ���� ��������������"; }
}
// ���������� ������ �� �����
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
	else { throw "������� �� 0"; }
	return list;
}
// ��������� ����� ���������
std::list<double> Modify(std::list<double> list, int k, std::list<double>::iterator begin, std::list<double>::iterator end)
{
	std::list<double> newlist;
	int neg = Findneg(list);
	double knum = FindK(list, k); // �������� k �� ����������� �������� �����, ���� �� �����������?
	double numToDel = (knum + neg) / 2;
	if (numToDel != 0)
	{
		for (std::list<double>::iterator it = begin; it != end; it++)
		{
			newlist.push_back(*it / numToDel);
		}
		return newlist;
	}
	else { throw "������� �� 0"; }
	return newlist;
}
// ��������� ����� transform
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
	else { throw "������� �� 0"; }
	return newlist;
}
//��������� ����� for_each
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
	else { throw "������� �� 0"; }
	return list;
}
// ����� �� ������
double listSum(std::list<double> list)
{
	int sum = 0;
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
			file.open(fileName);
			/*while (!file.is_open())
			{
				std::cout << "������������ ���, ��������� ����\n";
				std::cin >> fileName;
				file.open(fileName);
			}*/
			option = ShowMenu();
			break;
		case 2:
			int n, M;
			o = 0;
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
			fileName = "���-�� ��� ����� �� �������.txt";
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
			list= Getlist(fileName);
			option = ShowMenu();
			break;
		case 3:
			std::cout << "������� ����� �\n";
			std::cin >> k;
			list = Modify(list, k);
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 4:
			std::cout << "������� ����� �\n";
			std::cin >> k;
			list = Modify(list, k, list.begin(),list.end());
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 5:
			std::cout << "������� ����� �\n";
			std::cin >> k;
			list = ModifyTransform(list, k);
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 6:
			std::cout << "������� ����� �\n";
			std::cin >> k;
			list = ModifyForEach(list, k);
			OutputResultConsole(list);
			option = ShowMenu();
			break;
		case 7:
			std::cout << "����� = " << listSum << "\n";
			std::cout << "�������� �������������� = " << listAverage << "\n";
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

