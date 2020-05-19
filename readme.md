# Classmoor Build Directions

## Mac OS/Linux
### Requirements:
* QT 4.12^
* C++ Compiler (QMake)
*  [AWS-cpp-sdk]([https://github.com/aws/aws-sdk-cpp](https://github.com/aws/aws-sdk-cpp))
### Prerequisites
In the .pro there is a line
`QML_IMPORT_PATH  =/opt/Qt5.14.2/gcc_64/qml/QtGraphicalEffects/`
Please use the correct file path or just comment it out.
### Steps To build
1. Clone the AWS SDK repo and follow the directions to build.

2. I recommend you put all classmoor dependencies in one root folder and add the sdk there in two folders; the source folders and the built CMake files.

3. Create a folder called `aws-build` and run this command `cmake -DBUILD_ONLY="s3;dynamodb;sns" ../aws-sdk-cpp/` If following the way we built our file system it should start running the cmake process.
4.  After, we will install the dependencies to our local user include file. by running this
        1. `make`
        2. `sudo make install`
***This will take a while too, we are basically compiling all the sdk's we need***
5. If linked successfully, you can now run the program in QT, by opening the pro file with QT. You should see `AWS SDK connected` in your console as that means it is working. Each .pro file will be different since the OS will have varying different installation paths.
#### Issues
* I noticed when running Qt you might get this error [here](https://stackoverflow.com/questions/35509731/dyld-symbol-not-found-cg-jpeg-resync-to-restart)

#### Run Without AWS
Comment out Line 16 and 17 in the .pro file
```
INCLUDEPATH  +=  /usr/local/include
LIBS  +=  -L/usr/local/lib  -laws-cpp-sdk-core  -laws-cpp-sdk-s3
```
