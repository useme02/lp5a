#include<iostream>
#include<iomanip>
#include<sys/time.h>
#include<omp.h>
#include<cstdlib>
#include<ctime>
using namespace std;

void bubble_seq(int arr[],int n)
{
    cout<<"\nSequential Bubble sort"<<endl;
    for(int i=0;i<n-1;i++)
    {
      for(int j=0;j<n-i-1;j++)
      {
        if(arr[j]>arr[j+1])
        {
          int temp=arr[j];
          arr[j]=arr[j+1];
          arr[j+1]=temp;
        }
      }
    }
}
void bubble_parallel(int arr[],int n)
{
  cout<<"\nParallel Bubble sort"<<endl;
    for(int i=0;i<n-1;i++)
    {
      #pragma omp parallel for
      for(int j=0;j<n-i-1;j++)
      {
        #pragma omp critical
        {
        if(arr[j]>arr[j+1])
        {
          int temp=arr[j];
          arr[j]=arr[j+1];
          arr[j+1]=temp;
        }
        }
      }
    }
}
void merge(int arr[],int left,int mid,int right)
{
  int p1=left;
  int p2=mid+1;
  int narr[right-left+1];
  int i=0;
  
  while(p1<=mid && p2<=right)
  {
    if(arr[p1]<=arr[p2])
        narr[i++] = arr[p1++];
    else
        narr[i++]=arr[p2++];
  }
  while(p1<=mid)
  {
    narr[i++]=arr[p1++];
  }
  while(p2<=right)
  {
    narr[i++]=arr[p2++];
  }
  for(int k=0,x=left;k<i;k++,x++)
  {
    arr[x] = narr[k];
  }
}
void merge_seq(int arr[],int left,int right)
{
  
  if(left<right)
  {
    int mid = left + (right - left)/2;
    merge_seq(arr,left,mid);
    merge_seq(arr,mid+1,right);
    merge(arr,left,mid,right);
  }
}
void merge_parallel(int arr[],int left,int right)
{

  if(left<right)
  
  {
    int mid = left + (right - left)/2;
    #pragma omp parallel sections
    {
    #pragma omp section
    merge_seq(arr,left,mid);
    #pragma omp section
    merge_seq(arr,mid+1,right);
    }
    merge(arr,left,mid,right);
  }
  
}
void printArray(int arr[],int n)
{
  int limit = min(n,10);
  for(int i=0;i<limit;i++)
  {
    cout<<arr[i]<<" ";
  }
  if(n>10) cout<<"....";
  cout<<endl;
}
int main()
{
 int n,choice;
 cout<<"\n1.User Defined Array\n2.Generate Random Array\nEnter Choice";
 cin>>choice;
 if(choice==1)
 {
    cout<<"\nEnter size of array : ";
    cin>>n;
 }
 else if(choice == 2)
 {
    n=100000;
    cout<<"\nRandom array of "<<n<<" elements will be generated ";
 }
 else
 {
    cout<<"\nInvalid Choice";
    return 0;
 }
 int arr[n];
 if(choice ==1)
 {
    cout<<"\nEnter the elemnets : ";
    for(int i=0;i<n;i++)
    {
        cin>>arr[i];
    }
 }
 else if(choice == 2)
 {
    srand(time(0));
    for(int i=0;i<n;i++)
    {
        arr[i] = rand() % 100000;
    }
 }
 
 struct timeval start,end;
 int tempArr[n];
 double time_taken;
 
 copy(arr,arr+n,tempArr);
 gettimeofday(&start,NULL);
 bubble_seq(tempArr,n);
 gettimeofday(&end,NULL);
 printArray(tempArr,n);
 time_taken=(end.tv_sec - start.tv_sec)+(end.tv_usec - start.tv_usec)/1e6;
 cout<<fixed<<setprecision(6)<<"\nTime : "<<time_taken<<" seconds "<<endl;
 
 copy(arr,arr+n,tempArr);
 gettimeofday(&start,NULL);
 bubble_parallel(tempArr,n);
 gettimeofday(&end,NULL);
 printArray(tempArr,n);
 time_taken=(end.tv_sec - start.tv_sec)+(end.tv_usec - start.tv_usec)/1e6;
 cout<<fixed<<setprecision(6)<<"\nTime : "<<time_taken<<" seconds "<<endl;
 
 copy(arr,arr+n,tempArr);
 cout<<"\nSequential Merge Sort"<<endl;
 gettimeofday(&start,NULL);
 merge_seq(tempArr,0,n-1);
 gettimeofday(&end,NULL);
 printArray(tempArr,n);
 time_taken=(end.tv_sec - start.tv_sec)+(end.tv_usec - start.tv_usec)/1e6;
 cout<<fixed<<setprecision(6)<<"\nTime : "<<time_taken<<" seconds "<<endl;
 
 copy(arr,arr+n,tempArr);
 cout<<"\nParallel Merge Sort"<<endl;
 gettimeofday(&start,NULL);
 merge_parallel(tempArr,0,n-1);
 gettimeofday(&end,NULL);
 printArray(tempArr,n);
 time_taken=(end.tv_sec - start.tv_sec)+(end.tv_usec - start.tv_usec)/1e6;
 cout<<fixed<<setprecision(6)<<"\nTime : "<<time_taken<<" seconds "<<endl;
 return 0;
}

