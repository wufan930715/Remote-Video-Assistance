//
//  AppShare.m
//  RealTimeTransport
//
//  Created by tan on 13-5-20.
//  Copyright (c) 2013年 常 贤明. All rights reserved.
//

#include <sys/socket.h>
#include <sys/sysctl.h>
#include <net/if.h>
#include <net/if_dl.h>

#import "AppShare.h"
#import "NSStringAdditions.h"


#define CACHE_FOLDER        @"Caches"
#define IMAGE_CACHE_FOLDER  @"ImageCache"
#define AUDIO_CACHE_FOLDER  @"AudioCache"

#define MY_PIC_FOLDER    @"MyPicture"
#define MY_AUDIO_FOLDER  @"MyAudio"
#define MY_VIDEO_FOLDER  @"MyVideo"

#define LOCAL_AUDIO_FOLDER  @"RecordAudioCahe"

#define DADABASE_FOLDER     @"DataBase"
#define DADABASE_NAME       @"UNS_NetWork_Telephone.sqlite3"

@implementation AppShare

+ (NSString *)documentsFolderPath
{
    return  [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
}

+ (NSString *)cacheFolderPath
{
    NSString *path=[[self documentsFolderPath] stringByAppendingPathComponent:CACHE_FOLDER];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:path]) {
        [fileManager createDirectoryAtPath:path withIntermediateDirectories:YES attributes:nil error:nil];
    }
    return  path;
}

+ (NSString *)imageCacheFolderPath
{
    NSString *imageCacheFolder = [[AppShare cacheFolderPath] stringByAppendingPathComponent:IMAGE_CACHE_FOLDER];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:imageCacheFolder]) {
        [fileManager createDirectoryAtPath:imageCacheFolder withIntermediateDirectories:YES attributes:nil error:nil];
    }
    return  imageCacheFolder;
}

+ (NSString *)imageCachePathWithName:(NSString *)imageURL
{
    NSString *md5Str = [imageURL stringFromMD5];
    NSString *imageCacheFolder = [AppShare imageCacheFolderPath];
    NSString *imageCachePath = [imageCacheFolder stringByAppendingPathComponent:md5Str];
    return imageCachePath;
}

+ (void)saveImageToCache:(NSDictionary *)imageInfo
{
    NSString *imageCachePath = [AppShare imageCachePathWithName:[imageInfo objectForKey:IMAGE_NAME]];
    
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:imageCachePath]) {
        [fileManager removeItemAtPath:imageCachePath error:NULL];
    }
    
    [fileManager createFileAtPath:imageCachePath contents:[imageInfo objectForKey:IMAGE_DATA] attributes:nil];
    
    id dataValue=[imageInfo objectForKey:ETAG];
    if (![dataValue isMemberOfClass:[NSNull class]]) {
        [self addExtendedAttributeWithPath:imageCachePath key:ETAG value:[dataValue dataUsingEncoding:NSUTF8StringEncoding]];
    }
    
    dataValue=[imageInfo objectForKey:LAST_MODIFIED];
    if (![dataValue isMemberOfClass:[NSNull class]]) {
        [self addExtendedAttributeWithPath:imageCachePath key:LAST_MODIFIED value:[dataValue dataUsingEncoding:NSUTF8StringEncoding]];
    }
}

+ (UIImage *)cacheImage:(NSString *)imageURL
{
    NSString *imageCachePath = [AppShare imageCachePathWithName:imageURL];
    
    NSFileManager *manager = [NSFileManager defaultManager];
    if ([manager fileExistsAtPath:imageCachePath]) {
        return [UIImage imageWithData:[NSData dataWithContentsOfFile:imageCachePath]];
    }
    return nil;
}

+ (NSMutableArray *)refreshedImageArray
{
    static NSMutableArray *refreshedImageArray;
    static dispatch_once_t flag;
    
	dispatch_once(&flag, ^{
		refreshedImageArray = [NSMutableArray new];
	});
	
	return refreshedImageArray;
}

+ (NSString *)audioCacheFolderPath
{
    NSString *audioCacheFolder = [[AppShare cacheFolderPath] stringByAppendingPathComponent:AUDIO_CACHE_FOLDER];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:audioCacheFolder]) {
        [fileManager createDirectoryAtPath:audioCacheFolder withIntermediateDirectories:YES attributes:nil error:nil];
    }
    return  audioCacheFolder;
}

