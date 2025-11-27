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
	int borrowId;
	int bookId;
	struct Date borrowDate;
	struct Date borrowReturn;
	char borrowerName[50];
	int status;
};

int generateId();  // ham tu tang id
void toLowerCase(char *str);                                   // ham  chuyen chu hoa thanh chu thuong
void inputBookData(struct Book b[], int *n);
void updateBookData(struct Book b[], int n);
void outputBookData(struct Book b[], int n);
int searchBook(struct Book b[], int n, int id);                // tim kiem id sach
int titleExists(char title[], struct Book books[], int n);     // kiem tra ten sach trung nhau
int isPositiveInteger(char str[]);                             // kiem tra so nguyen bang truoi
int inputPositiveInt();                                        // nhap truoi de kiem tra so nguyen
int isValidString(const char s[]);                             // kiem tra rong cua chuoi
int addBorrow(struct Borrow borrows[], int *m, struct Book books[], int n);
int isBookBeingBorrowed(struct Borrow borrows[], int m, int bookId);
int deleteBook(struct Book books[], int *n, struct Borrow borrows[], int m);
void searchBookByTitle(struct Book books[], int n);

int main (){
	struct Book books[MAX];
	int n = 0;
	struct Borrow borrows[MAX];
	int m = 0;
	
	int choice;
	char buffer[100];
	do{
		printf("\n|=================MENU=================|\n");
		printf("|1. Them moi sach                      |\n");
		printf("|2. Cap nhap thong tin sach            |\n");
		printf("|3. Hien thi danh sach sach            |\n");
		printf("|4. Xoa thong tin sach                 |\n");
		printf("|5. Tim kiem sach                      |\n");
		printf("|6. Them moi phieu muon                |\n");
		printf("|7. Tra sach                           |\n");
		printf("|8. Hien thi danh sach phieu muon      |\n");
		printf("|9. Thoat                              |\n");
		printf("|======================================|\n");
		
		while (1){
		fflush(stdin);
		printf("Moi nhap lua chon cua ban\n");
		
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		
		if(!isPositiveInteger(buffer)){
			printf("Loi! Chi duoc nhap so 1-9 \n");
			continue;
		}
		choice = atoi(buffer);
		break;
	    }
		
		switch (choice){
			case 1:{
				char bufferr[100];
				int addBook;

				while (1) {
                    printf("Nhap so luong sach muon them: ");
                    fgets(buffer, sizeof(buffer), stdin);
                    int ok = 1;
                    for (int i = 0; buffer[i] != '\0' && buffer[i] != '\n'; i++) {
                        if (!isdigit((unsigned char)buffer[i])) {
                            ok = 0;
                            break;
                        }
                    }

                    if (ok) {
                        addBook = atoi(buffer);
                        if (addBook > 0) break;  
                    }

                    printf("Hay nhap so nguyen duong!\n");
                }
			
				if(addBook + n > MAX){
					printf("so luong sach da day \n");
					break;
				}
				
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
				if(n == 0){
					printf("chu co sach de xoa\n");
					break;
				}
				
				deleteBook(books, &n, borrows, m);
				break;
			}
			case 5:{
				if(n == 0){
					printf("chu co sach de xoa\n");
					break;
				}
				
				searchBookByTitle(books, n);
				break;
			}
			case 6:{
				if(n == 0){
					printf("chu co sach de muon\n");
					break;
				}
				
				if(addBorrow(borrows, &m, books, n) == 0){
					printf("them phieu that bai!\n");
				}
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
				printf("Lua chon khong hop le\n");
				break;
			}
		}
		
		
	}while(choice != 9);
	return 0;
}

