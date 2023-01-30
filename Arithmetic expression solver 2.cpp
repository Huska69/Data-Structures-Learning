//Arithmetic expression solver 2 C++

//Please use the class "BigDecimal" you wrote to redo the Arithmetic problem you did last week.
//All the rules are the same as the Arithmetic problem in the last week.
//You must use your own data structure and are not allowed to use any build in STL library or you will get up to 0 points.


//Input
//Expressions end up with line-break or end-of-file.
//123+456/789-2^(20+1)*2
//1/2^3
//0.1+0.035+8*2
//(((-8)/3)*0.5))^10
//++++++
//(^.^)/
///^0^)/)

//Output
//Result of the expression to the 2nd decimal place, "ERROR" when parentheses count does not match or operation error, ending with a "\n" of each line
//-4194180.42
//0.12
//16.14
//18.67
//ERROR
////ERROR
ERROR

#include <iostream>
#include <string>
using namespace std;
template <class T>

class Node
{
public:
    Node() {}
    Node(T d)
    {
        data = d;
    }
    Node(T d, Node<T> *p, Node<T> *n)
    {
        data = d;
        prev = p;
        next = n;
    }
    Node<T> *prev;
    Node<T> *next;
    T data;
};
template <class T>
class LinkedList
{
public:
    LinkedList()
    {
        head = NULL;
        tail = NULL;
    }
    void addToTail(T _data)
    {
        Node<T> *new_node = new Node<T>(_data, NULL, NULL);
        if (head == NULL)
        {
            head = new_node;
            tail = new_node;
        }
        else
        {
            tail->next = new_node;
            new_node->prev = tail;
            tail = new_node;
        }
    }
    Node<T> *head;
    Node<T> *tail;
};
template <class T>
class Stack
{
public:
    Stack()
    {
        list = new LinkedList<T>;
    }
    void push(T _data)
    {
        list->addToTail(_data);
    }
    T pop()
    {
        if (list->head == list->tail)
        {
            T t = list->head->data;
            list->head = NULL;
            list->tail = NULL;
            return t;
        }
        else
        {
            T t = list->tail->data;
            list->tail = list->tail->prev;
            list->tail->next = NULL;
            return t;
        }
    }
    T top()
    {
        Node<T> *cur = list->head;
        while (cur->next != NULL)
            cur = cur->next;
        T t = cur->data;
        return t;
    }
    bool isEmpty()
    {
        if (list->head == NULL)
            return 1;
        else
            return 0;
    }
    int size()
    {
        int n = 0;
        Node<T> *cur = list->head;
        while (cur != NULL)
        {
            n++;
            cur = cur->next;
        }
        return n;
    }
    void print()
    {
        Node<T> *cur = list->head;
        while (cur != NULL)
        {
            cout << cur->data << " ";
            cur = cur->next;
        }
    }
    LinkedList<T> *list;
};
string bankerrounding(string temp)
{
    if (temp.size() <= 2)
    {
        if (temp.size() < 2)
            temp += '0';
        if (temp.size() < 1)
            temp += '0';
        return temp;
    }
    string ans;
    if (temp[2] > '5')
    {
        char tp = temp[1] + 1;
        if (tp - '0' == 10)
        {
            tp = '0';
            ans += tp;
            tp = temp[0] + 1;
            ans = tp + ans;
        }
        else
        {
            ans += temp[0];
            char tp = temp[1] + 1;
            ans += tp;
        }
    }
    else if (temp[2] < '5')
    {
        ans += temp[0];
        ans += temp[1];
    }
    else
    {
        for (int i = 3; i < temp.size(); i++)
        {
            if (temp[i] != '0')
            {
                char tp = temp[1] + 1;
                if (tp - '0' == 10)
                {
                    tp = '0';
                    ans += tp;
                    tp = temp[0] + 1;
                    ans = tp + ans;
                }
                else
                {
                    ans += temp[0];
                    char tp = temp[1] + 1;
                    ans += tp;
                }
                return ans;
            }
        }
        int num = temp[1] - '0';
        if (num % 2 == 1)
        {
            char tp = temp[1] + 1;
            if (tp - '0' == 10)
            {
                tp = '0';
                ans += tp;
                tp = temp[0] + 1;
                ans = tp + ans;
            }
            else
            {
                ans += temp[0];
                char tp = temp[1] + 1;
                ans += tp;
            }
            return ans;
        }
        else
        {
            ans += temp[0];
            ans += temp[1];
        }
    }
    return ans;
}
class BigDecimal
{
public:
    BigDecimal()
    {
        inte = "";
        deci = "";
    }
    void input(string r)
    {
        inte = "";
        deci = "";
        int i = 0;
        if (r[i] == '-')
        {
            this->minus = true;
            i++;
        }
        else
            this->minus = false;
        while (r[i] != '.' && i < r.length())
            inte += r[i++];
        i++;
        while (i < r.length())
            deci += r[i++];
    }
    void align(BigDecimal *temp)
    {
        // int部分
        int numa, numb, dis;
        numb = temp->inte.size();
        numa = inte.size();
        if (numa > numb)
        {
            dis = numa - numb;
            for (int i = 0; i < dis; i++)
            {
                temp->inte = '0' + temp->inte;
            }
        }
        else if (numa < numb)
        {
            dis = numb - numa;
            for (int i = 0; i < dis; i++)
            {
                inte = '0' + inte;
            }
        }
        //小數部分
        numb = temp->deci.size();
        numa = deci.size();
        if (numa > numb)
        {
            dis = numa - numb;
            for (int i = 0; i < dis; i++)
            {
                temp->deci += '0';
            }
        }
        else if (numa < numb)
        {
            dis = numb - numa;
            for (int i = 0; i < dis; i++)
            {
                deci += '0';
            }
        }
    }

