
#include <math.h>

#include <loop.hxx>

#include "cctk.h"
#include "cctk_Arguments_Checked.h"
#include "cctk_Parameters.h"

void driver_pt1_BSSN_Ricci(CCTK_ARGUMENTS) {
    DECLARE_CCTK_ARGUMENTS_driver_pt1_BSSN_Ricci;
    
    const CCTK_REAL invdx0 = 1.0/CCTK_DELTA_SPACE(0);
    const CCTK_REAL invdx1 = 1.0/CCTK_DELTA_SPACE(1);
    const CCTK_REAL invdx2 = 1.0/CCTK_DELTA_SPACE(2);
Loop::GF3D<std::remove_reference<decltype(*lambdaU0GF)>::type,0,0,0> lambdaU0GF_(cctkGH,lambdaU0GF);
Loop::GF3D<std::remove_reference<decltype(*hDD00GF)>::type,0,0,0> hDD00GF_(cctkGH,hDD00GF);
Loop::GF3D<std::remove_reference<decltype(*RbarDD00GF)>::type,0,0,0> RbarDD00GF_(cctkGH,RbarDD00GF);
Loop::GF3D<std::remove_reference<decltype(*hDD01GF)>::type,0,0,0> hDD01GF_(cctkGH,hDD01GF);
Loop::GF3D<std::remove_reference<decltype(*RbarDD01GF)>::type,0,0,0> RbarDD01GF_(cctkGH,RbarDD01GF);
Loop::GF3D<std::remove_reference<decltype(*hDD02GF)>::type,0,0,0> hDD02GF_(cctkGH,hDD02GF);
Loop::GF3D<std::remove_reference<decltype(*RbarDD02GF)>::type,0,0,0> RbarDD02GF_(cctkGH,RbarDD02GF);
Loop::GF3D<std::remove_reference<decltype(*lambdaU1GF)>::type,0,0,0> lambdaU1GF_(cctkGH,lambdaU1GF);
Loop::GF3D<std::remove_reference<decltype(*hDD11GF)>::type,0,0,0> hDD11GF_(cctkGH,hDD11GF);
Loop::GF3D<std::remove_reference<decltype(*RbarDD11GF)>::type,0,0,0> RbarDD11GF_(cctkGH,RbarDD11GF);
Loop::GF3D<std::remove_reference<decltype(*hDD12GF)>::type,0,0,0> hDD12GF_(cctkGH,hDD12GF);
Loop::GF3D<std::remove_reference<decltype(*RbarDD12GF)>::type,0,0,0> RbarDD12GF_(cctkGH,RbarDD12GF);
Loop::GF3D<std::remove_reference<decltype(*lambdaU2GF)>::type,0,0,0> lambdaU2GF_(cctkGH,lambdaU2GF);
Loop::GF3D<std::remove_reference<decltype(*hDD22GF)>::type,0,0,0> hDD22GF_(cctkGH,hDD22GF);
Loop::GF3D<std::remove_reference<decltype(*RbarDD22GF)>::type,0,0,0> RbarDD22GF_(cctkGH,RbarDD22GF);

#include "BSSN_Ricci.h"
}
