CC = gcc

server:
	@ gcc -o tcp_server tcp_server.c
	@ ./tcp_server

client:
	@ gcc -o tcp_client tcp_client.c
	@ ./tcp_client

clean:
	@ rm ./tcp_client ./tcp_server

.PHONY = client server clean
