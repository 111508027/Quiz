project: project.c 
	cc -g  project.c `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` -I /usr/local/libxml2/include/libxml2/ -lxml2 -o project

	
project.o: project.c  
	cc -g  project.c `pkg-config --cflags gtk+-2.0` `pkg-config --libs gtk+-2.0` -I /usr/local/libxml2/include/libxml2/ -lxml2 -Wall
	./project	