    void adjust()
    {
        int num1 = 0;
        string ans, ans1;
        for (num1 = 0; num1 < inte.size(); num1++)
        {
            if (num1 == inte.size() - 1 || inte[num1] != '0')
                break;
        }
        for (; num1 < inte.size(); num1++)
        {
            ans += inte[num1];
        }
        inte = ans;
        for (num1 = deci.size() - 1; num1 >= 0; num1--)
        {
            if (num1 == 0 || deci[num1] != '0')
                break;
        }
        for (; num1 >= 0; num1--)
        {
            ans1 = deci[num1] + ans1;
        }
        deci = ans1;
    }
    BigDecimal operator+(BigDecimal bigDecimal) //對齊後再加
    {
        BigDecimal ans;
        BigDecimal numa;
        BigDecimal numb;
        numa = (*this);
        numb = bigDecimal;
        //判斷正負
        if (this->minus || bigDecimal.minus)
        {
            if (minus && !bigDecimal.minus)
            {
                minus = false;
                ans = bigDecimal - (*this);
                minus = true;
                return ans;
            }
            else if (!minus && bigDecimal.minus)
            {
                bigDecimal.minus = false;
                ans = (*this) - bigDecimal;
                bigDecimal.minus = true;
                return ans;
            }
            else
            {
                bigDecimal.minus = false;
                minus = false;
                ans = (*this) + bigDecimal;
                bigDecimal.minus = true;
                minus = true;
                ans.minus = true;
                return ans;
            }
        }
        numa.align(&numb); ///////ao6e93
        string str1, str2;
        str1 = numa.deci;
        str2 = numb.deci;
        int overflow = 0, tempnum;
        char charnum;
        for (int i = str1.size() - 1; i >= 0; i--)
        {
            tempnum = str1[i] - '0' + str2[i] - '0' + overflow;
            overflow = 0;
            if (tempnum >= 10)
            {
                tempnum -= 10;
                overflow++;
            }
            charnum = '0' + tempnum;
            ans.deci = charnum + ans.deci;
        }
        str1 = numa.inte;
        str2 = numb.inte;
        for (int i = str1.size() - 1; i >= 0; i--)
        {
            tempnum = str1[i] - '0' + str2[i] - '0' + overflow;
            overflow = 0;
            if (tempnum >= 10)
            {
                tempnum -= 10;
                overflow++;
            }
            charnum = '0' + tempnum;
            ans.inte = charnum + ans.inte;
        }
        if (overflow != 0)
        {
            ans.inte = '1' + ans.inte;
        }
        ans.adjust(); //////////////////
        return ans;
    }

