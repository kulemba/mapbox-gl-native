#!/bin/bash
pushd platform/android &> /dev/null
./gradlew -Pmapbox.buildtype="release" -Pmapbox.abis="armeabi-v7a arm64-v8a x86 x86_64" :MapboxGLAndroidSDK:clean :MapboxGLAndroidSDK:publishMapboxMapsSdkPublicationPublicationToMavenLocal
popd &> /dev/null
