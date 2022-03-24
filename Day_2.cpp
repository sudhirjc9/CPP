#include<iostream>
#include<cstring>
#define LEN 80
#define MAX 40
using namespace std;

class Stack
{
    private:
        char st[MAX];
        int top;
    public:
        Stack()
        {
            top=0;
        }
    void push(char var)
        {
            st[++top]=var;
        }
    char pop()
    {
        return st[top--];
    }
    int gettop()
    {
        return top;
    }
};

class express
{
    private:
        Stack s;
        char *pStr;
        int len;
    public:
        express(char *ptr)
        {
            pStr=ptr;
            len=strlen(pStr);
        }
        void parse();
        int solve();
};

void express::parse(){
    char ch;
    char lastval;
    char lasttop;

    for(int j=0; j<len; j++)
        {
            ch = pStr[j];
            if(ch>'0' && ch<='9')
                    s.push(ch-'0');
            else if(ch=='+' || ch=='-' || ch=='*' || ch=='/')
                {
                    if(s.gettop()==1)
                        s.push(ch);
                    else
                        {
                            lastval=s.pop();
                            lasttop=s.pop();
                            if((ch=='*' || ch=='/') && (lasttop=='+'|| lasttop=='-'))
                                {
                                    s.push(lasttop);
                                    s.push(lastval);
                                }
                            else
                                {
                                    switch(lasttop)
                                    {
                                        case '+':s.push(s.pop()+lastval); break;
                                        case '-':s.push(s.pop()-lastval); break;
                                        case '*':s.push(s.pop()*lastval); break;
                                        case '/':s.push(s.pop()/lastval); break;

                                        default: {cout<<"Unknown Operator"<<endl;
                                                    exit(0);
                                                }

                                    }
                                }
                            s.push(ch);
                        }
                }
            else
                {
                    cout<<"\n Unknown Operator";
                    exit(1);
                }
        }
}


int express::solve()
{
    char lastval;
    while(s.gettop()>1)
        {
            lastval=s.pop();
            switch(s.pop())
                {
                     case '+':s.push(s.pop()+lastval); break;
                    case '-':s.push(s.pop()-lastval); break;
                    case '*':s.push(s.pop()*lastval); break;
                     case '/':s.push(s.pop()/lastval); break;

                  default: {cout<<"Unknown Operator"<<endl;
                            exit(0);
                           }
                }
        }
    return int(s.pop());
}


int main(){
    char ans;
    char string[LEN];
    cout<<"Enter expression"<<endl;
    do
        {
            cin>>string;
            express *eptr=new express(string);
            eptr->parse();
            cout<<"\n The numerical value is: "<<eptr->solve()<<endl;
            delete eptr;
            cout<<"Do another "<<endl;
            cin>>ans;
        }while(ans=='y');

    return 0;
}