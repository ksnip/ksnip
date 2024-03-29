Ksnip follows the KDELibs (see https://community.kde.org/Policies/Kdelibs_Coding_Style)
coding style, with a few exceptions:

1. The access modifier ordering is: public, public slots, signals,
   protected, protected slots, private, private slots. Member variables
   come at beginning, before all member functions. This is not strictly
   enforced, but is a good rule to follow.

2. Headers are cumulative, i.e., all headers that a particular class
   requires, are #include-ed in the class's header file, not the .cpp
   code file. The .cpp code file includes only one header, which is
   its own .h file. E.g., a class Foo, defined in Foo.h, will have its
   code in Foo.cpp, and Foo.cpp will #include only a single header
   Foo.h

3. Member variables follow the format mCamelCase, and not m_camelCase
   which is more common throughout the rest of the KDE Applications

4. Source files are mixed case, named the same as the class they
   contain. i.e., SomeClass will be defined in SomeClass.cpp, not
   someclass.cpp

5. Function parameters, if classes, should be past as const references, if
   basic types like bool, int, float, enum, can be passed by value. Functions
   that do not change anything on the class (like getters), should be const.

6. Use single TAB instead of four spaces to indent.

7. UnitTest should have the following naming convention:
    `<MethodUnderTes>_Should_<ExpectedBehavior>_When_<OptionCondition>`
   Example:
    `StoreImagesPath_Should_NotSavePath_When_PathAlreadyStored`

8. Tabs should be used for indentation.
