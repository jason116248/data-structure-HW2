#include <iostream>
#include <fstream>
using namespace std;
typedef struct
{
    int col;
    int row;
    int value;

} term;
void transpose(term a[], term b[])
{
    int n,i,j,currentb=1;
    n = a[0].value;
    b[0].row = a[0].col;
    b[0].col = a[0].row;
    b[0].value = n;

    if(n>0){
        for(i=0;i< a[0].col ;i++)
            for(j=1;j<=n;j++)
            if( a[j].col == i){
                b[currentb].row = a[j].col;
                b[currentb].col = a[j].row;
                b[currentb].value = a[j].value;
                currentb++;
            }
    }
}

void multiple(term c[], term b[])
{
    int x=1, y=1, amount_y=0, sum=0,temp,n,num, result_num=0;
    int row1_var, row2_var;
    int row1_max, row2_max;
    row1_max = c[0].row;
    row2_max = b[0].row;
    term result[row1_max * row2_max];

    for(row2_var=0; row2_var<row2_max;row2_var++)
    {
        while( b[y].row!=row2_var)
        {
            y++;
        }
        temp = y;
        x = 1;

        for(row1_var=0; row1_var<row1_max;row1_var++)
        {
            n = row1_var;
            for(num=0; num<c[0].col;num++)
            {
                if( b[y].row>row2_var)
                {
                    y = y-amount_y;
                    amount_y = 0;
                }

                if(c[x].row==n)
                {
                    if(c[x].col - b[y].col==0)
                    {
                        sum+= c[x].value * b[y].value;
                        x++;
                        y++;
                        amount_y++;

                        if(x > c[0].value)
                        {
                            x=1;
                            num = c[0].col;
                        }
                    }
                    else if(c[x].col - b[y].col > 0)
                    {
                        y++;
                        amount_y++;
                    }
                    else if(c[x].col - b[y].col < 0)
                    {
                        x++;
                        if(x > c[0].value)
                        {
                            x=1;
                            num = c[0].col;
                        }
                    }
                }
                else if(c[x].row < n)
                {
                    x++;
                    num--;
                }
                else if(c[x].row > n)
                {
                    //do nothing
                }
            }
            amount_y = 0;
            y = temp;
            if(sum!=0)
            {
                result[result_num].col = row2_var;
                result[result_num].row = row1_var;
                result[result_num].value = sum;
                result_num++;
                sum = 0;
            }
            else{
                result[result_num].col = 0;
                result[result_num].row = 0;
                result[result_num].value = 0;
                result_num++;
            }
        }
    }

    // print out

    for(int length=0; length < row1_max * row2_max;length++)
    {
        if(result[length].value!=0)
            cout << result[length].row << " " << result[length].col << " " << result[length].value << endl;
    }
}
int main()
{
    char ch;
    string str="",str2[2];
    int col[2]= {0},row[2]= {0},i=0,k=0,num[2]= {0},z=0;
    int leng,leng0;
    bool flag = true;
    char file_name[20]={};

    cout << "Please enter file's name(remember to enter file's format): ";
    cin >> file_name;

    ifstream ifile(file_name,ios::in);
    if(!ifile.is_open())
    {
         cout << "file is not exist, please check your folder" << endl;
    }
    else
    {
        while(ifile.get(ch))
    {
        if(ch=='|')
        {
            k=1; //渡過空白和換行所需的次數
            //col[i]--;
            i++;
        }

        if(ch=='\n')
        {

            flag = false;
            row[i]++;
            if(k>0)
            {
                flag = true;
                k--;
            }

        }

        if( (ch=='0' || ch=='1' || ch=='2' || ch=='3' || ch=='4' || ch=='5' || ch=='6' || ch=='7' || ch=='8' || ch=='9')
           &&flag == true)
        {
            col[i]++;
            if(k>0)
                col[i]--;

        }
        if(ch=='0' || ch=='1' || ch=='2' || ch=='3' || ch=='4' || ch=='5' || ch=='6' || ch=='7' || ch=='8' || ch=='9' )
        {
            if(ch!='0')
            {
                num[i]++;

            }
            str2[i]+=ch;

        }
        str+=ch;
    }

    leng0 = num[0];
    leng = num[1];
    leng0++;
    leng++;
    term C[leng0];
    term A[leng],B[leng];


    C[0].row = row[0];
    C[0].col = col[0];
    C[0].value = num[0];
    A[0].row = row[1];
    A[0].col = col[1];
    A[0].value = num[1];

    int N=1,w=0;
    for(int x=0; x<row[0]; x++)
    {
        for(int y=0; y<col[0]; y++)
        {
            if(str2[0].at(w)!='0')
            {
                //cout << str2[1].at(z) << endl;
                C[N].row = x;
                C[N].col = y;
                C[N].value = (str2[0].at(w))-48;

                N++;
            }
            w++;
        }
    }

    int n=1;
    for(int x=0; x<row[1]; x++)
    {
        for(int y=0; y<col[1]; y++)
        {
            if(str2[1].at(z)!='0')
            {
                //cout << str2[1].at(z) << endl;
                A[n].row = x;
                A[n].col = y;
                A[n].value = (str2[1].at(z))-48;

                n++;
            }
            z++;
        }
    }

    cout << endl;
    transpose(A,B);

    multiple(C,B);

    }
    ifile.close();

    return 0;
}
