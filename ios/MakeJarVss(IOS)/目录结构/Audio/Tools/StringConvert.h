//
//  StringConvert.h
//  REducation
//
//  Created by changxm on 14-3-22.
//  Copyright (c) 2014年 changxm. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef unsigned long long UNDWORD;
typedef unsigned short WORD;
#define BYTE Byte


@interface StringConvert : NSObject

// 日期转为格式化字符串
+ (NSString* ) dateToLocalString:(NSDate* )nDate;

// 时间戳转为字符串
+ (NSString* ) dateTimeToLocalString:(UNDWORD) udwTime;

// utf8转为字符串
+ (NSString*) convertUTF8toString:(BYTE* )pStrUTF8 strSize:(WORD)pLen;

// gbk转为字符串
+ (NSString* ) convertGBKtoString:(BYTE* )pStrGBK strSize:(WORD)pLen;

// 字符串转为gbk
+ (const char* ) convertStringtoGBK:(NSString* )str;

// NSdate转换为string
+ (NSString* ) stringFromDate:(NSDate* )date;
+ (NSString* ) stringFromDate:(NSDate* )date withMode:(NSString* )mode;

+ (NSString* ) stringFromInterval:(long long)sec;
+ (NSString* ) stringFromInterval:(long long)sec withMode:(NSString* )mode;

// 得到生日格式的字符串
+ (NSString* ) brithStringFromInterval:(long long)sec;

// 字符串md5转为char
+ (unsigned char* ) MD5Chars:(NSString* )str;

// 字符串转为md5串
+ (NSString* ) MD5String:(NSString* )str;

// 将urlString分割开
+ (void) separateURLString:(NSString *)urlString ToPreString:(NSString **)preString pathString:(NSString **)pathString;

// 获取扩展名
+ (NSString* ) extendName:(NSString* )path;

// 获取距离现在的时长表达字符串
+ (NSString*) timeSpaceFromeNow:(long long) sec;

@end
