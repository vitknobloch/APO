make:
	gcc -mssse3 -g -O1 -Wall -Werror -std=c99 -o main main.c -lm

run:
	valgrind --tool=cachegrind --I1=32768,8,64 --D1=32768,8,64 --LL=1048576,16,64 ./main test/vit_normal.ppm

zip:
	zip cur.zip main.c

clean:
	find . -type f -name 'cachegrind.out.*' -exec rm -f {} +
	rm output.ppm output.txt output_ref output_ref_ref

