#ifndef VoxarAnalytics_h
#define VoxarAnalytics_h

//
//  VoxarAnalytics.h
//  VoxarAnalytics
//
//  Created by Matheus Coelho Berger on 22/12/16.
//  Copyright © 2016 Voxar. All rights reserved.
//

#ifdef __APPLE__

#import <UIKit/UIKit.h>

//! Project version number for VoxarAnalytics.
FOUNDATION_EXPORT double VoxarAnalyticsVersionNumber;

//! Project version string for VoxarAnalytics.
FOUNDATION_EXPORT const unsigned char VoxarAnalyticsVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <VoxarAnalytics/PublicHeader.h>

#include <VoxarAnalytics/Analytics.h>
#include <VoxarAnalytics/Features.h>

#else
#include "Analytics.h"
#include "Features.h"
#endif

#endif