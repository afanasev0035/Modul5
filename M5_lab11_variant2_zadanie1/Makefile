all: my_prog11

my_prog11:UDPEchoClient.c
	gcc -Wall -o Client UDPEchoClient.c -std=c99 -lpthread
	gcc -Wall -o Server UDPEchoServer.c -std=c99 -lpthread
	./Server 3333 &
	./Client
