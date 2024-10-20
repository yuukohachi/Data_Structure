#include "functions.h"
#include <iostream>

int main()
{
	SqList<int> sq1(5), sq2(5);
	sq1.insert(0, 1);
	sq1.insert(1, 2);
	sq1.insert(2, 3);
	sq1.insert(3, 4);
	sq1.insert(4, 5);// sq1={1,2,3,4,5}
	sq2.insert(0, 20);// 另一种插入演示
	sq2.insert(0, 10);
	sq2.insert(0, 6);
	sq2.insert(0, 4);
	sq2.insert(0, 2);// sq2={2,4,6,10,20}

	std::cout << "sq1:" << sq1 << std::endl << "sq2:" << sq2 << std::endl << std::endl;
	std::cout << "合并后:" << merge(sq1, sq2) << std::endl << std::endl;

	LinkList<int> la, lb;
	la.insert(0, 10);
	la.insert(0, 5);
	la.insert(0, 0);// la={0,5,10}
	lb.insert(lb.size(), 5);
	lb.insert(lb.size(), 6);
	lb.insert(lb.size(), 7);// lb={5,6,7}

	std::cout << "la:" << la << std::endl << "lb:" << lb << std::endl << std::endl;
	LinkList<int> lc = merge(la, lb);
	std::cout << "合并后:" << lc << std::endl;

	deduplicate(lc);
	std::cout << "删除重复元素后:" << lc << std::endl;

	reverse(lc);
	std::cout << "逆置后:" << lc << std::endl;

	// 以下为选作内容
	std::cout << std::endl;

	std::cout << "以形如 2x3+3x5+1x1+7x0 的方式输入多项式。常数项须以 x0 形式输入。系数范围0~999" << std::endl;
	SqList<int> polynomial = polynomialRead();
	std::cout << "相加结果为:";
	polynomialOut(polynomial);

	std::cout << std::endl << std::endl;

	HeadedLinkList<int> L, La, Lb;
	std::cin.clear();

	std::cout << "输入链表L的数据(以Ctrl+Z结尾)：";
	int data;
	while (std::cin >> data) {
		L.insert(L.size(), data);
	}
	split(L, La, Lb);

	std::cout << "La为：" << La << std::endl << "Lb为：" << Lb << std::endl;

	system("pause");

	return 0;
}