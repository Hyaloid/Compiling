# include<iostream>
#include <bits/stdc++.h>
using namespace std;

bool key_words(string s)//�ؼ���
{
    static vector<string> keyVec = { "main", "int", "float", "double", "char",
        "if", "then","else", "switch", "case", "break", "continue", "while",
        "do", "for" ,"#include","using","namespace","std","return"};
    vector<string>::iterator result = find(keyVec.begin(), keyVec.end(),s);
    if (result != keyVec.end())
        return true;
    else return false;
}
bool ident(string s)//��ʶ��
{
    if (!key_words(s))//��ʶ�������ǹؼ���
    {
        if ((s[0] >= 'a'&&s[0] <= 'z') || (s[0] >= 'A'&&s[0] <= 'Z'))//����ĸ
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

bool digit(string s)//����
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

bool points(string s)//С��
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

bool is_operator(string s)//�����
{
    static vector<string> opeVec = { "=","+","-","*","/","<","<=","==","!=",
        ">",">=",";","(",")","?",":",",","+=","-=" };
    vector<string>::iterator result = find(opeVec.begin(), opeVec.end(), s);
    if (result != opeVec.end())
        return true;
    else return false;
}

bool is_operator(char c)//�����
{
    static vector<char> opeVec = { '=','+','-','*','/','<','>',';','(',')','?',':',',' };
    vector<char>::iterator result = find(opeVec.begin(), opeVec.end(), c);
    if (result != opeVec.end())
        return true;
    else return false;
}

string result(string s)//���ݴ���Ĳ���s������Ӧ�����
{
    //��ʶ��
    if (ident(s))
        return "(��ʶ��,"+s+")";

    //�ؼ���
    if (key_words(s))
        return "(�ؼ���,"+s+")";

    //���ͳ���
    if (digit(s))
        return "(����,"+s+")";

    //С��
    if (points(s))
        return "(С��,"+s+")";

    //�����
    static map<string, string> opeMap;
    opeMap["="] = "(�Ⱥţ�=��";
    opeMap["<"] = "(С�ں�,<)";
    opeMap["<="] = "(С�ڵ��ں�,<=)";
    opeMap["+="] = "(�ӵ��ں�,+=)";
    opeMap["-="] = "(�����ں�,-=)";
    opeMap["=="] = "(��ֵ�������==��";
    opeMap["!="] = "(�����ں�,!=)";
    opeMap[">"] = "(���ں�,>)";
    opeMap[">="] = "(���ڵ��ں�,>=)";
    opeMap[";"] = "(�ֺ�,;)";
    opeMap["+"] = "(�Ӻ�,+)";
    opeMap["("] = "(������,( )";
    opeMap["-"] = "(����,-)";
    opeMap[")"] = "(������,) )";
    opeMap[">"] = "(���ں�,>)";
    opeMap["*"] = "(�Ǻ�,*)";
    opeMap["?"] = "(�ʺ�,?)";
    opeMap["/"] = "(����,/)";
    opeMap[":"] = "(ð��,:)";
    opeMap[","] = "(����,,)";
    if (is_operator(s))
        return opeMap[s];
    return "Error";
}

int main()
{
    string file = ("C:\\Users\\zhs\\Desktop\\test.txt");
    ifstream input(file);

    ofstream output("C:\\Users\\zhs\\Desktop\\Result.txt",ofstream::app);
    //�Ƚ�testData.txt���ݿ�����Result.txt��
    string copy;

    getline(input, copy, '\0');
    cout<< copy << endl;//�����Ƿ���ȷ

    //��ʱinput�Ѿ�ָ�����ļ�β��Ϊ�˺���Ķ�ȡ����Ҫ�ر��ٴ�
    input.close();
    input.open(file);

    output << "ԭ����:\n";
    output << copy;
    output << "�������:\n20169009 �Ժ�ɼ\n";

    string str;
    string words;

    cout << "�������:\n20169009 �Ժ�ɼ\n";
    int l=0;//��������
    while (getline(input, str)) //��ȡ�ļ�ÿһ�ζ�ȡһ��,����EOF����
    {
        l++;
        //���������л�ȡ���ʣ���Ҫ�õ����������󣬼�istringstream
        istringstream strCin(str);
        string s;
        while (strCin >> words)
        {
            //�ؼ��ֿ϶��ǵ�����Ϊһ�����ʵ�
            if (key_words(words))
            {
                s = result(words);
                cout <<"Line "<<l<<":"<< s << endl;
                output <<"Line "<<l<<":"<< s << endl;
                continue;
            }

            //�Ե��ʽ���ɨ�裬�϶��Ǳ�ʶ��������������ŷֺ�,���ֵȵȻ����һ��ĵ���
            vector<int> index = {0};
            vector<string> mulWords;//��words�ֽ�Ϊ�������
            for (int i = 0; i < words.length(); i++)
            {

                //���������λ�ģ�����"<=",">=","==","!=","-=","+="
                if ((i < words.length() - 1) && is_operator(words[i]) && is_operator(words[i + 1]))
                {
                    //����Ҫע��ֻ������6����λ�����������+-,))�Ͳ���,����))����Ҫ���),)
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
                //���ţ��������Ϊ�ָ�
                 else if (is_operator(words[i]))
                {
                    if (find(index.begin(), index.end(), i) == index.end())
                    //��������"a,b"�����±�0��1��a�ֿ���1��2�����ŷֿ���2��3��b�ֿ�
                        index.push_back(i);
                    if (find(index.begin(), index.end(), i+1) == index.end())
                        index.push_back(i + 1);
                }

            }
            for (int i = 0; i < index.size()-1; i++)
            {
                string rel;
                //��������"<="����Ҫ��ȡ��<=��
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

