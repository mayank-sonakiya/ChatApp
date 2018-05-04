/*
  Shared memory layout.
*/
#define BUFFER_SZ 1024

struct shared_use_st {
	int written_for_1;
	int written_for_2;
	int written_for_3;
    int written_for_4;
    int flag;
	char message[BUFFER_SZ];
};

