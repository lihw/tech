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


class PAbstractGesture;
class PEvent;

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

class P_DLLEXPORT PAbstractGestureHandler
{
public:
    PAbstractGestureHandler(void *data, PGestureTypeEnum type);
    virtual ~PAbstractGestureHandler();

    P_INLINE PGestureTypeEnum type() const { return m_type; }

protected:
    void *m_data;
    PGestureTypeEnum m_type;
};

class P_DLLEXPORT PGesturePanHandler : public PAbstractGestureHandler
{
public:
    PGesturePanHandler(void *data) : PAbstractGestureHandler(data, P_GESTURE_TYPE_PAN) {}
    virtual ~PGesturePanHandler() {}

    virtual void onPanBegin(pint32 x, pint32 y) {}
    virtual void onPan(pint32 x, pint32 y, pint32 dx, pint32 dy) {}
    virtual void onPanEnd(pint32 x, pint32 y, pint32 dx, pint32 dy) {}
};

class P_DLLEXPORT PGesturePinchHandler : public PAbstractGestureHandler
{
public:
    PGesturePinchHandler(void *data) : PAbstractGestureHandler(data, P_GESTURE_TYPE_PINCH) {}
    virtual ~PGesturePinchHandler() {}

    virtual void onPinchBegin(const pint32 *pt1, const pint32 *pt2) {}
    virtual void onPinch(const pint32 *pt1, const pint32 *pt2, pfloat32 angle, pfloat32 scaling) {}
    virtual void onPinchEnd() {}
};

class P_DLLEXPORT PGestureFlingHandler : public PAbstractGestureHandler
{
public:
    PGestureFlingHandler(void *data) : PAbstractGestureHandler(data, P_GESTURE_TYPE_FLING) {}
    virtual ~PGestureFlingHandler() {}

    virtual void onFling(pfloat32 x, pfloat32 y) {}
};

class P_DLLEXPORT PGestureTapHandler : public PAbstractGestureHandler
{
public:
    PGestureTapHandler(void *data) : PAbstractGestureHandler(data, P_GESTURE_TYPE_TAP) {}
    virtual ~PGestureTapHandler() {}

    virtual void onTap(pint32 x, pint32 y, puint32 count) {}
};

class P_DLLEXPORT PGestureLongPressHandler : public PAbstractGestureHandler
{
public:
    PGestureLongPressHandler(void *data) : PAbstractGestureHandler(data, P_GESTURE_TYPE_LONGPRESS) {}
    virtual ~PGestureLongPressHandler() {}

    virtual void onLongPress(pint32 x, pint32 y) {}
};

class P_DLLEXPORT PGestureManager : public PModule
{
public:
    PGestureManager(PContext *context);
    virtual ~PGestureManager();
    
    virtual void update();
    virtual void uninitialize();
    virtual pbool resume();

    void recognize(PEvent *event);

    void addHandler(PAbstractGestureHandler *handler);

    P_INLINE PAbstractGestureHandler *handler(PGestureTypeEnum type) const
    { return m_handlers[type]; }
    P_INLINE PAbstractGesture *gesture(PGestureTypeEnum type) const
    { return m_gestures[type]; }

private:
    // TODO: move this functionality to platform layer, so that every touch event is inside
    // application's window region.
    void clamp(pint32 &x, pint32 &y);

private:
    PAbstractGesture *m_gestures[P_GESTURE_TYPE_NUMBER];
    PAbstractGestureHandler *m_handlers[P_GESTURE_TYPE_NUMBER];
};

#endif // PGESTUREMANAGER_H
