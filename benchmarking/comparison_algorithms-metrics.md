# Comparison of Algorithm Efficiency

## Raw Measurements

### Run 1
Naive algorithm time: 2.779135 seconds  
Single-pass algorithm time: 0.000106 seconds  

### Run 2
Naive algorithm time: 2.769487 seconds  
Single-pass algorithm time: 0.000105 seconds  

### Run 3
Naive algorithm time: 2.770792 seconds  
Single-pass algorithm time: 0.000106 seconds  

---

## Average Execution Times

- Naive algorithm average: **2.773138 seconds**  
- Single-pass algorithm average: **0.0001057 seconds**  

---

## Relative Performance

The naive algorithm is approximately **26,240 times slower** than the single-pass algorithm.

---

## Notes

- Both algorithms return correct results.
- The naive implementation uses nested loops → **O(n²)**.
- The single-pass implementation uses one loop → **O(n)**.
- The large performance gap reflects the difference in algorithmic complexity.