    BigDecimal operator-(BigDecimal bigDecimal) //對齊後再減
    {
        BigDecimal ans;
        BigDecimal numa;
        BigDecimal numb;
        numa = (*this);
        numb = bigDecimal;
        //判斷正負
        if (minus || bigDecimal.minus)
        {
            if (minus && !bigDecimal.minus)
            {
                minus = false;
                ans = (*this) + bigDecimal;
                minus = true;
                ans.minus = true;
                return ans;
            }
            else if (!minus && bigDecimal.minus)
            {
                bigDecimal.minus = false;
                ans = (*this) + bigDecimal;
                bigDecimal.minus = true;
                return ans;
            }
            else
            {
                bigDecimal.minus = false;
                minus = false;
                ans = bigDecimal - (*this);
                bigDecimal.minus = true;
                minus = true;
                return ans;
            }
        }
        numa.align(&numb); ////////////////////////
        //比大小
        string str1, str2;
        str1 = numa.inte + numa.deci;
        str2 = numb.inte + numb.deci;
        if (str1 < str2)
        {
            ans = bigDecimal - (*this);
            ans.minus = true;
            return ans;
        }
        str1 = numa.deci;
        str2 = numb.deci;
        int overflow = 0, tempnum;
        char charnum;
        for (int i = str1.size() - 1; i >= 0; i--)
        {
            tempnum = str1[i] - str2[i] + overflow;
            overflow = 0;
            if (tempnum < 0)
            {
                tempnum += 10;
                overflow--;
            }
            charnum = '0' + tempnum;
            ans.deci = charnum + ans.deci;
        }
        str1 = numa.inte;
        str2 = numb.inte;
        for (int i = str1.size() - 1; i >= 0; i--)
        {
            tempnum = str1[i] - str2[i] + overflow;
            overflow = 0;
            if (tempnum < 0)
            {
                tempnum += 10;
                overflow--;
            }
            charnum = '0' + tempnum;
            ans.inte = charnum + ans.inte;
        }
        ans.adjust(); ///////////////////
        return ans;
    }

    BigDecimal operator*(BigDecimal bigDecimal) //直式乘法
    {
        BigDecimal ans;
        BigDecimal beadd;
        BigDecimal temp;
        BigDecimal obj1;
        BigDecimal obj2;
        obj1 = (*this);
        obj2 = bigDecimal;
        string numa, numb;
        int floatnum, num1, num2, count = 0, overflow = 0;
        char tp;
        beadd.inte += '0';
        beadd.deci += '0';
        temp.deci += '0';
        obj1.align(&obj2); ///////////
        floatnum = obj2.deci.size() * 2;
        numa = obj1.inte + obj1.deci;
        numb = obj2.inte + obj2.deci;
        int arr[numa.size() * 2];
        for (int i = 0; i < numa.size() * 2; i++)
        {
            arr[i] = 0;
        }
        for (int i = numb.size() - 1; i >= 0; i--) //數字陣列結束
        {
            num2 = numb[i] - '0';
            temp.inte = "";
            for (int m = numa.size() - 1; m >= 0; m--)
            {
                num1 = numa[m] - '0';
                arr[i + m + 1] += (num1 * num2);
            }
        }
        for (int i = numb.size() * 2 - 1; i > 0; i--)
        {
            while (arr[i] >= 10)
            {
                arr[i] -= 10;
                arr[i - 1] += 1;
            }
        }
        for (int i = numb.size() * 2 - floatnum; i < numb.size() * 2; i++)
        {
            tp = arr[i] + '0';
            ans.deci += tp;
        }
        for (int i = 0; i < numb.size() * 2 - floatnum; i++)
        {
            tp = arr[i] + '0';
            ans.inte += tp;
        }
        ans.adjust(); ////////////////////
        if (minus || bigDecimal.minus)
        {
            if (minus && bigDecimal.minus)
            {
            }
            else
                ans.minus = true;
        }
        if (ans.deci.length() > 10)
            ans.deci = ans.deci.substr(0, 55);
        return ans;
    }

