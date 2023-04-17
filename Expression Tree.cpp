#include <iostream>

using namespace std;
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
        // int part
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
        //decimal part
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
    BigDecimal operator+(BigDecimal bigDecimal) //after aligning
    {
        BigDecimal ans;
        BigDecimal numa;
        BigDecimal numb;
        numa = (*this);
        numb = bigDecimal;
        //Judge positive or negative
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
        numa.align(&numb); 
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
        ans.adjust(); 
        return ans;
    }

    BigDecimal operator-(BigDecimal bigDecimal) //Subtract after alignment
    {
        BigDecimal ans;
        BigDecimal numa;
        BigDecimal numb;
        numa = (*this);
        numb = bigDecimal;
        //Judge positive or negative
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
        numa.align(&numb); 
        //than size
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
        ans.adjust(); 
        return ans;
    }

    BigDecimal operator*(BigDecimal bigDecimal) //straight multiplication
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
        obj1.align(&obj2); 
        floatnum = obj2.deci.size() * 2;
        numa = obj1.inte + obj1.deci;
        numb = obj2.inte + obj2.deci;
        int arr[numa.size() * 2];
        for (int i = 0; i < numa.size() * 2; i++)
        {
            arr[i] = 0;
        }
        for (int i = numb.size() - 1; i >= 0; i--) //end of number array
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
        ans.adjust(); 
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

    BigDecimal operator/(BigDecimal bigDecimal) //Subtract from the larger number of digits
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
        obj1.align(&obj2); 
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
        ans.adjust(); 
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
            ans.adjust(); 
            return ans;
        }
        //decimal part;
        //First calculate ln a;
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
            temp = temp * numc;  // xExponentiation
            temp2 = temp / numb;
            lnans = lnans + temp2;
        }
        if (here)
            ans = lnans;
        else
            ans = ans * lnans;
        if (bigDecimal.minus)
            ans = one / numa;
        ans.adjust(); 
        return ans;
    }

    friend std::ostream &operator<<(std::ostream &out, BigDecimal bigDecimal)
    {

        int i = 0, num = 0;
        string ans;
        string temp;
        i = bigDecimal.deci.size() - 1;
        while (i > 0 && bigDecimal.deci[i] == '0')
            i--;
        for (int m = 0; m <= i; m++)
            temp += bigDecimal.deci[m];
        temp = bankerrounding(temp);
        if (temp[0] - '0' == 10)
        {
            temp[0] = '0';
            num++;
        }
        i = 0;
        while (i < bigDecimal.inte.size() - 1 && bigDecimal.inte[i] == '0')
            i++;
        char tp;
        for (int m = bigDecimal.inte.size() - 1; m >= i; m--)
        {
            tp = bigDecimal.inte[m] + num;
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
        else //decimal point
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
template <class T>
class expression
{
public:
    expression()
    {
        str_index = 0;
        for (int i = 0; i < 1000; i++)
            str[i] = "";
    }
    void insert(string s)
    {
        for (int i = 0; i < s.length(); i++)
        {
            string copy = "";
            while (s[i] != ',' && i < s.length())
            {
                copy += s[i];
                i++;
            }
            if (copy != "")
            {
                str[str_index] = copy;
                str_index++;
            }
        }
    }
    bool check()
    { // correct
        int ch = 0, number = 0;
        for (int i = 0; i < str_index; i++)
        {
            if (str[i] == "-" || str[i] == "+" || str[i] == "*" || str[i] == "/" || str[i] == "^")
                ch++;
            else if (str[i] == "NULL")
                continue;
            else
                number++;
        }
        if (number - 1 == ch)
            return true;
        return false;
    }
    bool checkla()
    {
        for (int i = 1; i < str_index; i++)
        {
            if (str[i] != "    " && str[i] != "NULL")
                return false;
        }
        return true;
    }
    string output()
    {
        if (!check())
        {
            string ans = "ERROR";
            return ans;
        }
        for (int i = str_index - 1; i >= 0; i--)
        {
            string num1 = "", num2 = "";
            if (str[i] == "+" || str[i] == "-" || str[i] == "*" || str[i] == "/" || str[i] == "^")
            {
                bool flag = false;
                for (int j = str_index - 1; j >= 0; j--)
                {
                    if ((str[j][0] >= '0' && str[j][0] <= '9') || (str[j][0] == '-' && str[j][1] >= '0' && str[j][1] <= '9'))
                    {
                        if (flag == false)
                        {
                            num1 = str[j];
                            flag = true;
                            str[j] = "    ";
                        }
                        else if (flag)
                        {
                            num2 = str[j];
                            flag = false;
                            str[j] = "    ";
                            break;
                        }
                    }
                }
                BigDecimal compute1, compute2;
                compute1.input(num2), compute2.input(num1);
                BigDecimal re;
                if (str[i] == "+")
                    re = compute1 + compute2;
                else if (str[i] == "-")
                    re = compute1 - compute2;
                else if (str[i] == "*")
                    re = compute1 * compute2;
                else if (str[i] == "/")
                    re = compute1 / compute2;
                else if (str[i] == "^")
                    re = compute1 ^ compute2;
                re.deci = bankerrounding(re.deci);
                string k = "";
                if (re.minus)
                    k += "-";
                k += re.inte;
                k += ".";
                k += re.deci;
                str[i] = k;
            }
        }
        if (!checkla())
        {
            string ans = "ERROR";
            return ans;
        }
        return str[0];
    }
    string str[1000];
    int str_index;
};
string addzero(string s)
{
    if (s == "ERROR")
        return s;
    bool index = 0;
    for (int i = 0; i < s.length(); i++)
    {
        if (s[i] == '.')
        {
            index = 1;
            if (i == s.length() - 2)
                s += '0';
            break;
        }
    }
    if (index == 0)
        s += "0.00";
    return s;
}
string align_int(string s)
{
    s[s.length() - 2] = '0';
    int i = s.length() - 4;
    bool flag = 0;
    while (1)
    {
        if (flag)
            break;
        else if (s[i] == '-')
            break;
        else if (i == 0)
        {
            s[i] = '0';
            break;
        }
        else
        {
            if (s[i] == '9')
                s[i] = '0';
            else
            {
                flag = 1;
                s[i]++;
            }
        }
        i--;
    }
    if (flag == 0)
    {
        if (s[0] == '-')
        {
            string k = "-1";
            for (int i = 1; i < s.length(); i++)
                k += s[i];
            s = k;
        }
        else
        {
            string k = "1";
            k += s;
            s = k;
        }
    }
    return s;
}
int main()
{
    string input = "";
    while (getline(cin, input))
    {
        expression<string> *tree = new expression<string>();
        tree->insert(input);
        string ans = tree->output();
        ans = addzero(ans);
        if (ans[ans.length() - 2] == ':')
            ans = align_int(ans);
        cout << ans << endl;
    }
    return 0;
}
