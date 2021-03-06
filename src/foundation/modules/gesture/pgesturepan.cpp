// pgesturepan.cpp
// The gesture pan file.
//
// Copyright 2012 - 2014 Future Interface. 
// This software is licensed under the terms of the MIT license.
//
// Hongwei Li lihw81@gmail.com


#include "pgesturemanager.h"
#include "pgesture_private.h"

#include <PFoundation/pgesturemanager.h>
#include <PFoundation/pcontext.h>

PGesturePan::PGesturePan(PGestureManager* manager, pfloat32 distanceThreshold)
    : PAbstractGesture(manager, P_GESTURE_TYPE_PAN)
{
    m_distanceThreshold = distanceThreshold;

    reset();
}

PGesturePan::~PGesturePan()
{
}

void PGesturePan::setDistanceThreshold(pfloat32 value)
{
    m_distanceThreshold = value;
}

void PGesturePan::touchDown(pint32 x, pint32 y, puint32 timeStamp, pint32 pointer)
{
    if (!m_enabled)
    {
        return ;
    }

    if (pointer > 0)
    {
        // During pan, receiving another pointer down, send pan end event and reset
        if (m_state == STATE_MOVING)
        {
             m_manager->context()->onPanEnd();
        }

        reset();
    }
    else
    {
        m_x = x;
        m_y = y;

        m_state = STATE_POSSIBLE;
    }
}

void PGesturePan::touchMove(pint32 x, pint32 y, puint32 timeStamp, pint32 pointer)
{
    if (!m_enabled)
    {
        return ;
    }

    if (pointer > 0)
    {
        return;
    }

    switch (m_state)
    {
        case STATE_POSSIBLE:
            {
                // If we moved enought distance 
                pfloat32 dx = (pfloat32)m_x - (pfloat32)x;
                pfloat32 dy = (pfloat32)m_x - (pfloat32)y;

                if (dx * dx + dy * dy > m_distanceThreshold * m_distanceThreshold)
                {
                    // Call pan begin.
                    m_manager->context()->onPanBegin(m_x, m_y);
    
                    // Call pan move.
                    m_manager->context()->onPan(m_x, m_y, x - m_x, y - m_y);

                    m_x = x;
                    m_y = y;

                    // Update the state to move.
                    m_state = STATE_MOVING;
                }
            }
            break;
        case STATE_MOVING:
            {
                // Call pan move.
                m_manager->context()->onPan(m_x, m_y, x - m_x, y - m_y);

                m_x = x;
                m_y = y;

                // Update the state to move.
                m_state = STATE_MOVING;
            }
            break;
        default:
            break;
    } 
}

void PGesturePan::touchUp(pint32 x, pint32 y, puint32 timeStamp, pint32 pointer)
{
    if (!m_enabled)
    {
        return ;
    }

    if (pointer > 0)
    {
        return;
    }
    
    switch (m_state)
    {
        case STATE_MOVING:
            {
                // Call pan end.
                m_manager->context()->onPanEnd();
                reset();
            }
            break;
        default:
            break;
    }
}

void PGesturePan::reset()
{
    m_state = STATE_READY;
}

