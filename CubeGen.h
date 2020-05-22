#pragma once
#include "pch.h"
#include "sites.h"

enum class fileType { XYZ, ToFeTOut, MESOut };
bool WriteCubeFile(sites& siteList, std::string title, std::string desc, char out[]);