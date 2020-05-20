#pragma once

enum class fileType{ XYZ, ToFeTOut, MESOut };
void BuildCubeFile_XYZ(char in[], char out[], std::string title, std::string desc);
void BuildCubeFile_ToFeT(char in[], char out[], std::string title, std::string desc);
void BuildCubeFile_MES(char in[], char out[], std::string title, std::string desc);