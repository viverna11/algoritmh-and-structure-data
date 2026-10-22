#include <iostream>
#include<Windows.h>

using namespace std;

// ===========================
// Прямий пошук
// ===========================
int linearSearch(int arr[], int size, int key, int& p)
{
    p = 0;
    for (int i = 0; i < size; i++){
        p++;
        if (arr[i] == key)return i;
    }
    return -1;
}

// ===========================
// Бінарний пошук
// ===========================
int binarySearch(int arr[], int size, int key, int& p)
{
    p = 0;

    int left = 0;
    int right = size - 1;

    while (left <= right)
    {
        int mid = (left + right) / 2;
        p++;

        if (arr[mid] == key)
            return mid;

        if (arr[mid] < key)
            left = mid + 1;

        else
            right = mid - 1;
    }
    return -1;
}

// ===========================
// Сортування вибором
// ===========================
void selectionSort(int arr[], int size)
{
    for (int i = 0; i < size - 1; i++)
    {
        int minIndex = i;

        for (int j = i + 1; j < size; j++)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }

        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// ===========================
// Автоматична перевірка
// ===========================
void test(int arr[], int size, int key, int expected)
{
    int comparisons;

    int result = linearSearch(arr, size, key, comparisons);

    if (result == expected)
        cout << "Успішно";
    else
        cout << "Помилка";

    cout << " | ключ = "
         << key
         << " | очікувалось = "
         << expected
         << " | отримано = "
         << result
         << endl;
}

// ===========================
// Пункт 4
// Порівняльний експеримент
// ===========================
void experiment(int n)
{
    int* arr = new int[n];

    for (int i = 0; i < n; i++)
        arr[i] = i;

    int linearCmp;
    int binaryCmp;

    linearSearch(arr, n, 0, linearCmp);
    binarySearch(arr, n, 0, binaryCmp);

    cout << "\nСценарій A (елемент на початку)" << endl;
    cout << "Лінійний: " << linearCmp
         << " Бінарний: " << binaryCmp << endl;

    linearSearch(arr, n, -1, linearCmp);
    binarySearch(arr, n, -1, binaryCmp);

    cout << "Сценарій B (елемент відсутній)" << endl;
    cout << "Лінійний: " << linearCmp
         << " Бінарний: " << binaryCmp << endl;

    linearSearch(arr, n, n - 1, linearCmp);
    binarySearch(arr, n, n - 1, binaryCmp);

    cout << "Сценарій C (останній елемент)" << endl;
    cout << "Лінійний: " << linearCmp
         << " Бінарний: " << binaryCmp << endl;

    delete[] arr;
}

// ===========================
// Пункт 5
// Середні значення
// ===========================
void averageExperiment(int n)
{
    int* arr = new int[n];

    for (int i = 0; i < n; i++)
        arr[i] = i;

    long long linearSum = 0;
    long long binarySum = 0;

    for (int key = 0; key < n; key++)
    {
        int cmp;

        linearSearch(arr, n, key, cmp);
        linearSum += cmp;

        binarySearch(arr, n, key, cmp);
        binarySum += cmp;
    }

    cout << "\nn = " << n << endl;
    cout << "Середня кількість порівнянь (лінійний): "
         << (double)linearSum / n << endl;

    cout << "Середня кількість порівнянь (бінарний): "
         << (double)binarySum / n << endl;

    delete[] arr;
}

int main()
{
    SetConsoleOutputCP(CP_UTF8);
    int arr[] = {13, 26, 4, 38, 9, 20, 1};
    int size = 7;

    // ===========================
    // Завдання 1 і 2
    // ===========================
    cout << "=== ПРЯМИЙ ПОШУК ===\n";

    int keys[] = {13, 38, 17};

    for (int i = 0; i < 3; i++)
    {
        int cmp;

        int index = linearSearch(arr, size, keys[i], cmp);

        cout << "Ключ "
             << keys[i]
             << " -> індекс "
             << index
             << ", порівнянь "
             << cmp
             << endl;
    }

    int sorted[7];

    for (int i = 0; i < size; i++)
        sorted[i] = arr[i];

    selectionSort(sorted, size);

    cout << "\n=== БІНАРНИЙ ПОШУК ===\n";

    for (int i = 0; i < 3; i++)
    {
        int cmp;

        int index = binarySearch(sorted, size, keys[i], cmp);

        cout << "Ключ "
             << keys[i]
             << " -> індекс "
             << index
             << ", порівнянь "
             << cmp
             << endl;
    }

    // ===========================
    // Завдання 3
    // ===========================
    cout << "\n=== АВТОМАТИЧНІ ТЕСТИ ===\n";

    int t1[] = {8};
    test(t1, 1, 8, 0);

    int t2[] = {8};
    test(t2, 1, 3, -1);

    int t3[] = {2,5,8,11,14,17,20};

    test(t3, 7, 2, 0);
    test(t3, 7, 11, 3);
    test(t3, 7, 20, 6);
    test(t3, 7, 9, -1);
    test(t3, 7, -4, -1);
    test(t3, 7, 100, -1);

    // власні тести
    test(arr, size, 13, 0);
    test(arr, size, 38, 3);
    test(arr, size, 17, -1);

    // ===========================
    // Завдання 4
    // ===========================
    cout << "\n=== ПОРІВНЯЛЬНИЙ ЕКСПЕРИМЕНТ ===\n";

    experiment(10);
    experiment(100);
    experiment(1000);
    experiment(100000);

    // ===========================
    // Завдання 5
    // ===========================
    cout << "\n=== СЕРЕДНІ ЗНАЧЕННЯ ===\n";

    averageExperiment(10);
    averageExperiment(100);
    averageExperiment(1000);

    // ===========================
    // Завдання 6
    // ===========================
    cout << "\n=== НЕВІДСОРТОВАНИЙ МАСИВ ===\n";

    int badCmp;

    int wrongResult = binarySearch(arr, size, 13, badCmp);

    cout << "Результат бінарного пошуку у невідсортованому масиві: "
         << wrongResult << endl;

    cout << "Висновок: бінарний пошук працює коректно тільки для відсортованого масиву."
         << endl;

    return 0;
}
