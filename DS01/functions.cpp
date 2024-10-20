#include "functions.h"

SqList<int> polynomialRead()
{
	using namespace std;

	SqList<int> result(1000);
	for (int i = 0; i < 1000; ++i) {
		result.insert(i, 0);// ��ʼ��
	}

	string input;// �������򣬵�����
	cin >> input;

	int coef, exp;
	string temp;  // ��ʱ�洢�����ַ����ַ���
	bool C_E = true;// Coefficient/Exponent�����ڽ���ϵ����ָ��

	for (char ch : input) {
		if (isdigit(ch)) {
			temp += ch;
		}
		else
		{
			// ת���洢�������ַ���
			if (!temp.empty())
			{
				int num = stoi(temp);
				if (C_E) { coef = num; }
				else {// ÿ������д��һ��
					exp = num;
					int coefTemp = result.get(exp);
					result.change(exp, coef + coefTemp);// ʵ��+=
				}

				C_E = !C_E;// �л��������
				temp.clear();
			}
		}
	}

	// ĩβ���ֵĴ���
	if (!temp.empty()) {
		if (!C_E) {
			exp = stoi(temp);
			int coefTemp = result.get(exp);
			result.change(exp, coef + coefTemp);
		}
	}

	return result;
}

void polynomialOut(const SqList<int>& sq)
{
    using namespace std;

    int nonzero = 0;
    for (int i = 0; i < 1000; ++i) {
        if (sq.get(i)) ++nonzero;// ͳ�Ʒ����������
    }

    if (nonzero == 0) {// ���û�з�������Ϊ0
        cout << "0" << endl;
        return;
    }

    int exp = 999;
    bool firstTerm = true;// ��־�Ƿ�Ϊ��һ��������ļӺ�
    while (exp >= 0 && nonzero > 0)
    {
        int coef = sq.get(exp);
        if (coef != 0)
        {
            if (!firstTerm) {
                cout << (coef > 0 ? "+" : "");// �ǵ�һ��ʱ��������
            }

            if (exp == 0)
            {
                cout << coef;// ������ֱ�����
            }
            else if (exp == 1)
            {
                if (coef == 1) {
                    cout << "x";
                }
                else if (coef == -1) {
                    cout << "-x";
                }
                else {
                    cout << coef << "x";
                }
            }
            else
            {
                if (coef == 1) {
                    cout << "x^" << exp;
                }
                else if (coef == -1) {
                    cout << "-x^" << exp;
                }
                else {
                    cout << coef << "x^" << exp;
                }
            }

            --nonzero;
            firstTerm = false;// �������һ��
        }
        --exp;
    }
}

void split(HeadedLinkList<int>& input, HeadedLinkList<int>& La, HeadedLinkList<int>& Lb)
{
    La.clear(), Lb.clear();// ȷ�� La Lb �ǿձ�

    auto it_in = input.begin();// typename HeadedLinkList<int>::Iterator ���̫����
                                //������֪��Ϊʲô����д������ auto ��

    while (it_in!=NULL)
    {
        if (*it_in % 2) {// ����
            La.insert(La.size(), *it_in);
        }
        else {// ż��
            Lb.insert(Lb.size(), *it_in);
        }
        ++it_in;
    }
}
