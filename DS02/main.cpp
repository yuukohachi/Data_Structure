#include "functions.h"
#include <iostream>

int main()
{
	// 2.��չ
	Dec_2_N_Base();
	std::cout << std::endl << std::endl;

	// 4.
	int row;
	std::cout << "����������ǵ�������";
	std::cin >> row;
	if (row <= 0) throw("����ֵ������Χ");
	std::cout << "������ǣ�" << std::endl;
	triangle(row);
	std::cout << std::endl;

	// 5.
	std::cout << "������ʽ���س�������Ctrl+Z��";
	std::cin.clear();
	int x = brackets();

	switch (x)
	{
	case -1:
		std::cout << "�����Ź���" << std::endl;
		break;
	case -2:
		std::cout << "�����Ź���" << std::endl;
		break;
	default:
		std::cout << "���Ƕ��" << x << "��" << std::endl;
		break;
	}

	system("pause");

	return 0;
}