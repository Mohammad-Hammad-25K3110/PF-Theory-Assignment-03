#include <stdio.h>
#include <string.h>

struct Book{
	int id;
	int popularityScore;
};

struct Shelf{
	struct Book books[100]; // Maximum number of books = 100
    int order[100];
    int size;
    int capacity;
};

void addBook(struct Shelf *shelf, int id, int popularity){
	int found = 0;
	for(int i = 0; i < shelf->size; i++){
		if(shelf->books[shelf->order[i]].id == id){
			shelf->books[shelf->order[i]].popularityScore = popularity;
			for(int j = i; j < shelf->size - 1; j++){
				shelf->order[j] = shelf->order[j+1];
			}
			shelf->order[shelf->size - 1] = i;
            found = 1;
            break;
		}
	}
	if(!found){
        if(shelf->size < shelf->capacity){
            shelf->books[shelf->size].id = id;
            shelf->books[shelf->size].popularityScore = popularity;
            shelf->order[shelf->size] = shelf->size;
            shelf->size++;
        }
        else{
            for(int i = 0; i < shelf->size - 1; i++){
                shelf->order[i] = shelf->order[i + 1];
            }
            shelf->books[shelf->size].id = id;
            shelf->books[shelf->size].popularityScore = popularity;
            shelf->order[shelf->size] = shelf->size;
        }
    }
}

int accessBook(struct Shelf *shelf, int id) {
    for (int i = 0; i < shelf->size; i++) {
        if (shelf->books[shelf->order[i]].id == id) {
            for (int j = i; j < shelf->size - 1; j++) {
                shelf->order[j] = shelf->order[j + 1];
            }
            return shelf->books[shelf->order[i]].popularityScore;
        }
    }
	return -1;
}


int main(){
	int capacity, Q;
	printf("Enter Capacity of Shelf : ");
    scanf("%d", &capacity);
    printf("Enter Number of Operations : ");
    scanf("%d", &Q);
    struct Shelf shelf;
    shelf.size = 0;
    shelf.capacity = capacity;
    for (int i = 0; i < Q; i++){
        char operation[10];
        int x, y;
        printf("Enter operation : ");
        scanf("%s", operation);
        if (strcmp(operation, "ADD") == 0){
        	printf("Enter Book ID : ");
            scanf("%d", &x);
            printf("Enter Popularity Score : ");
            scanf("%d", &y);
            addBook(&shelf, x, y);
		}
        else if (strcmp(operation, "ACCESS") == 0){
            printf("Enter Book ID : ");
			scanf("%d", &x);
            int popularity = accessBook(&shelf, x);
            if(popularity == -1){
            	printf("-1\n");
			}
			else{
				printf("Popularity Score : %d", popularity);
			}
        }
    }
    return 0;
}
