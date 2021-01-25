#include <iostream>
#include <vector>
#include <chrono>
#include <random>

int sukeitimai = 0, vid_sukeitimu = 0, palyginimai = 0, vid_palyginimai = 0;
std::chrono::duration<double> elapsed_seconds_avg;

// funkcija sukeisti reiksmems
void swap(int* x, int* y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// funkcija padeti elementa i jo pozicija, t.y. visi mazesni elementai yra gale rikiuojamo elemento, visi didesni elementai eina po jo
int Partition(int A[], int low, int high) 
{
    //isrenkame mediana is pirmos, vidurines ir paskutines reiksmiu
    int a = A[low], b = A[(high - low) / 2+low], c = A[high - 1];
    int i = low - 1, j = high, pivot = 0;
    if (b > a && b < c || b > c && b < a)
    {
        pivot = b;
    }
    else if (c > a && c < b || c > b && c < a)
    {
        pivot = c;
    }
    else
    {
        pivot = a;
    }

    while (true) {
        do 
        { 
           palyginimai++;
           j--;    //j eina is galo ir iesko reiksmiu mazesniu uz asi
        } while (A[j] > pivot);
        do
        {
           palyginimai++;
           i++;  //i eina is priekio ir iesko reiksmiu didesniu uz asi
        } while (A[i] < pivot);
        //sukeiciame reiksmes jei i neuzejo uz j
        if (i < j)
        {       
            swap(&A[i], &A[j]);
            sukeitimai++;
        }
        //jei i virsija j, graziname surikiuota elemento pozicija
        else return j + 1;
    }
}

void QuickSort(int A[], int low, int high) {
    //poaibi sudaro 1 elementas, todel baigiame
    if (high - low < 2)
    {
        return;
    }
    int pivot = Partition(A, low, high);
    QuickSort(A, low, pivot);   //rekursiskai rikiuojame nuo pradzios iki asies
    QuickSort(A, pivot, high);  //rekursiskai rikiuojame nuo asies iki pabaigos
}

std::vector<int> GetGaps(int n)
{
    std::vector<int>Gaps(1,1);
    int k = 1, gap = 0;
    while(gap < n)
    {
        gap = pow(4, k) + 3 * pow(2, k - 1) + 1;
        Gaps.push_back(gap);
        k++;
    }
    Gaps.pop_back();
    std::reverse(Gaps.begin(), Gaps.end());
    return Gaps;
}

void ShellSort(int A[], int n, std::vector<int>& Gaps)
{
    //einame pro visus tarpus
    for (auto gap : Gaps)
    {
        //einame pro kiekviena elementa
        for (int i = gap; i < n; i++)
        {
            palyginimai++;
            int temp = A[i];
            int j;
            //keiciam reiksmes kol randam teisinga A[i] pozicija
            for (j = i; j >= gap && A[j - gap] > temp; j -= gap)
            {
                A[j] = A[j - gap];
                sukeitimai++;
            }
            A[j] = temp;
        }  
    }
}

void printArray(int arr[], int size)
{
    for (int i = 0; i < size; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

int main()
{   
    int A[51] = { 0 };

    std::cout << "Shell Sort:" << std::endl;
    for (int i = 0; i < 5; i++)
    {
        //atsitiktiniu reiksmiu generavimas
        for (int j = 0; j < 50; j++)
        {
           unsigned int seed = std::chrono::steady_clock::now().time_since_epoch().count();
           std::default_random_engine engine(seed); //varikliukas
           std::uniform_int_distribution<int> distr(1000, 9999); //reiksmiu rezis
           int a = distr(engine);
           A[j] = a;
        }

        int n = sizeof(A) / sizeof(A[0]);    
       // QuickSort(A, 0, n);
       // std::reverse(A, A + n);
        auto start = std::chrono::steady_clock::now();
        std::vector<int> Gaps = GetGaps(n);
        ShellSort(A, n, Gaps);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        elapsed_seconds_avg += elapsed_seconds;
        std::cout << "Bandymas nr." << i + 1 << std::endl;
        std::cout << "Buvo atlikta " << palyginimai << " palyginimu ir " << sukeitimai << " sukeitimu." << std::endl;  
        std::cout << "Atlikta per: " << elapsed_seconds.count()<< "s\n";
        vid_sukeitimu += sukeitimai;
        vid_palyginimai += palyginimai;
        sukeitimai = 0; palyginimai = 0;   
    }

    std::cout << "Vidutiniskai sukeitimu: " << vid_sukeitimu / 5 << std::endl;
    std::cout << "Vidutiniskai palyginimu: " << vid_palyginimai / 5 << std::endl;
    std::cout << "Vidutinis laikas " << elapsed_seconds_avg.count()/5 << "s\n";   
}