    BigDecimal operator/(BigDecimal bigDecimal) //從位數大的開始減
    {
        bool zeroflag = true;
        BigDecimal ans;
        BigDecimal numa;
        BigDecimal numb;
        BigDecimal temp;
        BigDecimal obj1;
        BigDecimal obj2;
        obj1 = (*this);
        obj2 = bigDecimal;
        obj1.align(&obj2); //////////////
        numb.inte = obj2.inte + obj2.deci;
        numb.deci = "0";
        numa.inte = obj1.inte + obj1.deci;
        numa.deci = "0";
        temp.deci += '0';
        for (int i = 0; i < numb.inte.size(); i++)
        {
            if (numb.inte[i] != '0')
            {
                zeroflag = false;
                break;
            }
        }
        if (zeroflag)
        {
            ans.inte = "0";
            ans.deci = "0";
            return ans;
        }
        int floatnum = obj2.deci.size(), count = 0;
        char tp;
        // int part
        for (int i = 0; i < numa.inte.size(); i++)
        {
            BigDecimal *abc = new BigDecimal;
            temp.inte += numa.inte[i];
            temp = temp - numb;
            while (!temp.minus)
            {
                count++;
                temp = temp - numb;
            }
            temp = temp + numb;
            tp = count + '0';
            ans.inte += tp;
            count = 0;
        }
        for (int i = 0; i < 50; i++)
        {
            temp.inte += '0';
            temp = temp - numb;
            while (!temp.minus)
            {

                count++;
                temp = temp - numb;
            }
            temp = temp + numb;
            tp = count + '0';
            ans.deci += tp;
            count = 0;
        }
        ans.adjust(); //////////////////
        if (minus || bigDecimal.minus)
        {
            if (minus && bigDecimal.minus)
            {
            }
            else
                ans.minus = true;
        }
        return ans;
    }

    BigDecimal operator^(BigDecimal bigDecimal)
    {
        if ((bigDecimal.inte == "0") && (bigDecimal.deci == "0" || bigDecimal.deci.length() == 0 || bigDecimal.deci == "00"))
        {
            BigDecimal re;
            re.inte = "1";
            return re;
        }
        if (this->minus && this->inte == "1" && this->deci == "00" &&
            (bigDecimal.inte[bigDecimal.inte.length() - 1] - '0') % 2 == 0)
        {
            BigDecimal re;
            re.minus = false;
            re.inte = "1";
            return re;
        }
        int count = 0;
        bool here = false;
        BigDecimal ans;
        BigDecimal numa;
        BigDecimal numb;
        BigDecimal numc;
        BigDecimal temp;
        BigDecimal multi;
        BigDecimal one;
        BigDecimal lnans;
        one.inte += '1';
        one.deci += '0';
        ans = (*this);
        numc = ans;
        numb = bigDecimal;
        numb.minus = false;
        numb = numb - one;
        numb = numb - one;
        while (!numb.minus)
        {
            ans = ans * numc;
            numb = numb - one;
        }
        numb = numb + one;
        if (numb.minus)
        {
            here = true;
            numb = numb + one;
        }
        numb.adjust();
        if (numb.deci.size() == 1 && numb.deci[0] == '0')
        {
            if (bigDecimal.minus)
                ans = one / ans;
            ans.adjust(); ///////////
            return ans;
        }
        // cout<<ans<<endl;
        //小數部分;
        //先算ln a;
        numa = (*this);
        multi = one; // n
        numc = numa - one;
        numc = numc / numa;
        temp = numc;  // x-1/x
        lnans = numc; //
        for (int i = 0; i < 8000; i++)
        {
            BigDecimal temp2;
            multi = multi + one; // n++
            temp = temp * numc;  //
            temp2 = temp / multi;
            lnans = lnans + temp2;
        }
        lnans = lnans * numb;
        //算exp
        temp = lnans;
        numc = lnans;
        lnans = lnans + one; // x
        multi = one;         // n
        numb = one;
        for (int i = 0; i < 50; i++)
        {
            BigDecimal temp2;
            multi = multi + one; // n++
            numb = multi * numb; // n!
            temp = temp * numc;  // x乘冪
            temp2 = temp / numb;
            lnans = lnans + temp2;
        }
        if (here)
            ans = lnans;
        else
            ans = ans * lnans;
        if (bigDecimal.minus)
            ans = one / numa;
        ans.adjust(); ///////////////
        return ans;
    }

