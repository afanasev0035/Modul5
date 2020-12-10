all: my_prog

my_prog:UDPEchoClient.c
	gcc -Wall -o Client UDPEchoClient.c -std=c99 -lpthread
	gcc -Wall -o Server UDPEchoServer.c -std=c99 -lpthread
	./Server 2222 &
	./Client
