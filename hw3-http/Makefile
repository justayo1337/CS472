all: client-cc client-ka

client-cc: client-cc.c http.c
	gcc -g client-cc.c http.c -o client-cc

client-ka: client-ka.c http.c
	gcc -g client-ka.c http.c -o client-ka

clean:
	rm -f client-ka
	rm -f client-cc

.PHONY: run-cc
run-cc:
	./client-cc httpbin.org 80 /

.PHONY: run-cc3
run-cc3:
	./client-cc httpbin.org 80 / /json /html

.PHONY: run-ka
run-ka:
	./client-ka httpbin.org 80 /

.PHONY: run-ka3
run-ka3:
	./client-ka httpbin.org 80 / /json /html

.PHONY: run-ka4
run-ka4:
	./client-ka httpbin.org 80 / /json /html /post