CC=clang++
BM_LIBS=-I/usr/local/include /usr/local/lib/libbenchmark.a /usr/local/lib/libbenchmark_main.a

all: bm_vector bm_no_vector

bm_vector:
	$(CC) -mavx -march=native -O2 -o $@ bm.cc $(BM_LIBS) -lpthread

bm_no_vector:
	$(CC) -mno-avx -mno-sse -mno-sse2 -mno-mmx -fno-vectorize -march=native -O2 -o $@ bm.cc $(BM_LIBS) -lpthread

clean:
	rm -f bm_vector bm_no_vector
