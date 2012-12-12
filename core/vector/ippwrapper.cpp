#include "core/vector/ippwrapper.h"

#ifndef NICE_USELIB_IPP
const char *ippGetStatusString(IppStatus status)
{
    switch(status) {
        case ippStsDataTypeErr:
            return "Bad or unsupported data type";
        case ippStsOutOfRangeErr:
            return "Argument is out of range or point is outside the image";
        case ippStsDivByZeroErr:
            return "An attempt to divide by zero";
        case ippStsMemAllocErr:
            return "Not enough memory allocated for the operation";
        case ippStsNullPtrErr:
            return "Null pointer error";
        case ippStsRangeErr:
            return "Bad values of bounds: the lower bound is greater than the upper bound";
        case ippStsSizeErr:
            return "Wrong value of data size";
        case ippStsBadArgErr:
            return "Function arg/param is bad";
        case ippStsNoMemErr:
            return "Not enough memory for the operation";
        case ippStsErr:
            return "Unknown error";
        case ippStsNoErr:
            return "No error"; 
        case ippStsDivByZero:
            return "Zero value(s) of the divisor in the function Div"; 
        default:
            return "Unknown error";
    }
    return "";
}
#endif
