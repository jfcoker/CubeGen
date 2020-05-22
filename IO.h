#pragma once
#include "pch.h"
#include "sites.h"

class frmtStrStream
{
private:

    std::stringstream strm;

public:

    std::string Int(int i)
    {
        strm.str("");
        strm.width(4);
        strm.precision(0);
        strm << std::fixed << std::right << i;
        return strm.str();
    }

    std::string Dec(double d)
    {
        strm.str("");
        strm.width(12);
        strm.precision(6);
        strm << std::fixed << std::right << d;
        return strm.str();
    }

    std::string Sci(double d)
    {
        strm.str("");
        strm.width(14);
        strm.precision(5);
        strm << std::scientific << std::left << d;
        return strm.str();
    }
};

frmtStrStream fss;