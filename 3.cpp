#include<iostream>
#include<sys/time.h>
#include<omp.h>
#include<iomanip>
using namespace std;

double sum_seq(double arr[],int n)
{
    double sum =0;
    for(int i=0;i<n;i++)
    {
      sum+=arr[i];
    }
    return sum;
}
double sum_parallel(double arr[],int n)
{
  double sum =0;
  #pragma omp parallel for reduction(+:sum)
  for(int i=0;i<n;i++)
  {
    sum+=arr[i];
  }
  return sum;
}
double avg_seq(double arr[],int n)
{
    double sum = sum_seq(arr,n);
    return sum/n;
}
double avg_parallel(double arr[],int n)
{
    double sum = sum_parallel(arr,n);
    return sum/n;
}
double min_seq(double arr[],int n)
{
    double min=999999;
    for(int i=0;i<n;i++)
    {
      if(arr[i]<min)
        min=arr[i];
    }
    return min;
}
double min_parallel(double arr[],int n)
{
  double min=999999;
  #pragma omp parallel for reduction(min:min)
  for(int i=0;i<n;i++)
  {
    if(arr[i]<min)
        min=arr[i];
  }
  return min;
}
double max_seq(double arr[],int n)
{
  double max =0;
  for(int i=0;i<n;i++)
  {
    if(arr[i]>max)
        max=arr[i];
  }
  return max;
}
double max_parallel(double arr[],int n)
{
  double max =0;
  #pragma omp parallel for reduction(max:max)
  for(int i=0;i<n;i++)
  {
    if(arr[i]>max)
        max=arr[i];
  }
  return max;
}


void fill_random(double arr[], int n) {
    srand(time(0));
    for(int i = 0; i < n; i++)
        arr[i] = rand() % 1000000; // random 0-999
}

void fill_user(double arr[], int n) {
    cout << "\nEnter " << n << " elements:\n";
    for(int i = 0; i < n; i++)
        cin >> arr[i];
}

void display_array(double arr[], int n) {
    cout << "\nArray elements: ";
    for(int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;
}
int main()
{
    int n, array_choice;
    
    cout << "\n--- Array Input Menu ---";
    cout << "\n1. User Defined Array";
    cout << "\n2. Random Array";
    cout << "\nEnter your choice: ";
    cin >> array_choice;

    cout << "\nEnter size of array: ";
    cin >> n;
    double arr[n];

    if(array_choice == 1) {
        fill_user(arr, n);
    } else if(array_choice == 2) {
        fill_random(arr, n);
        display_array(arr, n);
    } else {
        cout << "\nInvalid choice. Exiting.";
        return 0;
    }

    
    struct timeval start,end;
    
    gettimeofday(&start,NULL);
    cout<<"\nSequential Sum : "<<sum_seq(arr,n);
    gettimeofday(&end,NULL);
    cout<<"\nTime : "<<(end.tv_sec - start.tv_sec)*1e9 + (end.tv_usec - start.tv_usec)*1000<<" ns "<<endl;
    
    gettimeofday(&start,NULL);
    cout<<"\nParallel Sum : "<<sum_parallel(arr,n);
    gettimeofday(&end,NULL);
    cout<<"\nTime : "<<(end.tv_sec - start.tv_sec)*1e9 + (end.tv_usec - start.tv_usec)*1000<<" ns "<<endl;
    
    gettimeofday(&start,NULL);
    cout<<"\nSequential Average : "<<avg_seq(arr,n);
    gettimeofday(&end,NULL);
    cout<<"\nTime : "<<(end.tv_sec - start.tv_sec)*1e9 + (end.tv_usec - start.tv_usec)*1000<<" ns "<<endl;
    
    gettimeofday(&start,NULL);
    cout<<"\nParallel Average: "<<avg_parallel(arr,n);
    gettimeofday(&end,NULL);
    cout<<"\nTime : "<<(end.tv_sec - start.tv_sec)*1e9 + (end.tv_usec - start.tv_usec)*1000<<" ns "<<endl;
    
    gettimeofday(&start,NULL);
    cout<<"\nSequential MIN : "<<min_seq(arr,n);
    gettimeofday(&end,NULL);
    cout<<"\nTime : "<<(end.tv_sec - start.tv_sec)*1e9 + (end.tv_usec - start.tv_usec)*1000<<" ns "<<endl;
    
    gettimeofday(&start,NULL);
    cout<<"\nParallel MIN : "<<min_parallel(arr,n);
    gettimeofday(&end,NULL);
    cout<<"\nTime : "<<(end.tv_sec - start.tv_sec)*1e9 + (end.tv_usec - start.tv_usec)*1000<<" ns "<<endl;
    
    gettimeofday(&start,NULL);
    cout<<"\nSequential MAX : "<<max_seq(arr,n);
    gettimeofday(&end,NULL);
    cout<<"\nTime : "<<(end.tv_sec - start.tv_sec)*1e9 + (end.tv_usec - start.tv_usec)*1000<<" ns "<<endl;
    
    gettimeofday(&start,NULL);
    cout<<"\nParallel MAX : "<<max_parallel(arr,n);
    gettimeofday(&end,NULL);
    cout<<"\nTime : "<<(end.tv_sec - start.tv_sec)*1e9 + (end.tv_usec - start.tv_usec)*1000<<" ns "<<endl;
    
   
}
