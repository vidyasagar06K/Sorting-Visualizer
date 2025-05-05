Sorting Visualizer - README

This Sorting Visualizer allows you to visualize various sorting algorithms in action.
You can choose from the following sorting algorithms:
1. Selection Sort
2. Insertion Sort
3. Bubble Sort
4. Merge Sort
5. Quick Sort
6. Heap Sort

Each algorithm can be selected through the following keyboard keys:
- 1: Selection Sort
- 2: Insertion Sort
- 3: Bubble Sort
- 4: Merge Sort
- 5: Quick Sort
- 6: Heap Sort

Additionally, you can regenerate the array by pressing the 'R' key.

The visualization will update as the algorithm sorts the array, with different colors indicating the sorting process:
- Red: Currently selected element
- Blue: Secondary element in comparison
- Green: Tertiary element
- Orange: Default color for all elements

Features:
- Manual selection of sorting algorithm.
- Real-time array visualization with highlights.
- Ability to regenerate a new random array.

Instructions:
1. Compile and run the code.
2. Use number keys 1-6 to select an algorithm.
3. Press 'R' to regenerate a new array.
4. Press ESC to quit.

Dependencies:
- SDL2 (for graphical rendering)

To build and run this project:
1. Install SDL2 library.
2. Compile using the following command:
   ```g++ SortingVisualizer.cpp -o output.exe -IC:\SDL2-2.32.4\i686-w64-mingw32\include\SDL2 -LC:\SDL2-2.32.4\i686-w64-mingw32\lib -lmingw32 -lSDL2main -lSDL2 ```
3. Run the generated executable with:
   ```./output.exe ```

Requirements:
- SDL2 library
- g++ compiler (MinGW)
- Windows operating system (assuming you're using the SDL2 Windows version)

Ensure you have the correct version of SDL2 installed and that all paths are correctly set in the compile command. If you encounter issues, refer to the SDL2 documentation for troubleshooting.

Enjoy visualizing sorting algorithms!
