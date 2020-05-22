#pragma once
#include "pch.h"

// A single site
class site
{
private:

	// A structure that will be used to hold the position of the site.
	struct vec 
	{ 
		double X, Y, Z;
		vec(double x, double y, double z) : X(x), Y(y), Z(z) {}
	};


public:

	// The position of the site. Coordinates are multiples of the bohr radius.
	vec pos;

	// The charge of the site in multiples of the standard charge. Equalt to the occupation probability multiplied by -1.
	double charge;

	// Construct a site object
	site(double x, double y, double z, double charge);

	// outputs information about the site formatted as: <atomic number of atom i (int)> <nuclear charge of atom i (float)> <position of atom i (3 x float)>
	friend std::ostream& operator<<(std::ostream& os, const site& st);

};

// An abstract class which holds a list of sites.
// Different methods will be used to build the list depending on the input file type.
// Each of these methods is treated as an implementation of the pure virtual function held by this abstract class.
class sites
{

public:

	std::vector<site> list;

	// For each site, outputs a newline formatted as: <atomic number of atom i (int)> <nuclear charge of atom i (float)> <position of atom i (3 x float)>
	friend std::ostream& operator<<(std::ostream& os, const sites& sts);

private:

	// Pure virtual function with multiple implementations, one for each input file type.
	virtual bool BuildSiteList(char* file) = 0;

};

class sites_xyz : public sites {bool BuildSiteList(char* xyz_file);};

// Note: If MESolver found multiple solutions, only the first will be used to build the cube file.
// This can happen if the singular value tolerance is set too high.
class sites_mesout : public sites { bool BuildSiteList(char* mesout_file); };

class sites_tofetout : public sites { bool BuildSiteList(char* tofetout_file); };

