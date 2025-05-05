// Sorting Visualizer with Manual Algorithm Selection
// Includes: Selection, Insertion, Bubble, Merge, Quick, and Heap Sort

#include <SDL.h>          // Library for graphics rendering
#include <iostream>       // For console output
#include <ctime>          // For random number generation
#include <iomanip>        // For output formatting (not actively used)
#include <queue>          // For queue data structure (not actively used)
#include <stack>          // For stack data structure (not actively used)

using namespace std;

// Constants for window and array configuration
const int WIDTH = 1000;   // Window width in pixels
const int HEIGHT = 600;   // Window height in pixels
const int SIZE = 200;     // Number of elements in the array

// SDL global variables
SDL_Window* window = NULL;    // Main application window
SDL_Renderer* renderer;       // Renderer for drawing graphics
SDL_Event event;              // For handling user input events
bool quit = false;            // Flag to control main loop

// Enumeration of available sorting algorithms
enum Algorithm {
    SELECTION,       // Selection Sort
    INSERTION,       // Insertion Sort
    BUBBLE,          // Bubble Sort
    MERGE,           // Merge Sort
    QUICK,           // Quick Sort
    HEAP,            // Heap Sort
    TOTAL_ALGORITHMS // Total count of algorithms
};

// Global state variables
Algorithm currentAlgorithm = SELECTION; // Currently selected algorithm
bool algorithmCompleted = false;        // Flag to track if sorting is done
bool arrayGenerated = false;            // Flag to check if array is initialized
int arr[SIZE];                         // Main array to be sorted

// Function declarations
void GenerateArray(int* arr);          // Initializes array with random values
void Swap(int* arr, int i, int j);     // Swaps two array elements
void draw(int* arr, int i = -1, int j = -1, int k = -1); // Visualizes array with highlights
void drawArray(int* arr);              // Draws array without highlights
void setup();                          // Initializes SDL window and renderer
bool processEvent();                   // Handles user input events
void runAlgorithm();                   // Runs the currently selected algorithm

// Sorting algorithm implementations
void SelectionSort(int* arr);          // Selection Sort implementation
void InsertionSort(int* arr);          // Insertion Sort implementation
void BubbleSort(int* arr);             // Bubble Sort implementation
void merge(int* arr, int l, int m, int r); // Merge helper for Merge Sort
void mergeSort(int* arr, int l, int r);    // Recursive Merge Sort
void MergeSort(int* arr);              // Wrapper for Merge Sort
int partition(int* arr, int low, int high); // Partition for Quick Sort
void quickSort(int* arr, int low, int high); // Recursive Quick Sort
void QuickSort(int* arr);              // Wrapper for Quick Sort
void heapify(int* arr, int n, int i);  // Heapify for Heap Sort
void HeapSort(int* arr);               // Heap Sort implementation

// Function implementations

// Generates a random array of values between 10 and HEIGHT-10
void GenerateArray(int* arr) {
    srand(time(NULL)); // Seed random number generator
    for (int i = 0; i < SIZE; i++) {
        arr[i] = 10 + rand() % (HEIGHT - 10); // Random height for each bar
    }
    arrayGenerated = true;    // Mark array as generated
    algorithmCompleted = false; // Reset completion flag
}

// Swaps two elements in the array
void Swap(int* arr, int i, int j) {
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;
}

// Visualizes the array with optional highlighted elements
// i = red (primary highlight), j = blue (secondary), k = green (tertiary)
void draw(int* arr, int i, int j, int k) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer); // Clear screen
    
    // Draw each element in the array
    for (int x = 0; x < SIZE; x++) {
        // Set color based on highlight status
        if (x == i) SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red
        else if (x == j) SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue
        else if (x == k) SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green
        else SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange (default)
        
        // Draw rectangle for current array element
        SDL_Rect rect = { x * (WIDTH / SIZE), HEIGHT - arr[x], WIDTH / SIZE, arr[x] };
        SDL_RenderFillRect(renderer, &rect);
    }
    
    SDL_RenderPresent(renderer); // Update screen
    SDL_Delay(10); // Small delay for visualization
}

