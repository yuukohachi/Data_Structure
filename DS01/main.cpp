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
	sq2.insert(0, 20);// ��һ�ֲ�����ʾ
	sq2.insert(0, 10);
	sq2.insert(0, 6);
	sq2.insert(0, 4);
	sq2.insert(0, 2);// sq2={2,4,6,10,20}

	std::cout << "sq1:" << sq1 << std::endl << "sq2:" << sq2 << std::endl << std::endl;
	std::cout << "�ϲ���:" << merge(sq1, sq2) << std::endl << std::endl;

	LinkList<int> la, lb;
	la.insert(0, 10);
	la.insert(0, 5);
	la.insert(0, 0);// la={0,5,10}
	lb.insert(lb.size(), 5);
	lb.insert(lb.size(), 6);
	lb.insert(lb.size(), 7);// lb={5,6,7}

	std::cout << "la:" << la << std::endl << "lb:" << lb << std::endl << std::endl;
	LinkList<int> lc = merge(la, lb);
	std::cout << "�ϲ���:" << lc << std::endl;

	deduplicate(lc);
	std::cout << "ɾ���ظ�Ԫ�غ�:" << lc << std::endl;

	reverse(lc);
	std::cout << "���ú�:" << lc << std::endl;

	// ����Ϊѡ������
	std::cout << std::endl;

	std::cout << "������ 2x3+3x5+1x1+7x0 �ķ�ʽ�������ʽ������������ x0 ��ʽ���롣ϵ����Χ0~999" << std::endl;
	SqList<int> polynomial = polynomialRead();
	std::cout << "��ӽ��Ϊ:";
	polynomialOut(polynomial);

	std::cout << std::endl << std::endl;

	HeadedLinkList<int> L, La, Lb;
	std::cin.clear();

	std::cout << "��������L������(��Ctrl+Z��β)��";
	int data;
	while (std::cin >> data) {
		L.insert(L.size(), data);
	}
	split(L, La, Lb);

	std::cout << "LaΪ��" << La << std::endl << "LbΪ��" << Lb << std::endl;

	system("pause");

	return 0;
}