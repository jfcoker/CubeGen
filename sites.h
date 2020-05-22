#pragma once
#include "pch.h"

// A single site
const class site
{
private:

	// A structure that will be used to hold the position of the site.
	struct vec 
	{ 
		double X, Y, Z;
		vec(double x, double y, double z) : X(x), Y(y), Z(z) {}
	};


public:



	// The position of the site.
	vec pos;

	// The charge of the site in multiples of the standard charge. Equalt to the occupation probability multiplied by -1.
	double charge;

	// Construct a site object
	site(double x, double y, double z, double charge);

};

// An abstract class which holds a list of sites.
// Different methods will be used to build the list depending on the input file type.
// Each of these methods is treated as an implementation of the pure virtual function held by this abstract class.
class sites
{
private:

	const std::vector<site> siteList;

	// Pure virtual function with multiple implementations, one for each input file type.
	virtual bool BuildSiteList(char* file) = 0;

};

class sites_xyz : public sites {bool BuildSiteList(char* xyz_file);};

class sites_mesout : public sites { bool BuildSiteList(char* mesout_file); };

class sites_tofetout : public sites { bool BuildSiteList(char* tofetout_file); };

