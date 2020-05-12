#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int isPowerTwo(int);
void allocate_cache(int, int, int);
int getAssoc(int, int, char*);
int check_hit(unsigned int, unsigned int, int);
void write_cache(unsigned int, unsigned int, int);
void clear_cache(int, int);

struct Cacheblock {
	unsigned int valid;
	unsigned long int tag;
	unsigned int time;
};

//global cache
struct Cacheblock** cache;
//global time variable
int timevar = 1;

void clear_cache(int sets, int assoc){
	int i,j;
	for(i=0; i<sets; i++){
		for(j=0; j<assoc; j++){
			cache[i][j].valid=0;
			cache[i][j].tag=0;
			cache[i][j].time=0;
		}
	}
}

int isPowerTwo(int x){
	if(x==0)
		return 0;
	if(ceil(log2(x)) == floor(log2(x)))
		return 1;
	return 0;
}

int getAssoc(int cache_size, int block_size, char* a){
	int assoc=0;
	if(strcmp(a, "direct") == 0){
		assoc = 1;
	}
	else if(strcmp(a, "assoc") == 0){
		assoc = (cache_size/block_size);
	}
	else{
		char c = a[strlen(a)-1];
		assoc = c-'0';
	}
	return assoc;
}

void allocate_cache(int cache_size, int block_size, int assoc){
	int numSets = 0;	
	//we now have C, B, and A. Use equation C = S*A*B to get number of sets
	numSets = cache_size/(assoc*block_size);
	cache = malloc(numSets * sizeof(struct Cacheblock*));
	int i=0;
	for(i=0; i<numSets; i++)
		cache[i] = malloc(sizeof(struct Cacheblock) * assoc);
	return;
}

int check_hit(unsigned int set_index, unsigned int tag, int assoc){
	int i=0;
	for(i=0; i<assoc; i++){
		if(cache[set_index][i].valid == 1 && cache[set_index][i].tag == tag){
			return 1;			
		}
	}
	return 0;
}

void write_cache(unsigned int set_index, unsigned int tag, int assoc){
	int i=0, write=0;
	for(i=0; i<assoc; i++){
		if(cache[set_index][i].valid == 0){
			cache[set_index][i].valid = 1;
			cache[set_index][i].tag = tag;
			if(cache[set_index][i].time == 0){
				cache[set_index][i].time = timevar;
				timevar++;
			}
		write=1;
		}		
	}
	if(write==0){ //all entries in set are valid. FIFO replace the lowest time
		int min=cache[set_index][0].time, index=0;
		for(i=0; i<assoc; i++){
			if(cache[set_index][i].time < min){
				min = cache[set_index][i].time;
				index = i;
			}
		}
		cache[set_index][index].tag = tag;
		cache[set_index][index].time = timevar;
		timevar++;
	}
	return;
}

int main(int argc, char** argv){
	if(argc < 6){
		printf("error");
		exit(0);
	}
	int cache_size=atoi(argv[1]);
	int block_size=atoi(argv[2]);
	//char* cache_policy = argv[3];
	char* associativity = argv[4];
	int prefetch_size=atoi(argv[5]);
	FILE *tf = fopen(argv[6], "r");		
	//validate inputs
	//check if cache size, block size is a power of 2
	if(isPowerTwo(cache_size) == 0 || isPowerTwo(block_size) == 0){
		printf("error");
		exit(0);
	}
	if(tf == NULL){
		printf("error");
		exit(0);
	}
	int numSets=0;
	int hits=0;
	int miss=0;
	int mem_read=0;
	int mem_write=0;
	char mode;
	unsigned int setbits=0;
	unsigned int blockbits=0;
	unsigned int mask=0;
	unsigned int address=0;
	int assoc = getAssoc(cache_size, block_size, associativity);
	allocate_cache(cache_size, block_size, assoc);
	numSets = cache_size / (assoc*block_size);
	setbits = log(numSets)/log(2);
	blockbits = log(block_size)/log(2);
	mask = (1 << setbits) - 1;
	//start reading from trace file
	while(fscanf(tf, "%c", &mode) != EOF){
		if(mode == '#')
			break;
		fscanf(tf, "%x\n", &address);
		unsigned int set_index = (address >> blockbits) & mask;
		unsigned long tag = (address >> blockbits) >> setbits;
		if(check_hit(set_index, tag, assoc)==1){ //it is a hit!
			hits++;
			if(mode == 'W')
				mem_write++;
		}
		else { //miss
			miss++;
			write_cache(set_index, tag, assoc);
			if(mode == 'R')
				mem_read++;
			else{
				mem_read++;
				mem_write++;
			}	
		}
	}
	printf("no-prefetch\n");
	printf("Memory reads: %d\n", mem_read);
	printf("Memory writes: %d\n", mem_write);
	printf("Cache hits: %d\n", hits);
	printf("Cache misses: %d\n", miss);
	mem_read = 0;
	mem_write=0;
	hits=0;
	miss=0;
	clear_cache(numSets, assoc);
	rewind(tf);
	while(fscanf(tf, "%c", &mode) != EOF){
		if(mode == '#')
			break;
		fscanf(tf, "%x\n", &address);
		unsigned int set_index = (address >> blockbits) & mask;
		unsigned long tag = (address >> blockbits) >> setbits;
		if(check_hit(set_index, tag, assoc)==1){ //it is a hit!
			hits++;
			if(mode == 'W')
				mem_write++;
		}
		else { //miss
			miss++;
			write_cache(set_index, tag, assoc);
			if(mode == 'R')
				mem_read++;
			else{
				mem_read++;
				mem_write++;
			}
			//prefetch
			unsigned int prefetch_address = address;
			int i=0;
			for(i=0; i<prefetch_size; i++){
				prefetch_address = prefetch_address + block_size;
				unsigned int prefetchset = (prefetch_address >> blockbits) & mask;
				unsigned long pretag = (prefetch_address >> blockbits) >> setbits;
				if(check_hit(prefetchset, pretag, assoc) == 0){ //prefetch miss
					write_cache(prefetchset, pretag,	assoc);
					mem_read++;
				}	
			}	
		}
	}
	printf("with-prefetch\n");
	printf("Memory reads: %d\n", mem_read);
	printf("Memory writes: %d\n", mem_write);
	printf("Cache hits: %d\n", hits);
	printf("Cache misses: %d\n", miss);
	int i=0;
	for(i=0; i<numSets; i++){
		free(cache[i]);
	}
	free(cache);
	return 0;
}
