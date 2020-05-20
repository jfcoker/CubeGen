#include "pch.h"
#include "CubeGen.h"

fileType inType;

int main(int argc, char* argv[])
{
    // Check if user is asking for help on this command
    if (argc == 2 && (strcmp(argv[1], "-h") || strcmp(argv[1], "--help")))
    {
        std::cout << "CubeGen.exe <file type: 'XYZ' OR 'ToFeT' OR 'MES'> <path to .xyz file OR ToFeT .out file OR MESolver .out file> \n";
        return 0;
    }

    //Parse command line parameters.
    if (argc < 3) 
    {
        std::cout << "*** ERROR ***: Expect at least two argument: Input file type, and path to input file\n";
        exit(-1);
    }

    if (strcmp(argv[1], "XYZ")) inType = fileType::XYZ;
    else if (strcmp(argv[1], "TOFET")) inType = fileType::ToFeTOut;
    else if (strcmp(argv[1], "MES")) inType = fileType::MESOut;

    char infile[128], outfile[128];
    char* chptr;
    strcpy_s(infile, argv[2]);
    
    // Create the path to outfile by removing the infile file extension and replacing it with '.cube'
    chptr = strchr(argv[2],'.');
    if (chptr != NULL) *chptr = '\0';
    strcpy_s(outfile, strcat(argv[2], ".cube"));
}
