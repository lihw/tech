tech
====

The foundation library for all future interface products, like paper3d, panel3d and bamboo. It provides the a variety of useful helper classes, like container, algorithms, math, a C++ wrapper of OpenGL ES 2.0 and encapsulate the difference of each operating systems, so that above application layer can concentrate on the logic and content.

Please visit http://lihw.github.com/tech for release notes, API manual and milestones.

#Version
The latest version is 0.91a.

#Platform
Windows 7 32&64 bit, iOS 7.0, Android 4.1 and above.

#Developement requirements
The preferable develpoment platform is Windows 7 64bit with a discrete video card. The MacOS X 10.9 can also be used.

|               | Win32         | Andoird      |    iOS   |
| ------------- | ------------- |--------------|----------|
| Windows 7     | YES           |  Yes         |   No
| OSX           | No            | Not supported|   Yes    |

#Installation
Use either `git clone https://github.com/lihw/tech.git <dir>;git checkout 0.91a` or download the zip file at [https://github.com/lihw/tech/archive/0.91a.zip](https://github.com/lihw/tech/archive/0.91a.zip), and then uncompress the zip file to any dir you want. 

**The path of installation dir should not include and blank spaces**

## Windows
1. Run install.bat **as administrator**
2. Download and install Microsoft Visual Studio 2012 Express
[http://www.microsoft.com/en-us/download/details.aspx?id=34673](http://www.microsoft.com/en-us/download/details.aspx?id=34673)

## OSX
1. Run install.sh
 
## Android dev on Windows
1. Install the Android SDK and Eclipse bundle 
32bit: [http://dl.google.com/android/adt/adt-bundle-windows-x86-20131030.zip](http://dl.google.com/android/adt/adt-bundle-windows-x86-20131030.zip)
64bit: TODO
2. Install ANT
[http://ant.apache.org/bindownload.cgi?Preferred=http%3A%2F%2Fmirrors.cnnic.cn%2Fapache%2F](http://ant.apache.org/bindownload.cgi?Preferred=http%3A%2F%2Fmirrors.cnnic.cn%2Fapache%2F)
3. Install JDK 1.7
[http://www.oracle.com/technetwork/java/javase/downloads/jdk7-downloads-1880260.html](http://www.oracle.com/technetwork/java/javase/downloads/jdk7-downloads-1880260.html)
**Needs to be installed to C:\JDK**
4. Install the latest Android NDK
[https://developer.android.com/tools/sdk/ndk/index.html#Installing](https://developer.android.com/tools/sdk/ndk/index.html#Installing)
5. Setup environment variables
JAVA_HOME=C:\JDK
ANT_HOME=`<ANT installation dir>`
ANDROID_SDK=`<Android SDK path>`
Add `<ANT installation dir>\bin;<Android NDK installation dir>\;<Android SDK installation dir>\platform-tools\` to PATH

## Android dev on OSX
Not supported yet.

#Build

## Windows
1. Open <Dir>\tech\configs\msvc2012\tech.sln in MSVC2012, choose **Debug** profile and build. When finished, build the **Release** profile.
2. Open <Dir>\tech\configs\android\ in dos window, and enter `build.bat debug`. When finished, enter `build.bat release`.

## OSX
1. Open <Dir>/tech/configs/ios/Tech.xcodeproj, select **buildall** as active scheme and build.



