#pragma once
#include "pch.h"
#include "sites.h"

enum class fileType { XYZ, ToFeTOut, MESOut };
bool WriteCubeFile(sites& siteList, char out[], std::string title, std::string desc);