int generateId(){
	static int id = 1;
	return id++;
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
	str[strcspn(str, "\n")] ='\0';
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
	newBook.bookId = generateId();
	
	do{
		
		printf("nhap ten sach: ");
		fgets(newBook.title, sizeof(newBook.title), stdin);
		newBook.title[strcspn(newBook.title, "\n")] = '\0';
		if (!isValidString(newBook.title)){
			printf("Loi! khong nhap khoang trang va phai nhap 2 ki tu lien nhau tro len.\n");
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
		if (!isValidString(newBook.author)){
			printf("Loi! khong nhap khoang trang va phai nhap 2 ki tu lien nhau tro len\n");
			continue;
	    }
	    break;

	}while (1);
	
	do{
		printf("nhap nam xuat ban (>1900): ");
		
		newBook.publishYear = inputPositiveInt();
		if(newBook.publishYear <= 1900 || newBook.publishYear >=2027){
			printf("phai lon hon 1900 va nho hon 2027\n");
			
		}  
	}while (newBook.publishYear <= 1900 || newBook.publishYear >=2027);
	
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
	char buffer[100];
	int id;
	
	while (1){
		fflush(stdin);
		printf("Nhap ID cua sach can sua: ");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		
		if(!isPositiveInteger(buffer)){
			printf("ID ko hop le! \n");
			continue;
		}
		id = atoi(buffer);
		break;
	}
	
	int index = searchBook(b, n, id);
	
	if(index == -1){
		printf("khong tim thay sach co ID %d\n", id);
		return;
	}
	
	do{
		printf("nhap ten sach: ");
		fgets(b[index].title, sizeof(b[index].title), stdin);
		b[index].title[strcspn(b[index].title, "\n")] = '\0';
		if (!isValidString(b[index].title)){
			printf("Loi! khong nhap khoang trang va phai nhap 2 ki tu lien nhau tro len\n");
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
		if (!isValidString(b[index].author)){
			printf("Loi! khong nhap khoang trang va phai nhap 2 ki tu lien nhau tro len\n");
			continue;
	    }
		break;

	}while (1);
	
	do{
		printf("nhap nam xuat ban (> 1900): ");
		
		b[index].publishYear = inputPositiveInt();
		if(b[index].publishYear <= 1900 || b[index].publishYear >= 2027){
			printf("phai lon hon 1900 va nho hon 2027\n");
			
		} 
	}while (b[index].publishYear <= 1900 || b[index].publishYear >= 2027);
	
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
	int pageNumber = 1;
    int pageSize = 2;
    int choicePage;
    char input[100];
    int totalPage = (n + pageSize - 1) / pageSize;
    
    
    do{
    	
        int start = (pageNumber-1)*pageSize;
        int end = start + pageSize;
        printf("Trang %d/%d: \n", pageNumber, totalPage);
	    printf("+---+------------------------------+--------------------+-----+--------+\n");
	    printf("|%-3s|%-30s|%-20s|%-5s|%-8s|\n", "ID", "Tieu De", "Tac Gia", "Nam", "So Luong");
	    printf("+---+------------------------------+--------------------+-----+--------+\n");
	    if(end > n){
	    	end = n;
		}
	    for(int i = start; i < end; i++){
		    printf("|%-3d|%-30s|%-20s|%-5d|%-8d|\n", b[i].bookId, b[i].title, b[i].author, b[i].publishYear, b[i].quantity);
	    }
	    printf("+---+------------------------------+--------------------+-----+--------+\n");
	    
	    printf("Lua chon:\n");
	    if(pageNumber > 1){
	    	printf("1. Quay lai trang truoc\n");
	    	printf("2. Thoat ra menu\n");
		}
		if(pageNumber < totalPage){
			printf("3. Chuyen sang trang tiep\n");
			printf("2. Thoat ra menu\n");
		}
		
		do{
			
			printf("Nhap lua chon (1-3): ");
			if(!fgets(input, sizeof(input), stdin)){
				continue;
			}
			input[strcspn(input, "\n")] = '\0';
			if(strlen(input) == 0){
				printf("Khong duoc de trong. Nhap lai!\n");
				continue;
			}
			
			if(!isPositiveInteger(input)){
				printf("Nhap khong hop le! Chi nhap so nguyen\n");
				continue;
			}
			choicePage = atoi(input);
			if(choicePage < 1 || choicePage > 3){
				printf("Nhap khong hop le. Nhap lai(1-3)\n");
				continue;
			}
			break;
		}while (1);
		
		if(choicePage == 1 && pageNumber > 1){
			pageNumber--;
		}else if(choicePage == 3 && pageNumber < totalPage){
			pageNumber++;
		}else if(choicePage == 2){
			break;
		}
    } while (1);
}
// const khong cho phep sua doi noi dung trong chuoi
// unsigned char de dam bao chi nhan gia tri tu 0 - 255 1 cach an toan nhat
int isValidString(const char s[]) {
    int len = strlen(s);

    if(len == 0){
    	return 0;
	}

    if(isspace((unsigned char)s[0])){
    	return 0;
	}

    int consecutiveLetters = 0;       // dem so chu cai lien tiep nhau
    int hasLetter = 0;           
    for(int i = 0; i < len; i++) {
        unsigned char c = (unsigned char)s[i];

        if(!isalpha(c) && !isspace(c)) {
            return 0;
        }

        if(isalpha(c)) {
            hasLetter = 1;
            consecutiveLetters++;
            if(consecutiveLetters >= 2) {
                break;
            }
        } else {
            consecutiveLetters = 0; 
        }
    }

    if(!hasLetter){
    	return 0;
	}              
    if(consecutiveLetters < 2) {
    	return 0; 
	}   

    return 1; 
}

int addBorrow(struct Borrow borrows[], int *m, struct Book books[], int n){
	if(*m >= MAX){
		printf("Them phieu muon that bai! Dach da day\n");
		return 0;
	}
	
	struct Borrow br;
	char buffer[100];
	
	br.borrowId = generateId();
	
	int id;
	while (1){
		printf("nhap bookId: ");
		fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        
        if(!isPositiveInteger(buffer)){
        	printf("Loi! Chi nhap so nguyen duong\n");
        	continue;
		}
		id = atoi(buffer);
		int pos = searchBook(books, n, id);
		
		if(pos == -1){
			printf("Khong co sach co ID = %d. Nhap lai\n", id);
			continue;
		}
		
		if(books[pos].quantity <= 0){
			printf("sach het hang! khong the muon\n");
			return 0;
		}
		
		br.bookId = id;
		break;
	}
	
	// Nhap ngay muon
    printf("Nhap ngay muon: ");
    br.borrowDate.day = inputPositiveInt();

    printf("Nhap thang muon: ");
    br.borrowDate.month = inputPositiveInt();

    printf("Nhap nam muon: ");
    br.borrowDate.year = inputPositiveInt();

    // nhap ngay tra
    printf("Nhap ngay tra: ");
    br.borrowReturn.day = inputPositiveInt();

    printf("Nhap thang tra: ");
    br.borrowReturn.month = inputPositiveInt();

    printf("Nhap nam tra: ");
    br.borrowReturn.year = inputPositiveInt();
    
    do{
    	printf("Nhap ten nguoi muon: ");
        fgets(br.borrowerName, sizeof(br.borrowerName), stdin);
        br.borrowerName[strcspn(br.borrowerName, "\n")] = '\0';

        if (!isValidString(br.borrowerName)) {
            printf("Ten khong duoc de trong va phai nhap 2 ki tu lien nhau tro len! Nhap lai!\n");
            continue;
        }
        break;
	}while (1);
	
	int bookIndex = searchBook(books, n, br.bookId);
	books[bookIndex].quantity--;
	
	br.status = 1;
	
	borrows[*m] = br;
	(*m)++;
	
	printf("Them phieu muon thanh cong\n");
	return 1;
}

// kiem tra muon sach
int isBookBeingBorrowed(struct Borrow borrows[], int m, int bookId){
	for(int i = 0; i < m; i++){
		if(borrows[i].bookId == bookId && borrows[i].status == 1){
			return 1;    // duoc muon
		}
	}
	return 0;            // ko muon
}

int deleteBook(struct Book books[], int *n, struct Borrow borrows[], int m){
	char buffer[100];
	int id;
	
	do{
		printf("Nhap ID sach can xoa: ");
		fgets(buffer, sizeof(buffer), stdin);
		buffer[strcspn(buffer, "\n")] = '\0';
		
		if(!isPositiveInteger(buffer)){
			printf("ID khong hop le! Nhap lai(so nguyen)\n");
			continue;
		}
		id = atoi(buffer);
		break;	
	}while (1);
	
	int index = searchBook(books, *n, id);
	if(index == -1){
		printf("Khong tim thay sach co ID %d\n", id);
		printf("Xoa sach that bai!\n");
		return 0;
	}
	
	if(isBookBeingBorrowed(borrows, m, id)){
		printf("Khong the xoa sach vi co nguoi dang muon!\n");
        printf("Xoa sach that bai!\n");
        return 0;
	}
	
	for(int i = index; i < *n - 1; i++){
		books[i] = books[i + 1];
	}
	(*n)--;
	printf("Xoa sach thanh cong!\n");
	return 1;
}

void toLowerCase(char *str){             // chuyen chu hoa thanh chu thuong
	for(int i = 0; str[i]; i++){
		str[i] = tolower((unsigned char) str[i]);
	}
}

void searchBookByTitle(struct Book books[], int n){
	char key[100];
	
	do{
		printf("Nhap ten sach muon tim: ");
		fgets(key, sizeof(key), stdin);
		key[strcspn(key, "\n")] = '\0';
		
		if(strlen(key) == 0){
			printf("Khong duoc de trong! Nhap lai\n");
			continue;
		}
		
		if(!isValidString(key)){
			printf("Loi! khong nhap full khoang trang va ki tu khong hop le\n");
			continue;
		}
		break;
	}while (1);
	
	char searchKey[100];
	strcpy(searchKey, key);
	toLowerCase(searchKey);
	
	int found = 0;
	
	printf("\nKet qua tim kiem:\n");
    printf("+---+------------------------------+--------------------+-----+--------+\n");
    printf("|%-3s|%-30s|%-20s|%-5s|%-8s|\n", "ID", "Tieu De", "Tac Gia", "Nam", "So Luong");
    printf("+---+------------------------------+--------------------+-----+--------+\n");
    
    for(int i = 0; i < n; i++){
    	char titleLower[100];
    	strcpy(titleLower, books[i].title);
    	toLowerCase(titleLower);
    	
    	if(strstr(titleLower, searchKey) != NULL){
    		printf("|%-3d|%-30s|%-20s|%-5d|%-8d|\n",books[i].bookId, books[i].title, books[i].author, books[i].publishYear, books[i].quantity);
    		found = 1;
		}
	}
	printf("+---+------------------------------+--------------------+-----+--------+\n");
	
	if(!found){
		printf("Khong tim thay ten sach phu hop\n");
	}
}
