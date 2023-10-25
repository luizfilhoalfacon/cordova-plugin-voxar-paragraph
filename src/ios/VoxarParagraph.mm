#import "VoxarParagraph.h"
#import "ImageUtils.h"
#import <opencv2/features2d/features2d.hpp>
#import <opencv2/imgcodecs/ios.h>

#import "voxarparagraph/paragraph/paragraph.h"

#define HASH_SIZE 128000000ul

using namespace cv;

@interface VoxarParagraph()
{
    NSString *callbackID;
    PARagraph *paragraph;
}

@end

@implementation VoxarParagraph

- (void)init:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        
        char *uuid = (char*)[[[[UIDevice currentDevice] identifierForVendor] UUIDString] UTF8String];
        
        NSString *tempFilePath = [NSTemporaryDirectory() stringByAppendingPathComponent:[NSString stringWithUTF8String:"temp"]];
        char *rawTempFilePath = (char*)[tempFilePath UTF8String];
        
        NSString *filePath = [NSTemporaryDirectory() stringByAppendingPathComponent:[NSString stringWithUTF8String:"pages-"]];
        const char *rawFilePath = [filePath UTF8String];
        std::string userAgent = "ios";
        
        if(!paragraph) {
            paragraph = new PARagraph(HASH_SIZE, 1, uuid, rawTempFilePath, "ios", rawFilePath, 7, 6, PARagraph::Invariant::TRIANGLE_AREAS_RATIO);
        }
        
        CDVPluginResult* plugin_result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK];
        [self.commandDelegate sendPluginResult:plugin_result callbackId:command.callbackId];
    }];
}

- (void)open:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* plugin_result = nil;
        NSString* database = [command.arguments objectAtIndex:0];
        
        //NSLog(@"entrou no open!");
        
        if (database != nil && [database length] > 0) {
            if(!paragraph) {
                
                char *uuid = (char*)[[[[UIDevice currentDevice] identifierForVendor] UUIDString] UTF8String];
                
                NSString *tempFilePath = [NSTemporaryDirectory() stringByAppendingPathComponent:[NSString stringWithUTF8String:"temp"]];
                char *rawTempFilePath = (char*)[tempFilePath UTF8String];
                
                NSString *filePath = [NSTemporaryDirectory() stringByAppendingPathComponent:[NSString stringWithUTF8String:"pages-"]];
                const char *rawFilePath = [filePath UTF8String];
                
                paragraph = new PARagraph(HASH_SIZE, 1, uuid, rawTempFilePath, "ios", rawFilePath, 7, 6, PARagraph::Invariant::TRIANGLE_AREAS_RATIO);
            }
            
            //NSString *path = [[NSBundle mainBundle] pathForResource:@"pagina3" ofType:@"par"];
            //NSURL *url = [NSURL fileURLWithPath:path];
            //const char *cfilename=[[url path] UTF8String];
            
            //printf("%s\n", cfilename);
            
            
            
            const char *cdatabase= [database UTF8String];
            //paragraph->deserialize(cdatabase);
            if(paragraph->deserialize(cdatabase)) {
                //if(paragraph->deserialize(cfilename)) {
                plugin_result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:1];
            } else {
                plugin_result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsInt:0];
            }
        } else {
            plugin_result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR messageAsInt:0];
        }
        
        [self.commandDelegate sendPluginResult:plugin_result callbackId:command.callbackId];
    }];
}
- (void)retrieveFromPath:(CDVInvokedUrlCommand*)command
{
    [self.commandDelegate runInBackground:^{
        CDVPluginResult* plugin_result = nil;
        NSString* imagePath = [command.arguments objectAtIndex:0];
        
        if (imagePath != nil && [imagePath length] > 0) {
            document_id_type retrieved_id = -1;
            cv::Mat homography, gray;
            
            UIImage* resImage = [UIImage imageWithContentsOfFile:imagePath];
            UIImageToMat(resImage, gray);
            
            cvtColor(gray, gray, CV_BGRA2GRAY);
            
            if(paragraph->retrieve_document(gray, retrieved_id, homography, 0.6)) {
                plugin_result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:retrieved_id];
            } else {
                plugin_result = [CDVPluginResult resultWithStatus:CDVCommandStatus_OK messageAsInt:-1];
            }
            
        } else {
            plugin_result = [CDVPluginResult resultWithStatus:CDVCommandStatus_ERROR];
        }
        
        [self.commandDelegate sendPluginResult:plugin_result callbackId:command.callbackId];
    }];
}

@end
