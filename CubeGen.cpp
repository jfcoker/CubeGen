#include "pch.h"
#include "IO.h"
#include "sites.h"
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
    strcat_s(argv[2], sizeof argv[2], ".cube");
    strcpy_s(outfile, argv[2]);

    // Generate cube file
    //switch (inType)
    //{
    //case fileType::XYZ: BuildCubeFile_XYZ(infile, outfile, "title", "desc"); break;

    //case fileType::ToFeTOut: BuildCubeFile_ToFeT(infile, outfile, "title", "desc"); break;

    //case fileType::MESOut: BuildCubeFile_MES(infile, outfile, "title", "desc"); break;

    //}


}

double ToBohr(double angs) { return angs * 1.8897259886; }

bool WriteCubeFile_NoVolData(sites& sites, std::string title, std::string desc, char out[])
{
    const size_t maxCommentLength = 78; //80 chars minus 2 for possible linefeed and carriage return chars.
    if (title.length() >= maxCommentLength || desc.length() >= maxCommentLength)
    {
        std::cout << "***ERROR***: Couldn't build .cube file: Title or description exceeded 80 characters.\n";
        return false;
    }

    if (sites.list.empty())
    {
        std::cout << "***ERROR***: Couldn't build .cube file: empty site vector provided.\n";
        return false;
    }

    // Open/create output file
    std::ofstream cube;
    cube.open(out);
    if (!cube)
    {
        std::cout << "***ERROR***: Couldn't build .cube file: Failed to open " << out << "\n";
        return false;
    }
    
    // Write <title> and <desc> lines
    cube << title << "\n";
    cube << desc << "\n";

    // Write <# sites (int)> <origin coords (3 x float)> <# data vals per voxel (int)>
    cube << fss::Int(sites.list.size()) << fss::Dec(0.0) << fss::Dec(0.0) << fss::Dec(0.0) << fss::Int(1) << "\n";

    // Write <# voxels along X,Y,Z-axis (int)> <vector defining size of voxel in units of bohr radius (3 x float)> 
    cube << fss::Int(1) << fss::Dec(1.0) << fss::Dec(0.0) << fss::Dec(0.0) << "\n";
    cube << fss::Int(1) << fss::Dec(0.0) << fss::Dec(1.0) << fss::Dec(0.0) << "\n";
    cube << fss::Int(1) << fss::Dec(0.0) << fss::Dec(0.0) << fss::Dec(1.0) << "\n";

    // Write <atomic number of atom i (int)> <nuclear charge of atom i (float)> <position of atom i (3 x float)>
    cube << sites;

    // Write value of the single voxel.
    cube << fss::Dec(0.0) << "\n";

    cube.close();
    return true;
 }

 bool WriteCubeFile(sites& sites, std::string title, std::string desc, char out[])
 {

     // Not currently implemented: Just display an error message and return false to indicate failure.
     std::cout << "***ERROR***: function 'WriteCubeFile' not implemented. Use 'WriteCubeFile_NoVolData' for now.\n";
     return false;

     // ToDo: implement. Commented out code below might be useful.

     //// For each axis grab the min and max site positions, as well as the smallest gap between sites 
     //double minX = std::numeric_limits<double>::max(), minY = minX, minZ = minX;
     //double maxX = std::numeric_limits<double>::min(), maxY = maxX, maxZ = maxX;
     //double sepX = std::numeric_limits<double>::max(), sepY = sepX, sepZ = sepX;
     //double sep;
     //for (int i = 0; i < sites.list.size(); i++)
     //{
     //    if (sites[i].pos.X < minX) minX = sites[i].pos.X;
     //    if (sites[i].pos.Y < minY) minY = sites[i].pos.Y;
     //    if (sites[i].pos.Z < minZ) minZ = sites[i].pos.Z;
     //    if (sites[i].pos.X > maxX) maxX = sites[i].pos.X;
     //    if (sites[i].pos.Y > maxY) maxY = sites[i].pos.Y;
     //    if (sites[i].pos.Z > maxZ) maxZ = sites[i].pos.Z;

     //    if (i != 0)
     //    {
     //        sep = abs(sites[i].pos.X - sites[i - 1].pos.X); if (sep < sepX) sepX = sep;
     //        sep = abs(sites[i].pos.Y - sites[i - 1].pos.Y); if (sep < sepY) sepY = sep;
     //        sep = abs(sites[i].pos.Z - sites[i - 1].pos.Z); if (sep < sepZ) sepZ = sep;
     //    }

     //}

     //// length of sides of voxel, in multiples of the bohr radius
     //double vx = 5.0;
     //double vy = 5.0;
     //double vz = 5.0;

     //// Number of voxels along each side of the cube
     //int Nx = 1;
     //int Ny = 1;
     //int Nz = 1;

     //// This next block would set the voxel size using the smallest seperation between sites
     ////if (sepX > 0) vx = ToBohr(sepX);
     ////if (sepY > 0) vy = ToBohr(sepY);
     ////if (sepZ > 0) vz = ToBohr(sepX);

     //// However, for now, just set the number of voxels by using a the voxel size of 1 bohr
     //Nx = (int)ceil(ToBohr(maxX - minX) / vx);
     //Ny = (int)ceil(ToBohr(maxY - minY) / vy);
     //Nz = (int)ceil(ToBohr(maxZ - minZ) / vz);


     //// Create a 3D array, with each element holding the intensity value of the corresponding voxel
     //// If more than one site falls within a voxel bounds, just sum there intensities
     //double* valArray = new double[Nx * Ny * Nz]; // The array is flattened to 1D

     ////Might be a quicker way to do this
     //double upperX, lowerX, upperY, lowerY, upperZ, lowerZ, posX, posY, posZ;
     //for (int k = 0; k < Nz; ++k)
     //{
     //    lowerZ = minZ + k * vz;
     //    upperZ = minZ + (k + 1.0) * vz;
     //
     //    for (int j = 0; j < Ny; ++j)
     //    {

     //        lowerY = minY + j * vy;
     //        upperY = minY + (j + 1.0) * vy;

     //        for (int i = 0; i < Nx; ++i)
     //        {

     //            lowerX = minX + i * vx;
     //            upperX = minX + (i + 1.0) * vx;

     //            double sum = 0.0;

     //            for (int s = 0; s < sites.size(); s++)
     //            {
     //                posX = ToBohr(sites[s].pos.X);
     //                posY = ToBohr(sites[s].pos.Y);
     //                posZ = ToBohr(sites[s].pos.Z);

     //                if ((posX >= lowerX && posX < upperX)
     //                    && (posY >= lowerY && posY < upperY)
     //                    && (posZ >= lowerZ && posZ < upperZ))
     //                    sum += sites[s].occProb;
     //            }

     //            valArray[i + j + k] = sum;
     //        }
     //    }
     //}


     //// Write <title> and <desc> lines
     //cube << title << "\n";
     //cube << desc << "\n";

     //// Write <# sites (int)> <origin coords (3 x float)> <# data vals per site (int)>
     //formattedStrStream fss;
     //cube << fss::Int(sites.size()) << fss::Dec(minX) << fss::Dec(minY) << fss::Dec(minZ) << fss::Int(1) << "\n";

     //// Write <# voxels along X,Y,Z-axis (int)> <vector defining size of voxel in units of bohr radius (3 x float)> 
     //cube << fss::Int(Nx) << fss::Dec(vx) << fss::Dec(0.0) << fss::Dec(0.0) << "\n";
     //cube << fss::Int(Ny) << fss::Dec(0.0) << fss::Dec(vy) << fss::Dec(0.0) << "\n";
     //cube << fss::Int(Nz) << fss::Dec(0.0) << fss::Dec(0.0) << fss::Dec(vz) << "\n";

     //// Write <atomic number of atom i (int)> <nuclear charge of atom i (float)> <position of atom i (3 x float)>
     //for (int i = 0; i < sites.size(); i++)
     //    cube << fss::Int(1) << fss::Dec(sites[i].occProb * -1.0) << fss::Dec(ToBohr(sites[i].pos.X)) << fss::Dec(ToBohr(sites[i].pos.Y)) << fss::Dec(ToBohr(sites[i].pos.Z)) << "\n";

     //// Write data for each voxel
     //// Outer loop: Z, Middle loop: Y, Inner loop: X
     //for (int k = 0; k < Nz; k++)
     //    for (int j = 0; j < Ny; j++)
     //    {
     //        for (int i = 0; i < Nx; i++)
     //        {
     //            //cube << fss::Dec(valArray[i + j + k]); // Uncomment this line if we are using voxels / volumetric data
     //            cube << fss::Dec(0.0);
     //            if ((i + 1) % 6 == 0) cube << "\n"; // Don't include more than 6 values per line
     //        }
     //        cube << "\n";
     //    }


     //cube.close();
     //delete[] valArray; // Uncomment this line if we are using voxels / volumetric data
     //return true;
 }



