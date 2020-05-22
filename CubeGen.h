#pragma once
#include "pch.h"
#include "sites.h"

//Represents different possible formats of our input data file.
enum class fileType { XYZ, ToFeTOut, MESOut };

// Create/overwrite a .cube file with position and charge values of sites
// Volumetric data will not be used. 
// To maintain standard formatting, a single voxel is defined at the origin with arbitrary value and dimensions.
bool WriteCubeFile_NoVolData(sites& sites, std::string title, std::string desc, char out[]);

// Create/overwrite a .cube file with position and charge values of sites.
// Not currently implemented
bool WriteCubeFile(sites& sites, std::string title, std::string desc, char out[]);