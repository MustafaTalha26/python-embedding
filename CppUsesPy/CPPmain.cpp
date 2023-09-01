#include <stdio.h>
#include <iostream>
#include "C:\Users\mtmert\AppData\Local\Programs\Python\Python310\include\Python.h"
// Find and include your Python installation's Python.h file

//<ItemGroup>
//  <Library Include = "..\..\..\AppData\Local\Programs\Python\Python310\libs\python310_d.lib" />
//</ItemGroup>

// Add ItemGroup above to your .vcxproj file
// If you don't have "python310_d.lib" debugger
// Modify your python with "Download debug binaries (requires VS 2017 or later)"
// in Advanced Options. (can be done with Python installer)

struct stats
{
	int lport;
	int rport;
};


int main() {
	// This part, we add sys.path to add our python file to project.
	// Change directory as python file's directory.
	Py_Initialize();
	const char* directory = "C:/Users/mtmert/Desktop/CppUsesPy/CppUsesPy/";
	PyObject* sys = PyImport_ImportModule("sys");
	PyObject* path = PyObject_GetAttrString(sys, "path");
	PyObject* FuncDirectory = PyObject_GetAttrString(path, "append");

	if (FuncDirectory && PyCallable_Check(FuncDirectory)) {
		PyObject* ArgsDirectory = Py_BuildValue("(s)", directory);
		PyObject* ValueDirectory = PyObject_CallObject(FuncDirectory, ArgsDirectory);
	}
	else {
		printf("ERROR: Couldnt use sys.path\n");
	}
	//At this point our python file is ready to use.


	// This is a example part. This is baseline for simple solutions.
	int arg1 = 100, arg2 = 2;

	PyObject* pModule = PyImport_ImportModule("MyMath");
	PyObject* pClass = PyObject_GetAttrString(pModule, "SimpleMath");

	if (pModule) {
		PyObject* pFunc = PyObject_GetAttrString(pClass, "divide");
		if (pFunc && PyCallable_Check(pFunc)) {
			PyObject* pArgs = Py_BuildValue("(ii)", arg1, arg2);
			PyObject* pValue = PyObject_CallObject(pFunc, pArgs);
			printf("OUTPUT: func() = %ld\n", PyLong_AsLong(pValue));
		}
		else {
			printf("ERROR: Couldn't reach func\n");
		}
	}
	else {
		printf("ERROR: Module not imported\n");
	}

	// This is a example for multidimension. We can create arrays with this way.
	// We can't send Cpp/C structure to Python the way it is.
	// We need to figure out Python combination to replicate our C structure.
	// If we don't want to figure out Python combination here, we can choose to use
	// ctypes library and create c like structures in Python end.
	struct stats myList = { 11, 2 };

	PyObject* list = PyList_New(5);
	Py_ssize_t size = PyList_GET_SIZE(list);

	for (Py_ssize_t s = 0; s < size; s++)
	{
		PyList_SetItem(list, s, Py_BuildValue("{s:i,s:i}", "lport", s*myList.lport, "rport", s*myList.rport));
	}

	if (pModule) {
		PyObject* pFunc2 = PyObject_GetAttrString(pClass, "trystruct");
		if (pFunc2 && PyCallable_Check(pFunc2)) {
			PyObject* pValue2 =  PyObject_CallFunctionObjArgs(pFunc2, list, NULL);
			PyObject* returnlist = PyList_GetItem(list, 2);
			PyObject* returndict = PyDict_GetItemString(returnlist, "lport");
			printf("OUTPUT: func() = %ld\n", PyLong_AsLong(returndict));
		}
		else {
			printf("ERROR: Couldn't reach func\n");
		}
	}
	else {
		printf("ERROR: Module not imported\n");
	}

	Py_Finalize();
	return 0;
}


// #include <numpy/arrayobject.h>
// can be usefull for python and cpp/c to have a common variables.

// Py_DECREF() can be usefull performance. 