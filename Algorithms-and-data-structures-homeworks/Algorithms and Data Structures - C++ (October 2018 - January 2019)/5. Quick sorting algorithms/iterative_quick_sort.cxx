#include <iostream>

unsigned long long int compare = 0;
unsigned long long int swap = 0;

int partition (int arr[], int l, int r) { 
    int m = (l+r)/2;
    std::swap(arr[r], arr[m]);
    int x = arr[r]; 
    int i = l; 
  
    for (int j = l; j <= r; j++) { 
        //compare += 2;
        
        if (arr[j] <= x) { 
            //swap += 3;
            std::swap (arr[i], arr[j]); 
            i++;
        }
    }
    //compare++;

    return i-1; 
} 

void quickSortIterative (int arr[], int lewy, int prawy) { 
    // Tworzę stos
    int stos[prawy - lewy + 1];

    int top = -1; 
  
    //swap += 2;
    stos[++top] = lewy;
    stos[++top] = prawy; 

    // Dopoki są elementy na stosie
    while (top >= 0) { 
        //compare++;
        
        // Ściągam r i l ze stosu
        prawy = stos[top--]; 
        lewy = stos[top--]; 

        // Ustawiam p na odpowiednią pozycję w tablicy
        int p = partition(arr, lewy, prawy); 
  
        // Jezeli są elementy po lewej stronie wybranego p
        // to wrzucam lewą stronę na stos
        //compare++;
        if (p-1 > lewy) { 
            //swap += 2;
            stos[++top] = lewy; 
            stos[++top] = p - 1; 
        } 
  
        // Jezeli są elementy po prawej stronie wybranego p
        // to wrzucam prawą strone na stos
        //compare++;
        if (p+1 < prawy) { 
            //swap += 2;
            stos[++top] = p + 1; 
            stos[++top] = prawy; 
        } 
    } 
    //compare++;
} 

void printArray(int arr[], int n) {

     for(int i = 0; i < n; i++) {
          std::cout << arr[i] << std::endl;
     }
}

int main(int argc, char* argv[]) {
    if(argc < 2) {
        std::cerr << "Not enough arguments" << std::endl; 
        exit(-1);
    }

    const int N = atoi(argv[1]);

    int i;
    int tab[N];

    for(i = 0; i < N; i++) {
        std::cin >> tab[i];
    }

    auto start = std::chrono::high_resolution_clock::now();

    quickSortIterative(tab, 0, N-1);

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> difference = end - start;
    //printf("iterative quick sort time for %d elements: %f\n", N, difference.count());

    printArray(tab, N);

    //printf("Porownan: %llu\nZapisy: %llu\n", compare, swap);

    return 0;
}