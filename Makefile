# this is set up to by default to make the top level and test with CppUTest
all: codeCppUTest

clean: cleanCodeCppUTest

cleanCode: cleanCodeCppUTest

codeCppUTest: CppUTest CppUTestExt
	make -i -f MakefileCppUTest.mk

cleanCodeCppUTest:
	make -i -f MakefileCppUTest.mk clean

CppUTest: cpputest/lib/libCppUTest.a

CppUTestExt: cpputest/lib/libCppUTestExt.a

cpputest/lib/libCppUTest.a:
	pwd
	make -i -C cpputest -f Makefile_using_MakefileWorker

cpputest/lib/libCppUTestExt.a:
	make -i -C cpputest -f Makefile_using_MakefileWorker extensions

format:
	make -i -f MakefileCppUTest.mk uncrustify

gcov: clean
	make -i -f MakefileCppUTest.mk gcov

check:
	make -i -f MakefileCppUTest.mk cppcheck
