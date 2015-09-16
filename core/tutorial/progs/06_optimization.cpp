/*
 * Tutorial 07 - Optimization Problmes
 * Sample Implementation
 *
 * @file 06_optimization.cpp
 * @brief Sample implementation for tutorial 07
 * @date 28.04.2014
 * @author Clemens-A. Brust
 */

#include <iostream>
#include <string>
#include <sstream>
#include <core/vector/VectorT.h>
#include <core/optimization/gradientBased/OptimizationProblemFirst.h>
#include <core/optimization/gradientBased/FirstOrderRasmussen.h>

class QuadraticOptimizationProblem : public NICE::OptimizationProblemFirst {
private:
	double a, b, c;

public:
	QuadraticOptimizationProblem(double a, double b, double c) :
		OptimizationProblemFirst(1),
		a(a), b(b), c(c) { }

	double computeObjective() {
		double x = parameters()(0);	
		return a * x * x + b * x + c;
	}
	
	void computeGradient(NICE::Vector& newGradient) {
		double x = parameters()(0);	
		double dx_dy = 2.0 * a * x + b;
		newGradient(0) = dx_dy;
	}
};


/*
 * Parameter conversion
 */
double convert_param(const std::string& s) {
	double r;
	if(!(std::istringstream(s) >> r)) {
		return 0;
	}
	return r;
}


/*
 * Entry point
 */
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

	// Instantiate and solve the problem
	QuadraticOptimizationProblem problem(param_a, param_b, param_c);
	NICE::FirstOrderRasmussen solver;
	solver.optimizeFirst(problem);

	// Display the solution
	double x_min = problem.position()(0);
	std::cout << "Solution: " << x_min << "\n";

	return 0;
}
