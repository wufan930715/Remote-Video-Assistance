//
//  ViewController.m
//  vh264enc
//
//  Created by YangXu on 2018/1/17.
//  Copyright © 2018年 OIT. All rights reserved.
//

#import "ViewController.h"
#import "vcodec/H264HwEncoderImpl.h"
#include "NetModule/localdef.h"
#import "LFScreenAVKit.h"
#import <WebKit/WKWebView.h>
#import <AVFoundation/AVFoundation.h>


#define ENC_VCX     320
#define ENC_VCY     480


#if 1
//#define IP_PORT    "222.186.58.233:40000"
#define IP_PORT    "222.186.58.112:40000"
#define PH_NUMBER  "15151987308"
#define GZ_NUM     "SZ_00002"

#else
//平安
//#define IP_PORT "eim-cobrowser-sdk-stg1.pingan.com.cn:52238"
#define IP_PORT    "103.28.215.253:52238"
#define PH_NUMBER  "17602110081"
#define GZ_NUM     "HlBoDqgAcv%2Bb2ITpo5Rjig%3D%3D"

#endif

//#define IP_PORT "192.168.1.104:52288"




BYTE gcbRgbData[ENC_VCX*ENC_VCY*4];


#define UIWeb 0
#define WKWeb 1

@interface ViewController ()<LFScreenAVKitCallBack>
{
    H264HwEncoderImpl       *mH264HwEncoderImpl;

    __weak IBOutlet UILabel *mLabel;
	NSDictionary *dict;
#if WKWeb
	WKWebView *mWebView;
#endif
#if UIWeb
	UIWebView *mWebView;
#endif
	id<LFScreenAVKit> mSCKitHnd;
	
    NSMutableArray *whiteList;
    
    
}

@end

@implementation ViewController

-(void)touchesBegan:(NSSet<UITouch *> *)touches withEvent:(UIEvent *)event
{
    [mSCKitHnd closeWhiteList];
    [[NSNotificationCenter defaultCenter] postNotificationName:@"PAEBankPageForwardNotification" object:@{@"pageUrl":@"5"}];
    //添加删除白名单
    NSArray *arr = @[@"/xinyidai/pages/limitFinal.html", @"1", @"2"];
    NSArray *array = @[@0, @1, @2];
    [mSCKitHnd addWhiteListWithArray:@[]];
    NSArray *arr1 = @[@"1", @"2", @"3"];
    [mSCKitHnd deleteWhiteListWithArray:arr1];
    
    // 播放音频
    
}



- (IBAction)stop:(id)sender {
	[mSCKitHnd StopSevice];
    mLabel.text = @"stoped record UIScreen";
}

- (IBAction)startSvice:(id)sender {
    
    int srcWidth          = [mSCKitHnd GetScreenWidth];
    int srcHeight         = [mSCKitHnd GetScreenHeight];
    
    char *phone = (char *)[_phoneNum UTF8String];
    char *work = (char *)[_workNum UTF8String];
    
    [mSCKitHnd StarSeviceWithJobNumCode:work AndSVMobile:phone AndRecodeWidth:320 AndRecodHeight:480 screenWidth:srcWidth screenHeight:srcHeight];
}

- (IBAction)getNewWindow:(id)sender {
	
	[mSCKitHnd ResetWindow];
}

- (IBAction)changeAudioSession:(id)sender {
    
    [mSCKitHnd changeAudioSession];
    
}
- (void)resignActive
{
    [mSCKitHnd pauseAudio];
}

- (void)becomeActive
{
    [mSCKitHnd reStartAudio];
}

-(void)SeviceStateChangeWithStatus:(SeviceStatus)lStauts
{
	if(lStauts < 2000 || lStauts == 2007 )
	{
        [mSCKitHnd StopSevice];
	}

	mLabel.text = [dict objectForKey:@(lStauts)];
    NSLog(@"%@",mLabel.text);
}

