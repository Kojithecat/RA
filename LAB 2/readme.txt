the c++ files contain the algorithm and export to the results folder the number of comparisons for that algorithm:

hoares_quickselect_normal.cpp -> Hoare's Quickselect algorithm.

randomized_selection.cpp -> Randomized selection algorithm.

hoares_quickselect_median3.cpp -> Quickselect with median of 3.


The python files make plots of the data from the comparisons:

quick_analysis.py -> Plots the results for the first part of the assignment (Quickselect)

randomized_selection_analysis.py -> Plots the results for the second part of the assignment (Randomized selection)

comparison.py -> Plots the results for the bonus part of the assignment (Comaring the algorithms)

c++ files: g++ -o output_file.x input_file.cpp
	   ./output_file.x
	   
python files: python3 input_file.py
