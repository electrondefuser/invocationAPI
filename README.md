# InvocationAPI

Mechanism to execute java methods via JNI (Jave Native Interface) by using a JVM (Java Virtual Machine) instance.

# What is this exactly?

In short this is a C application which using the android framework's ART (Android Runtime) will create a JavaVM and
execute application level java methods by using JNI caller code. The caller code can be modified by the
user for different applications. Here's a very simple example of how this works.

This image shows a very simple android application using JNI code that returns a "Hello Jni" string
from the native function.


![alt text](https://github.com/electrondefuser/InvocationAPI/blob/main/images/android_app_java_code.png)

Here's the caller code (present in the repo) in the main function that executes the method "callJni" java
method in the above class in the application.

![alt text](https://github.com/electrondefuser/InvocationAPI/blob/main/images/caller_code.png)

Compiling the above code and executing the android device will give the below result. This executed
the method "callJni" directly and prints the output of the return value of the function.

![alt text](https://github.com/electrondefuser/InvocationAPI/blob/main/images/exec.png)

# Why use this?

This can be helpful in many scenarios. One such would be in reverse engineering application
code in an isolated format, where you want to only execute specific parts
of the code to figure out the functioning of the application's native and java logic and how they
interact together. It's also helpful in enviroments where frida can't run because or DBI detection
logic being present (This is no way a replacement of frida though).

# How to use

Well it's extremely easy to use this. Clone the repository and open in a code editor. Make sure
you point to your ndk toolchain file in the build.sh file in order to compile the same.
Copy over your library (from the application your trying the reverse engineer) into the lib folder and
change the CMakeList.txt file's target_link_library section with your library name. Modify the caller code
depending upon your needs and build the entire thing with build.sh script.

Once the build is complete, push the main binary into the device and copy your main APK as base.apk into a folder called
"app_base" in the location "/data/local/tmp/".

Export the library path in the device in the following way (if the library isn't present, push the lib into a
folder called "libs" inside your application directory "/data/data/com.example.yourapplication/libs).

![alt text](https://github.com/electrondefuser/InvocationAPI/blob/main/images/lib_export_demo.png)

Once all the above steps are done, execute the "main" binary and it should start your caller code
and execute the appropriate logic.