-(void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    [self.navigationController setNavigationBarHidden:YES];
}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    
    
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(resignActive) name:UIApplicationWillResignActiveNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(becomeActive) name:UIApplicationDidBecomeActiveNotification object:nil];
    
    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(resignActive) name:UIApplicationProtectedDataWillBecomeUnavailable object:nil];

    [[NSNotificationCenter defaultCenter]addObserver:self selector:@selector(becomeActive) name:UIApplicationProtectedDataDidBecomeAvailable object:nil];
    
    
	CGFloat mWidth = [UIScreen mainScreen].bounds.size.width;
	
	mWebView =
#if UIWeb
	[[UIWebView alloc]initWithFrame:CGRectMake(10, 80,mWidth-20, 480)];
#endif
#if WKWeb
	[[WKWebView alloc]initWithFrame:CGRectMake(10, 80,mWidth-20, 480)];
#endif
    
    if (@available(iOS 12.0, *)){
        NSString *baseAgent = @"Mozilla/5.0 (iPhone; CPU iPhone OS 11_4 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Mobile/15F79";
    NSString *userAgent = [NSString stringWithFormat:@"%@ YCL",baseAgent];
    [mWebView setCustomUserAgent:userAgent];
   }
    
	[self.view addSubview:mWebView];

	[mWebView loadRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:@"https://www.baidu.com"]]];
	dict =
		@{
	  	@1002:							@"创建SVS_STATUS媒体服务实例失败",
		@1003:							@"没不创建SVS_STATUS媒体服务实例",
		@1004:							@"启动定时器失败",
		@1005:							@"启动屏屏通通知线程失败",
		@1006:							@"启动音频组件失败",
		@1007:							@"启动视频编码线程失败",
		@1008:							@"网络连接线程失败",
        @1009:							@"获取vss服务器ip:port失败",
		@1010:							@"视频服务器地址无效",
		@1011:							@"连接到负载服务器失败",
		@1012:							@"连接到视频服务器失败",
		@1013:							@"登录到视频服务器失败",
        @1014:                          @"获取ServiceCode失败",
        @1022:                         @"通知中pageUrl不在白名单中关闭远程辅助",
		@2001:							@"开始连接到lbs",
		@2002:							@"开始连接到vss",
		@2003:							@"开始请求VSS IP:PORT",
		@2004:							@"请求VSS IP:PORT成功",
		@2005:							@"开始登录到VSS服务器",
		@2006:							@"登录到VSS服务器成功",
		@2007:							@"客服端停止辅助服务"
		};

    LPCTSTR lpszLbsList	=	(char *)[_lbsNum UTF8String];
    
	mSCKitHnd = [LFAVKit CreateLFLiveScreenKit:(RegisterTypeVideo|RegisterTypeAudio)];
    [mSCKitHnd InitAVKitWith:(char*)lpszLbsList AndCallBack:self];
    
	[mSCKitHnd SetHasMkWebView:YES];
    [mSCKitHnd SetBusinessType:10 extVal:""];
	
    NSLog(@"-------%d", g_GlobalData.nBusinessType);
    
    int srcWidth          = [mSCKitHnd GetScreenWidth];
    int srcHeight         = [mSCKitHnd GetScreenHeight];
    
    char *phone = (char *)[_phoneNum UTF8String];
    char *work = (char *)[_workNum UTF8String];
    
    [mSCKitHnd StarSeviceWithJobNumCode:work AndSVMobile:phone AndRecodeWidth:320 AndRecodHeight:480 screenWidth:srcWidth screenHeight:srcHeight];

    
}


- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void) buildRgbData
{
    BYTE *pData=gcbRgbData;
    int nPreRowSize=ENC_VCX*4;
    
    for(int y=0;y<ENC_VCY;y++)
    {
        int nColor=ARGB32(y,y,y,255);
        memset(pData,nColor,nPreRowSize);
        pData+=nPreRowSize;
    }
    
}

@end
