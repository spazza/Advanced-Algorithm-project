CC = g++
CFLAGS = -Wall -O3
BOOSTDIR = /home/user/LLVM_STUFF/boost/boost_1_74_0
BOOSTINC = -I $(BOOSTDIR)
GRAPHDIR = ./code
GRAPHINC = -I $(GRAPHDIR)
TESTDIR = ./test/correctness/out_files
TESTSOURCES = ./test/correctness/*.cpp
PERFDIR = ./test/performance
BENCHINC = -isystem ./benchmark/include -L ./benchmark/build/src -lbenchmark -lpthread

unit_test:
	$(CC) $(CFLAGS) $(BOOSTINC) $(GRAPHINC) $(GRAPHDIR)/*.cpp ./test/correctness/unit_test.cpp -o $(TESTDIR)/unit_test ; \
	$(TESTDIR)/unit_test

correctness:
	if [ ! -d "$(TESTDIR)" ]; then \
		mkdir $(TESTDIR) ; \
	fi
	for CPPFILE in $(TESTSOURCES) ; do \
		echo Compiling: $$CPPFILE ; \
		OBJ=$$(basename $$CPPFILE .cpp) ; \
		$(CC) $(CFLAGS) $(BOOSTINC) $(GRAPHINC) $(GRAPHDIR)/*.cpp $$CPPFILE -o $(TESTDIR)/$$OBJ ; \
	done

correctness_exec:
	for OBJFILE in $(TESTDIR)/* ; do \
		echo Test executed: $$OBJFILE ; \
		$$OBJFILE ; \
	done

performance:
	$(CC) $(GRAPHDIR)/*.cpp $(PERFDIR)/fill_in_evaluation.cpp -o $(PERFDIR)/out_files/fill_in_evaluation  $(BENCHINC) $(GRAPHINC)

clean:
	rm -r $(TESTDIR)



