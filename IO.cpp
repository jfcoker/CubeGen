#include "pch.h"
#include "IO.h"

std::ostream& operator<<(std::ostream& os, const site& st)
{
    os << fss.Int(1) << fss.Dec(st.charge) << fss.Dec(st.pos.X) << fss.Dec(st.pos.Y) << fss.Dec(st.pos.Z);
    return os;
}

std::ostream& operator<<(std::ostream& os, const sites& sts)
{
    for (int i = 0; i < sts.list.size(); i++)
        os << sts.list[i];
    return os;
}