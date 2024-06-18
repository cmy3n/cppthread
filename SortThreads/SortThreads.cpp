#include <iostream>
#include <Windows.h>
#include <vector>
#include <thread>
using namespace std;

class mergesort{
public:
    void Sort(vector<int>& arr, int l, int r)
    {
        if (l < r)
        {
            int mid = ((l + r) / 2);

            thread thread1(&mergesort::Sort, this, ref(arr), l, mid);
            thread thread2(&mergesort::Sort, this, ref(arr), mid + 1, r);

            thread1.join();
            thread2.join();

            Merge(arr, l, mid, r);
        }
    }
private:
    void Merge(vector<int>& vec, int l, int mid, int r)
    {
        int a = l;
        int b = mid + 1;
        int c = 0;

        vector<int> vec2(r - l + 1);

        while ((a <= mid) && (b <= r))
        {
            if (vec[a] <= vec[b])
            {
                vec2[c] = vec[a];
                a++;
            }
            else
            {
                vec2[c] = vec[b];
                b++;
            }
            c++;
        }

        while (a <= mid)
        {
            vec2[c] = vec[a];
            a++;
            c++;
        }

        while (b <= r)
        {
            vec2[c] = vec[b];
            b++;
            c++;
        }

        for (size_t i = 0; i < vec2.size(); i++)
        {
            vec[l + i] = vec2[i];
        }
    }
};

int main() 
{
    setlocale(LC_ALL, "rus");
    SetConsoleCP(1251); 

    mergesort mergeSort;
    vector<int> vec(10);

    cout << "Введите числа:\n";
    for (size_t i = 0; i < 10; i++)
    {
        cin >> vec[i];
    }

    cout << endl;
    for (size_t i = 0; i < 10; i++) {
        cout << vec[i] << "\t";
    }
    cout << endl;

    auto sort = [&](vector<int>& arr) 
    {
        mergeSort.Sort(arr, 0, arr.size() - 1);
    };

    thread sortThread(sort, ref(vec));
    sortThread.join();

    cout << endl;
    for (size_t i = 0; i < 10; i++)
    {
        cout << vec[i] << "\t";
    }

    return 0;
}