// Draws the array without any highlights
void drawArray(int* arr) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
    SDL_RenderClear(renderer);
    
    // Draw all elements in orange
    for (int x = 0; x < SIZE; x++) {
        SDL_SetRenderDrawColor(renderer, 255, 165, 0, 255); // Orange
        SDL_Rect rect = { x * (WIDTH / SIZE), HEIGHT - arr[x], WIDTH / SIZE, arr[x] };
        SDL_RenderFillRect(renderer, &rect);
    }
    
    SDL_RenderPresent(renderer); // Update screen
}

// Handles SDL events (keyboard input, window close, etc.)
bool processEvent() {
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            quit = true;
            return true;
        }
        if (event.type == SDL_KEYDOWN) {
            switch (event.key.keysym.sym) {
                case SDLK_ESCAPE: // Quit on ESC
                    quit = true;
                    return true;
                case SDLK_r: // Regenerate array on R
                    GenerateArray(arr);
                    return true;
                // Switch algorithms with number keys 1-6
                case SDLK_1:
                    currentAlgorithm = SELECTION;
                    algorithmCompleted = false;
                    return true;
                case SDLK_2:
                    currentAlgorithm = INSERTION;
                    algorithmCompleted = false;
                    return true;
                case SDLK_3:
                    currentAlgorithm = BUBBLE;
                    algorithmCompleted = false;
                    return true;
                case SDLK_4:
                    currentAlgorithm = MERGE;
                    algorithmCompleted = false;
                    return true;
                case SDLK_5:
                    currentAlgorithm = QUICK;
                    algorithmCompleted = false;
                    return true;
                case SDLK_6:
                    currentAlgorithm = HEAP;
                    algorithmCompleted = false;
                    return true;
            }
        }
    }
    return false;
}

// Selection Sort implementation
void SelectionSort(int* arr) {
    for (int i = 0; i < SIZE - 1; i++) {
        int minIndex = i; // Assume current position is minimum
        // Find minimum in remaining array
        for (int j = i + 1; j < SIZE; j++) {
            if (arr[j] < arr[minIndex]) minIndex = j;
            // Visualize: current (i), comparing (j), minimum (minIndex)
            draw(arr, i, j, minIndex);
            if (processEvent()) return; // Check for user input
        }
        Swap(arr, i, minIndex); // Swap current with minimum
        draw(arr, i, minIndex); // Update visualization
    }
    algorithmCompleted = true; // Mark sorting as complete
}

// Insertion Sort implementation
void InsertionSort(int* arr) {
    for (int i = 1; i < SIZE; i++) {
        int key = arr[i]; // Current element to insert
        int j = i - 1;
        // Shift elements greater than key to the right
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            // Visualize: current (i), comparing (j)
            draw(arr, i, j);
            if (processEvent()) return;
            j--;
        }
        arr[j + 1] = key; // Insert key in correct position
        draw(arr, j + 1, i); // Update visualization
    }
    algorithmCompleted = true;
}

// Bubble Sort implementation
void BubbleSort(int* arr) {
    for (int i = 0; i < SIZE - 1; i++) {
        bool swapped = false; // Optimization flag
        // Compare adjacent elements
        for (int j = 0; j < SIZE - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                Swap(arr, j, j + 1);
                swapped = true;
            }
            // Visualize: comparing j and j+1
            draw(arr, j, j + 1);
            if (processEvent()) return;
        }
        if (!swapped) break; // Early exit if no swaps occurred
    }
    algorithmCompleted = true;
}

// Merge helper function for Merge Sort
void merge(int* arr, int l, int m, int r) {
    // Create temporary arrays for left and right halves
    int n1 = m - l + 1;
    int n2 = r - m;
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data to temp arrays
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

    // Merge the temp arrays back
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k] = L[i++];
        else arr[k] = R[j++];
        // Visualize: current position being written (k)
        draw(arr, k);
        if (processEvent()) return;
        k++;
    }

    // Copy remaining elements
    while (i < n1) {
        arr[k] = L[i++];
        draw(arr, k);
        if (processEvent()) return;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j++];
        draw(arr, k);
        if (processEvent()) return;
        k++;
    }

    // Free temporary memory
    delete[] L;
    delete[] R;
}