+ (NSString *)audioCacheFolderPathForCustomer:(NSString *)fileName userId:(NSString *)uId
{
    //第一层
    NSString *audioCacheFolder1 = [[AppShare cacheFolderPath] stringByAppendingPathComponent:AUDIO_CACHE_FOLDER];
    NSFileManager *fileManager1 = [NSFileManager defaultManager];
    if (![fileManager1 fileExistsAtPath:audioCacheFolder1]) {
        [fileManager1 createDirectoryAtPath:audioCacheFolder1 withIntermediateDirectories:YES attributes:nil error:nil];
    }
    //第二层
    NSString *audioCacheFolder2 = [audioCacheFolder1 stringByAppendingPathComponent:fileName];
    NSFileManager *fileManager2 = [NSFileManager defaultManager];
    if (![fileManager2 fileExistsAtPath:audioCacheFolder2]) {
        [fileManager2 createDirectoryAtPath:audioCacheFolder2 withIntermediateDirectories:YES attributes:nil error:nil];
    }
    //第三层
    NSString *audioCacheFolder3 = [audioCacheFolder2 stringByAppendingPathComponent:uId];
    NSFileManager *fileManager3 = [NSFileManager defaultManager];
    if (![fileManager3 fileExistsAtPath:audioCacheFolder3]) {
        [fileManager3 createDirectoryAtPath:audioCacheFolder3 withIntermediateDirectories:YES attributes:nil error:nil];
    }
    return  audioCacheFolder3;
}

+ (NSString* )recordLocalAudioFolderPath
{
    NSString *recordFolder = [[AppShare cacheFolderPath] stringByAppendingPathComponent:LOCAL_AUDIO_FOLDER];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:recordFolder]) {
        [fileManager createDirectoryAtPath:recordFolder withIntermediateDirectories:YES attributes:nil error:nil];
    }
    return  recordFolder;
}

+ (NSString* )myPicCacheFilePath:(NSString* )pic
{
    NSString *documentsDirec = [[AppShare cacheFolderPath] stringByAppendingPathComponent:MY_PIC_FOLDER];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:documentsDirec]) {
        [fileManager createDirectoryAtPath:documentsDirec withIntermediateDirectories:YES attributes:nil error:nil];
    }

    documentsDirec = [documentsDirec stringByAppendingFormat:@"/%@",pic];
    return documentsDirec;
}

+ (NSString* )myAudioCacheFilePath:(NSString* )audioURL
{
    NSString *documentsDirec = [[AppShare cacheFolderPath] stringByAppendingPathComponent:MY_AUDIO_FOLDER];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:documentsDirec]) {
        [fileManager createDirectoryAtPath:documentsDirec withIntermediateDirectories:YES attributes:nil error:nil];
    }
    
    NSArray* arr = [audioURL componentsSeparatedByString:@"/"];
    NSString* lastName = nil;
    if([arr count] > 0)
    {
        lastName = [arr lastObject];
    }
    
    documentsDirec = [documentsDirec stringByAppendingFormat:@"/%@",lastName];
    return documentsDirec;
}

+ (NSString* )myVideoCacheFilePath:(NSString* )videoURL
{
    NSString *documentsDirec = [[AppShare cacheFolderPath] stringByAppendingPathComponent:MY_VIDEO_FOLDER];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:documentsDirec]) {
        [fileManager createDirectoryAtPath:documentsDirec withIntermediateDirectories:YES attributes:nil error:nil];
    }
    
    NSArray* arr = [videoURL componentsSeparatedByString:@"/"];
    NSString* lastName = nil;
    if([arr count] > 0)
    {
        lastName = [arr lastObject];
    }
    
    documentsDirec = [documentsDirec stringByAppendingFormat:@"/%@",lastName];
    return documentsDirec;
}

+ (BOOL)fileExist:(NSString* )fileName
{
    NSFileManager *fileManage = [NSFileManager defaultManager];
    //文件存在
    if ([fileManage fileExistsAtPath:fileName])
    {
        return YES;
    }else{
        return NO;
    }
    return NO;
}

+ (BOOL)fileExist:(NSString *)fileName andUserId:(NSString *)uId andDataName:(NSString *)dataName
{
    NSString *audioCache = [[AppShare cacheFolderPath] stringByAppendingString:[NSString stringWithFormat:@"/%@/%@/%@/%@",AUDIO_CACHE_FOLDER,fileName,uId,dataName]];
    
    NSFileManager *fileManage = [NSFileManager defaultManager];
    //文件存在
    if ([fileManage fileExistsAtPath:audioCache])
    {
        return YES;
    //文件不存在
    }else{
    
        return NO;
    }
    return NO;
}
+ (NSString *)createFileName:(NSString *)fileName andUserId:(NSString *)uId andDataName:(NSString *)dataName
{
    NSString *audioCache = [[AppShare cacheFolderPath] stringByAppendingString:[NSString stringWithFormat:@"/%@/%@/%@/%@",AUDIO_CACHE_FOLDER,fileName,uId,dataName]];
    
    return audioCache;
}


