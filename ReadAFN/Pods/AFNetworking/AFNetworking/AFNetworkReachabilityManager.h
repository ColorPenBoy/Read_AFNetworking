// AFNetworkReachabilityManager.h
// Copyright (c) 2011–2016 Alamofire Software Foundation ( http://alamofire.org/ )
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#import <Foundation/Foundation.h>

#if !TARGET_OS_WATCH
#import <SystemConfiguration/SystemConfiguration.h>
/**
 *  网络类型
 */
typedef NS_ENUM(NSInteger, AFNetworkReachabilityStatus) {
    /** 未知 */
    AFNetworkReachabilityStatusUnknown          = -1,
    /** 无网络 */
    AFNetworkReachabilityStatusNotReachable     = 0,
    /** WWAN -> Wireless Wide Area Network，无线广域网，手机自带网络，蜂窝网（2G、3G、4G）*/
    AFNetworkReachabilityStatusReachableViaWWAN = 1,
    /** WiFi */
    AFNetworkReachabilityStatusReachableViaWiFi = 2,
};

NS_ASSUME_NONNULL_BEGIN


@interface AFNetworkReachabilityManager : NSObject

/** 当前网络状态 */
@property (readonly, nonatomic, assign) AFNetworkReachabilityStatus networkReachabilityStatus;

/** 当前是否可以获得网络 */
@property (readonly, nonatomic, assign, getter = isReachable) BOOL reachable;

/** 当前连接是否为WWAN */
@property (readonly, nonatomic, assign, getter = isReachableViaWWAN) BOOL reachableViaWWAN;

/** 当前连接是否是WiFi */
@property (readonly, nonatomic, assign, getter = isReachableViaWiFi) BOOL reachableViaWiFi;


/** 初始化方法 - 5种 */
+ (instancetype)sharedManager;
+ (instancetype)manager;
// 监听指定domain的网络状态
+ (instancetype)managerForDomain:(NSString *)domain;
// 监听某个socket地址的网络状态
+ (instancetype)managerForAddress:(const void *)address;
- (instancetype)initWithReachability:(SCNetworkReachabilityRef)reachability NS_DESIGNATED_INITIALIZER;

/** 开始、停止监控 */
- (void)startMonitoring;
- (void)stopMonitoring;

/** 返回一个网络状态的本地语言的字符串 */
- (NSString *)localizedNetworkReachabilityStatusString;

/** 网络转态改变的回调 */
- (void)setReachabilityStatusChangeBlock:(nullable void (^)(AFNetworkReachabilityStatus status))block;

@end

/**
 当网络可到达行改变时，发送通知。
 
 This notification assigns no notification object. The `userInfo` dictionary contains an `NSNumber` object under the `AFNetworkingReachabilityNotificationStatusItem` key, representing the `AFNetworkReachabilityStatus` value for the current network reachability.

 @warning In order for network reachability to be monitored, include the `SystemConfiguration` framework in the active target's "Link Binary With Library" build phase, and add `#import <SystemConfiguration/SystemConfiguration.h>` to the header prefix of the project (`Prefix.pch`).
 */
FOUNDATION_EXPORT NSString * const AFNetworkingReachabilityDidChangeNotification;
FOUNDATION_EXPORT NSString * const AFNetworkingReachabilityNotificationStatusItem;

/** 
 *  @description 根据状态获取字符串 -> 一个C语言格式的函数
 *  @param status 状态参数
 */
FOUNDATION_EXPORT NSString * AFStringFromNetworkReachabilityStatus(AFNetworkReachabilityStatus status);

NS_ASSUME_NONNULL_END
#endif






