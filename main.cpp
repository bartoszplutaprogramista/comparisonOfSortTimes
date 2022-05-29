#include <iostream>
#include <time.h>
#include <windows.h>

using namespace std;

int ile;
clock_t start,stop;
double czas;

void sortowanie_babelkowe(int *tab, int n)
{
    for(int i=1; i<n; i++)
    {
        for(int j=n-1; j>=1; j--)
        {
            if(tab[j]<tab[j-1])
            {
                int bufor;
                bufor=tab[j-1];
                tab[j-1]=tab[j];
                tab[j]=bufor;
            }
        }
    }
}

void quicksort(int *tablica, int lewy, int prawy)
{
    int v=tablica[(lewy+prawy)/2];
    int i,j,x;
    i=lewy;
    j=prawy;
    do
    {
        while(tablica[i]<v) i++;
        while(tablica[j]>v) j--;
        if(i<=j)
        {
            x=tablica[i];
            tablica[i]=tablica[j];
            tablica[j]=x;
            i++;
            j--;
        }
    }
    while(i<=j);
    if(j>lewy) quicksort(tablica,lewy, j);
    if(i<prawy) quicksort(tablica, i, prawy);
}

void scalanie(int *tablica, int start, int srodek, int koniec)
{

    int *tab_pom = new int[(koniec-start+1)];
    int i = start, j = srodek+1, k = 0;

    while (i <= srodek && j <= koniec)
    {
        if (tablica[j] < tablica[i])
        {
            tab_pom[k] = tablica[j];
            j++;
        }
        else
        {
            tab_pom[k] = tablica[i];
            i++;
        }
        k++;
    }

    if (i <= srodek)
    {
        while (i <= srodek)
        {
            tab_pom[k] = tablica[i];
            i++;
            k++;
        }
    }
    else
    {
        while (j <= koniec)
        {
            tab_pom[k] = tablica[j];
            j++;
            k++;
        }
    }

    for (i = 0; i <= koniec-start; i++)
        tablica[start+i] = tab_pom[i];

    delete [] tab_pom;
}

void SortowaniePrzezScalanie(int *tablica, int start, int koniec)
{
    int srodek;

    if (start != koniec)
    {
        srodek = (start + koniec)/2;
        SortowaniePrzezScalanie(tablica, start, srodek);
        SortowaniePrzezScalanie(tablica, srodek+1, koniec);
        scalanie(tablica, start, srodek, koniec);
    }
}

void selectionsort(int *tablica, int ilosc_liczb)
{
    int max, i,j, pomoc;

    for (i = 0; i < ilosc_liczb; i++)
    {
        max = i;
        for (j = i+1; j < ilosc_liczb; j++)
        {
            if (tablica[j] < tablica[max])
                max = j;
        }

        pomoc = tablica[max];
        tablica[max] = tablica[i];
        tablica[i] = pomoc;
    }
}
void insertionsort(int *tablica, int ilosc_liczb)
{
    int tymczasowa, i,j;

    for (i = 1; i < ilosc_liczb; i++)
    {
        tymczasowa = tablica[i]; // przechowanie elementu tablicy z zmiennej pomocniczej
        for (j = i-1; j >= 0; j--)
        {
            if (tymczasowa < tablica[j]) // zamiana miejsc
                tablica[j+1] = tablica[j];
            else
                break;
        }
        tablica[j+1] = tymczasowa;
    }
}

bool czyTablicaJestPosortowana(int tablica[], int iloscLiczb)
{
    bool posortowana = true;
    for (int i = 0; i < iloscLiczb-1; i++) { if (tablica[i] > tablica[i+1])
            posortowana = false;
    }
    return posortowana;
}

