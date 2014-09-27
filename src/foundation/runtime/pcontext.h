// pcontext.h
//
// Copyright 2012 - 2014 Future Interface. 
// This software is licensed under the terms of the MIT license.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PCONTEXT_H
#define PCONTEXT_H

#include <PFoundation/pcontextproperties.h>
#include <PFoundation/pclock.h>
#include <PFoundation/pstring.h>
#include <PFoundation/parray.h>
#include <PFoundation/pmodule.h>

class PDevice;
class PEvent;
class PGestureManager;
class PTimerManager;
class PEventManager;

enum PContextState
{
    P_CONTEXT_STATE_UNINITIALIZED, ///< Context is not initialized.
    P_CONTEXT_STATE_RUNNING,        ///< Context is running.
    P_CONTEXT_STATE_PAUSED,        ///< Context is paused. Freezed in the main loop.
    P_CONTEXT_STATE_QUITING,       ///< Context is about to quit.
    P_CONTEXT_STATE_ERROR,         ///< Some fatal errors in the context.

    P_CONTEXT_STATE_FIRST = P_CONTEXT_STATE_UNINITIALIZED,
    P_CONTEXT_STATE_LAST = P_CONTEXT_STATE_ERROR,
    P_CONTEXT_STATE_NUMBER = P_CONTEXT_STATE_LAST - P_CONTEXT_STATE_FIRST + 1,
};

class P_DLLEXPORT PContext
{
public:
    PContext(const PContextProperties &properties); 
    virtual ~PContext();

    pbool initialize(puint32 screenWidth, puint32 screenHeight);
    pbool update();
    void destroy();
    void quit();
    void pause();
    pbool resume();
    void dispatch(PEvent *event);
    void setState(PContextState state);
    void addModule(PModule *module); 

    template<typename T> 
    T *module(const pchar *name) const
    {
        for (puint32 i = 0; i < m_modules.size(); ++i)
        {
            if (m_modules[i]->name() == name)
            {
                return dynamic_cast<T*>(m_modules[i]);
            }
        }

        PASSERT_NOTREACHABLE("Failed to find the specified module.");
        PLOG_WARNING("No such module called %s in context.");
        return P_NULL;
    }
    
    virtual pbool onClose();
    virtual void onPause();
    virtual void onResume();
    virtual void onScreenResized(puint32 width, puint32 height);
    virtual pbool onInitialized();
    virtual void onDestroy();
    
    virtual void onPanBegin(pint32 x, pint32 y) {}
    virtual void onPan(pint32 x, pint32 y, pint32 dx, pint32 dy) {}
    virtual void onPanEnd(pint32 x, pint32 y, pint32 dx, pint32 dy) {}
    virtual void onPinchBegin(const pint32 *pt1, const pint32 *pt2) {}
    virtual void onPinch(const pint32 *pt1, const pint32 *pt2, pfloat32 angle, pfloat32 scaling) {}
    virtual void onPinchEnd() {}
    virtual void onLongPress(pint32 x, pint32 y) {}
    virtual void onTap(pint32 x, pint32 y, puint32 count) {}
    virtual void onFling(pfloat32 x, pfloat32 y) {}

    P_INLINE const PString       &name() const { return m_properties.m_contextName; }
    const puint32                *rect() const { return m_rect; }
    P_INLINE PContextState       state() const { return m_state; }
    P_INLINE PDevice             *device() const { return m_device; }
    P_INLINE PContextProperties  *properties() { return &m_properties; }
    P_INLINE PClock              &clock() { return m_clock; }
    P_INLINE PGestureManager *gestureManager() const { return m_gestureManager; }
    P_INLINE PTimerManager   *timerManager() const { return m_timerManager; }
    P_INLINE PEventManager   *eventManager() const { return m_eventManager; }

protected:
    virtual pbool onUpdate();

    virtual pbool onKeyboard(PEvent *event);
    virtual pbool onTouch(PEvent *event);
    virtual pbool onUserEvent(PEvent *event);
    virtual pbool onTimer(PEvent *event);


private:
    void updateRect(puint32 screenWidth, puint32 screenHeight);

private:
    PContextProperties      m_properties;
    PContextState           m_state;
    PDevice                *m_device;
    PClock                  m_clock;
    puint32                 m_rect[4];  // The drawable area.
    PArray<PModule *>       m_modules;
    PGestureManager        *m_gestureManager;
    PTimerManager          *m_timerManager;
    PEventManager          *m_eventManager;

};

#endif // !PCONTEXT_H
