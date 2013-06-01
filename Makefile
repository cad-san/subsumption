# this is set up to by default to make the top level and test with CppUTest
all: codeCppUTest

clean: cleanCodeCppUTest

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

release: clean
	make -i -f MakefileRelease.mk

gcov: clean
	make -i -f MakefileCppUTest.mk gcov

format:
	make -i -f MakefileUTil.mk uncrustify

check:
	make -i -f MakefileUtil.mk cppcheck
