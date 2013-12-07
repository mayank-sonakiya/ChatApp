ChatApp
=======

this is a Multi-client chat application Using shared memory and POSIX threads. this is developed on Linux with GCC compiler. This application contains 4 clients and demonstrated the one to one chat between them. 

/*Here is our shared memory structure that is to be included in all clients*/

#define BUFFER_SZ 1024

struct shared_use_st {
	int written_for_1;
	int written_for_2;
	int written_for_3;
    int written_for_4;
    int flag;
	char message[BUFFER_SZ];
};