+ (NSString *)dataBasePath
{
    NSString *databaseFolder = [[AppShare documentsFolderPath] stringByAppendingPathComponent:DADABASE_FOLDER];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:databaseFolder]) {
        [fileManager createDirectoryAtPath:databaseFolder withIntermediateDirectories:YES attributes:nil error:nil];
    }
    
    NSString *databasePath = [databaseFolder stringByAppendingPathComponent:DADABASE_NAME];
    if (![fileManager fileExistsAtPath:databasePath]) {
        [self createDataBaseWithPath:databasePath];//todo use other method - sql
    }
    return databasePath;
}

+ (BOOL)createDataBaseWithPath:(NSString *)path
{
    NSArray *array=[DADABASE_NAME componentsSeparatedByString:@"."];
    return [[NSData dataWithContentsOfFile:[[NSBundle mainBundle] pathForResource:[array objectAtIndex:0] ofType:[array objectAtIndex:1]]] writeToFile:path atomically:YES];
}

+ (BOOL)addExtendedAttributeWithPath:(NSString *)path key:(NSString *)key value:(NSData *)value
{
    NSDictionary *extendedAttribute = [NSDictionary dictionaryWithObject:[NSDictionary dictionaryWithObject:value forKey:key]
                                                                  forKey:@"NSFileExtendedAttributes"];
    
    BOOL ret = [[NSFileManager defaultManager] setAttributes:extendedAttribute
                                                ofItemAtPath:path error:NULL];
    return ret;
}

+ (NSString *)readExtendedAttributeWithPath:(NSString *)path key:(NSString *)key
{
    NSDictionary *attributes = [[NSFileManager defaultManager] attributesOfItemAtPath:path error:NULL];
    if (!attributes) {
        return nil;
    }
    
    NSDictionary *extendedAttributes = [attributes objectForKey:@"NSFileExtendedAttributes"];
    if (!extendedAttributes) {
        return nil;
    }
    
    return [[NSString alloc] initWithData:[extendedAttributes objectForKey:key] encoding:NSUTF8StringEncoding] ;
}

+ (NSMutableDictionary *)readAllExtendedAttributesWithPath:(NSString *)path
{
    NSDictionary *attributes = [[NSFileManager defaultManager] attributesOfItemAtPath:path error:NULL];
    if (!attributes) {
        return nil;
    }
    
    NSDictionary *extendedAttributes = [attributes objectForKey:@"NSFileExtendedAttributes"];
    if (!extendedAttributes) {
        return nil;
    }
    
    NSMutableDictionary *dict=[NSMutableDictionary new] ;
    for (id key in extendedAttributes) {
        [dict setObject:[[NSString alloc] initWithData:[extendedAttributes objectForKey:key] encoding:NSUTF8StringEncoding]  forKey:key];
    }
    
    return dict;
}

