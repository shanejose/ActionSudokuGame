/** @author Shane Jose
 *
 * Class that performs Google test
*/

#include <pch.h>
#include "gtest/gtest.h"
#include <wx/filefn.h>


/**
 * main class using Google Test
 * @param argc
 * @param argv
 * @return performs all tests
 */
int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);

    wxSetWorkingDirectory(L"..");
    wxInitAllImageHandlers();

    return RUN_ALL_TESTS();
}