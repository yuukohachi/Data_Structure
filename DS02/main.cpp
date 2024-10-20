#include "functions.h"
#include <iostream>

int main()
{
	// 2.扩展
	Dec_2_N_Base();
	std::cout << std::endl << std::endl;

	// 4.
	int row;
	std::cout << "输入杨辉三角的行数：";
	std::cin >> row;
	if (row <= 0) throw("输入值超出范围");
	std::cout << "杨辉三角：" << std::endl;
	triangle(row);
	std::cout << std::endl;

	// 5.
	std::cout << "输入表达式，回车后输入Ctrl+Z：";
	std::cin.clear();
	int x = brackets();

	switch (x)
	{
	case -1:
		std::cout << "右括号过多" << std::endl;
		break;
	case -2:
		std::cout << "左括号过多" << std::endl;
		break;
	default:
		std::cout << "最大嵌套" << x << "层" << std::endl;
		break;
	}

	system("pause");

	return 0;
}