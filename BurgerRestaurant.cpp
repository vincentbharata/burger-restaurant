#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 50
#define LENGTH 100

struct Burger{
	char name[LENGTH];
	char portion[LENGTH];
	int price;
}*bucket[SIZE];

int count = 0;

void init(){
	for(int i=0;i<SIZE;i++){
		bucket[i] = NULL;
	}
}

struct Burger* new_node(char name[], char portion[], int price){
	struct Burger* toinsert = (struct Burger*) malloc (sizeof(struct Burger));
	strcpy(toinsert->name, name);
	strcpy(toinsert->portion, portion);
	toinsert->price = price;
	return toinsert;
}

int hash_function(char name[]){
	int key = 0;
	for(int i=0;i<strlen(name);i++){
		key += i;
	}
	return key % SIZE;
}

struct Burger* search(char name[]){
	int hash_key = hash_function(name);
	int pos = hash_key;
	
	do{
		if(bucket[pos] && strcmp(bucket[pos]->name, name) == 0){
			return bucket[pos];
		} else{
			return 0;
		}
		
		pos = (pos + 1) % SIZE;
	}while(pos != hash_key);
}

void insert(char name[], char portion[], int price){
	int hash_key = hash_function(name);
	int pos = hash_key;
	
	//BUCKET FULL
	if(count == SIZE){
		printf("BUCKET FULL\n");
		
	}
	//COLLISION
	while(bucket[pos]){
		pos = (pos + 1) % SIZE;
	}
	
	//BUCKET YG DIMASUKIN KOSONG
	bucket[pos] = new_node(name, portion, price);
	count++;
}



int startsWith(char a[], char b[]){
	if(strncmp(a,b, strlen(b)) == 0){
		return 1;	
	} else {
		return 0;
	}
}

int chekName(char name[]){
	int i = 0;
	int count = 0;
	while(name[i] != '\n'){
		if(name[i] == ' '){
			count++;
		}
		i++;
	}
	if(count >= 1 && name[0] != ' '){
		return 1;
	} else {
		return 0;
	}
}

void insertBurger(){
	char name[LENGTH];
	char portion[LENGTH];
	int price;
	
	do{
		printf("Input Name : ");
		scanf("%[^\n]", name);
		getchar();
	}while(startsWith(name, "Burger") == 0 || chekName(name) == 0 || strlen(name) < 15);
	
	do{
		printf("Input Portion : ");
		scanf("%[^\n]", portion);
		getchar();
	}while(strcmp(portion, "Large") != 0 && strcmp(portion, "Regular") != 0);
	
	do{
		printf("Input Price : ");
		scanf("%d", &price);
		getchar();
	}while(price < 5000 || price > 10000);
	
	insert(name, portion, price);
}

void viewBurger(){
	printf("\n\nBurger SUNIB\n");
	for(int i=0;i<SIZE;i++){
		if(bucket[i]){
			printf("=============================\n");
			printf("Name : %s\n", bucket[i]->name);
			printf("Portion : %s\n", bucket[i]->portion);
			printf("Price : %d\n", bucket[i]->price);
			printf("=============================");
		}
	}
}

void deleteBurger(char name[]){
	int hash_key = hash_function(name);
	int pos = hash_key;
	
	do{
		if(bucket[pos] && strcmp(bucket[pos]->name, name) == 0){
			free(bucket[pos]);
			bucket[pos] = NULL;
			return;
		}
		
		pos = (pos + 1) % SIZE;
	}while(pos != hash_key);
}

void updatBurger(char search_name[]){
	char name[LENGTH];
	char portion[LENGTH];
	int price;
	
	struct Burger* toSearch = search(search_name);
	if(toSearch != NULL){
	do{
		printf("Input Name : ");
		scanf("%[^\n]", name);
		getchar();
	}while(startsWith(name, "Burger") == 0 || chekName(name) == 0 || strlen(name) < 15);
	
	do{
		printf("Input Portion : ");
		scanf("%[^\n]", portion);
		getchar();
	}while(strcmp(portion, "Large") != 0 && strcmp(portion, "Regular") != 0);
	
	do{
		printf("Input Price : ");
		scanf("%d", &price);
		getchar();
	}while(price < 5000 || price > 10000);
	
	strcpy(toSearch->name, name);
	strcpy(toSearch->portion, portion);
	toSearch->price = price;
	} else{
		printf("Burger Not Found!\n");
	}
}

int main(){
	
	int menu = 0;
	init();
	do{
		printf("Burger SUNIB\n");
		printf("1. Insert\n");
		printf("2. Delete\n");
		printf("3. Update\n");
		printf("4. Exit\n");
		
		printf(">> ");
		scanf("%d", &menu);
		getchar();
		
		if(menu == 1){
			insertBurger();
			viewBurger();
		}else if (menu == 2){
			char name[LENGTH];
			printf("Input name to delete: ");
			scanf("%[^\n]", name);
			getchar();
			
			deleteBurger(name);
			viewBurger();
		}else if (menu == 3){
			char name[LENGTH];
			printf("Input name to be update: ");
			scanf("%[^\n]", name);
			getchar();
			
			search(name);
			viewBurger();
		}
	}while(menu != 4);
	
	return 0;
}
