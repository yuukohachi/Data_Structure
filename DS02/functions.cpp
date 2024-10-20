#include "functions.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>

// 建立至多36进制所需要的 0-35 号字符映射表
const char charMap[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void Dec_2_N_Base()
{
	int n, input;
	std::cout << "输入基数N，N在2到36：";
	std::cin >> n;
	if (n < 2 || n>36) throw("N超出范围");

	std::cout << "输入一个正整数：";
	std::cin >> input;
	if (input <= 0) throw("输入值超出范围");

	Stack<int> result;
	while (input > 0)
	{
		result.push(input % n);
		input /= n;
	}

	// 输出
	std::cout << "其" << n << "进制表示为：";
	for (int num = result.size(); num; --num)
	{
		std::cout << charMap[result.pop()];
	}

}

void triangle(int row)
{
	Queue<int> q;

	q.push(1);

	for (int i = 0; i < row; ++i) {
		int prev = 0;// 存储前一个元素
		int size = q.size();

		for (int j = 0; j < size; ++j) {
			int curr = q.pop();

			std::cout << curr << " ";

			// 生成下一行
			q.push(prev + curr);
			prev = curr;
		}

		// 每行末尾装入一个1
		q.push(1);

		std::cout << std::endl;
	}
}

int brackets()
{
	Stack<bool> left;
	char ch;
	int max = 0;

	while (std::cin.get(ch))
	{
		if (ch == '(') {
			left.push(true);
		}
		else if (ch == ')') {
			if (max < left.size()) {
				max = left.size();
			}

			try {
				left.pop();
			}
			catch (...) {
				return -1;// 右括号过多
			}
		}
	}

	if (!left.empty()) {
		return -2;// 左括号过多
	}
	else {
		return max;
	}

}
