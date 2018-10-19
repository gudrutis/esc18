---
title: Managing resources
layout: main
category: cpp
---

The goal of this exercise is to get some confidence with the smart
pointers provided by the C++ standard library: `unique_ptr` and
`shared_ptr`.

Open the test program [`dir.cpp`]({{site.exercises_repo}}/hands-on/cpp/dir.cpp)
and, following the hints in the file, complete the existing code to:

* create a smart pointer managing a DIR resource obtained with the
  `opendir()` function call
* associate a deleter to that smart pointer
* implement a function to read the names of the files in that
  directory
* check if the deleter is called at the right moment
* hide the creation of the smart pointer behind a factory function
* hide the creation of the smart pointer behind a factory function
* populate a vector of FILEs, properly wrapped in a smart pointer, obtained
  opening the regular files in that directory

You can experiment with both kinds of smart pointers and with the type
of the function arguments.
