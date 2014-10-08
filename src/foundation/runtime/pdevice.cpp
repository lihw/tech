// pdevice.cpp
// Each PContext has one window instance which collect the current display
// screen's status and manges the input events.
//
// Copyright 2012 - 2014 Future Interface. 
// This software is licensed under the terms of the MIT license.
//
// Hongwei Li lihw81@gmail.com

#include "pdevice.h"

#include <PFoundation/PContext.h>
#include <PFoundation/pevent.h>
#include <PFoundation/peventtype.h>
#include <PFoundation/pgesturemanager.h>

#include <PFoundation/plog.h>
#include <PFoundation/passert.h>
#include <PFoundation/pnew.h>


PDevice::PDevice(PContext* context)
    : m_context(context)
{
    m_state = P_DEVICE_STATE_UNINITIALIZED;
    m_inputEventQueue = P_NULL;

    for (puint32 i = 0; i < P_KEY_COUNT; ++i)
    {
        m_keyStates[i] = P_KEY_DEVICE_STATE_UP;
    }
    
    m_state = P_DEVICE_STATE_ACTIVE;

    m_orientation = P_DEVICE_ORIENTATION_LANDSCAPE;
    m_orientationAngle = P_DEVICE_ORIENTATION_ANGLE_0;

    m_screenWidth = 0;
    m_screenHeight = 0;
    
    m_inputEventQueue = PNEW(PInputEventQueue(this));
}

PDevice::~PDevice()
{
    PDELETE(m_inputEventQueue);
}

void PDevice::update()
{
    // Handle the queued events.
    if (m_context->state() == P_CONTEXT_STATE_RUNNING ||
        m_context->state() == P_CONTEXT_STATE_PAUSED)
    {
        puint32 events = m_inputEventQueue->getNumberOfEvents();
        for (puint32 i = 0; i < events; ++i)
        {
            PInputEvent* event = m_inputEventQueue->getEventAtIndex(i);
            switch (event->getType())
            {
            case P_INPUT_EVENT_KEY:
                {
                    // Get the native event 
                    PInputEventKey* keyEvent = event->getKeyEvent();
                    m_context->onKeyboard(keyEvent->getState(), keyEvent->getNativeScanCode(), keyEvent->getKey());
                }
                break;
            case P_INPUT_EVENT_TOUCH:
                {
                    PInputEventTouch* touchEvent = event->getTouchEvent();
                    puint32 cursorCount = touchEvent->getCursorCount();
                    
                    for (puint32 i = 0; i < cursorCount; i++)
                    {
                        // Translate the input type to touch event type.
                        PInputEventTouch::TouchCursor *cursor = touchEvent->getCursor(i);

                        // TODO: use function pointer array instead of switch().
                        switch (cursor->m_state)
                        {
                            case P_CURSOR_STATE_DOWN:      
                                m_context->onTouchDown((pint32)cursor->m_id,
                                                       (pint32)cursor->m_x,
                                                       (pint32)cursor->m_y);
                                break;
                            case P_CURSOR_STATE_STATIONARY:
                                break;
                            case P_CURSOR_STATE_MOVE:
                                m_context->onTouchMove((pint32)cursor->m_id,
                                                       (pint32)cursor->m_x,
                                                       (pint32)cursor->m_y);
                                break;
                            case P_CURSOR_STATE_UP:
                                m_context->onTouchUp((pint32)cursor->m_id,
                                                     (pint32)cursor->m_x,
                                                     (pint32)cursor->m_y);
                                break;
                        }

                        // Gesture
                        m_context->gestureManager()->recognize(cursor);
                    }
                }
                break;
            default:
                    PLOG_WARNING("Unknown input event type.");
                    break;
            }
        }
    }

    m_inputEventQueue->clear();
}

void PDevice::setState(PDeviceStateEnum state)
{
    m_state = state;
}

pbool PDevice::onClose()
{
    if (m_context != P_NULL)
    {
        return m_context->onClose();
    }

    return true;
}

void PDevice::onFocusGained()
{
}

void PDevice::onFocusLost()
{
}

void PDevice::onResized(puint32 width, puint32 height)
{
    if (m_screenWidth != width || m_screenHeight != height)
    {
        PLOG_INFO("screen size is changed to %d x %d", width, height);
        m_screenWidth = width;
        m_screenHeight = height;

        // Provoke the callback
        m_context->onScreenResized(width, height);
    }

}

void PDevice::onOrientationChanged(PDeviceOrientationEnum orientation)
{
    PLOG_INFO("orientation is changed to %s", orientation == P_DEVICE_ORIENTATION_LANDSCAPE? 
        "landscape" : "portrait");

    m_orientation = orientation;
}

void PDevice::onOrientationAngleChanged(PDeviceOrientationAngleEnum angle)
{
    PLOG_INFO("orientation angle is changed to %s", angle == P_DEVICE_ORIENTATION_ANGLE_0? 
        "0" : "180");
}

void PDevice::setKeyState(PInputKey key, PInputKeyDeviceStateEnum state)
{
    PASSERTINFO(key < P_KEY_COUNT, "out of key range");
    if (key < P_KEY_COUNT)
    {
        m_keyStates[key] = state;
    }
}

