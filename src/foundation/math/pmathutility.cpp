// pmathutility.cpp 
// Some useful math function
//
// Copyright 2012 - 2014 Future Interface. 
// This software is licensed under the terms of the MIT license.
//
// Hongwei Li lihw81@gmail.com
//

#include "pmathutility.h"

pfloat32 P_APIENTRY pDegreesToRadians(pfloat32 degrees)
{
    return degrees * P_PIOVER180;
}

puint32 P_APIENTRY pLerp(puint32 a, puint32 b, pfloat32 r)
{
    pfloat32 x = a;
    pfloat32 d = (pfloat32)((pint32)b - (pint32)a);
    return (puint32)(x + d * r);
}