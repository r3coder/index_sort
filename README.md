
INDEX SORT : O(n) sort (maybe)

Disclaimer:Function is not fully implemented.

Compile Method : use Makefile

Information

Index sort is somewhat fast sort (usually faster than std::sort).
First, index_sort will iterate through first to end, finding max and min values.  - O(n)
Next, it will put each value to new position - which index is calculated by index. 

 index = value * min / max * length

If there is no data existing on index, then put it. - O(n)
If there is data, move data to find empty space. - O(n^2)

Because it directly put data to index, it is much faster than quicksort.
But, if data is distributed well, then index_sort will sort very fast.
you can use index_sort at float, double and etc for same O(n).



coder@dgist.ac.kr
