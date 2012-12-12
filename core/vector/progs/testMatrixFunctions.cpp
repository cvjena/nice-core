/** 
* @file testMatrixFunctions.cpp
* @author Alexander Lütz
* @date  07/10/2011
* @brief test routine for the main functions of the MatrixT-class (at the moment only row/col-deletion is tested)
*/

#include "core/vector/MatrixT.h"
#include "iostream"
#include "vector"
#include "core/basics/Exception.h"

using namespace std;

int main(int argc, char* argv[])
{
	NICE::Matrix foo(10,10,0.0);
	std::cerr << "foo: " << std::endl;
	for (uint i = 0; i < foo.rows(); i++)
	{
		for (uint j = 0; j < foo.cols(); j++)
		{
			if (i>0)
				foo(i,j) = i;
			else foo(i,j) = j;
			std::cerr << " " << foo(i,j);
		}
		std::cerr << std::endl;
	}
	
	foo.deleteRow(8);
	
	std::cerr << "foo after deleting row 8: " << std::endl;
	for (uint i = 0; i < foo.rows(); i++)
	{
		for (uint j = 0; j < foo.cols(); j++)
		{
			std::cerr << " " << foo(i,j);
		}
		std::cerr << std::endl;
	}
	
	foo.deleteCol(7);
	
	std::cerr << "foo after deleting col 7: " << std::endl;
	for (uint i = 0; i < foo.rows(); i++)
	{
		for (uint j = 0; j < foo.cols(); j++)
		{
			std::cerr << " " << foo(i,j);
		}
		std::cerr << std::endl;
	}
	
	std::vector<int> indices_to_delete;
	indices_to_delete.push_back(2);
	indices_to_delete.push_back(5);
	
	foo.deleteRows(indices_to_delete);
	std::cerr << "foo after deleting rows 2 and 5: " << std::endl;
	for (uint i = 0; i < foo.rows(); i++)
	{
		for (uint j = 0; j < foo.cols(); j++)
		{
			std::cerr << " " << foo(i,j);
		}
		std::cerr << std::endl;
	}
	
	foo.deleteCols(indices_to_delete);
	std::cerr << "foo after deleting cols 2 and 5: " << std::endl;
	for (uint i = 0; i < foo.rows(); i++)
	{
		for (uint j = 0; j < foo.cols(); j++)
		{
			std::cerr << " " << foo(i,j);
		}
		std::cerr << std::endl;
	}
	
	std::cerr << "Try to delete row 11, which should produce an error!" << std::endl;
	
	try{
		//this should produce an error!
		foo.deleteRow(11);
	}
	catch (NICE::Exception e)
	{
		std::cerr << "Exception succesfully thrown!" << std::endl;
	}
	
	return 0;
}