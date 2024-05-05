// JVMSTARTER.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include "jni.h"
#include <iostream>
using namespace std;
#include <Windows.h>
/*
This program demonstrates how to start a jvm and run a java program
Its analogies to how the JDK java.exe program works to run a java class file

IMPORTANT YOU MUST SET AN ENVIRONMENT VARIABLE IF YOUR ON WINDOWS NAMED "CLOADERSEARCH"  
THE VALUE OF IT MUST BE THE CLASSPATH TO SEARCH FOR ALL YOUR CLASSFILES.
BEFORE YOU EXECUTE/USE THIS PROGRAM

*/


int main(int argc, char** argv)
{

    LPSTR varval = (LPSTR)malloc( 32767*sizeof(char) );
    varval[0] = '\0';
    GetEnvironmentVariableA((LPSTR)"CLOADERSEARCH", varval, 32767);
    printf("CLOADERSEARCH=%s", varval);

    JavaVMInitArgs vmArgs;
    JavaVMOption jvmopt[2];
    string a("-verbose:jni");                    //Setting verbose output for jni
    string b("-Djava.class.path=");              //Setting the classpath
    if( varval != nullptr )
    b.append(varval);

    free(varval);

    printf("\n%s\n", b.c_str());
    jvmopt[0].optionString = (char *)b.c_str();  
    jvmopt[1].optionString = (char*)a.c_str();
    vmArgs.version = JNI_VERSION_21; //JDK version. This indicates version used is JNI 21


    vmArgs.nOptions = 2;
    vmArgs.options = jvmopt;
    vmArgs.ignoreUnrecognized = false;

    JavaVM* javaVM;
    JNIEnv* jniEnv;

    int reAt = JNI_CreateJavaVM(&javaVM, (void**)&jniEnv, &vmArgs);

    if (reAt < 0)
    {
        printf("Failed creating the JVM %i" , reAt);
        return 0;
    }
    else
    {
        printf("Succeed in creating the JVM\n");
        fflush(stdout);
        javaVM->GetEnv((void**)&jniEnv,JNI_VERSION_21);
        
        jclass jclazzz = jniEnv->FindClass(argv[1]);  //EXAMPLE: PACKAGE/SUBPACKAGE/MAINCLASS  / NOT . DELIMITING 
        jniEnv->ExceptionDescribe();
        jmethodID mid = jniEnv->GetStaticMethodID(jclazzz, "entrypoint" , "([Ljava/lang/String;)V" );
        jniEnv->ExceptionDescribe();

        jstring jinitialize = jniEnv->NewStringUTF("");
        jclass strclass = jniEnv->FindClass("java/lang/String");
        jobjectArray jparams = jniEnv->NewObjectArray(argc, strclass, jinitialize);
        
        
        for (int i = 0; i < argc; i++) {
            jstring pelements = jniEnv->NewStringUTF(argv[i]);
            jniEnv->SetObjectArrayElement(jparams, i, pelements);

        }

        jniEnv->CallStaticVoidMethod(jclazzz, mid, jparams);
        jniEnv->ExceptionDescribe();
        printf("DESTROYING/SHUTTING DOWN  JVM");
        fflush(stdout);

        javaVM->DestroyJavaVM();
       
    }


}

