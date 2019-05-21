
#include <iostream>
#include <cctype>
#include <stack>
#include <string>
#include <vector>
#include <map>
using namespace std;
vector<string>s;
map<string, int>mm;
stack<string>st;
string t, alls, all;
int main()
{

    //���ȼ�
    mm["+"] = 1;
    mm["-"] = 1;
    mm["*"] = 2;
    mm["/"] = 2;
    mm["("] = 3;
    getline(cin, alls);



    //ɾ�ո��зǷ�����
    for (int i = 0; i < alls.size(); i++)
    {
        if (!isdigit(alls[i]) && alls[i] != '+' && alls[i] != '-' && alls[i] != '*' && alls[i] != '/' && alls[i] != '(' && alls[i] != ')' && alls[i] != '.' && alls[i] != ' ')
        {
            printf("#ERROR\n");
            printf("Unknown symbol\n");
            return 0;
        }
        if (alls[i] != ' ')
            all += alls[i];
    }



    //�жϱ��ʽ�Ƿ���ȷ
    int left_bracket = 0;
    for (int i = 0; i < all.size(); i++)
    {
        //������
        if (all[i] == '(')
            left_bracket++;
        else if (all[i] == ')')
        {
            if (left_bracket == 0)
            {
                printf("#ERROR\n");
                printf("Brackets do not match\n");
                return 0;
            }
            left_bracket--;
        }
        //���е�һ��
        if (i == 0)
        {
            if (all[i] != '+' && all[i] != '-' && all[i] != '(' && !isdigit(all[i]))
            {
                printf("#ERROR\n");
                printf("Operator error\n");
                return 0;
            }
        }
        //�������һ��
        else if (i == all.size() - 1)
        {
            if (all[i] != ')' && !isdigit(all[i]))
            {
                printf("#ERROR\n");
                printf("Operator error\n");
                return 0;
            }
            if (all[i] == ')' && all[i - 1] == '(')
            {
                printf("#ERROR\n");
                printf("Operator error\n");
                return 0;
            }
        }
        //�м��ַ���ö��ERROR���
        else
        {
            if (isdigit(all[i]))
            {
                if (all[i - 1] == ')' || all[i + 1] == '(')
                {
                    printf("#ERROR\n");
                    printf("Operator error\n");
                    return 0;
                }
            }
            else if (all[i] == '.')
            {
                if (!isdigit(all[i - 1]) || !isdigit(all[i + 1]))
                {
                    printf("#ERROR\n");
                    printf("radix point error\n");
                    return 0;
                }
            }
            else if (all[i] == '*' || all[i] == '/')
            {
                if ((!isdigit(all[i - 1]) && all[i - 1] != ')') || (!isdigit(all[i + 1]) && all[i + 1] != '+' && all[i + 1] != '-' && all[i + 1] != '('))
                {
                    printf("#ERROR\n");
                    printf("Operator error\n");
                    return 0;
                }
            }
            else if (all[i] == '+' || all[i] == '-')
            {
                if (isdigit(all[i - 1]) || all[i - 1] == ')')
                {
                    if (!isdigit(all[i + 1]) && all[i + 1] != '+' && all[i + 1] != '-')
                    {
                        printf("#ERROR\n");
                        printf("Operator error\n");
                        return 0;
                    }
                }
                else
                {
                    if (!isdigit(all[i + 1]))
                    {
                        printf("#ERROR\n");
                        printf("Operator error\n");
                        return 0;
                    }
                }
            }
            else if (all[i] == '(')
            {
                if (isdigit(all[i - 1]) || all[i - 1] == ')' || all[i + 1] == '*' || all[i + 1] == '/' || all[i + 1] == ')')
                {
                    printf("#ERROR\n");
                    printf("Operator error\n");
                    return 0;
                }
            }
            else if (all[i] == ')')
            {
                if ((!isdigit(all[i - 1]) && all[i - 1] != ')') || (all[i + 1] != '+' && all[i + 1] != '-' && all[i + 1] != '*' && all[i + 1] != '/' && all[i + 1] != ')'))
                {
                    printf("#ERROR\n");
                    printf("Operator error\n");
                    return 0;
                }
            }
        }
    }



    //��׺ת��׺
    for (int i = 0; i < all.size();)
    {
        if (!isdigit(all[i]))
        {
            //��ǰ�����ǼӼ��Ų���ǰһ���ַ��Ƿ����Ҳ��������ţ����ж�Ϊ������
            if ((i == 0 || !isdigit(all[i - 1])) && (all[i] == '+' || all[i] == '-') && (i == 0 || all[i - 1] != ')'))
            {
                if (all[i] == '-')
                    t = all[i];
                i++;
                goto qwe;
            }
            t = all[i];
            i++;
        }
        else
        {
            t.clear();
        qwe:
            for (; i < all.size(); i++)
            {
                if (!isdigit(all[i]) && all[i] != '.')
                    break;
                t += all[i];
            }
        }
        //���������
        if (isdigit(t[0]) || t.size() > 1)
            s.push_back(t);
        else
        {
            //����������ţ��������������ŵ����з���
            if (t == ")")
            {
                while (!st.empty())
                {
                    if (st.top() == "(")
                    {
                        st.pop();
                        break;
                    }
                    s.push_back(st.top());
                    st.pop();
                }
            }
            //������������
            else
            {
                while (!st.empty())
                {
                    if (st.top() == "(")
                        break;
                    if (mm[st.top()] >= mm[t])
                    {
                        s.push_back(st.top());
                        st.pop();
                    }
                    else
                        break;
                }
                st.push(t);
            }
        }
    }
    //ʣ�µķ��ų�������ȫ����ջ
    while (!st.empty())
    {
        if (st.top() != "(" && st.top() != ")")
            s.push_back(st.top());
        st.pop();
    }

    for (int i = 0; i < s.size(); i++)
    {
        if (i != 0)
            cout << " ";
        cout << s[i];
    }
    cout << endl;



    //��׺���ʽ��ֵ
    stack<double>num;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i].size() > 1 || isdigit(s[i][0]))
        {
            double nums = 0;
            double mul = 1;
            for (int j = s[i].size() - 1; j >= 0; j--)
            {
                if (isdigit(s[i][j]))
                {
                    nums += (s[i][j] - '0') * mul;
                    mul *= 10;
                }
                else if (s[i][j] == '.')
                {
                    nums /= mul;
                    mul = 1;
                }
                else if (s[i][j] == '-')
                    nums = -nums;
            }
            num.push(nums);
        }
        else
        {
            double a, b, sums;
            b = num.top();
            num.pop();
            a = num.top();
            num.pop();
            switch (s[i][0])
            {
            case '+':
                sums = a + b;
                break;
            case '-':
                sums = a - b;
                break;
            case '*':
                sums = a * b;
                break;
            case '/':
            {
                if (b == 0)
                {
                    printf("#ERROR\n");
                    printf("Can not be divided into zero.\n");
                    return 0;
                }
                sums = a / b;
            }
            }
            num.push(sums);
        }
    }
    printf("%.1lf\n", num.top());
}