// Recursive Merge Sort
void mergeSort(int* arr, int l, int r) {
    if (l >= r) return; // Base case
    int m = l + (r - l) / 2; // Middle point
    mergeSort(arr, l, m); // Sort left half
    mergeSort(arr, m + 1, r); // Sort right half
    merge(arr, l, m, r); // Merge sorted halves
}

// Wrapper for Merge Sort
void MergeSort(int* arr) {
    mergeSort(arr, 0, SIZE - 1);
    algorithmCompleted = true;
    drawArray(arr); // Final visualization
}

// Partition function for Quick Sort
int partition(int* arr, int low, int high) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = low - 1; // Index of smaller element

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            Swap(arr, i, j);
            // Visualize: pivot (high), partition (i), current (j)
            draw(arr, i, j, high);
            if (processEvent()) return -1; // Abort if user interrupted
        }
    }
    Swap(arr, i + 1, high); // Place pivot in correct position
    draw(arr, i + 1, high);
    return i + 1; // Return partition index
}

// Recursive Quick Sort
void quickSort(int* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        if (pi == -1) return; // Check for user interruption
        quickSort(arr, low, pi - 1); // Sort left partition
        quickSort(arr, pi + 1, high); // Sort right partition
    }
}

// Wrapper for Quick Sort
void QuickSort(int* arr) {
    quickSort(arr, 0, SIZE - 1);
    algorithmCompleted = true;
    drawArray(arr); // Final visualization
}

// Heapify function for Heap Sort
void heapify(int* arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) largest = left;
    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) largest = right;

    // If largest is not root
    if (largest != i) {
        Swap(arr, i, largest);
        // Visualize: current (i), largest child (largest)
        draw(arr, i, largest);
        if (processEvent()) return;
        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest);
    }
}

// Heap Sort implementation
void HeapSort(int* arr) {
    // Build heap (rearrange array)
    for (int i = SIZE / 2 - 1; i >= 0; i--)
        heapify(arr, SIZE, i);

    // One by one extract elements from heap
    for (int i = SIZE - 1; i > 0; i--) {
        Swap(arr, 0, i); // Move current root to end
        draw(arr, 0, i); // Visualize swap
        if (processEvent()) return;
        heapify(arr, i, 0); // Heapify reduced heap
    }
    algorithmCompleted = true;
}

// Runs the currently selected algorithm
void runAlgorithm() {
    if (!arrayGenerated) return; // Don't run if array isn't ready
    
    switch (currentAlgorithm) {
        case SELECTION: SelectionSort(arr); break;
        case INSERTION: InsertionSort(arr); break;
        case BUBBLE: BubbleSort(arr); break;
        case MERGE: MergeSort(arr); break;
        case QUICK: QuickSort(arr); break;
        case HEAP: HeapSort(arr); break;
    }
}

// Initializes SDL window and renderer
void setup() {
    window = SDL_CreateWindow("Sorting Visualizer", 
                             SDL_WINDOWPOS_CENTERED, 
                             SDL_WINDOWPOS_CENTERED, 
                             WIDTH, HEIGHT, 
                             0);
    if (window) {
        renderer = SDL_CreateRenderer(window, -1, 0);
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);
    }
}

// Main function
int main(int argc, char* args[]) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "SDL initialization failed: " << SDL_GetError() << endl;
        return -1;
    }

    setup(); // Create window and renderer
    GenerateArray(arr); // Create initial random array
    drawArray(arr); // Draw initial array

    // Main application loop
    while (!quit) {
        processEvent(); // Handle user input
        if (!algorithmCompleted) {
            runAlgorithm(); // Run sorting if not completed
        }
        SDL_Delay(16); // ~60 FPS (16ms per frame)
    }

    // Cleanup SDL resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}