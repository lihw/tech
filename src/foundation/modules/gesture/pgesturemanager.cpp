// pgesturemanager.cpp
// The gesture detector files.
//
// Copyright 2012 - 2014 Future Interface. 
// This software is licensed under the terms of the MIT license.
//
// Hongwei Li lihw81@gmail.com


#include "pgesturemanager.h"

#include "pgesture_private.h"

#include <PFoundation/pcontext.h>
#include <PFoundation/pnew.h>
#include <PFoundation/plog.h>
#include <PFoundation/passert.h>
#include <PFoundation/ptime.h>

#include "pgesture_private.h"
    
PGestureManager::PGestureManager(PContext *context)
    : PModule("gesture-manager", context)
{  
    m_gestures[P_GESTURE_TYPE_TAP]       = PNEW(PGestureTap(this));
    m_gestures[P_GESTURE_TYPE_LONGPRESS] = PNEW(PGestureLongPress(this));
    m_gestures[P_GESTURE_TYPE_FLING]     = PNEW(PGestureFling(this));
    m_gestures[P_GESTURE_TYPE_PAN]       = PNEW(PGesturePan(this));
    m_gestures[P_GESTURE_TYPE_PINCH]     = PNEW(PGesturePinch(this));
    
    m_gesturesEnabled[P_GESTURE_TYPE_TAP]       = false;
    m_gesturesEnabled[P_GESTURE_TYPE_LONGPRESS] = false;
    m_gesturesEnabled[P_GESTURE_TYPE_FLING]     = false;
    m_gesturesEnabled[P_GESTURE_TYPE_PAN]       = false;
    m_gesturesEnabled[P_GESTURE_TYPE_PINCH]     = false;
}

PGestureManager::~PGestureManager()
{
    PASSERT(m_gestures[P_GESTURE_TYPE_TAP] == P_NULL);
    PASSERT(m_gestures[P_GESTURE_TYPE_LONGPRESS] == P_NULL);
    PASSERT(m_gestures[P_GESTURE_TYPE_FLING] == P_NULL);
    PASSERT(m_gestures[P_GESTURE_TYPE_PAN] == P_NULL);
    PASSERT(m_gestures[P_GESTURE_TYPE_PINCH] == P_NULL);
}

void PGestureManager::uninitialize()
{
    PDELETE(m_gestures[P_GESTURE_TYPE_TAP]);
    PDELETE(m_gestures[P_GESTURE_TYPE_LONGPRESS]);
    PDELETE(m_gestures[P_GESTURE_TYPE_FLING]);
    PDELETE(m_gestures[P_GESTURE_TYPE_PAN]);
    PDELETE(m_gestures[P_GESTURE_TYPE_PINCH]);
}

void PGestureManager::update()
{
    pfloat32 deltaTime = m_context->clock().systemDeltaTime();

    m_gestures[P_GESTURE_TYPE_TAP]->update(deltaTime);
    m_gestures[P_GESTURE_TYPE_LONGPRESS]->update(deltaTime);
    m_gestures[P_GESTURE_TYPE_FLING]->update(deltaTime);
    m_gestures[P_GESTURE_TYPE_PAN]->update(deltaTime);
    m_gestures[P_GESTURE_TYPE_PINCH]->update(deltaTime);
}

pbool PGestureManager::resume()
{
    m_gestures[P_GESTURE_TYPE_TAP]->reset();
    m_gestures[P_GESTURE_TYPE_LONGPRESS]->reset();
    m_gestures[P_GESTURE_TYPE_FLING]->reset();
    m_gestures[P_GESTURE_TYPE_PAN]->reset();
    m_gestures[P_GESTURE_TYPE_PINCH]->reset();

    return true;
}

void PGestureManager::recognize(PInputEventTouch::TouchCursor *cursor)
{
    pint32  x         = cursor->m_x;
    pint32  y         = cursor->m_y;
    pint32  pointer   = cursor->m_id;
    puint32 timestamp = cursor->m_timestamp;

    if (pointer > 1)
    {
        return ;
    }

    if (cursor->m_state == P_CURSOR_STATE_DOWN)
    {
        if (m_gesturesEnabled[P_GESTURE_TYPE_TAP])
        {
            m_gestures[P_GESTURE_TYPE_TAP]->touchDown(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_LONGPRESS])
        {
            m_gestures[P_GESTURE_TYPE_LONGPRESS]->touchDown(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_FLING])
        {
            m_gestures[P_GESTURE_TYPE_FLING]->touchDown(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_PAN])
        {
            m_gestures[P_GESTURE_TYPE_PAN]->touchDown(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_PINCH])
        {
            m_gestures[P_GESTURE_TYPE_PINCH]->touchDown(x, y, timestamp, pointer);
        }
    }
    else if (cursor->m_state == P_CURSOR_STATE_UP)
    {
        clamp(x, y);

        if (m_gesturesEnabled[P_GESTURE_TYPE_TAP])
        {
            m_gestures[P_GESTURE_TYPE_TAP]->touchUp(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_LONGPRESS])
        {
            m_gestures[P_GESTURE_TYPE_LONGPRESS]->touchUp(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_FLING])
        {
            m_gestures[P_GESTURE_TYPE_FLING]->touchUp(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_PAN])
        {
            m_gestures[P_GESTURE_TYPE_PAN]->touchUp(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_PINCH])
        {
            m_gestures[P_GESTURE_TYPE_PINCH]->touchUp(x, y, timestamp, pointer);
        }
    }
    else if (cursor->m_state == P_CURSOR_STATE_MOVE)
    {
        clamp(x, y);

        if (m_gesturesEnabled[P_GESTURE_TYPE_TAP])
        {
            m_gestures[P_GESTURE_TYPE_TAP]->touchMove(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_LONGPRESS])
        {
            m_gestures[P_GESTURE_TYPE_LONGPRESS]->touchMove(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_FLING])
        {
            m_gestures[P_GESTURE_TYPE_FLING]->touchMove(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_PAN])
        {
            m_gestures[P_GESTURE_TYPE_PAN]->touchMove(x, y, timestamp, pointer);
        }
        if (m_gesturesEnabled[P_GESTURE_TYPE_PINCH])
        {
            m_gestures[P_GESTURE_TYPE_PINCH]->touchMove(x, y, timestamp, pointer);
        }
    }
}
    
void PGestureManager::clamp(pint32 &refX, pint32 &refY)
{
    refX = pMax(refX, (pint32)m_context->rect()[0]);
    refX = pMin(refX, (pint32)(m_context->rect()[0] + m_context->rect()[2] - 1));
    refY = pMax(refY, (pint32)m_context->rect()[1]);
    refY = pMin(refY, (pint32)(m_context->rect()[1] + m_context->rect()[3] - 1));
}

void PGestureManager::setGestureEnabled(PGestureTypeEnum type, pbool enabled)
{
    m_gesturesEnabled[type] = enabled;
}