    friend std::ostream &operator<<(std::ostream &out, BigDecimal bigDecimal)
    {

        int i = 0, num = 0;
        string ans;
        string temp;
        i = bigDecimal.deci.size() - 1;
        // cout<<bigDecimal->deci<<endl;
        while (i > 0 && bigDecimal.deci[i] == '0')
            i--;
        for (int m = 0; m <= i; m++)
            temp += bigDecimal.deci[m];
        // cout<<"??"<<bigDecimal->deci[0]<<"??"<<endl;
        temp = bankerrounding(temp);
        if (temp[0] - '0' == 10)
        {
            temp[0] = '0';
            num++;
        }
        // cout<<temp<<endl;
        i = 0;
        while (i < bigDecimal.inte.size() - 1 && bigDecimal.inte[i] == '0')
            i++;
        char tp;
        for (int m = bigDecimal.inte.size() - 1; m >= i; m--)
        {
            tp = bigDecimal.inte[m] + num;
            // cout<<tp<<endl;
            num = 0;
            if (tp - '0' >= 10)
            {
                tp = '0';
                num++;
            }
            ans = tp + ans;
        }
        if (num != 0)
        {
            ans = '1' + ans;
        }
        ans += '.';
        ans += temp;
        if (bigDecimal.minus)
            ans = '-' + ans;
        out << ans;
        return out;
    }

    friend std::istream &operator>>(std::istream &in, BigDecimal *data)
    {
        string temp;
        data->inte = "";
        data->deci = "";
        data->minus = false;
        in >> temp;
        int i = 0;
        if (temp[0] == '-')
        {
            data->minus = true;
            i++;
        }
        for (; i < temp.size() && temp[i] != '.'; i++)
        {
            data->inte += temp[i];
        }
        if (i == temp.size())
        {
            data->deci += '0';
        }
        else //小數點
        {
            for (i++; i < temp.size(); i++)
            {
                data->deci += temp[i];
            }
        }
        return in;
    }

