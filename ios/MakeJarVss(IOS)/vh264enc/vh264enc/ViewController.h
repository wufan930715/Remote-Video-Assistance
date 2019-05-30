//
//  ViewController.h
//  vh264enc
//
//  Created by YangXu on 2018/1/17.
//  Copyright © 2018年 OIT. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "vcodec/H264HwEncoderImpl.h"

@interface ViewController : UIViewController <H264HwEncoderImplDelegate>

@property (nonatomic, copy)NSString *phoneNum;
@property (nonatomic, copy)NSString *workNum;
@property (nonatomic, copy)NSString *lbsNum;

@end