+ (NSString *)macAddress
{
    int mib[6];
    size_t len;
    char *buf;
    unsigned char *ptr;
    struct if_msghdr *ifm;
    struct sockaddr_dl *sdl;
    
    mib[0] = CTL_NET;
    mib[1] = AF_ROUTE;
    mib[2] = 0;
    mib[3] = AF_LINK;
    mib[4] = NET_RT_IFLIST;
    
    if ((mib[5] = if_nametoindex("en0")) == 0) {
        printf("Error: if_nametoindex error/n");
        return NULL;
    }
    
    if (sysctl(mib, 6, NULL, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 1/n");
        return NULL;
    }
    
    if ((buf = malloc(len)) == NULL) {
        printf("Could not allocate memory. error!/n");
        return NULL;
    }
    
    if (sysctl(mib, 6, buf, &len, NULL, 0) < 0) {
        printf("Error: sysctl, take 2");
        return NULL;
    }
    
    ifm = (struct if_msghdr *)buf;
    sdl = (struct sockaddr_dl *)(ifm + 1);
    ptr = (unsigned char *)LLADDR(sdl);
    
    NSString *outstring = [NSString stringWithFormat:@"%02x:%02x:%02x:%02x:%02x:%02x", *ptr, *(ptr+1), *(ptr+2), *(ptr+3), *(ptr+4), *(ptr+5)];
    free(buf);
    return [outstring uppercaseString];
}

+ (BOOL)isJailBreak
{
    BOOL jailbroken = NO;
	NSString * cydiaPath = @"/Applications/Cydia.app";
	NSString * aptPath = @"/private/var/lib/apt/";
	if([[NSFileManager defaultManager]fileExistsAtPath:cydiaPath]){
		jailbroken = YES;
	}
	if([[NSFileManager defaultManager]fileExistsAtPath:aptPath]){
		jailbroken = YES;
	}
	return jailbroken;
}

+ (NSString *)currentAppVersion
{
	NSString *path=[[NSBundle mainBundle]pathForResource:@"Info" ofType:@"plist"];
	NSDictionary *dic=[NSDictionary dictionaryWithContentsOfFile:path];
	NSString *version=[dic objectForKey:@"CFBundleVersion"];
	return version;
}

+ (NSString *)transformString:(NSString *)string
{
    
    NSMutableString *result;
    if(string)
    {
        result = [NSMutableString stringWithString:string];
    }
    else
    {
        result = [[NSMutableString alloc] init];
    }
    
    //url
    NSString *regexStr = @"[a-zA-z]+://[^\\s\\u4e00-\\u9fa5]*";
    NSString *replace;
	NSRange range=[result rangeOfString:regexStr options:NSRegularExpressionSearch range:NSMakeRange(0, [result length])];
    while (range.length>0)
	{
        replace=[NSString stringWithFormat:@"<a>%@</a>",[result substringWithRange:range]];
        [result replaceCharactersInRange:range withString:replace];
        range=NSMakeRange(range.location+replace.length, [result length]-(range.location+replace.length));
		range=[result rangeOfString:regexStr options:NSRegularExpressionSearch range:range];
	}
    
    //phone num
    regexStr = @"\\d{3}-\\d{8}|\\d{4}-\\d{7}|1+[358]+\\d{9}|\\d{8}|\\d{7}";
	range=[result rangeOfString:regexStr options:NSRegularExpressionSearch range:NSMakeRange(0, [result length])];
    while (range.length>0)
	{
        replace=[NSString stringWithFormat:@"<a>%@</a>",[result substringWithRange:range]];
        [result replaceCharactersInRange:range withString:replace];
        range=NSMakeRange(range.location+replace.length, [result length]-(range.location+replace.length));
		range=[result rangeOfString:regexStr options:NSRegularExpressionSearch range:range];
	}
    
    //face
    regexStr = @"\\[[a-zA-Z0-9\\u4e00-\\u9fa5]+\\]";
    NSDictionary *faceDict = [[NSDictionary alloc] initWithContentsOfFile:[[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:@"faceMap2_ch.plist"]];
	range=[result rangeOfString:regexStr options:NSRegularExpressionSearch range:NSMakeRange(0, [result length])];
    while (range.length>0)
	{
        replace=[NSString stringWithFormat:@"<img src='%@' width='16' height='16' />",[faceDict objectForKey:[result substringWithRange:range]]];
        [result replaceCharactersInRange:range withString:replace];
        range=NSMakeRange(range.location+replace.length, [result length]-(range.location+replace.length));
		range=[result rangeOfString:regexStr options:NSRegularExpressionSearch range:range];
	}
	
    
    return result;
}

+ (UIView *)horizontalSolidLineWithRect:(CGRect)frame
{
    UIView *horizontalView=[[UIView alloc] initWithFrame:frame];
    [horizontalView setBackgroundColor:[UIColor colorWithPatternImage:[[UIImage imageNamed:@"separator.png"] imageScaledToScale:0.5]]];
    
    return horizontalView ;
}

+ (NSString*)dataFilePath:(NSString*)fileName
{
    NSArray* paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString* documentsDirec = [paths objectAtIndex:0];
    NSString* filePath = [documentsDirec stringByAppendingPathComponent:[NSString stringWithFormat:@"%@.png",fileName]];
    
    return filePath;
}

+ (NSString *)pathByWriteData:(NSData *)data toFileName:(NSString *)fileName
{
    NSString* filePath = [self dataFilePath:fileName];
    if([[NSFileManager defaultManager] fileExistsAtPath:filePath])
        [data writeToFile:filePath atomically:YES];
    else
    {
        if(![[NSFileManager defaultManager] createFileAtPath:filePath contents:nil attributes:nil])
        {
            NSLog(@"picture create file to store picture failed!\n");
        }
        else
        {
            [data writeToFile:filePath atomically:YES];
        }
    }
    return filePath;
}

// 图片临时缓存
+ (NSString* )tmpCacheFilePath:(NSString* )name withDirect:(NSString* )dir
{
    NSString* direct = [NSString stringWithFormat:@"%@",NSTemporaryDirectory()];
    NSString *path=[direct stringByAppendingPathComponent:dir];
    NSFileManager *fileManager = [NSFileManager defaultManager];
    if (![fileManager fileExistsAtPath:path]) {
        [fileManager createDirectoryAtPath:path withIntermediateDirectories:YES attributes:nil error:nil];
    }
    NSString* filePath = [NSString stringWithFormat:@"%@/%@",path,name];
    
    return filePath;
}


@end
