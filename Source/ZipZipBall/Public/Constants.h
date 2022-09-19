#pragma once


const FString SdkKey = "KD34DzE0nS6GQh_zN4lxNavmzReH-buPUp-O7IIQ-pB2H6Hxcyc_uvZuvifyb43TpM5mT2pEoe2ViM_q7OCUTt";

namespace AdUnitIdentifier
{
#if PLATFORM_IOS
    const FString Banner = "6713e8ff133daf34";
    const FString MRec = "IOS_MREC_AD_UNIT_ID";
    const FString Interstitial = "2d67363a6b504e7f";

    const FString Rewarded = "ae3496a85885b0ef";
    const FString Rewardedtwo = "50b77f359b557200";
    const FString Rewardedthree = "70dfe14aaf3af26e";
    const FString Rewardedfour = "419eba03a3a63fa6";
#elif PLATFORM_ANDROID
    const FString Banner = "c009171d0545bff7";
    const FString MRec = "ANDROID_MREC_AD_UNIT_ID";
    const FString Interstitial = "5728c31011cd8d33";
    const FString Interstitialtwo = "b613262e21f65a9d";

    const FString Rewarded = "fc3bada858862f85";
    const FString Rewardedtwo = "4a1c91c9664d677e";
    const FString Rewardedthree = "c4cb655aa78997e8";
    const FString Rewardedfour = "97cb670788cae91a";
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
