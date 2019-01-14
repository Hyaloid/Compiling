# include<iostream>
#include <bits/stdc++.h>
using namespace std;

bool key_words(string s)//关键字
{
    static vector<string> keyVec = { "main", "int", "float", "double", "char",
        "if", "then","else", "switch", "case", "break", "continue", "while",
        "do", "for" ,"#include","using","namespace","std","return"};
    vector<string>::iterator result = find(keyVec.begin(), keyVec.end(),s);
    if (result != keyVec.end())
        return true;
    else return false;
}
bool ident(string s)//标识符
{
    if (!key_words(s))//标识符不能是关键字
    {
        if ((s[0] >= 'a'&&s[0] <= 'z') || (s[0] >= 'A'&&s[0] <= 'Z'))//是字母
        {
            for (int i = 1; i < s.length(); i++)
            {
                if ((s[i] >= 'a'&&s[i] <= 'z') || (s[i] >= 'A'&&s[i] <= 'Z')
                    || (s[i] >= '0'&&s[i] <= '9'))
                    continue;
                else return false;
            }
            return true;
        }
        return false;
    }
    return false;
}

bool digit(string s)//整数
{
    if (s[0] >= '0'&&s[0] <= '9')
    {
        for (int i = 1; i < s.length(); ++i)
            if (s[i] >= '0'&&s[i] <= '9')
                continue;
            else return false;
        return true;
    }
    return false;
}

bool points(string s)//小数
{
    if (s[0] >= '0'&&s[0] <= '9')
    {
        for (int i = 1; i < s.length(); ++i)
            if ((s[i] >= '0'&&s[i] <= '9')||s[i]=='.')
                continue;
            else return false;
        return true;
    }
    return false;
}

bool is_operator(string s)//运算符
{
    static vector<string> opeVec = { "=","+","-","*","/","<","<=","==","!=",
        ">",">=",";","(",")","?",":",",","+=","-=" };
    vector<string>::iterator result = find(opeVec.begin(), opeVec.end(), s);
    if (result != opeVec.end())
        return true;
    else return false;
}

bool is_operator(char c)//运算符
{
    static vector<char> opeVec = { '=','+','-','*','/','<','>',';','(',')','?',':',',' };
    vector<char>::iterator result = find(opeVec.begin(), opeVec.end(), c);
    if (result != opeVec.end())
        return true;
    else return false;
}

string result(string s)//根据传入的参数s产生对应的输出
{
    //标识符
    if (ident(s))
        return "(标识符,"+s+")";

    //关键字
    if (key_words(s))
        return "(关键字,"+s+")";

    //整型常量
    if (digit(s))
        return "(整数,"+s+")";

    //小数
    if (points(s))
        return "(小数,"+s+")";

    //运算符
    static map<string, string> opeMap;
    opeMap["="] = "(等号，=）";
    opeMap["<"] = "(小于号,<)";
    opeMap["<="] = "(小于等于号,<=)";
    opeMap["+="] = "(加等于号,+=)";
    opeMap["-="] = "(减等于号,-=)";
    opeMap["=="] = "(赋值运算符，==）";
    opeMap["!="] = "(不等于号,!=)";
    opeMap[">"] = "(大于号,>)";
    opeMap[">="] = "(大于等于号,>=)";
    opeMap[";"] = "(分号,;)";
    opeMap["+"] = "(加号,+)";
    opeMap["("] = "(左括号,( )";
    opeMap["-"] = "(减号,-)";
    opeMap[")"] = "(右括号,) )";
    opeMap[">"] = "(大于号,>)";
    opeMap["*"] = "(星号,*)";
    opeMap["?"] = "(问号,?)";
    opeMap["/"] = "(除号,/)";
    opeMap[":"] = "(冒号,:)";
    opeMap[","] = "(逗号,,)";
    if (is_operator(s))
        return opeMap[s];
    return "Error";
}

int main()
{
    string file = ("C:\\Users\\zhs\\Desktop\\test.txt");
    ifstream input(file);

    ofstream output("C:\\Users\\zhs\\Desktop\\Result.txt",ofstream::app);
    //先将testData.txt内容拷贝到Result.txt中
    string copy;

    getline(input, copy, '\0');
    cout<< copy << endl;//测试是否正确

    //此时input已经指到了文件尾，为了后面的读取，需要关闭再打开
    input.close();
    input.open(file);

    output << "原数据:\n";
    output << copy;
    output << "处理后结果:\n20169009 赵海杉\n";

    string str;
    string words;

    cout << "处理后结果:\n20169009 赵海杉\n";
    int l=0;//计算行数
    while (getline(input, str)) //读取文件每一次读取一行,遇到EOF结束
    {
        l++;
        //从输入流中获取单词，需要用到输入流对象，即istringstream
        istringstream strCin(str);
        string s;
        while (strCin >> words)
        {
            //关键字肯定是单独作为一个单词的
            if (key_words(words))
            {
                s = result(words);
                cout <<"Line "<<l<<":"<< s << endl;
                output <<"Line "<<l<<":"<< s << endl;
                continue;
            }

            //对单词进行扫描，肯定是标识符，运算符，逗号分号,数字等等混合在一起的单词
            vector<int> index = {0};
            vector<string> mulWords;//将words分解为多个单词
            for (int i = 0; i < words.length(); i++)
            {

                //运算符有两位的，比如"<=",">=","==","!=","-=","+="
                if ((i < words.length() - 1) && is_operator(words[i]) && is_operator(words[i + 1]))
                {
                    //但是要注意只有以上6种两位运算符，比如+-,))就不是,但是))还是要输出),)
                    if (string(words.begin() + i, words.begin() + i + 2) == "<=" ||
                        string(words.begin() + i, words.begin() + i + 2) == ">=" ||
                        string(words.begin() + i, words.begin() + i + 2) == "==" ||
                        string(words.begin() + i, words.begin() + i + 2) == "-=" ||
                        string(words.begin() + i, words.begin() + i + 2) == "+=" ||
                        string(words.begin() + i, words.begin() + i + 2) == "!=")
                    {
                        index.push_back(i);
                        index.push_back(i + 2);
                        ++i;
                    }
                    else if (is_operator(words[i]))
                    {
                        if (find(index.begin(), index.end(), i) == index.end())
                            index.push_back(i);
                        if (find(index.begin(), index.end(), i + 1) == index.end())
                            index.push_back(i + 1);

                    }
                }
                //逗号，运算符作为分隔
                 else if (is_operator(words[i]))
                {
                    if (find(index.begin(), index.end(), i) == index.end())
                    //比如遇到"a,b"这里下标0和1将a分开，1到2将逗号分开，2到3将b分开
                        index.push_back(i);
                    if (find(index.begin(), index.end(), i+1) == index.end())
                        index.push_back(i + 1);
                }

            }
            for (int i = 0; i < index.size()-1; i++)
            {
                string rel;
                //比如遇到"<="，需要提取”<=“
                rel=result(string(words.begin() + index[i], words.begin() + index[i + 1]));

                output <<"Line "<<l<<":"<< rel << endl;
                cout <<"Line "<<l<<":"<< rel<<endl;
            }
        }
    }
    output << endl;
    output.close();
    input.close();
    system("pause");
    return 0;
}

