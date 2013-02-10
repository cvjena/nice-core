#include "GMSparseVectorMatrix.h"
#include <assert.h>

using namespace NICE;
using namespace NICE;
using namespace std;

GMSparseVectorMatrix::GMSparseVectorMatrix (uint _rows, uint _cols):m_rows (_rows), m_cols (_cols)
{
	resize (_rows, _cols);
}

GMSparseVectorMatrix::GMSparseVectorMatrix (const NICE::Matrix & iceA, double epsilon)
{
	m_rows = iceA.rows ();
	m_cols = iceA.cols ();
	newvectors = true;
	for (uint r = 0; r < m_rows; r++)
	{
		SparseVector *tmp = new SparseVector (m_cols);
		for (uint c = 0; c < m_cols; c++)
		{
			if (fabs (iceA (r, c)) > epsilon)
				(*tmp)[c] = iceA (r, c);
		}
		A.push_back (tmp);
	}
}

GMSparseVectorMatrix::~GMSparseVectorMatrix ()
{
	clear ();
}

SparseVector & GMSparseVectorMatrix::operator[](int i) const
{
 return *A[i];
}

void GMSparseVectorMatrix::addRow (const NICE::Vector & x)
{
	SparseVector *v = new SparseVector (x);
	m_cols = x.size ();
	v->setDim (m_cols);
	A.push_back (v);
	++m_rows;
}

void
GMSparseVectorMatrix::addRow (SparseVector * x)
{
	newvectors = false;
	A.push_back (x);
	++m_rows;
	m_cols = x->getDim ();
}

void
GMSparseVectorMatrix::clear ()
{
	if (newvectors)
	{
		for (uint i = 0; i < A.size (); i++)
		{
			delete A[i];
		}
	}
	A.clear ();
}

void
GMSparseVectorMatrix::resize (int _rows, int _cols)
{
	m_rows = _rows;
	m_cols = _cols;
	newvectors = true;
	for (uint i = 0; i < m_rows; i++)
	{
		SparseVector *tmp = new SparseVector (m_cols);
		A.push_back (tmp);
	}
}

void
GMSparseVectorMatrix::mult2 (GMSparseVectorMatrix & y, GMSparseVectorMatrix & out, bool transpx, bool transpy)
{
	int rowsx, colsx, rowsy, colsy;
	if (transpx)
	{
		colsx = m_rows;
		rowsx = m_cols;
	} else
	{
		rowsx = m_rows;
		colsx = m_cols;
	}

	if (transpy)
	{
		colsy = y.rows ();
		rowsy = y.cols ();
	} else
	{
		rowsy = y.rows ();
		colsy = y.cols ();
	}

	if (rowsy != colsx)
	{
		cout << "GMSparse::mult matrix sizes missmatched" << endl;
		exit (1);
	}

	out.resize (rowsx, colsy);

	double xval, yval, val, val2;

	for (int c = 0; c < colsy; c++)
	{
		for (int i = 0; i < rowsy; i++)
		{
			if (transpy)
				yval = y[c].get (i);
			else
				yval = y[i].get (c);

			if (yval != 0.0)
			{
				for (int r = 0; r < rowsx; r++)
				{
					if (transpx)
						xval = (*A[i]).get (r);
					else
						xval = (*A[r]).get (i);

					val = out[r].get (c);
					val2 = val + xval * yval;
					if (fabs (val2) > 10e-10)
						out[r][c] = val2;
					else if (val != 0.0)
						out[r].erase (c);
				}
			}
		}
	}
}

void
GMSparseVectorMatrix::mult (GMSparseVectorMatrix & y, GMSparseVectorMatrix & out, bool transpx, bool transpy)
{
	int rowsx, colsx, rowsy, colsy;
	if (transpx)
	{
		colsx = m_rows;
		rowsx = m_cols;
	} else
	{
		rowsx = m_rows;
		colsx = m_cols;
	}

	if (transpy)
	{
		colsy = y.rows ();
		rowsy = y.cols ();
	} else
	{
		rowsy = y.rows ();
		colsy = y.cols ();
	}

	if (rowsy != colsx)
	{
		cout << "GMSparse::mult matrix sizes missmatched" << endl;
		exit (1);
	}

	out.resize (rowsx, colsy);

	double xval, yval, val;
	for (int r = 0; r < rowsx; r++)
	{

		for (int c = 0; c < colsy; c++)
		{
			val = 0.0;
			for (int i = 0; i < rowsy; i++)
			{
				if (transpx)
					xval = (*A[i]).get (r);
				else
					xval = (*A[r]).get (i);

				if (transpy)
					yval = y[c].get (i);
				else
					yval = y[i].get (c);

				val += xval * yval;
			}

			if (fabs (val) > 10e-7)
				out[r][c] = val;

			if (!NICE::isFinite (val * val))
			{
				cout << "val " << val << endl;
				for (int i = 0; i < rowsy; i++)
				{
					if (transpx)
						xval = (*A[i]).get (r);
					else
						xval = (*A[r]).get (i);

					if (transpy)
						yval = y[c].get (i);
					else
						yval = y[i].get (c);

					val += xval * yval;
					cout << " xval: " << xval << " yval " << yval << endl;
				}
				getchar ();
			}
		}
	}


}

void
GMSparseVectorMatrix::mult (SparseVector & y, GMSparseVectorMatrix & out, bool transpx, bool transpy)
{
	int rowsx, colsx, rowsy, colsy;
	if (transpx)
	{
		colsx = m_rows;
		rowsx = m_cols;
	} else
	{
		rowsx = m_rows;
		colsx = m_cols;
	}

	if (transpy)
	{
		colsy = 1;
		rowsy = y.getDim ();
	} else
	{
		rowsy = 1;
		colsy = y.getDim ();
	}

	if (rowsy != colsx)
    fthrow(Exception, "GMSparseVectorMatrix::mult sizes of the input matrices do not match!");

	out.resize (rowsx, colsy);

	double xval, yval, val;
	for (int r = 0; r < rowsx; r++)
	{

		for (int c = 0; c < colsy; c++)
		{
			val = 0.0;
			for (int i = 0; i < rowsy; i++)
			{
				if (transpx)
					xval = (*A[i]).get (r);
				else
					xval = (*A[r]).get (i);

				if (transpy)
					yval = y.get (i);
				else
					yval = y.get (c);

				val += xval * yval;
			}

			if (fabs (val) > 10e-7)
				out[r][c] = val;
		}
	}
}

void
GMSparseVectorMatrix::multiply (NICE::Vector & y, const NICE::Vector & x) const
{
	//FIXME: einbauen
}

void
GMSparseVectorMatrix::store (ostream & os, int format) const
{
	os << m_rows << " " << m_cols << " " << A.size () << endl;
	for (int i = 0; i < (int) A.size (); i++)
	{
		A[i]->store (os, format);
	}
}

void
GMSparseVectorMatrix::restore (istream & is, int format)
{
	A.clear ();
	is >> m_rows;
	is >> m_cols;
	int size;
	is >> size;
	for (int i = 0; i < size; i++)
	{
		SparseVector *s = new SparseVector (m_cols);
		s->restore (is, format);
		A.push_back (s);
	}
}

void
GMSparseVectorMatrix::setDel (bool del)
{
	newvectors = del;
}
