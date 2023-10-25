#import <UIKit/UIKit.h>

#import <Cordova/CDVPlugin.h>

#define __USEVOXARPARAGRAPH__

@interface VoxarParagraph : CDVPlugin
    {
    }
    
-(void)init:(CDVInvokedUrlCommand*)command;
    
-(void)open:(CDVInvokedUrlCommand*)command;
    
-(void)retrieveFromPath:(CDVInvokedUrlCommand*)command;
    
    @end
