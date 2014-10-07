// parcball.cpp
// To rotate the scene based on the mouse input in the screen.
//
// Copyright 2012 - 2014 Future Interface. 
// This software is licensed under the terms of the MIT license.
//
// Hongwei Li lihw81@gmail.com
//



#include "parcball.h"


PArcball::PArcball()
{
    m_moving = false;
}
    
PArcball::~PArcball()
{
}

void PArcball::restart()
{
    m_moving = false;
    m_lastRotation = m_rotation;
}

void PArcball::updateMouse(const pfloat32 x, const pfloat32 y)
{
    if (!m_moving)
    {
        mapToSphere(x, y, &m_lastArcballCoordinate.m_v[0]);
        pQuaternionIdentity(m_deltaRotation.m_q);
        m_moving = true;
    }
    else
    {
        mapToSphere(x, y, &m_arcballCoordinate[0]);

        PVector3 perp;
        pVector3Cross(&m_lastArcballCoordinate.m_v[0], 
                      &m_arcballCoordinate.m_v[0], 
                      &perp.m_v[0]);

        // Compute the rotating quaternion
        pfloat32 l = perp.length();

        if (l > 1e-4f) 
        {
            m_deltaRotation.m_q[0] = perp[0];
            m_deltaRotation.m_q[1] = perp[1];
            m_deltaRotation.m_q[2] = perp[2];
            m_deltaRotation.m_q[3] = m_lastArcballCoordinate.dot(m_arcballCoordinate); 
        } 
        else 
        {
            pQuaternionIdentity(m_deltaRotation.m_q);
        }

        pQuaternionMultiply(m_lastRotation.m_q, m_deltaRotation.m_q, m_rotation.m_q);
    }
}

const pfloat32* PArcball::rotationMatrixF() const
{
    pQuaternionGetMatrix3x3(&m_rotation.m_q[0], &m_rotationMatrix.m_m[0]);
    return &m_rotationMatrix.m_m[0];
}

const PMatrix3x3 &PArcball::rotationMatrix() const
{
    pQuaternionGetMatrix3x3(&m_rotation.m_q[0], &m_rotationMatrix.m_m[0]);
    return m_rotationMatrix;
}

void PArcball::mapToSphere(const pfloat32 x, const pfloat32 y, pfloat32* coordinate)
{
    coordinate[0] = (pfloat32)x;
    coordinate[1] = (pfloat32)y;

    pfloat32 l = coordinate[0] * coordinate[0] + coordinate[1] * coordinate[1];

    if (l > 1.0f) 
    {
        pfloat32 inv = 1.0f / sqrt(l);
        coordinate[0] *= inv;
        coordinate[1] *= inv;
        coordinate[2] = 0.0f;
    } 
    else 
    {
        coordinate[2] = sqrt(1.0f - l);
    }
}

