// pios32glviewcontroller.h
// The OpenGL view controller.
//
// Copyright 2012 - 2014 Future Interface. 
// This software is licensed under the terms of the MIT license.
//
// Hongwei Li lihw81@gmail.com
//

#ifndef PIOSGLVIEWCONTROLLER_H
#define PIOSGLVIEWCONTROLLER_H

#import <UIKit/UIKit.h>


class PContext;

@interface PIOSGLViewController : UIViewController {
    PContext *_pcontext;
    CGRect    _frame;
}

- (id)initWithFrame:(CGRect)frame TechContext:(PContext *)pcontext;

@end

#endif // !PIOSGLVIEWCONTROLLER_H
