# Multithreaded-Sorting-Application
A tiny demo that shows how to use **three threads** to sort an integer list:

1. **Thread 0** – sorts the left half.  
2. **Thread 1** – sorts the right half.  
3. **Thread 2** – merges the two sorted halves.

The sort inside each half is **Insertion Sort** (simple, in-place).  
The final result is a fully ordered list that is printed to `stdout`.
