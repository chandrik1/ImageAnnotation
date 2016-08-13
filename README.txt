This implementation of Image Annotation uses a classification like approach to annotate an input image into any of the predefined categpries. This is done by giving some sample data for each category and extracting SURF(Speeded Up Robust Features) descriptors and training SVM(Support Vector Machine)s for each category. This step is called training phase. Each of the SVMs is trained with positive data(its samples) and negative data(samples of the other categories). These supoort vector machines are stored so that they can be recalled in the second phase. Also Bag of Words has to be generated using vocabulary(a sample of each category i.e., templates) and is clustered using k-means algorithm.

In the second phase called testing, we are calculating the SURF descriptors of the test image and predicting the value the function in CvSVM(found in OpenCV C++) is giving. The least value is taken as the best prediction based on that function and its corresponding category is taken as the category of the object.

Basic code is taken from the book 'PRACTICAL OPENCV'.

Software Requirements: 
1.C++ compiler: 

Tested on:$ g++ -v 
Using built-in specs. 
COLLECT_GCC=g++ 
COLLECT_LTO_WRAPPER=/usr/lib/gcc/i686-linux-gnu/4.7/lto-wrapper 
Target: i686-linux-gnu 
Configured with: ../src/configure -v --with-pkgversion='Ubuntu/Linaro 4.7.2-2ubuntu1' --with-bugurl=file:///usr/share/doc/gcc-4.7/README.Bugs --enable-languages=c,c++,go,fortran,objc,obj-c++ --prefix=/usr --program-suffix=-4.7 --enable-shared --enable-linker-build-id --with-system-zlib --libexecdir=/usr/lib --without-included-gettext --enable-threads=posix --with-gxx-include-dir=/usr/include/c++/4.7 --libdir=/usr/lib --enable-nls --with-sysroot=/ --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --enable-gnu-unique-object --enable-plugin --enable-objc-gc --enable-targets=all --disable-werror --with-arch-32=i686 --with-tune=generic --enable-checking=release --build=i686-linux-gnu --host=i686-linux-gnu --target=i686-linux-gnu 
Thread model: posix 
gcc version 4.7.2 (Ubuntu/Linaro 4.7.2-2ubuntu1) 

Installation Command: $ sudo apt-get install g++ 

2.Opencv C++ : 

OpenCV version:
$ pkg-config --modversion opencv 
2.3.1 

Installed packages:

$ dpkg -l |grep libopencv 
ii  libopencv-calib3d-dev                     2.3.1-11ubuntu2                               i386         development files for libopencv-calib3d 
ii  libopencv-calib3d2.3                      2.3.1-11ubuntu2                               i386         computer vision Camera Calibration library 
ii  libopencv-contrib-dev                     2.3.1-11ubuntu2                               i386         development files for libopencv-contrib 
ii  libopencv-contrib2.3                      2.3.1-11ubuntu2                               i386         computer vision contrib library 
ii  libopencv-core-dev                        2.3.1-11ubuntu2                               i386         development files for libopencv-core 
ii  libopencv-core2.3                         2.3.1-11ubuntu2                               i386         computer vision core library 
ii  libopencv-dev                             2.3.1-11ubuntu2                               i386         development files for opencv 
ii  libopencv-features2d-dev                  2.3.1-11ubuntu2                               i386         development files for libopencv-features2d 
ii  libopencv-features2d2.3                   2.3.1-11ubuntu2                               i386         computer vision Feature Detection and Descriptor Extraction library 
ii  libopencv-flann-dev                       2.3.1-11ubuntu2                               i386         development files for libopencv-flann 
ii  libopencv-flann2.3                        2.3.1-11ubuntu2                               i386         computer vision Clustering and Search in Multi-Dimensional spaces library 
ii  libopencv-gpu-dev                         2.3.1-11ubuntu2                               i386         development files for libopencv-gpu 
ii  libopencv-gpu2.3                          2.3.1-11ubuntu2                               i386         computer vision GPU Processing library 
ii  libopencv-highgui-dev                     2.3.1-11ubuntu2                               i386         development files for libopencv-highgui 
ii  libopencv-highgui2.3                      2.3.1-11ubuntu2                               i386         computer vision High-level GUI and Media I/O library 
ii  libopencv-imgproc-dev                     2.3.1-11ubuntu2                               i386         development files for libopencv-imgproc 
ii  libopencv-imgproc2.3                      2.3.1-11ubuntu2                               i386         computer vision Image Processing library 
ii  libopencv-legacy-dev                      2.3.1-11ubuntu2                               i386         development files for libopencv-legacy 
ii  libopencv-legacy2.3                       2.3.1-11ubuntu2                               i386         computer vision legacy library 
ii  libopencv-ml-dev                          2.3.1-11ubuntu2                               i386         development files for libopencv-ml 
ii  libopencv-ml2.3                           2.3.1-11ubuntu2                               i386         computer vision Machine Learning library 
ii  libopencv-objdetect-dev                   2.3.1-11ubuntu2                               i386         development files for libopencv-objdetect 
ii  libopencv-objdetect2.3                    2.3.1-11ubuntu2                               i386         computer vision Object Detection library 
ii  libopencv-video-dev                       2.3.1-11ubuntu2                               i386         development files for libopencv-video 
ii  libopencv-video2.3                        2.3.1-11ubuntu2                               i386         computer vision Video analysis library 


  Installation steps:
1. Open synaptic package manager.
2. Search for opencv.
3. Mark and download the required packages from the above list.

3.Boost Library: For iterating through directories.


Boost Version used:
$ dpkg -s libboost-dev | grep 'Version' 
Version: 1.49.0.1 


Installation command:
$ sudo apt-get install libboost-all-dev

NOTE: We have to give dev privileges to boost library so that our code can make use of it.

4. cmake

cmake Version:
$ cmake --version 
cmake version 2.8.9 

cmake dependency version:
$ curl --version 
curl 7.27.0 (i686-pc-linux-gnu) libcurl/7.27.0 OpenSSL/1.0.1c zlib/1.2.7 libidn/1.25 librtmp/2.3 
Protocols: dict file ftp ftps gopher http https imap imaps ldap ldaps pop3 pop3s rtmp rtsp smtp smtps telnet tftp 
Features: Debug GSS-Negotiate IDN IPv6 Largefile NTLM NTLM_WB SSL libz TLS-SRP 


Installing cmake:
$ sudo apt-get install curl
$ wget http://www.cmake.org/files/v2.8/cmake-2.8.9.tar.gz
$ tar xzf cmake-2.8.9.tar.gz
$ cd cmake-2.8.9
For configuring:
$ ./configure  --prefix=/opt/cmake 
$ make
$make install
  OR
$ sudo apt-get install curl
$ sudo apt-get install cmake

NOTE: All dependencies required by that system for cmake is taken care of.

To verify:
$ cmake  --version

How to compile and run the code?

Save all the training data ./data/train_images/ by creating subfolders in the same like /train_images/car/, /train_images/human, and so on.
XMLs of the trained SVMs will be generated in ./data as well.

Compiling and execution of the code is done in 2 parts.
1) Training:
    $ cmake .
    $ make
    $ ./code

2)Testing:
  $ g++ test_disp.cpp 'pkg-config --cflags --libs opencv' -lboost_filesystem -lboost_system 
  $ ./a.out <image name from the folder '/var/www/annotation'>

Example: $ ./a.out 3.jpeg
