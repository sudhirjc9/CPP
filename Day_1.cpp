#include<iostream>
using namespace std;


void swapVal(int *val1, int *val2)
{
    int temp=*val1;
    *val1=*val2;
    *val2=temp;
}

void BubbleSort(int *arr, int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=i+1;j<n;j++)
        {
            if(*(arr+i) > *(arr+j))
                swapVal(&arr[i],&arr[j]);
        }
    }
}

int main(){
    int arr[]={10,7,3,4,5,1,0};
    BubbleSort(arr,7);
    for(auto &x:arr)
        cout<<x<<" ";
    return 0;
}