int main()
{
    cout << "Porownanie czasow sortowania sortowanie babelkowe, quicksort, sortowanie przez scalanie, selectionsort, insertionsort " << endl;

    cout<<"Ile losowych liczb w tablicy: ";
    cin>>ile;

    //dynamiczna alokacja tablicy
    int *tablica;
    tablica=new int [ile];

    int *tablica2;
    tablica2=new int [ile];

    int *tablica3;
    tablica3=new int [ile];

    int *tablica4;
    tablica4=new int [ile];

    int *tablica5;
    tablica5=new int [ile];

    //inicjowanie generatora
    srand(time(NULL));

    //wczytywanie losowych liczb do tablicy
    for(int i=0; i<ile; i++)
    {
        tablica[i] = rand()%100000+1;
    }

    //przepisanie tablicy do tablicy2
    for(int i=0; i<ile; i++)
    {
       tablica2[i]=tablica[i];
    }

    //przepisanie tablicy do tablicy3
    for(int i=0; i<ile; i++)
    {
       tablica3[i]=tablica[i];
    }

    //przepisanie tablicy do tablicy4
    for(int i=0; i<ile; i++)
    {
       tablica4[i]=tablica[i];
    }

    //przepisanie tablicy do tablicy5
    for(int i=0; i<ile; i++)
    {
       tablica5[i]=tablica[i];
    }

    cout<<"Sortuje teraz babelkowo. Prosze czekac!"<<endl;
    start = clock();
    sortowanie_babelkowe(tablica,ile);
    stop = clock();
    czas = (double)(stop-start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas sortowania babelkowego: "<<czas<<" s"<<endl;

        if (czyTablicaJestPosortowana(tablica,ile) == true)
        cout << "TAK. Tablica (babelkowo) jest posortowana." << endl;
        else
        cout << "NIE. Tablica (babelkowo) nie jest posortowana." << endl;

    cout<<endl<<"Sortuje teraz algorytmem quicksort. Prosze czekac!"<<endl;
    start = clock();
    quicksort(tablica2, 0, ile-1);
    stop = clock();
    czas = (double)(stop-start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas sortowania quicksort: "<<czas<<" s"<<endl;

        if (czyTablicaJestPosortowana(tablica2,ile) == true)
        cout << "TAK. Tablica (quicksort) jest posortowana." << endl;
        else
        cout << "NIE. Tablica (quicksort) nie jest posortowana." << endl;

    cout<<endl<<"Sortuje teraz algorytmem sorotwanie przez scalanie. Prosze czekac!"<<endl;
    start = clock();
    SortowaniePrzezScalanie(tablica3, 0, ile-1);
    stop = clock();
    czas = (double)(stop-start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas sortowania algorytmem sorotwanie przez scalanie: "<<czas<<" s"<<endl;

        if (czyTablicaJestPosortowana(tablica3,ile) == true)
        cout << "TAK. Tablica (sorotwanie przez scalanie) jest posortowana." << endl;
        else
        cout << "NIE. Tablica (sorotwanie przez scalanie) nie jest posortowana." << endl;

    cout<<endl<<"Sortuje teraz algorytmem selectionsort. Prosze czekac!"<<endl;
    start = clock();
    selectionsort(tablica4, ile);
    stop = clock();
    czas = (double)(stop-start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas sortowania selectionsort: "<<czas<<" s"<<endl;

        if (czyTablicaJestPosortowana(tablica4,ile) == true)
        cout << "TAK. Tablica (selectionsort) jest posortowana." << endl;
        else
        cout << "NIE. Tablica (selectionsort) nie jest posortowana." << endl;

    cout<<endl<<"Sortuje teraz algorytmem insertionsort. Prosze czekac!"<<endl;
    start = clock();
    insertionsort(tablica5, ile);
    stop = clock();
    czas = (double)(stop-start) / CLOCKS_PER_SEC;
    cout<<endl<<"Czas sortowania insertionsort: "<<czas<<" s"<<endl;

        if (czyTablicaJestPosortowana(tablica5,ile) == true)
        cout << "TAK. Tablica (insertionsort) jest posortowana." << endl;
        else
        cout << "NIE. Tablica (insertionsort) nie jest posortowana." << endl;

    delete [] tablica;
    delete [] tablica2;
    delete [] tablica3;
    delete [] tablica4;
    delete [] tablica5;

    return 0;
}
