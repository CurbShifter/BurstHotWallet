/* =========================================================================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#ifndef BINARYDATA_H_123713452_INCLUDED
#define BINARYDATA_H_123713452_INCLUDED

namespace BinaryData
{
    extern const char*   BurstHotWalleticon_svg;
    const int            BurstHotWalleticon_svgSize = 9351;

    extern const char*   cog_svg;
    const int            cog_svgSize = 2479;

    extern const char*   groupchat_svg;
    const int            groupchat_svgSize = 9692;

    extern const char*   hatnubgp1_svg;
    const int            hatnubgp1_svgSize = 4079;

    extern const char*   hatnubgp2_svg;
    const int            hatnubgp2_svgSize = 4156;

    extern const char*   Ubuntu_Medium_Nerd_Font_Complete_ttf;
    const int            Ubuntu_Medium_Nerd_Font_Complete_ttfSize = 1040724;

    extern const char*   NotoSansRegular_ttf;
    const int            NotoSansRegular_ttfSize = 313144;

    // Points to the start of a list of resource names.
    extern const char* namedResourceList[];

    // Number of elements in the namedResourceList array.
    const int namedResourceListSize = 7;

    // If you provide the name of one of the binary resource variables above, this function will
    // return the corresponding data and its size (or a null pointer if the name isn't found).
    const char* getNamedResource (const char* resourceNameUTF8, int& dataSizeInBytes) throw();
}

#endif
