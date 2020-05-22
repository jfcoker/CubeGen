#include "pch.h"
#include "sites.h"

site::site(double x, double y, double z, double charge) : pos(x, y, z), charge(charge) {}

// Remember: pos data is stored in multiples of Bohr raduis

bool sites_xyz::BuildSiteList(char* xyz_file)
{
	// ToDo: implement
	return false;
}

bool sites_mesout::BuildSiteList(char* mesout_file)
{
	// ToDo: implement
	return false;
}

bool sites_tofetout::BuildSiteList(char* tofetout_file)
{
	// ToDo: implement
	return false;
}


