#include <jni.h>

/* 
    Primitive java datatypes which can be used as parameters in functions
    or simply as return types. This is for reference only.

    Other types are as follows:
    (args/parametes) return_value eg. (I)Z (Integer argurment and Boolean return value)

    For fully qualified class use "L" symbol following by the class name
    or datetype.
    
     eg. Ljava/lang/String;

     Array can be denanoted by "[" and the datatype or class that goes
     along with it.

     eg. [Ljava/lang/String;
*/

#define JNI_BOOLEAN "Z";
#define JNI_BYTE    "B";
#define JNI_CHAR    "C";
#define JNI_SHORT   "S";
#define JNI_INT     "I";
#define JNI_LONG    "J";
#define JNI_FLOAT   "F";
#define JNI_DOUBLE  "D";
