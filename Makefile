CC = g++
CFLAGS = -Wall -g 
SRCDIR = ./code
BOOSTDIR = /home/user/LLVM_STUFF/boost/boost_1_74_0
TESTDIR = ./test/correctness/out_files
TESTSOURCES = ./test/correctness/*.cpp

correctness:
	if [ ! -d "$(TESTDIR)" ]; then \
		mkdir $(TESTDIR) ; \
	fi
	for CPPFILE in $(TESTSOURCES) ; do \
		echo Compiling: $$CPPFILE ; \
		OBJ=$$(basename $$CPPFILE .cpp) ; \
		$(CC) $(CFLAGS) -I $(BOOSTDIR) $$CPPFILE -o $(TESTDIR)/$$OBJ ; \
	done

correctness_exec:
	for OBJFILE in $(TESTDIR)/* ; do \
		echo Test executed: $$OBJFILE ; \
		$$OBJFILE ; \
	done

clean:
	rm -r $(TESTDIR)



