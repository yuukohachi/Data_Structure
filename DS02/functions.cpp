#include "functions.h"
#include "Stack.h"
#include "Queue.h"
#include <iostream>

// ��������36��������Ҫ�� 0-35 ���ַ�ӳ���
const char charMap[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void Dec_2_N_Base()
{
	int n, input;
	std::cout << "�������N��N��2��36��";
	std::cin >> n;
	if (n < 2 || n>36) throw("N������Χ");

	std::cout << "����һ����������";
	std::cin >> input;
	if (input <= 0) throw("����ֵ������Χ");

	Stack<int> result;
	while (input > 0)
	{
		result.push(input % n);
		input /= n;
	}

	// ���
	std::cout << "��" << n << "���Ʊ�ʾΪ��";
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
		int prev = 0;// �洢ǰһ��Ԫ��
		int size = q.size();

		for (int j = 0; j < size; ++j) {
			int curr = q.pop();

			std::cout << curr << " ";

			// ������һ��
			q.push(prev + curr);
			prev = curr;
		}

		// ÿ��ĩβװ��һ��1
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
				return -1;// �����Ź���
			}
		}
	}

	if (!left.empty()) {
		return -2;// �����Ź���
	}
	else {
		return max;
	}

}
