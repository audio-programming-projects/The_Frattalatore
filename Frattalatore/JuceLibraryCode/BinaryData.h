/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#pragma once

namespace BinaryData
{
    extern const char*   burningShipBackgroundImg_png;
    const int            burningShipBackgroundImg_pngSize = 64349;

    extern const char*   JuliaBackgroundImg1_png;
    const int            JuliaBackgroundImg1_pngSize = 139153;

    extern const char*   JuliaBackgroundImg2_png;
    const int            JuliaBackgroundImg2_pngSize = 121878;

    extern const char*   Knob2_png;
    const int            Knob2_pngSize = 33608;

    extern const char*   LOGO_Capr_png;
    const int            LOGO_Capr_pngSize = 1712519;

    extern const char*   mandelbrotBackgroundImg_png;
    const int            mandelbrotBackgroundImg_pngSize = 59553;

    // Number of elements in the namedResourceList and originalFileNames arrays.
    const int namedResourceListSize = 6;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Points to the start of a list of resource filenames.
    extern const char* originalFilenames[];

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes);

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding original, non-mangled filename (or a null pointer if the name isn't found).
    const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
}
