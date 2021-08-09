CC = g++
CFLAGS = -g -Wall
BOOSTDIR = /home/user/LLVM_STUFF/boost/boost_1_74_0
BOOSTINC = -I $(BOOSTDIR)
GRAPHDIR = ./code
GRAPHINC = -I $(GRAPHDIR)
TESTDIR = ./test/correctness
TESTSOURCES = ./test/correctness/*.cpp
PERFDIR = ./test/performance
BENCHINC = -isystem ./benchmark/include -L ./benchmark/build/src -lbenchmark -lpthread

unit_test:
	$(CC) $(CFLAGS) $(BOOSTINC) $(GRAPHINC) $(GRAPHDIR)/*.cpp $(TESTSOURCES) -o $(TESTDIR)/out_files/unit_test ; \
	$(TESTDIR)/out_files/unit_test

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

performance_fill:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(PERFDIR)/fill_in_evaluation.cpp -o $(PERFDIR)/out_files/fill_in_evaluation  $(BENCHINC) $(GRAPHINC) $(BOOSTINC)

performance_lex_p:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(PERFDIR)/lex_p_evaluation.cpp -o $(PERFDIR)/out_files/lex_p_evaluation $(BENCHINC) $(GRAPHINC) $(BOOSTINC)

performance_lex_m:
	$(CC) $(CFLAGS) $(GRAPHDIR)/*.cpp $(PERFDIR)/lex_m_evaluation.cpp -o $(PERFDIR)/out_files/lex_m_evaluation $(BENCHINC) $(GRAPHINC) $(BOOSTINC)

clean:
	rm -r $(TESTDIR)/out_files



