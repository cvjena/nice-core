# Tutorial 07 - Optimization Problems
NICE can solve different kinds of optimization problems using different
algorithms in a modular fashion.

Some standard problems are already defined in NICE-core, including:
* Solving linear systems
* Approximating bilinear products

See the relevant doxygen documentation for more information on these.

This tutorial will show you how to implement your own, non-standard
optimization problems in a way that is compatible with NICE.

The sample problem is a simple one: find the minimum of the quadratic
function _f(x)=ax^2 +bx+c_.
The values are read from the command line.

We start by implementing the problem as a subclass of
_OptimizationProblemFirst_.
The "first" stands for first-order, meaning that the objective function is
differentiable.

The class provides us with helper functions and manages the state of the
optimization.
The member variable __parameters__ holds the current position in parameter
space.

Two functions must be implemented: __computeObjective__ and
__computeGradient__.
There also has to be a constructor that explicitly calls the
_OptimizationProblemFirst_ constructor because it needs to know the
dimensionality of the problem.

## Includes
The sample program needs some STL includes for I/O and to convert the command
line parameters to floating-point values.
We use the integrated _FirstOrderRasmussen_ solver in this example:

```c++
#include <iostream>
#include <string>
#include <sstream>
#include <core/vector/VectorT.h>
#include <core/optimization/gradientBased/OptimizationProblemFirst.h>
#include <core/optimization/gradientBased/FirstOrderRasmussen.h>
```

## The _QuadraticOptimizationProblem_ class
Our _QuadraticOptimizationProblem_ class has member variables for each of the
parameters. Everything else is managed by the base class.

The constructor initializes the member variables and class the base constructor
with the parameter "1", because this is a one-dimensional problem.

```c++
class QuadraticOptimizationProblem : public NICE::OptimizationProblemFirst {
private:
	double a, b, c;

public:
	QuadraticOptimizationProblem(double a, double b, double c) :
		OptimizationProblemFirst(1),
		a(a), b(b), c(c) { }
```

Because we want to find the minimum of the quadratic function f(x), the
objective function is the same.
The __parameters__ function returs the current state (position) of the
optimization process.

```c++
double computeObjective() {
	double x = parameters()(0);	
	return a * x * x + b * x + c;
}
```

The gradient function is just as simple.
It gets called with a const reference to a _Vector_ that matches the
dimensionality of the problem.
We write the value of the derivative f'(x) = 2ax+b into the _Vector_:

```c++
void computeGradient(NICE::Vector& newGradient) {
	double x = parameters()(0);	
	double dx_dy = 2.0 * a * x + b;
	newGradient(0) = dx_dy;
}
```

## The program
First, a small utility function to convert the command line arguments:

```c++
double convert_param(const std::string& s) {
	double r;
	if(!(std::istringstream(s) >> r)) {
		return 0;
	}
	return r;
}
```

Now, the main function.
We start by counting the argmuments and converting them if there are enough
of them.
They are the displayed for verification:

```c++
int main(int argc, char** argv) {
	// Check if enough parameters were supplied
	if (argc < 4) {
		std::cout << "USAGE: " << argv[0] << " <a> <b> <c>\n";
		return -1;
	}

	// Convert the arguments
	double param_a = convert_param(argv[1]);
	double param_b = convert_param(argv[2]);
	double param_c = convert_param(argv[3]);
	std::cout << "Optimizing function f(x) = " << param_a << " x^2 + ";
	std::cout << param_b << " x + " << param_c << "\n";
```

Solving the problem is very simple and done in three lines:

```c++
QuadraticOptimizationProblem problem(param_a, param_b, param_c);
NICE::FirstOrderRasmussen solver;
solver.optimizeFirst(problem);
```

The solution is part of the problem's state and can be accessed by calling the
__position__ method:

```c++
double x_min = problem.position()(0);
std::cout << "Solution: " << x_min << "\n";
```

## Running the sample

_Command line:_

```bash
./06_optimization 4.3 5 2.3
```

_Output:_

```
Optimizing function f(x) = 4.3 x^2 + 5 x + 2.3
FirstOrderRasmussen: initial value of the objective function is 2.3
Iteration 1 / 100  objective function = 2.3
FirstOrderRasmussen: new objective value 0.846598
Iteration 3 / 100  objective function = 0.846598
FirstOrderRasmussen: new objective value 0.846512
Iteration 7 / 100  objective function = 0.846512
FirstOrderRasmussen: low gradient 7.72715e-14 < 1e-05 = epsilonG
Solution: -0.581395
```
