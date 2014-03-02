main : main.o reply.o request_parser.o request_handler.o mime_types.o
	g++ -o main main.o reply.o  request_parser.o request_handler.o mime_types.o

main.o : main.h
	g++ -g -c main.cpp

reply.o : reply.h
	g++ -g -c reply.cpp

request_parser.o : request_parser.h
	g++ -g -c request_parser.cpp

request_handler.o : request_handler.h
	g++ -g -c request_handler.cpp

mime_types.o : mime_types.h
	g++ -g -c mime_types.cpp

