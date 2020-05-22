#pragma once
#include "pch.h"

//Represents different possible formats of our input data file.
enum class fileType { XYZ, ToFeTOut, MESOut };

class fss
{

public:

    static std::string Int(int i)
    {
        std::stringstream strm;
        strm.width(4);
        strm.precision(0);
        strm << std::fixed << std::right << i;
        return strm.str();
    }

    static std::string Dec(double d)
    {
        std::stringstream strm;
        strm.width(12);
        strm.precision(6);
        strm << std::fixed << std::right << d;
        return strm.str();
    }

    static std::string Sci(double d)
    {
        std::stringstream strm;
        strm.width(14);
        strm.precision(5);
        strm << std::scientific << std::left << d;
        return strm.str();
    }
};