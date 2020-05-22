#include "pch.h"
#include "IO.h"
#include "sites.h"

site::site(double x, double y, double z, double charge) : pos(x, y, z), charge(charge) {}


double ToBohr(double angs) { return angs * 1.8897259886; }

bool sites_xyz::BuildSiteList(char* xyz_file)
{
    list.clear();

    // Use contents of .xyz file to populate site vector
    // First 3 columns should be formatted as: x (float), y (float), z (float). Other columns are ignored.
    std::ifstream in;
    in.open(xyz_file);
    if (!in) 
    {
        std::cout << "***ERROR***: Couldn't open file '" << xyz_file << "'\n";
        return false;
    }

    std::string line;
    int linenum = 0;
    while (std::getline(in, line))
    {
        linenum++;
        std::stringstream linestream(line);
        double x, y, z;
        linestream >> x >> y >> z;

        if (linestream.fail())
        {
            std::cout << "***ERROR***: Unexpected formatting of .xyz file at line " << linenum << ". Expected at least 3 columns with value type float.\n";
            in.close();
            return false;
        }

        // .xyz file contains no charge/occupancy data, just defualt to 0.
        list.push_back(site(ToBohr(x), ToBohr(y), ToBohr(z), 0.0));
    }

    in.close();
    return true;
}

bool sites_mesout::BuildSiteList(char* mesout_file)
{

    list.clear();

    std::ifstream in;
    in.open(mesout_file);
    if (!in)
    {
        std::cout << "***ERROR***: Couldn't open file '" << mesout_file << "'\n";
        return false;
    }

    std::string line;
    int linenum = 0;
    while (std::getline(in, line))
    {
        linenum++;
        std::stringstream linestream(line);

        // Look for the start of the occupation densities data block
        if (line.find("Occupation densities") != std::string::npos)
        {

            double x, y, z, o;

            // Now start reading in site data until we reach a blank line, indicating we have reached the end of the block.
            std::getline(in, line);
            while (!line.empty())
            {
                linestream >> x >> y >> z >> o;
                if (linestream.fail())
                {
                    std::cout << "***ERROR***: Unexpected formatting of occupation densities block file at line " << linenum << ". Expected at least 4 columns with value type float.\n";
                    in.close();
                    return false;
                }

                // multiply occupation probability by -1.0 to get charge.
                list.push_back(site(ToBohr(x), ToBohr(y), ToBohr(z), o * -1.0));

                std::getline(in, line);
            }

            in.close();
            return true;

        }
    }

    // If we reached this point, then the occupation densities data block was never found
    std::cout << "***ERROR***: Reached EOF without finding 'Occupation densities' header. Perhaps this file contained no solutions?\n";
    in.close();
    return false;

}

bool sites_tofetout::BuildSiteList(char* tofetout_file)
{
    list.clear();

    std::ifstream in;
    in.open(tofetout_file);
    if (!in)
    {
        std::cout << "***ERROR***: Couldn't open file '" << tofetout_file << "'\n";
        return false;
    }

    std::string line;
    int linenum = 0;
    while (std::getline(in, line))
    {
        linenum++;
        std::stringstream linestream(line);

        // Look for the start of the occupation densities data block
        if (line.find("TOTAL OCCUPATION TIMES AND TIMES VISITED") != std::string::npos)
        {
            // Skip the next line, which contains column headers
            std::getline(in, line);

            double x, y, z, o;

            // Now start reading in site data until we reach EOF or a blank line, indicating we have reached the end of the block.
            std::getline(in, line);
            while (!linestream.eof() && !line.empty())
            {
                linestream >> x >> y >> z >> o;
                if (linestream.fail())
                {
                    std::cout << "***ERROR***: Unexpected formatting of occupation densities block file at line " << linenum << ". Expected at least 4 columns with value type float.\n";
                    in.close();
                    return false;
                }

                // multiply occupation probability by -1.0 to get charge.
                list.push_back(site(ToBohr(x), ToBohr(y), ToBohr(z), o * -1.0));

                std::getline(in, line);
            }

            in.close();
            return true;

        }
    }

    // If we reached this point, then the occupation densities data block was never found
    std::cout << "***ERROR***: Reached EOF without finding occupation densities header.\n";
    in.close();
    return false;

}

std::ostream& operator<<(std::ostream& os, const site& st)
{
    os << fss::Int(1) << fss::Dec(st.charge) << fss::Dec(st.pos.X) << fss::Dec(st.pos.Y) << fss::Dec(st.pos.Z);
    return os;
}

std::ostream& operator<<(std::ostream& os, const sites& sts)
{
    for (int i = 0; i < sts.list.size(); i++)
        os << sts.list[i] << "\n";
    return os;
}
