#include<stdio.h>
#include<stdlib.h>
#include<math.h>

typedef struct node {
	int hash;
	float latitude,longitude,temperature;
	struct node * next;
} node_t;


void add_end(node_t * head, int hash,float latitude,float longitude,float temperature)
{
	node_t * current = head;
	while (current->next != NULL)
	{
		current = current->next;
	}

	current->next = malloc(sizeof(node_t));
	current->next->hash = hash;
	current->next->latitude = latitude;
	current->next->longitude = longitude;
	current->next->temperature = temperature;
	current->next->next = NULL;
}


int main(){
	
	char line[99];
	float latitude,longitude,temperature;
	node_t * head;
	int temp,hash[2000],i=0;


	FILE * file;
file = fopen( "veri.txt" , "r");
if (file) {
    while (fscanf(file, "%[^\n]%*c", line)!=EOF){
	

		sscanf(line, "%f %f %f", &latitude, &longitude, &temperature);
		
		// hash fonksiyonu
        temp = latitude * 1e6 + longitude * 1e6; 
		hash[i]= ((int)abs(temp)) % 1085;
		
		
		
		
		// sadece ilk baðlý liste düðümünü oluþturur
		if(i==0){
				head = malloc(sizeof(node_t));	
		head->hash = hash[i];
	head->latitude = latitude;
	head->longitude = longitude;
	head->temperature = temperature;
	head->next = NULL;
		}
		
		// kalan bütün düðümler burada baðlý listenin sonuna eklenir
		else{
		add_end(head, hash[i],latitude,longitude,temperature);
		}
		
		i=i+1;
		}
     }
	fclose(file);

	


// hash sýralama
int n=sizeof(hash)/sizeof(hash[0]);
 int  j;
 for (i = 0; i < (2000 - 1); ++i)
 {
      for (j = 0; j < 2000 - 1 - i; ++j )
      {
           if (hash[j] > hash[j+1])
           {
                temp =hash[j+1];
                hash[j+1] = hash[j];
                hash[j] = temp;
           }
      }
 }



//for(i=0;i<2000;i++){
//printf("%d  ",hash[i]);}	
	 


// hash deðeri minimum olan düðümdeki elemanlarý yazdýrýr
	node_t * current = head;
	while (current != NULL) {
		if(current->hash==hash[0])  // hash deðeri 0 olan iki eleman var.
		{
			printf("minimum hash degerine sahip dugumun elemanlari: ");
			printf("%f ", current->latitude);
			printf("%f ", current->longitude);
			printf("%f ", current->temperature);
			printf("hash=%d\n", current->hash); 
		}
		current = current->next; 	}



	return 0;
}
