#include "functions.h"

SqList<int> polynomialRead()
{
	using namespace std;

	SqList<int> result(1000);
	for (int i = 0; i < 1000; ++i) {
		result.insert(i, 0);// 初始化
	}

	string input;// 可以正则，但是懒
	cin >> input;

	int coef, exp;
	string temp;  // 暂时存储数字字符的字符串
	bool C_E = true;// Coefficient/Exponent，用于交替系数和指数

	for (char ch : input) {
		if (isdigit(ch)) {
			temp += ch;
		}
		else
		{
			// 转换存储的数字字符串
			if (!temp.empty())
			{
				int num = stoi(temp);
				if (C_E) { coef = num; }
				else {// 每读两次写入一次
					exp = num;
					int coefTemp = result.get(exp);
					result.change(exp, coef + coefTemp);// 实现+=
				}

				C_E = !C_E;// 切换处理对象
				temp.clear();
			}
		}
	}

	// 末尾数字的处理
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
        if (sq.get(i)) ++nonzero;// 统计非零项的数量
    }

    if (nonzero == 0) {// 如果没有非零项，输出为0
        cout << "0" << endl;
        return;
    }

    int exp = 999;
    bool firstTerm = true;// 标志是否为第一项，避免多余的加号
    while (exp >= 0 && nonzero > 0)
    {
        int coef = sq.get(exp);
        if (coef != 0)
        {
            if (!firstTerm) {
                cout << (coef > 0 ? "+" : "");// 非第一项时处理正号
            }

            if (exp == 0)
            {
                cout << coef;// 常数项直接输出
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
            firstTerm = false;// 处理完第一项
        }
        --exp;
    }
}

void split(HeadedLinkList<int>& input, HeadedLinkList<int>& La, HeadedLinkList<int>& Lb)
{
    La.clear(), Lb.clear();// 确保 La Lb 是空表

    auto it_in = input.begin();// typename HeadedLinkList<int>::Iterator 真的太蠢了
                                //我现在知道为什么别人写代码用 auto 了

    while (it_in!=NULL)
    {
        if (*it_in % 2) {// 奇数
            La.insert(La.size(), *it_in);
        }
        else {// 偶数
            Lb.insert(Lb.size(), *it_in);
        }
        ++it_in;
    }
}