    bool minus = false;
    string inte;
    string deci;
};
int priority(char c)
{
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    else
        return 0;
}
int index = 0;
string negative(string s)
{
    int flag = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
            flag = 1;
        if (s[i] == '-')
        {
            if (!flag)
            {
                s[i] = '&';
            }
            else if (s[i + 1] == '-')
            {
                s[i] = '+';
                s.erase(i + 1, 1);
            }
        }
        if ((s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '^') && s[i + 1] == '-')
            s[i + 1] = '&';
    }
    return s;
}
bool check(string s)
{
    int len = s.length(), left = 0, right = 0;
    if (s[len - 1] == '+' || s[len - 1] == '-' || s[len - 1] == '*' || s[len - 1] == '/' || s[len - 1] == '^' || s[len - 1] == '(')
        return false;
    int flag = 0;
    if (s[0] == '.' || s[0] == '*' || s[0] == '/' || s[0] == '+')
        return false;
    for (int i = 0; i < len; i++)
    {
        if (s[i] == '+' || s[i] == '*' || s[i] == '/' || s[i] == '^' || s[i] == '.')
        {
            if (s[i + 1] == s[i])
                return false;
            if (s[i + 1] == '.')
                return false;
        }
        if (s[i] == '-')
        {
            if (!(s[i + 1] >= '0' && s[i + 1] <= '9') && s[i + 2] == '-')
                return false;
        }
        if (s[i] == '(')
        {
            if (s[i + 1] == '+' || s[i + 1] == '*' || s[i + 1] == '/' || s[i + 1] == '^' || s[i + 1] == '.')
                return false;
        }
        if (s[i] >= '0' && s[i] <= '9')
            flag = 1;
        if (s[i] == '(')
            right++;
        else if (s[i] == ')')
            left++;
    }
    if (left != right)
        return false;
    if (!flag)
        return false;
    return true;
}
string *transfer(string s)
{
    static string st[2000];
    index = 0;
    Stack<char> *op = new Stack<char>;
    if (!check(s))
        return NULL;
    s = negative(s);
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            string n = "";
            while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
            {
                n += s[i];
                i++;
            }
            index++;
            st[index] = n;
            i--;
        }
        else if (s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^')
        {
            while (op->size() != 0 && priority(s[i]) <= priority(op->top()))
            {
                string _op = "";
                _op += op->pop();
                index++;
                st[index] = _op;
            }
            op->push(s[i]);
        }
        else if (s[i] == '&')
        {
            i++;
            string n = "&";
            while ((s[i] >= '0' && s[i] <= '9') || s[i] == '.')
            {
                n += s[i];
                i++;
            }
            index++;
            st[index] = n;
            i--;
        }
        else if (s[i] == '(')
            op->push(s[i]);
        else if (s[i] == ')')
        {
            while (op->size() != 0 && op->top() != '(')
            {
                string _op = "";
                _op += op->pop();
                index++;
                st[index] = _op;
            }
            op->pop();
        }
    }
    while (op->size() != 0)
    {
        string _op = "";
        _op += op->pop();
        index++;
        st[index] = _op;
    }
    return st;
}

BigDecimal compute(string st[2000])
{
    Stack<string> *d = new Stack<string>;
    for (int i = 0; i <= index; i++)
    {
        if (st[i][0] >= '0' && st[i][0] <= '9')
            d->push(st[i]);
        else if (st[i][0] == '&')
        {
            st[i].erase(0, 1);
            string c = "-";
            c += st[i];
            d->push(c);
        }
        else if (st[i] == "+" || st[i] == "-" || st[i] == "*" || st[i] == "/" || st[i] == "^")
        {
            string b = d->pop();
            string a = d->pop(); 
            BigDecimal r1;
            BigDecimal r2;
            r1.input(a);
            r2.input(b);
            BigDecimal p;
            if (st[i] == "+")
                p = r1 + r2;
            else if (st[i] == "-")
                p = r1 - r2;
            else if (st[i] == "*")
                p = r1 * r2;
            else if (st[i] == "/")
                p = r1 / r2;
            else if (st[i] == "^")
                p = r1 ^ r2;
            p.deci = bankerrounding(p.deci);
            string c = "";
            if (p.minus)
                c += "-";
            c += p.inte;
            c += ".";
            c += p.deci;
            d->push(c);
        }
    }
    BigDecimal re;
    re.input(d->pop());
    return re;
}
int main()
{
    string s;
    while (cin >> s)
    {
        string *str = transfer(s);
        if (str == NULL)
            cout << "ERROR\n";
        else
            cout << compute(str) << endl;
    }
}
