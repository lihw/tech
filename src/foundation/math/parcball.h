// parcball.h
// To rotate the scene based on the mouse input in the screen.
//
// Copyright 2012 - 2014 Future Interface. 
// This software is licensed under the terms of the MIT license.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PARCBALL_H
#define PARCBALL_H

#include <PFoundation/pvector3.h>
#include <PFoundation/pmatrix3x3.h>
#include <PFoundation/pquaternion.h>

class P_DLLEXPORT PArcball
{
public:
    PArcball();
    ~PArcball();

    // Restart the arcball movement. Clean the current state.
    void restart();

    // Update the current mouse position in the viewport coordinate (OpenGL coordinate).
    void updateMouse(const pfloat32 x, const pfloat32 y);

    // Fetch the current 3x3 rotation matrix of this arcball.
    const pfloat32* rotationMatrixF() const;
    const PMatrix3x3 &rotationMatrix() const;
    // Return the rotation quaternion of this arcball.
    P_INLINE const PQuaternion &rotation() const { return m_rotation; }
    // Return the rotation of this mouse movement (from restart() to current).
    P_INLINE const PQuaternion &deltaRotation() const { return m_deltaRotation; }

private:
    PQuaternion         m_rotation;
    PQuaternion         m_lastRotation;
    PQuaternion         m_deltaRotation;
    mutable PMatrix3x3  m_rotationMatrix;
    PVector3            m_lastArcballCoordinate;
    PVector3            m_arcballCoordinate;
    pbool               m_moving; // In moving mode, the rotation matrix keeps updating.
    

    // Map the viewport coordinate mouse position to the sphere coordinate.
    void mapToSphere(const pfloat32 x, const pfloat32 y, pfloat32* coordinate);
};

#endif
