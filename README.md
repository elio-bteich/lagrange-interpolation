# Lagrange Interpolation

This project is a part of the course "Digital Creation" at Université de Nantes for the second semester of the Bachelor's Degree 2nd Year program. The purpose of this project is to demonstrate understanding of the Lagrange Interpolation method and its implementation in code. The project aims to provide an interactive experience for students to visualize and understand the concepts in a hands-on manner.  
  
By default the function that we are interpoling is f(x)=x/sqrt(x), the x that we are evaluating is 0.55, the interval is 0 to 2, and the interpolation points number is 10, you can change that whenever you want by modifying its values in the main.cpp file.

## Installing Dependencies

#### Mac
```
brew install gnuplot
```
#### Linux
```
sudo apt-get install gnuplot
```

## Compiling
```bash
make
```

## Executing
```bash
./run.out
```
## Output

Interpolation image of f(x) compared to x/sqrt(x) for a given x  
Maximum relative and absolute errors  
.eps files that contains the interpolation and error charts drawn with gnuplot
