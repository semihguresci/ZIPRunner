#pragma once


const FString SdkKey = "";

namespace AdUnitIdentifier
{
#if PLATFORM_IOS
    const FString Banner = "";
    const FString MRec = "";
    const FString Interstitial = "";

    const FString Rewarded = "";
    const FString Rewardedtwo = "";
    const FString Rewardedthree = "";
    const FString Rewardedfour = "";
#elif PLATFORM_ANDROID
    const FString Banner = "";
    const FString MRec = "";
    const FString Interstitial = "";
    const FString Interstitialtwo = "";

    const FString Rewarded = "";
    const FString Rewardedtwo = "";
    const FString Rewardedthree = "";
    const FString Rewardedfour = "";
#else // Empty values for compiling in editor or other platforms
    const FString Banner = "";
    const FString MRec = "";
    const FString Interstitial = "";


    const FString Rewarded = " ";
    const FString Rewardedtwo = " ";
    const FString Rewardedthree = " ";
    const FString Rewardedfour = " ";

#endif
}
