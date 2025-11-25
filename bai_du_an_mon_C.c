#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX 1000

struct Date{
	int day;
	int month;
	int year;
};

struct Book{
	int bookId;
	char title[50];
	char author[50];
	int publishYear;
	int quantity;
};

struct Borrow{
	int borrowld;
	int bookId;
	struct Date borrowDate;
	struct Date borrowReturn;
	char borrowerName[50];
	int status;
};

void inputBookData(struct Book b[], int *n);
void updateBookData(struct Book b[], int n);
void outputBookData(struct Book b[], int n);
int searchBook(struct Book b[], int n, int id);                // tim kiem id sach
int titleExists(char title[], struct Book books[], int n);     // kiem tra ten sach trung nhau
int isPositiveInteger(char str[]);
int inputPositiveInt();

int main (){
	struct Book books[MAX];
	int n = 0;
	int choice;
	do{
		printf("\n=================MENU=================\n");
		printf("1. Them moi sach\n");
		printf("2. Cap nhap thong tin sach\n");
		printf("3. Hien thi danh sach sach\n");
		printf("4. Xoa thong tin sach\n");
		printf("5. Tim kiem sach\n");
		printf("6. Them moi phieu muon\n");
		printf("7. Tra sach\n");
		printf("8. Hien thi danh sach phieu muon\n");
		printf("9. Thoat\n");
		printf("======================================\n");
		printf("Moi nhap lua chon cua ban\n");
		scanf("%d", &choice);
		switch (choice){
			case 1:{
				int addBook;
				printf("nhap so luong sach muon them: ");
				scanf("%d", &addBook);
				getchar();
				
				for(int i = 0; i < addBook; i++){
					inputBookData(books, &n);
				}
				
				break;
			}
			case 2:{
				if(n == 0){
					printf("chu co sach\n");
					break;
				}
				updateBookData(books, n);
				break;
			}
			case 3:{
				if(n == 0){
					printf("chu co sach\n");
					break;
				}
				outputBookData(books, n);
				break;
			}
			case 4:{
				
				break;
			}
			case 5:{
				
				break;
			}
			case 6:{
				
				break;
			}
			case 7:{
				
				break;
			}
			case 8:{
				
				break;
			}
			case 9:{
				printf("Thoat!\n");
				break;
			}
			default :{
				
				break;
			}
		}
		
		
	}while(choice != 9);
	return 0;
}

int titleExists(char title[], struct Book books[], int n){

	for(int i = 0; i < n; i++){
		if(strcmp(books[i].title, title) == 0){
			return 1;
		}
	}
	return 0;
}

int isPositiveInteger(char str[]){
	int i = 0;
	
	while (isspace(str[i])){
		i++;
	}
	
	if(str[i] == '\0'){
		return 0;
	}
	
	if(str[i] == '+' || str[i] == '-'){
		return 0;
	}
	
	for(; str[i] != '\0'; i++){
		if(!isdigit(str[i])){                 // kiem tra ki tu co phai so nguyen khong
			return 0;
		}
	}
	return 1;
}

int inputPositiveInt(){
	char buffer[100];
	
	while (1){
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		
		if(isPositiveInteger(buffer)){
			int value = atoi(buffer);
			if(value > 0){
				return value;
			}else{
				printf("vui long nhap so nguyen duong: ");
			}
		}
		else{
			printf("nhap sai! hay nhap so nguyen duong: \n");
		}
		
	}
}

void inputBookData(struct Book b[], int *n){
	struct Book newBook;
	newBook.bookId = *n + 1;
	
	do{
		printf("nhap ten sach: ");
		fgets(newBook.title, sizeof(newBook.title), stdin);
		newBook.title[strcspn(newBook.title, "\n")] = '\0';
		if(strlen(newBook.title) == 0){
			printf("ban chua nhap du lieu nay!\n");
			continue;
		}
		if(titleExists(newBook.title, b, *n)){
			printf("ten sach da ton tai. Nhap lai\n");
			continue;
		}
		break;
	}while (1);
	
	do{
		printf("nhap ten tac gia: ");
		fgets(newBook.author, sizeof(newBook.author), stdin);
		newBook.author[strcspn(newBook.author, "\n")] = '\0';
		if(strlen(newBook.author) == 0){
			printf("ban chua nhap du lieu nay!\n");
			
		}
	}while (strlen(newBook.author) == 0);
	
	do{
		printf("nhap nam xuat ban (>1900): ");
		
		newBook.publishYear = inputPositiveInt();
		if(newBook.publishYear <= 1900 ){
			printf("phai lon hon 1900\n");
			
		}else{
			break;
		}
	}while (1);
	
	do{
		printf("nhap so luong: ");
		
		newBook.quantity = inputPositiveInt();
		if(newBook.quantity <= 0){
			printf("phai lon hon 0\n");
			
		}else{
			break;
		}
	}while (1);
	
	
	b[*n] = newBook;;
	(*n)++;
	printf("them thanh cong\n");
}

int searchBook(struct Book b[], int n, int id){
	for(int i = 0; i < n; i++){
		if(b[i].bookId == id){
			return i;
		}
	}
	return -1;
}

void updateBookData(struct Book b[], int n){
	int id;
	printf("Nhap ID cua sach can sua: ");
	scanf("%d", &id);
	int index = searchBook(b, n, id);
	
	if(index == -1){
		printf("khong tim thay sach co ID %d\n", id);
		return;
	}
	getchar();
	do{
		printf("nhap ten sach: ");
		fgets(b[index].title, sizeof(b[index].title), stdin);
		b[index].title[strcspn(b[index].title, "\n")] = '\0';
		if(strlen(b[index].title) == 0){
			printf("ban chua nhap du lieu nay!\n");
			continue;
		}
		int duplicate = 0;
		for(int i = 0; i < n; i++){
			if(i != index && strcmp(b[i].title, b[index].title) == 0){
				duplicate = 1;
				break;
			}
		}
		if(duplicate){
			printf("Ten sach da ton tai. Nhap lai\n");
		}else{
			break;
		}
	}while (1);
	
	do{
		printf("nhap ten tac gia: ");
		fgets(b[index].author, sizeof(b[index].author), stdin);
		b[index].author[strcspn(b[index].author, "\n")] = '\0';
		if(strlen(b[index].author) == 0){
			printf("ban chua nhap du lieu nay!\n");
			
		}
	}while (strlen(b[index].author) == 0);
	
	do{
		printf("nhap nam xuat ban: ");
		
		b[index].publishYear = inputPositiveInt();
		if(b[index].publishYear <= 1900 || b[index].publishYear >= 2027){
			printf("phai lon hon 1900\n");
			
		}else{
			break;
		}
	}while (1);
	
	do{
		printf("nhap so luong: ");
		
		b[index].quantity = inputPositiveInt();
		if(b[index].quantity <= 0){
			printf("phai lon hon 0\n");
		}else{
			break;
		}
	}while (1);
	
	printf("Cap nhat sach thanh cong\n");
}

void outputBookData(struct Book b[], int n){
	
	printf("+---+------------------------------+--------------------+-----+--------+\n");
	printf("|%-3s|%-30s|%-20s|%-5s|%-8s|\n", "ID", "Tieu De", "Tac Gia", "Nam", "So Luong");
	printf("+---+------------------------------+--------------------+-----+--------+\n");
	for(int i = 0; i < n; i++){
		printf("|%-3d|%-30s|%-20s|%-5d|%-8d|\n", b[i].bookId, b[i].title, b[i].author, b[i].publishYear, b[i].quantity);
	}
	printf("+---+------------------------------+--------------------+-----+--------+\n");
}


