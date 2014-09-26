// pios32glviewcontroller.cmm
// The OpenGL view controller.
//
// Copyright 2012 - 2014 Future Interface. 
// This software is licensed under the terms of the MIT license.
//
// Hongwei Li lihw81@gmail.com
//

#import "piosglviewcontroller.h"

#import "piosglview.h"

#include <PFoundation/pglobal.h>

@implementation PIOSGLViewController

- (id)initWithFrame:(CGRect)frame TechContext:(PContext *)pcontext {
    
    self = [super init];
    if (self)
    {
        _pcontext = pcontext;
        _frame = frame;
    }
    
    return self;
}

- (void)viewDidAppear:(BOOL)animated {
    
    UIInterfaceOrientation orientation = [UIApplication sharedApplication].statusBarOrientation;
    if (orientation == UIInterfaceOrientationLandscapeRight)
    {
        pSwap(_frame.size.width, _frame.size.height);
    }
    
    self.view = [[PIOSGLView alloc] initWithFrame:_frame TechContext:_pcontext];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    return NO;
}

- (void)didRotateFromInterfaceOrientation:(UIInterfaceOrientation)fromInterfaceOrientation {
}

@end
