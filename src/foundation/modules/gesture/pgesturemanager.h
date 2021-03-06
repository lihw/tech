// pgesturemanager.h
// The gesture Manager header file.
//
// Copyright 2012 - 2014 Future Interface. 
// This software is licensed under the terms of the MIT license.
//
// Hongwei Li lihw81@gmail.com


#ifndef PGESTUREMANAGER_H
#define PGESTUREMANAGER_H

#include <PFoundation/pmodule.h>
#include <PFoundation/pinput.h>


class PAbstractGesture;

enum PGestureTypeEnum
{
    P_GESTURE_TYPE_TAP,
    P_GESTURE_TYPE_LONGPRESS,
    P_GESTURE_TYPE_PAN,
    P_GESTURE_TYPE_PINCH,
    P_GESTURE_TYPE_FLING,
    
    P_GESTURE_TYPE_FIRST = P_GESTURE_TYPE_TAP,
    P_GESTURE_TYPE_LAST = P_GESTURE_TYPE_FLING,
    P_GESTURE_TYPE_NUMBER = P_GESTURE_TYPE_LAST - P_GESTURE_TYPE_FIRST + 1,
};

class P_DLLEXPORT PGestureManager : public PModule
{
public:
    PGestureManager(PContext *context);
    virtual ~PGestureManager();
    
    virtual void update();
    virtual void uninitialize();
    virtual pbool resume();

    void recognize(PInputEventTouch::TouchCursor *cursor);

    void setGestureEnabled(PGestureTypeEnum type, pbool enabled);

    P_INLINE PAbstractGesture *gesture(PGestureTypeEnum type) const
    { return m_gestures[type]; }
    P_INLINE pbool isGestureEnabled(PGestureTypeEnum type) const
    { return m_gesturesEnabled[type]; }

private:
    // TODO: move this functionality to platform layer, so that every touch event is inside
    // application's window region.
    void clamp(pint32 &x, pint32 &y);

private:
    PAbstractGesture *m_gestures[P_GESTURE_TYPE_NUMBER];
    pbool             m_gesturesEnabled[P_GESTURE_TYPE_NUMBER];
};

#endif // PGESTUREMANAGER_H
