#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#pragma warning (disable:4996)

//CONSTANTS
#define MAX_STAFF 50 //MAXIMUM NUMBER OF RECORDS PERMITTED
#define MAX_BOOKINGS 100
#define MAX_SCHEDULE 50
#define MAX_MEMBERS 100
#define MAX_LENGTH 50

typedef struct {
	int yr, mth, day;
}date;

struct staffDetail {
	char id[10], name[51], password[15];
	int rpin;
	date dateEmp;
	char email[51], department[38];
};

struct report {
	char action[55];
	char name[30];
};

struct Booking {
	char passenger_name[56];
	char booking_id[10];
	char bookingID;
	int booking_no;
	char member_id[10];
	char train_id[10];
	char booking_date[20];
	char seat_number[5];
	char coach;
	int  quantity;
	char payment_info[20];
	double amount;
};

typedef struct {
	double deparTime, arrivTime, tickeTime, price;
	char destination[51], trainID[51], departure[51];
	int day, month, year;
}TimeSchedule;

typedef struct {
	char username[MAX_LENGTH];
	char password[MAX_LENGTH];
	char email[MAX_LENGTH];
	char contactNum[MAX_LENGTH];
	char icNum[MAX_LENGTH];
	char mID[MAX_LENGTH];
	int loyaltyPoints;
} Member;


////////////////////////////////// Function prototype /////////////////////////////////
void menu();

//ADMIN - TanJinYuan
void staffCreate();
void staffEdit();
void staffDelete();
void staffLog();
void staffDisplay();
void staffSearch();
void writelog(char action[], char name[]);
int staffEdit2(struct staffDetail allStf[], int index, int recCount);
void staffMain();

//SCHEDULE - KerZhengFeng
void choiceSelect();
void writeRecord();
void readRecord();
void editSchedule();
void searchTrain();
void deleteSchedule();
void scheduleReport();

//MEMBER - GanKaChun
int login(Member members[], int numMembers, int* loggedInIndex);
void changeInfo(Member* member);
int saveMembers(Member members[], int numMembers);
void addMember(Member members[], int* numMembers);
int userpage(Member members[], int numMembers, int* loggedInIndex);
void memberMain();
int deleteAccount(Member members[], int* numMembers, int* loggedInIndex);
int searchMember(Member members[], int numMembers, int* loggedIndex);
int displayMember(Member members[], int numMembers, int* loggedInIndex);
int loyalty(Member members[], int numMembers, int* loggedInIndex);
int check(Member members[], int numMembers, int* loggedInIndex);
void header();
void edit();
void regis();



//BOOKING - Patricia
void  bookingMENU();
void  addBooking();
void  updateBooking();
void  searchBooking();
void  displayBooking();
void  cancelBooking();
void  reportBooking();
int isValidSeatNumber(const char* seat_number);
char* generateBookingID();
char* timeF();

//////////////////////////////////////////////////////////////////////////////////////////

void main() {
	menu();
}

/// GENERAL MENU
void menu() {
	int choice = 0; ///initialise
	do {
		system("cls");
		if (choice == -1){
			printf("Invalid Selection! Try again.\n\n");
		}
		printf("===============================================================================\n"
			"_____  ___  _____ __ _____ _____ __ __   __ _____ _____ _____   __\n"
			"||_// ||=|| ||_// || ||  ) ||==  ||<<   ((  ||_// ||_// ||==   ((\n"
			"|| \\\\ || || ||    || ||_// ||___ || \\\\ \\_)) ||    || \\\\ ||___ \\_))\n\n"
			"===============================================================================\n");
		printf("Welcome to RapidEkspres! Choose a Function\n\n");
		printf("1. Staff\n");
		printf("2. Member\n");
		printf("3. Booking\n");
		printf("4. Scheduling\n");
		printf("5. Exit Program\n\n--> ");
		
		rewind(stdin);
		scanf("%d", &choice);
		if (choice == 1) {
			printf("You chose Staff.\n");
			staffMain();
		}
		else if (choice == 2) {
			printf("You chose Member.\n");
			system("pause");
			memberMain();
		}
		else if (choice == 3) {
			printf("You chose Booking.\n");
			system("pause"); 
			bookingMENU(); 
		}
		else if (choice == 4) {
			printf("You chose Scheduling.\n");
			choiceSelect();
		}
		else if (choice == 5) {
			printf("Exiting...\n");
		}
		else {
			choice = -1; //Invalid
		}

	} while (choice != 5);
	system("pause");
}

///////////////// STAFF ////////////////////
void staffMain() {
	int choice = 0,otp = 0;
	printf("Enter admin PIN to continue: ");
	rewind(stdin);
	scanf("%d",&otp);
	if (otp != 8888) {
		printf("Access is denied.\n");
		system("pause");
		return;
	}
	
	do {
		system("cls");
		if(choice == -1)
			printf("Invalid Selection! Try again.\n\n");

		printf("============================\n");
		printf("\tStaff Menu\n");
		printf("============================\n");
		printf("1. Create Staff\n");
		printf("2. View Staff Credentials (ADMIN only)\n");
		printf("3. Search for Staff\n");
		printf("4. Delete a Staff Record\n");
		printf("5. Edit Staff Details\n");
		printf("6. Check Log File\n");
		printf("\n7. RETURN TO MENU\n");
		printf("============================\n");
		printf("Your Choice: ");
		rewind(stdin);
		scanf("%d", &choice);

		if (choice == 1) {
			staffCreate();
		}
		else if (choice == 2) {
			staffDisplay();
		}
		else if (choice == 3) {
			staffSearch();
		}
		else if (choice == 4) {
			staffDelete();
		}
		else if (choice == 5) {
			staffEdit();
		}
		else if (choice == 6) {
			staffLog();
		}
		else if (choice == 7) {
			printf("Returning..\n");
			system("pause");
		}
		else {
			choice = -1; //Invalid
		}


	} while (choice !=7);
}
void staffEdit() {
	struct staffDetail stf[MAX_STAFF]; //read file
	char id[30], psw[30],pswChoice;
	int localRpin, changes = 0;
	int match = 0, kickCount = 0, index = -1, noOfRecords = 0;
	
	system("cls");
	printf("============================\n");
	printf("     Edit Staff Account\n");
	printf("============================\n");
	FILE* fedit;
	fedit = fopen("admin.dat", "rb");
	if (fedit == NULL) {
		printf("File checking failed.\n");
		system("pause");
		return;
	}
	noOfRecords = fread(&stf, sizeof(struct staffDetail), MAX_STAFF, fedit);
	fclose(fedit);
	//printf("FILE OK: There are %d staff\n\n", noOfRecords);
	printf("You must be logged in to continue.\n");
	do{
		if (kickCount >= 3) {
			printf("Multiple failed login attempts. Do you want to sign in with password recovery?\n(Y to accept, other key to exit) :");
			rewind(stdin);
			scanf("%c", &pswChoice);
			if (toupper(pswChoice) == 'Y') {
				system("cls");
				printf("====Recovery PIN Sign ON====\n");
				printf("Enter your ID followed by 4-digit RECOVERY PIN\n(e.g. A8481 8481): ");
				rewind(stdin);
				scanf("%s %d", id,&localRpin);

				for (int i = 0; i < noOfRecords; i++) {
					if (strcmp(id, stf[i].id) == 0 && (localRpin == stf[i].rpin)) {
						match = 1;
						index = i;
					}
				}
				if (match == 1) { //Signed in
					printf("Logged in as %s..",stf[index].name);
					break;
				}
				else {
					printf("Login failed. Please sign in again from main menu...");
					system("pause");
					return;
				}
			}
			else {
				printf("Exiting....");
				system("pause");
				return;
			}
		}
		printf("Enter your ID: ");
		rewind(stdin);
		scanf("%s",id);
		printf("Enter your Password: ");
		scanf("%s", psw);
		rewind(stdin);
		for (int i = 0; i < noOfRecords; i++) {
			if (strcmp(id, stf[i].id) == 0 && strcmp(psw, stf[i].password) == 0) {
				match = 1;
				index = i;
			}
		}
		if (match == 0) {
			printf("Login failed.\n\n");
		}
		kickCount++;

	} while (match == 0);

	if (index != -1) {
		changes = staffEdit2(stf,index,noOfRecords);
		if (changes) { // 1 means records are different from previous
			//REWRITE RECORDS
			fedit = fopen("admin.dat", "wb");
			if (fedit == NULL) {
				printf("Rewrite file error, process terminated\n");
			}
			else {
				for (int i = 0; i < noOfRecords; i++) {
					fwrite(&stf[i], sizeof(struct staffDetail), 1, fedit);
				}
				printf("Sucessfully saved all changes.\n");
				fclose(fedit);
				writelog("Attempted to change his/her details", stf[index].id);
			}
		}
		else {
			printf("You did not make any changes.\n");
		}
	}
	else
		printf("index error\n");
	system("pause");
}
//EDIT STAFF SUB-FUNCTION
int staffEdit2(struct staffDetail allStf[], int index, int recCount) {
	struct staffDetail oldStaff; //Stores staff details b4 change
	oldStaff = allStf[index];
	int choice = 8,invCount = 0 , temp;   //invcount to count invalid characters
	const char mths[12][5] = { "Jan","Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec"};
	
	int changed = 0; //Detects changes in records
	do{
		system("cls");
		if ( strcmp(oldStaff.department,allStf[index].department) != 0 ||
			strcmp(oldStaff.password, allStf[index].password) != 0 ||
			strcmp(oldStaff.email, allStf[index].email) != 0 ||
			oldStaff.rpin != allStf[index].rpin ||
			strcmp(oldStaff.name, allStf[index].name) != 0 ||
			oldStaff.dateEmp.day != allStf[index].dateEmp.day ||
			oldStaff.dateEmp.mth != allStf[index].dateEmp.mth ||
			oldStaff.dateEmp.yr != allStf[index].dateEmp.yr
			) {
			changed = 1;
		}
		else 
			changed = 0;

		if (choice == -1) {
			printf("Invalid choice!\n");
		}
		printf("-----------------------------------------\n");
		printf("You are logged in.....\n");
		printf("Your user details\n: %s %s --- %s\n", allStf[index].name, allStf[index].id,allStf[index].email);
		printf("Currently working in %s Dep since %d %s %d\n", allStf[index].department, allStf[index].dateEmp.day, mths[allStf[index].dateEmp.mth-1], allStf[index].dateEmp.yr);
		printf("-----------------------------------------\n");
		printf("1. Change Password and Update Recovery PIN\n");
		printf("2. Change Name\n");
		printf("3. Change Department\n");
		printf("4. Change Hire Date\n");
		printf("5. Change Email\n\n");
		printf("0. SAVE CHANGES AND EXIT\n");
		printf("\n\nNOTE: Changing of User ID is forbidden.\n--->");
		rewind(stdin);
		scanf("%d",&choice);
		switch (choice){
		case 1: //PASSWORD AND PIN
			do {
				char pinChoice;
				printf("Enter a new password: ");
				rewind(stdin);
				scanf("%s", allStf[index].password);
				if (strlen(allStf[index].password) < 5 || strlen(allStf[index].password) > 12) {
					printf("ERROR: Password should be 5-12 charcters. Try again...\n\n");
				}
				else{
					printf("You wish to change password to: ");
					printf("%c%c******\n", allStf[index].password[0], allStf[index].password[1]);
					printf("Do you wish to create a new recovery PIN? (Y/N, default to exit) :");
					rewind(stdin);
					pinChoice = getchar();
					if (toupper(pinChoice) == 'Y') {
						do {
							rewind(stdin);
							printf("Enter a 4-digit recovery pin: ");
							if (scanf("%d", &allStf[index].rpin) != 1) {
								printf("ERROR: Invalid input! Try again...\n\n");
							}
							else if(allStf[index].rpin < 0 || allStf[index].rpin > 9999){
								printf("ERROR: Invalid input! Try again...\n\n");
							}
							else {
								printf("Changed PIN to %04d\n", allStf[index].rpin);
								pinChoice = 'x';
							}
						}while (toupper(pinChoice) == 'Y');
					}
					choice = 8;
					system("pause");
				}
			} while (choice == 1);
			break;
		case 2:
		do {//Change Name
			invCount = 0;
			printf("Enter new name :");
			rewind(stdin);
			gets(allStf[index].name);

			for (int i = 0; i < strlen(allStf[index].name); i++) {
				if (isdigit(allStf[index].name[i]) != 0 || ispunct(allStf[index].name[i]) != 0) {
					invCount++;
				}
			}

			if (strlen(allStf[index].name) < 4) {
				printf("ERROR: Name too short! Try again...\n\n");
			}
			if (strlen(allStf[index].name) > 30) {
				printf("ERROR: Name too long! Try again...\n\n");
			}
			else if (invCount > 0) {
				printf("ERROR: Invalid Characters! Try again...\n\n");
			}
			else {
				printf("Sucessfully changed name.\n");
				system("pause");
				choice = 8;
			}

		} while (choice == 2);
			break;
		case 3: //DEPARTMENT
			do{
				invCount = 0;
				printf("Enter new department (e.g Finance): ");
				rewind(stdin);
				scanf("%[^\n]",allStf[index].department);
				for (int i = 0; i < strlen(allStf[index].department); i++) {
					if (isdigit(allStf[index].department[i]) != 0 || (ispunct(allStf[index].department[i]) != 0)) {
						invCount++;
					}
				}
				if (strcmp(allStf[index].department, "Administration") == 0) {
					printf("Access is denied.\n");
				}
				else if (invCount == 0 && strlen(allStf[index].department) >= 2) {
					if (strcmp(allStf[index].department, "SYSA") == 0) {
						strcpy(allStf[index].department, "Administration");
					}

					printf("You wish to change department to %s\n", allStf[index].department);
					choice = 8;
					system("pause");
				}
				else {
					printf("ERROR: Invalid Input! Try again...\n\n");
				}
			} while (choice == 3);
			break;
		case 4: //Change date
			do {
				printf("Enter new date of employment (DD/MM/YYYY) : ");
				rewind(stdin);
				temp = scanf("%d/%d/%d", &allStf[index].dateEmp.day, &allStf[index].dateEmp.mth, &allStf[index].dateEmp.yr);
				if (temp != 3) {
					printf("ERROR: Invalid Input! Try again...\n\n");
				}
				else if (allStf[index].dateEmp.day > 31 || allStf[index].dateEmp.day < 1) { //check day
					printf("ERROR: Invalid Input! Try again...\n\n");
				}
				else if (allStf[index].dateEmp.mth > 12 || allStf[index].dateEmp.mth < 1) { //check month
					printf("ERROR: Invalid Input! Try again...\n\n");
				}
				else if (allStf[index].dateEmp.yr > 2024 || allStf[index].dateEmp.yr < 1957) { //check year
					printf("ERROR: Invalid Input! Try again...\n\n");
				}
				else {
					choice = 8;
					printf("You wish to change D.O.E to %d %s %d\n", allStf[index].dateEmp.day, mths[allStf[index].dateEmp.mth - 1], allStf[index].dateEmp.yr);
					system("pause");
				}
			} while (choice == 4);
			break;
		case 5://emailllll
			do {
				int count1 = 0, count2 = 0;
				//Here, invcount is used to check for duplicate email
				invCount = 0;
				rewind(stdin);
				printf("Enter new email: ");
				scanf("%s",allStf[index].email);
				for (int a = 0; a < recCount;a++) {
					if (strcmp(allStf[index].email,allStf[a].email) == 0 && index != a)
						invCount = 1;
				}
				for (int i = 0; i < strlen(allStf[index].email); i++) {
					if (allStf[index].email[i] == '@')			//count1 check for 1 '@' character
						count1++;
					else if (allStf[index].email[i] == '.')			//count2 check for 1 '.' character
						count2++;
					//check for 1 '.' character
				}
				if ( invCount || strlen(allStf[index].email) <=5 || count1!=1 || count2 < 1 ) {
					printf("ERROR: %s\n",(invCount)?"Email is used by someone else!":"Invalid email! Try again...");
				}
				else {
					choice = 8;
					printf("You wish to change email to %s.\n", allStf[index].email);
					system("pause");
				}
				
			} while (choice == 5);
			break;
		case 0:
			printf("Exiting..\n\n");
			break;
		default:
			choice = -1;
		}

	} while (choice !=0);

	return changed;
}
void staffCreate() {
	system("cls");
	struct staffDetail staff = { "" }; //No array needed for add
	struct staffDetail stf[MAX_STAFF]; //THIS IS FOR VALIDATION TO PREVENT DUPLICATE RECORD,

	int validatePass = 0, invCount, noOfRecords = 0,duplicate = 0;
	printf("============================\n");
	printf("Register a Staff Account\n");
	printf("============================\n");
	printf("NOTE: Changing of Staff ID is prohibited after to prevent spoof records\n\n");
	//NOTE : validatePass is 0 when data validation failed



	//Check if file records are over the limit
	FILE* fcheck;
	fcheck = fopen("admin.dat", "rb");
	if (fcheck == NULL) {
		printf("File Checking failed..Assuming creating new file\n");
		system("pause");
	}
	else {
		noOfRecords = fread(&stf, sizeof(struct staffDetail), MAX_STAFF, fcheck);
		if (noOfRecords >= MAX_STAFF) {
			printf("There are too many records (%d). Please delete some before continuing.\n",noOfRecords);
			system("pause");
			return;
		}
		else {
			printf("No of records: %d\n",noOfRecords); //FOR DEBUGGING
		}
		fclose(fcheck);
	}

	//Get ID
	do {
		rewind(stdin);
		invCount = 0; duplicate = 0;
		int intCount = 0;

		printf("Enter X to exit, or enter your staff ID to continue(e.g.: A0001): ");
		scanf("%6s", staff.id);
		for (int i = 0; i < strlen(staff.id); i++) {
			if (ispunct(staff.id[i]) != 0)
				invCount++;
			else if (isdigit(staff.id[i]) != 0)
				intCount++;
		}
		for (int i = 0; i < noOfRecords; i++) {
			if (strcmp(staff.id, stf[i].id) == 0)
				duplicate = 1;
		}


		if (toupper(staff.id[0]) == 'X' || strlen(staff.id) == 1) {
			printf("Exiting.....");
			system("pause");
			fclose(fcheck);
			return;
		}
		else if (duplicate) {
			printf("ERROR: ID already exists! \n\n");
		}

		else if (staff.id[0] != 'A') {  //All staff ids must start with A
			printf("ERROR: Your staff id should be in the format 'Axxxx'\n\n");
		}
		else if (strlen(staff.id) < 5) {
			printf("ERROR: Your staff id should be in the format 'Axxxx'\n\n");
		}
		else if (invCount > 0 || intCount != 4) {
			printf("ERROR: Invalid input! Try again...\n\n");
		}
		else {
			validatePass = 1;
		}
	} while (validatePass == 0);


	//Get Name
	do {
		validatePass = 0;
		invCount = 0;//invcount to count invalid characters

		printf("Enter staff full name :");
		rewind(stdin);
		gets(staff.name);

		for (int i = 0; i < strlen(staff.name); i++) {
			if (isdigit(staff.name[i]) != 0) {
				invCount++;
			}
			else if (ispunct(staff.name[i]) != 0)
				invCount++;
		}

		if (strlen(staff.name) < 4) {
			printf("ERROR: Name too short! Try again...\n\n");
		}
		if (strlen(staff.name) > 30) {
			printf("ERROR: Name too long! Try again...\n\n");
		}
		else if (invCount > 0) {
			printf("ERROR: Invalid Characters! Try again...\n\n");
		}
		else {
			validatePass = 1;
		}

	} while (validatePass == 0);

	//Get Password
	do
	{
		validatePass = 0;

		printf("Enter a suitable password: ");
		rewind(stdin);
		scanf("%s", staff.password);

		if (strlen(staff.password) < 5 || strlen(staff.password) > 12) {
			printf("ERROR: Password should be 5-12 charcters. Try again...\n\n");
		}
		else {
			validatePass = 1;
		}

	} while (validatePass == 0);

	//Recovery Pin 
	do
	{
		validatePass = 0;
		rewind(stdin);
		printf("Enter a 4-digit recovery pin: ");
		if (scanf("%d", &staff.rpin) != 1) {
			printf("ERROR: Invalid input! Try again...\n\n");
		}
		else if (staff.rpin > 9999 || staff.rpin < 0) { //Invalid range
			printf("ERROR: Please CREATE another PIN. \n\n");
		}
		else
		{
			validatePass = 1;
		}

	} while (validatePass == 0);

	//Date of employment
	int temp; //Validates date input

	do {
		validatePass = 0;
		printf("Enter your date of employment (DD/MM/YYYY) : ");
		rewind(stdin);
		temp = scanf("%d/%d/%d", &staff.dateEmp.day, &staff.dateEmp.mth, &staff.dateEmp.yr);
		if (temp != 3) {
			printf("ERROR: Invalid Input! Try again...\n\n");
		}
		else if (staff.dateEmp.day > 31 || staff.dateEmp.day < 1) { //check day
			printf("ERROR: Invalid Input! Try again...\n\n");
		}
		else if (staff.dateEmp.mth > 12 || staff.dateEmp.mth < 1) { //check month
			printf("ERROR: Invalid Input! Try again...\n\n");
		}
		else if (staff.dateEmp.yr > 2024 || staff.dateEmp.yr < 1957) { //check year
			printf("ERROR: Invalid Input! Try again...\n\n");
		}
		else {
			validatePass = 1;
		}

	} while (validatePass == 0);
	//Email
	int count1, count2; //Here, this is used to count a '@' and a '.' character, 

	do {
		duplicate = count1 = count2 = validatePass = 0;
		rewind(stdin);
		printf("Enter an email: ");
		scanf("%s", staff.email);
		for (int i = 0; i < strlen(staff.email); i++) {
			if (staff.email[i] == '@')			//count1 check for 1 '@' character
				count1++;
			else if (staff.email[i] == '.')			//count2 check for 1 '.' character
				count2++;
			//check for 1 '.' character
		}
		for (int i = 0; i < noOfRecords; i++) {
			if (strcmp(staff.email, stf[i].email) == 0)
				duplicate = 1;
		}
		if (duplicate)
			printf("ERROR: Duplicate email detected. Try again...\n\n");

		else if (strlen(staff.email) > 5 && count1 == 1 && count2 >= 1) {
			validatePass = 1;
		}
		else {
			printf("ERROR: Invalid email! Try again...\n\n");
		}
	} while (validatePass == 0);



	//Department
	do {
		rewind(stdin);
		invCount = 0;
		validatePass = 0;
		printf("Enter your current department (e.g Finance): ");
		gets(staff.department);
		for (int i = 0; i < strlen(staff.department); i++) {
			if (isdigit(staff.department[i]) != 0) {
				invCount++;
			}
			else if (ispunct(staff.department[i]) != 0)
				invCount++;
		}

		if (invCount > 0 || strlen(staff.department) < 2) {
			printf("ERROR: Invalid Input! Try again...\n\n");
		}
		else if (strcmp(staff.department,"Administration") == 0) {
			printf("ERROR: Invalid Input! Try again...\n\n");
		}
		else {
			if (strcmp(staff.department, "SYSA") == 0) {
				strcpy(staff.department, "Administration");
			}
			validatePass = 1;
		}

	} while (validatePass == 0);


	//WRITE TO FILE
	FILE* fadd;
	fadd = fopen("admin.dat", "ab+");
	if (fadd == NULL) {
		printf("Error saving to file! Operation aborted.\n");
		system("pause");
		return;
	}
	fwrite(&staff, sizeof(struct staffDetail), 1, fadd);
	printf("Successfully added records. Your admin PIN is 8888\n");
	fclose(fadd);

	writelog("Added a new staff record", staff.name);

	system("pause");

}
void writelog(char action[],char name[]) {
	struct report log;
	FILE* flog;
	flog = fopen("logadmin.bin", "wb");
	if (flog == NULL) {
		printf("Error writting to log file!\n");
		system("pause");
		return;
	}
	else {
		strcpy(log.action, action);
		strcpy(log.name, name);

		//WRITE TO LOG FILE
		fwrite(&log, sizeof(struct report), 1, flog);
		fclose(flog);
	}
}
void staffDisplay() {
	int count = 0,kickCount = 1;
	struct staffDetail staff;
	char id[10], password[20];

	FILE* fdisp;
	fdisp = fopen("admin.dat", "rb");
	if (!fdisp) {
		printf("Error opening file, process aborted.\n");
		system("pause");
		exit(-1);
	}
	else {
		do{
			printf("Login as ADMINISTRATOR staff to continue. ");
			printf("<id> <password> :");
			rewind(stdin);
			scanf("%6s %12s", id, password);
			while (fread(&staff, sizeof(struct staffDetail), 1, fdisp) != 0) {
				//printf("%s", staff.department);
				if (strcmp(staff.id, id) == 0 && strcmp(staff.password, password)==0) {
					if (strcmp(staff.department, "Administration") == 0) {
						kickCount = -1;
						writelog("Logged into system",staff.id);
						break;
					}
				}
			}
			if (kickCount != -1) {
				if (kickCount > 2) {
					printf("Multiple failed logins...Exiting..\n");
					system("pause");
					return;
				}
				else
					printf("Login failed.\n");
				kickCount++;
			}
			rewind(fdisp);
		} while (kickCount!= -1);
		fclose(fdisp); //close first time

		system("cls");
		printf("=====================================\n");
		printf("\t  Staff Credentials\n");
		printf("=====================================\n");
		count = 0;
		fdisp = fopen("admin.dat", "rb"); //open 2nd time No need validation as already started at beginning.
		while (fread(&staff, sizeof(struct staffDetail), 1, fdisp))
		{
			printf("+----------Staff %02d----------+\n", count+1);
			printf("Name : %s\n",staff.name);
			printf("ID   : %s\n", staff.id);
			printf("Email: %s\n", staff.email);
			printf("Working in %s Department since %d/%d/%d\n\n",staff.department,staff.dateEmp.day, staff.dateEmp.mth, staff.dateEmp.yr);
			printf("PASSCODE: %s %04d\n",staff.password,staff.rpin);
			printf("+-----------------------------+\n\n\n\n");
			count++;
		}
		printf("%d staff records shown...\n",count);
	}
	fclose(fdisp);
	system("pause");
}
void staffDelete() {
	struct staffDetail stf[MAX_STAFF];
	char id[30], psw[30], del[10];
	int match = 0, kickCount = 0, index = -1, noOfRecords = 0;

	FILE* fptr;
	fptr = fopen("admin.dat", "rb");
	if (fptr == NULL) {
		printf("File error");
		exit(-1);
	}

	noOfRecords = fread(&stf, sizeof(struct staffDetail), MAX_STAFF, fptr);
	fclose(fptr);
	system("cls");
	printf("NOTE: There are %d staff\n\n", noOfRecords);

	printf("============================\n");
	printf("   Delete a Staff Record\n");
	printf("============================\n");

	printf("You must be logged in to continue.\n");
	do {
		if (kickCount >= 3) {
			printf("Multiple failed login attempts. Exiting...\n");
			system("pause");
			return;
		}
		printf("Enter your ID and Password. ( Type \"<id> <password>\" )\n");
		printf("(e.g: NMB01 abcxyz) :");
		rewind(stdin);
		scanf("%s %s", id, psw);
		for (int i = 0; i < noOfRecords; i++) {
			if (strcmp(id, stf[i].id) == 0 && strcmp(psw, stf[i].password) == 0) {
				match = 1;
				index = i;
				break;
			}
		}
		if (match == 0) {
			system("cls");
			printf("Login failed.\n\n");
		}
		kickCount++;

	} while (match == 0);
	printf("Are you sure you want to delete %s\'s record (%s)?\n(type \"DELETE\" to confirm): ", stf[index].name, stf[index].id);
	rewind(stdin);
	scanf("%s", del);
	if (strcmp(del, "DELETE") != 0)
		printf("You chose not to delete. Returning to menu...\n");
	else {
		printf("Deleting...\n");
		FILE* fdlt;
		fdlt = fopen("admin.dat", "wb"); //Overwrite existing file
		if (fdlt == NULL) {
			printf("FILE ERROR! Process terminated.\n");
			system("pause");
			exit(-1);
		}
		else {
			for (int i = 0; i < noOfRecords; i++) {
				if (i == index)
					continue; //Skips writting deleted record to new file
				else
					fwrite(&stf[i], sizeof(struct staffDetail), 1, fdlt); //Write to file if not selected index
			}
			printf("Sucessfully deleted 1 record. (%s)\n", stf[index].id);
			writelog("Deleted record of", stf[index].id);
			fclose(fdlt);
		}
	}

	system("pause");

}
void staffLog() {
	struct report log; 
	system("cls");
	printf("============================\n");
	printf("    Accessing Log File...\n");
	printf("============================\n");
	printf("Showing the latest change made to system:\n\n");
	FILE* flog;
	flog = fopen("logadmin.bin", "rb");
	if (flog == NULL) {
		printf("Error accessing log file!\n");
		system("pause");
		return;
	}
	else {
		//READ LOG FILE
		fread(&log,sizeof(struct report),1,flog);
		printf("%s : %s\n\n",log.action,log.name);
		system("pause");
		fclose(flog);
	}
}
void staffSearch() {

	struct staffDetail staff[MAX_STAFF];
	FILE* fsearch;
	fsearch = fopen("admin.dat", "rb");
	if (fsearch == NULL) {
		printf("Error accessing admin.dat\n");
		system("pause");
		return;
	}
	int noOfRecords = 0, count;
	noOfRecords = fread(&staff,sizeof(struct staffDetail),MAX_STAFF, fsearch);
	char choice,query[51];
	do {
		count = 0;
		system("cls");
		printf("============================\n");
		printf("      Search for Staff\n");
		printf("============================\n");
		printf("There are %d staff.\n\n", noOfRecords);
		printf("Enter something to search (Name,ID,Email,Department): ");
		rewind(stdin);
		scanf("%[^\n]", query);
		for (int i = 0; i < noOfRecords; i++) {
			if (strcmp(query, staff[i].name) == 0 ||
				strcmp(query, staff[i].email) == 0 ||
				strcmp(query, staff[i].department) == 0 ||
				strcmp(query, staff[i].id) == 0
				) {
				printf("Name : %s\n", staff[i].name);
				printf("ID   : %s\n", staff[i].id);
				printf("Email: %s\n", staff[i].email);
				printf("Working in %s Department since %d/%d/%d\n\n", staff[i].department, staff[i].dateEmp.day, staff[i].dateEmp.mth, staff[i].dateEmp.yr);

				count++;
			}
		}
		if (count == 0)
			printf("\nNo records found!!!!\n");
		else
			printf("\n%d record(s) found.\n", count);
		
		writelog("Someone searched for", query);

		printf("Search again? (Y/N, Default is No) :");
		rewind(stdin);
		scanf("%c", &choice);
	} while (toupper(choice) == 'Y');
}
////////////////////////////////////////////


///////////////// schedule ////////////////////
void choiceSelect() {
	////////admin login
	struct staffDetail staff;
	FILE* freadS;
	freadS = fopen("admin.dat", "rb");
	char id[10], password[20];
	int staffInOrOut = 0;
	if (freadS == NULL) {
		printf("File checking failed. (ADMIN)\n");
		system("pause");
		return 0;
	}
	else {
		printf("Login as SCHEDULING staff to continue. \n");
		printf("Enter <id> <password> :");
		rewind(stdin);
		scanf("%6s %14s", id, password);
		while (fread(&staff, sizeof(struct staffDetail), 1, freadS) != 0) {
			//printf("%s", staff.department);
			if (strcmp(staff.id, id) == 0 && strcmp(staff.password, password) == 0) {
				if(strcmp(staff.department,"Scheduling") == 0) {
					writelog("Logged into system - Scheduling", staff.id);
					printf("Logged into Scheduling Module as %s.\n", staff.name);
					system("pause");
					staffInOrOut = 1;
					break; 
				}
			}
		}
		fclose(freadS);
		if (!staffInOrOut) { //LOGIN failed
			printf("Logged In Failed. ");
			system("pause");
			system("cls");
			return;
		}
	}
	///////////////
	int choice;
	system("cls");
	do {
		printf("==================\n");
		printf("  Train Schedule  \n");
		printf("==================\n");
		printf("\n");
		printf("\n1.Write Train Schedule ");
		printf("\n2.Read Train Schedule  ");
		printf("\n3.Edit Train Schedule ");
		printf("\n4.Search Train Schedule ");
		printf("\n5.Delete Train Schedule ");
		printf("\n6.Generate Schedule Report ");
		printf("\n7.Exit\n ");

		printf("\nPlease Enter Your Selection :");
		rewind(stdin);
		scanf("%d", &choice);
		if (choice == 1) {
			system("cls");
			writeRecord();

		}
		else if (choice == 2) {
			system("cls");
			readRecord();


		}
		else if (choice == 3) {
			system("cls");
			editSchedule();


		}
		else if (choice == 4) {
			system("cls");
			searchTrain();

		}
		else if (choice == 5) {
			system("cls");
			deleteSchedule();

		}
		else if (choice == 6) {
			system("cls");
			scheduleReport();
		}
		else if (choice == 7) {
			return;
		}
		else {
			system("cls");
			printf("Invalid Selection !\n\n\n");

		}
	} while (choice != 7);
}
//  ^^ADMIN LOGIN done
void writeRecord() {

	TimeSchedule time;
	char cont;
	const station[7][5] = { "TGM","KKB","RAS","BTK","SRH","KUG","SGB" };

	FILE* fptr1;
	fptr1 = fopen("Schedule.dat", "ab");

	if (fptr1 == NULL) {
		printf("Unable To Open The File !");
		exit(-1);
	};

	printf("Station Code For Destination ...\n\n");
	printf("TGM = Tanjung Malim\n");
	printf("KKB = Kuala Kubu Bharu\n");
	printf("RAS = Rasa\n");
	printf("BTK = Batang Kali\n");
	printf("SRH = Serendah\n");
	printf("KUG = Kuang\n");
	printf("SGB = Sungai Buloh\n\n\n");


	do {

		rewind(stdin);
		printf("Enter Train ID = ");
		rewind(stdin);
		gets(time.trainID);
		printf("Enter Departure Time = ");
		rewind(stdin);
		scanf("%lf", &time.deparTime);
		printf("Enter Arrival Time = ");
		rewind(stdin);
		scanf("%lf", &time.arrivTime);
		printf("Enter Departure From = ");
		rewind(stdin);
		gets(time.departure);
		printf("Enter Destination = ");
		rewind(stdin);
		gets(time.destination);
		printf("Enter Date ( DD-MM-YYYY ) = ");
		rewind(stdin);
		scanf("%d-%d-%d", &time.day, &time.month, &time.year);
		printf("Enter Price = ");
		rewind(stdin);
		scanf("%lf", &time.price);


		fwrite(&time, sizeof(time), 1, fptr1);
		printf("\n");
		printf("Any Record ? ( Y / N ) :");
		rewind(stdin);
		scanf("%c", &cont);

		printf("\n\n\n");

	} while (cont == 'Y' || cont == 'y');



	system("pause");


	fclose(fptr1);


	system("cls");
	return;
}
void readRecord() {

	TimeSchedule time;
	int selection;
	FILE* fptr2;
	fptr2 = fopen("Schedule.dat", "rb");

	if (fptr2 == NULL) {
		printf("Unable To Open The File !");
		exit(-1);
	};

	printf("Station Code For Destination ...\n\n");
	printf("TGM = Tanjung Malim\n");
	printf("KKB = Kuala Kubu Bharu\n");
	printf("RAS = Rasa\n");
	printf("BTK = Batang Kali\n");
	printf("SRH = Serendah\n");
	printf("KUG = Kuang\n");
	printf("SGB = Sungai Buloh\n\n\n");


	while (fread(&time, sizeof(time), 1, fptr2) != 0) {
		printf("\nTrain ID = %s\n", time.trainID);
		printf("Train Departure Time = %.2f\n", time.deparTime);
		printf("Train Arrival Time = %.2f\n", time.arrivTime);
		printf("Train Departure From = %s\n", time.departure);
		printf("Train Destination = %s\n", time.destination);
		printf("Train Date = %d-%d-%d\n", time.day, time.month, time.year);
		printf("Train Price = %.2f\n", time.price);

		printf("\n");

	}


	fclose(fptr2);

	system("pause");
	system("cls");

}
void editSchedule() {
	TimeSchedule time[MAX_SCHEDULE];
	char edit[31];
	int found = 0;
	int select;
	int selection;

	FILE* fptr2 = fopen("Schedule.dat", "rb");

	if (fptr2 == NULL) {
		printf("Unable To Open The File !");
		exit(-1);
	}


	int noOfRecords = 0, count = 0;
	noOfRecords = fread(&time, sizeof(TimeSchedule), MAX_SCHEDULE, fptr2);



	int match = 0, kickCount = 0, index = -1;

	printf("\nEnter Train ID or Destination To Edit = ");
	rewind(stdin);
	gets(edit);

	for (int i = 0; i < noOfRecords; i++) {
		if (strcmp(edit, time[i].trainID) == 0 || strcmp(edit, time[i].destination) == 0) {


			system("cls");

			printf("Train ID = %s\n", time[i].trainID);
			printf("Departure Time = %.2f\n", time[i].deparTime);
			printf("Arrival Time = %.2f\n", time[i].arrivTime);
			printf("Departure From = %s\n", time[i].departure);
			printf("Destination = % s\n", time[i].destination);
			printf("Train Date = %d-%d-%d\n", time[i].day, time[i].month, time[i].year);
			printf("Price = %.2f\n", time[i].price);

			match = 1;
			index = i;
			found = 1;
			break;

			if (found != 1) {
				printf("Train with ID %s not found.\n", edit);
			}

		}

	}

	fclose(fptr2);

	printf("\n\n\nAre You Sure To Edit This Schedule ?\n");
	printf("1.Yes\n");
	printf("2.No And Back\n");
	printf("Please Enter Your Selection Here = ");
	rewind(stdin);
	scanf("%d", &selection);

	if (selection == 1) {
		FILE* fedit;
		fedit = fopen("Schedule.dat", "wb"); //Overwrite existing file
		if (fedit == NULL) {
			printf("FILE ERROR! Process terminated.\n");
			system("pause");
			exit(-1);
		}
		else {
			for (int i = 0; i < noOfRecords; i++) {
				if (i == index) {
					printf("\n\nEnter New Train ID = ");
					rewind(stdin);
					gets(time[i].trainID);
					printf("Enter New Departure Time =");
					rewind(stdin);
					scanf("%lf", &time[i].deparTime);
					printf("Enter New Arrival Time = ");
					rewind(stdin);
					scanf("%lf", &time[i].arrivTime);
					printf("Enter New Departure From =");
					rewind(stdin);
					gets(time[i].departure);
					printf("Enter New Destination =");
					rewind(stdin);
					gets(time[i].destination);
					printf("Enter New Date ( DD-MM-YYYY ) = ");
					rewind(stdin);
					scanf("%d-%d-%d", &time[i].day, &time[i].month, &time[i].year);
					printf("Enter New Price = ");
					rewind(stdin);
					scanf("%lf", &time[i].price);

					fwrite(&time[i], sizeof(TimeSchedule), 1, fedit); //Write to file if not selected indexcontinue; //Skips writting deleted record to new file
				}
				else {



					fwrite(&time[i], sizeof(TimeSchedule), 1, fedit); //Write to file if not selected index
				}
			}
			printf("\n\n\n");
			printf("%s Edited Succesfully...", time[index].trainID);
			printf("\n\n\n");
			fclose(fedit);

			system("pause");
			system("cls");
		}
	}
	else if (selection == 2) {
		system("cls");
		return;
	}
	else {
		printf("Invalid Selection\n");
	}

}
void searchTrain() {


	TimeSchedule time[MAX_SCHEDULE];
	char search[31];
	int selection;
	int found = 0;
	FILE* fptr2;
	fptr2 = fopen("Schedule.dat", "rb+");

	if (fptr2 == NULL) {
		printf("Unable To Open The File !");
		exit(-1);
	};

	int noOfRecords = 0;
	noOfRecords = fread(&time, sizeof(TimeSchedule), MAX_SCHEDULE, fptr2);

	printf("Search Train ID = ");
	rewind(stdin);
	gets(search);
	for (int i = 0; i < noOfRecords; i++) {
		if (strcmp(search, time[i].trainID) == 0 || strcmp(search, time[i].destination) == 0) {

			system("cls");

			printf("Train ID = %s\n", time[i].trainID);
			printf("Departure Time = %.2f\n", time[i].deparTime);
			printf("Arrival Time = %.2f\n", time[i].arrivTime);
			printf("Departure From = %s\n", time[i].departure);
			printf("Destination = % s\n", time[i].destination);
			printf("Train Date = %d-%d-%d\n", time[i].day, time[i].month, time[i].year);
			printf("Price = %.2f\n", time[i].price);

			found = 1;
			break;

			if (found != 1) {
				printf("Train with ID %s not found.\n", search);
			}

		}

	}

	fclose(fptr2);

	system("pause");
	system("cls");

}
void deleteSchedule() {

	TimeSchedule time[MAX_SCHEDULE];
	char search[31];
	int selection;
	int found = 0;
	FILE* fptr2;
	fptr2 = fopen("Schedule.dat", "rb+");

	if (fptr2 == NULL) {
		printf("Unable To Open The File !");
		exit(-1);
	};

	int noOfRecords = 0, count = 0;
	noOfRecords = fread(&time, sizeof(TimeSchedule), MAX_SCHEDULE, fptr2);



	int match = 0, kickCount = 0, index = -1;

	printf("Search Train ID or Train Destination For Delete = ");
	rewind(stdin);
	gets(search);
	for (int i = 0; i < noOfRecords; i++) {
		if (strcmp(search, time[i].trainID) == 0 || strcmp(search, time[i].destination) == 0) {


			system("cls");

			printf("Train ID = %s\n", time[i].trainID);
			printf("Departure Time = %.2f\n", time[i].deparTime);
			printf("Arrival Time = %.2f\n", time[i].arrivTime);
			printf("Departure From = %s\n", time[i].departure);
			printf("Destination = % s\n", time[i].destination);
			printf("Train Date = %d-%d-%d\n", time[i].day, time[i].month, time[i].year);
			printf("Price = %.2f\n", time[i].price);

			match = 1;
			index = i;
			found = 1;
			break;

			if (found != 1) {
				printf("Train with ID %s not found.\n", search);
			}

		}

	}

	fclose(fptr2);

	printf("\n\n\nAre You Sure Delete This Schedule ?\n");
	printf("1.Yes\n");
	printf("2.No And Back\n");
	printf("Please Enter Your Selection Here = ");
	rewind(stdin);
	scanf("%d", &selection);

	if (selection == 1) {
		FILE* fdlt;
		fdlt = fopen("Schedule.dat", "wb"); //Overwrite existing file
		if (fdlt == NULL) {
			printf("FILE ERROR! Process terminated.\n");
			system("pause");
			exit(-1);
		}
		else {
			for (int i = 0; i < noOfRecords; i++) {
				if (i == index)
					continue; //Skips writting deleted record to new file
				else
					fwrite(&time[i], sizeof(TimeSchedule), 1, fdlt); //Write to file if not selected index
			}
			printf("\n\n\n");
			printf("%s Deleted Succesfully...", time[index].trainID);
			printf("\n\n\n");
			fclose(fdlt);


			system("pause");
			system("cls");
		}
	}
	else if (selection == 2) {
		system("cls");
		return;
	}
	else {
		printf("Invalid Selection\n");
	}



}
void scheduleReport() {
	TimeSchedule time[MAX_SCHEDULE];

	int count = 0;
	int tgm = 0;
	int kkb = 0;
	int ras = 0;
	int btk = 0;
	int srh = 0;
	int kug = 0;
	int sgb = 0;


	FILE* frep;

	frep = fopen("Schedule.dat", "rb+");
	if (frep == NULL) {
		printf("Unable To Open The File !");
		exit(-1);
	}
	int noOfRecords = 0;
	noOfRecords = fread(&time, sizeof(TimeSchedule), MAX_SCHEDULE, frep);

	printf("Generating Schedule Report ...\n\n");


	for (int i = 0; i < noOfRecords; i++) {
		count++;

		if (strcmp(time[i].destination, "SGB") == 0) {
			sgb++;
		}
		else if (strcmp(time[i].destination, "RAS") == 0) {
			ras++;
		}
		else if (strcmp(time[i].destination, "TGM") == 0) {
			tgm++;
		}
		else if (strcmp(time[i].destination, "BTK") == 0) {
			btk++;
		}
		else if (strcmp(time[i].destination, "KUG") == 0) {
			kug++;
		}
		else if (strcmp(time[i].destination, "SRH") == 0) {
			srh++;
		}
		else if (strcmp(time[i].destination, "KKB") == 0) {
			kkb++;
		}

	}

	printf("\n\nTotal of Train = %d\n", count);
	printf("\nTanjung Malim = %d\n", tgm);
	printf("Kuala Kubu Bharu = %d\n", kkb);
	printf("Rasa = %d\n", ras);
	printf("Batang Kali = %d\n", btk);
	printf("Serendah = %d\n", srh);
	printf("Kuang = %d\n", kug);
	printf("Sungai Buloh = %d\n\n\n", sgb);

	system("pause");
	system("cls");
}
////////////////////////////////////////////


/////////// BOOKING ///////////////////////
void addBooking() {
	struct Booking bookings[MAX_BOOKINGS];
	TimeSchedule time[MAX_SCHEDULE];
	Member members[MAX_MEMBERS];
	int num_bookings = 0; //booking
	int numMembers = 0; //member 
	int sch_i = 0; // Initialize sch_i to 0
	int check;
	int found;
	char cont = 'y';
	char input[50];
	bookings[num_bookings].bookingID = 'B';
	char* current_time = timeF();

	//read member
	FILE* file;
	file = fopen("members.txt", "r");
	if (file == NULL) {
		printf("unable to open member file");
		exit(-1);
	}

	while (fscanf(file, "%s %[^@]@%s %s %s %s %d\n",
		members[numMembers].mID,
		members[numMembers].username,
		members[numMembers].password,
		members[numMembers].email,
		members[numMembers].contactNum,
		members[numMembers].icNum,
		&members[numMembers].loyaltyPoints) == 7) {
		numMembers++;
	}

	//read booking
	FILE* bookfile;
	bookfile = fopen("bookings.txt", "r");

	if (bookfile == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}

	while (!feof(bookfile))
	{
		fscanf(bookfile, "%s %s %s %[^|]|  %[^\#]# %s %c %s %.2lf\n",
			&bookings[num_bookings].booking_id,
			&bookings[num_bookings].member_id,
			&bookings[num_bookings].train_id,
			&bookings[num_bookings].booking_date,
			&bookings[num_bookings].passenger_name,
			&bookings[num_bookings].seat_number,
			&bookings[num_bookings].coach,
			&bookings[num_bookings].payment_info,
			&bookings[num_bookings].amount);
		num_bookings++;
	}
	fclose(bookfile); //close booking file


	do {
		system("cls");
		printf("=============================================ADD BOOKING=========================================\n\n");

		FILE* fptr2;
		fptr2 = fopen("Schedule.dat", "rb");

		if (fptr2 == NULL) {
			printf("Unable To Open The File !");
			exit(-1);
		}

		printf("---------------------------------------------------------------------------------------------------------------------------\n");
		printf("| %-10s | %-20s | %-20s | %-15s | %-15s | %-10s |  %-10s |\n", "Train ID", "Departure Time", "Arrival Time", "Departure From", "Destination", "Date", "Price");
		printf("---------------------------------------------------------------------------------------------------------------------------\n");

		sch_i = 0;
		while (fread(&time[sch_i], sizeof(time[sch_i]), 1, fptr2) != 0) {
			printf("| %-10s | %-20.2f | %-20.2f | %-15s | %-15s | %02d-%02d-%04d | %10.2lf  |\n",
				time[sch_i].trainID,
				time[sch_i].deparTime,
				time[sch_i].arrivTime,
				time[sch_i].departure,
				time[sch_i].destination,
				time[sch_i].day,
				time[sch_i].month,
				time[sch_i].year,
				time[sch_i].price);
			sch_i++;
		}

		printf("---------------------------------------------------------------------------------------------------------------------------\n");

		//bookingID 
		FILE* fread;
		fread = fopen("bookings.txt", "r");
		if (fread != NULL) {
			while (!feof(fread)) {
				fscanf(fread, "%c%03d %s %s %[^|]|  %[^\#]# %s %c %s %lf\n",
					&bookings[num_bookings].bookingID,
					&bookings[num_bookings].booking_no,
					bookings[num_bookings].member_id,
					bookings[num_bookings].train_id,
					bookings[num_bookings].booking_date,
					bookings[num_bookings].passenger_name,
					bookings[num_bookings].seat_number,
					&bookings[num_bookings].coach,
					bookings[num_bookings].payment_info,
					&bookings[num_bookings].amount);
				bookings[num_bookings].booking_no++;
				num_bookings++;
			}

			// Printing the last booking ID read
			if (num_bookings > 0) {
				printf("+----------------+\n");
				printf("|Booking ID: %c%03d |\n", bookings[num_bookings - 1].bookingID, bookings[num_bookings - 1].booking_no);
				printf("+----------------+\n");
			}
			/*fprintf(fwrite, "%c%03d", bookings[num_bookings - 1].bookingID, bookings[num_bookings - 1].booking_no);*/
		}
		fclose(fread);

		//member login
		printf("Enter member ID (eg. M001) : ");
		scanf("%s", bookings[num_bookings].member_id);

		int found = 0;
		for (int i = 0; i < numMembers; i++) {
			if (strcmp(bookings[num_bookings].member_id, members[i].mID) == 0) {
				found = 1;
				break;
			}
		}

		if (!found) {
			printf("Invalid member ID. Please try again.\n");
			continue;
		}

		//Train ID
		int check = 0;
		do {
			printf("\n");
			printf("Enter Train ID (eg. T001): ");
			scanf("%s", bookings[num_bookings].train_id);

			check = 0;
			for (int i = 0; i < sch_i; i++) {
				if (strcmp(bookings[num_bookings].train_id, time[i].trainID) == 0) {
					printf("\t\t\t\t----------------------------------------\n");
					printf("\t\t\t\t Train ID = %s\n", time[i].trainID);
					printf("\t\t\t\t Departure Time = %.2f\n", time[i].deparTime);
					printf("\t\t\t\t Arrival Time = %.2f\n", time[i].arrivTime);
					printf("\t\t\t\t Departure From = %s\n", time[i].departure);
					printf("\t\t\t\t Destination = %s\n", time[i].destination);
					printf("\t\t\t\t Train Date = %d-%d-%d\n", time[i].day, time[i].month, time[i].year);
					printf("\t\t\t\t Price = %.2f\n", time[i].price);
					printf("\t\t\t\t----------------------------------------\n");
					check = 1;

					if (!check) {
						printf("\t\t\t\t NOT RECORD !!!\n");
					}

					else {
						//booking datE
						current_time = timeF();
						printf("Booking Date & Time: %s\n", current_time);
						strcpy(bookings[num_bookings].booking_date, current_time);

						//name
						printf("Enter Passenger Name: ");
						rewind(stdin);
						scanf("%[^\n]", bookings[num_bookings].passenger_name);

						//valid seat
						int valid_seat = 0;
						do {
							printf("Enter Seat Number for seat (e.g., 12A or 06D): ");
							rewind(stdin);
							scanf("%s", bookings[num_bookings].seat_number);

							if (!isValidSeatNumber(bookings[num_bookings].seat_number)) {
								printf("==========================================================================================\n");
								printf("Invalid seat number format. Please enter a valid seat number.\n");
								printf("First and Second range from 01 until 12, Third character should be 'A', 'B', 'C', or 'D'\n");
								printf("=========================================================================================\n\n");
							}
							else {
								valid_seat = 1;
							}
						} while (!valid_seat);

						//valid coach
						int valid_coach = 0;
						do {
							printf("Enter Coach for seat (A until H): ");
							rewind(stdin);
							scanf(" %c", &bookings[num_bookings].coach);

							if (bookings[num_bookings].coach >= 'A' && bookings[num_bookings].coach <= 'H') {
								valid_coach = 1;
							}
							else {
								printf("Invalid coach. Please enter a value from A to H.\n");
							}
						} while (!valid_coach);

						//payment
						printf("Enter Payment Info (CREDIT , DEBIT , BANKING): ");
						rewind(stdin);
						scanf("%s", bookings[num_bookings].payment_info);

						// Get train price
						float train_price = time[i].price; // Use price corresponding to the matched train ID

						// Calculate amount
						bookings[num_bookings].amount = train_price;

						printf("Amount: %.2f\n", bookings[num_bookings].amount);

					}
				}
			}


			if (!check) {
				printf("Invalid train id");
			}

		} while (!check);

		do {
			FILE* fwrite;
			fwrite = fopen("bookings.txt", "a");
			if (fwrite == NULL) {
				printf("Unable to open file.\n");
				exit(-1);
			}
			printf("do you confirm this booking? (y/n) : ");
			rewind(stdin);
			scanf("%c", &cont);

			if (toupper(cont) == 'Y') {
				fprintf(fwrite, "%c%03d %s %s %s| %s# %s %c %s %.2f\n",
					bookings[num_bookings - 1].bookingID,
					bookings[num_bookings - 1].booking_no,
					bookings[num_bookings].member_id,
					bookings[num_bookings].train_id,
					bookings[num_bookings].booking_date,
					bookings[num_bookings].passenger_name,
					bookings[num_bookings].seat_number,
					bookings[num_bookings].coach,
					bookings[num_bookings].payment_info,
					bookings[num_bookings].amount);

				fclose(fwrite);
				printf("+--------------------------+\n");
				printf("Booking added successfully!\n");
				printf("+--------------------------+\n");
				//num_bookings++;

				fclose(file); //close member file


				//when member successfull booking , will add loyalty point to member id in member 
				FILE* fpPoint;
				fpPoint = fopen("members.txt", "w");
				if (fpPoint == NULL) {
					printf("Unable to open file.\n");
					exit(-1);
				}

				int found = 0;
				for (int y = 0; y < numMembers; y++) {
					if (strcmp(bookings[num_bookings].member_id, members[y].mID) == 0) {
						members[y].loyaltyPoints += 10;
						found = 1; // Mark that a member is found
						for (int y = 0; y < numMembers; y++) {
							fprintf(fpPoint, "%s %s@%s %s %s %s %d\n",
								members[y].mID,
								members[y].username,
								members[y].password,
								members[y].email,
								members[y].contactNum,
								members[y].icNum,
								members[y].loyaltyPoints);
						}
					}
				}

				fclose(fpPoint);
				break;
			}

			else {
				printf("+----------------+\n");
				printf("Booking added fail!\n");
				printf("+----------------+\n");
			}


		} while (toupper(cont) != 'Y' && toupper(cont) != 'N');

		printf("Do you want to continue adding bookings? (y/n): ");
		rewind(stdin);
		scanf(" %c", &cont);
		fclose(fptr2);

	} while (toupper(cont) == 'Y');

	system("pause");
	fclose(file);
}
int isValidSeatNumber(const char* seat_number) // validate seat
{
	if (strlen(seat_number) != 3)
		return 0; // Invalid length

	// Validate first character
	if (seat_number[0] != '0' && seat_number[0] != '1') // First character should be '0' or '1'
		return 0;

	// Validate second character
	if ((seat_number[0] == '0' && (seat_number[1] < '1' || seat_number[1] > '9')) || // If first character is '0', second character can be '1' to '9'
		(seat_number[0] == '1' && (seat_number[1] != '0' && seat_number[1] != '1' && seat_number[1] != '2'))) // If first character is '1', second character can be '0', '1', or '2'
		return 0;

	// Validate third character
	if (seat_number[2] < 'A' || seat_number[2] > 'D') // Third character should be 'A', 'B', 'C', or 'D'
		return 0;

	return 1; // Seat number is valid
}
char* generateBookingID() {
	static int count = 0;
	char* booking_id = malloc(10 * sizeof(char));
	sprintf(booking_id, "B%03d", ++count);
	return booking_id;
}
char* timeF() {
	time_t time_now;
	struct tm* local_time;
	static char time_share[100];

	time(&time_now);
	local_time = localtime(&time_now);
	strftime(time_share, sizeof(time_share), "%H:%M:%S %d/%m/%y", local_time);
	return time_share;
}
void displayBooking() {
	struct Booking bookings[MAX_BOOKINGS];
	int num_bookings = 0;

	FILE* bookfile;
	bookfile = fopen("bookings.txt", "r");
	if (bookfile == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}

	while (fscanf(bookfile, "%9s %9s %9s %19[^|]| %49[^#]# %9s %c %19s %lf\n",
		bookings[num_bookings].booking_id,
		bookings[num_bookings].member_id,
		bookings[num_bookings].train_id,
		bookings[num_bookings].booking_date,
		bookings[num_bookings].passenger_name,
		bookings[num_bookings].seat_number,
		&bookings[num_bookings].coach,
		bookings[num_bookings].payment_info,
		&bookings[num_bookings].amount) == 9) {
		num_bookings++;
	}

	system("cls");
	printf("\t\t======================================================================================\n\n");
	printf("\t\t                             ALL BOOKING TICKET DETAILS                               \n\n");
	printf("\t\t======================================================================================\n\n");
	printf("\n");
	printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("  BOOKING ID    |   TRAIN ID   |   MEMBER  ID   |    BOOKING DATE       |    PASSENGER NAME     |    SEAT NUMBER    |   COACH   |  PAYMENT  INFO |       AMOUNT \n");
	printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	for (int i = 0; i < num_bookings; i++) {
		printf("     %-13s    %-13s   %-13s %-13s       %-27s   %-16s %-7c  %-16s   %.2lf\n",
			bookings[i].booking_id,
			bookings[i].train_id,
			bookings[i].member_id,
			bookings[i].booking_date,
			bookings[i].passenger_name,
			bookings[i].seat_number,
			bookings[i].coach,
			bookings[i].payment_info,
			bookings[i].amount);
	}

	printf(" ---------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t\t %d record(s) booking.\n\n", num_bookings);
	system("pause");
	fclose(bookfile);
}
void updateBooking() {
	struct Booking bookings[MAX_BOOKINGS];
	TimeSchedule time[MAX_SCHEDULE];
	int num_bookings = 0;
	int  sch_i = 0;
	char cont = 'y';
	int check;

	FILE* bookfile;
	FILE* fptr2;
	bookfile = fopen("bookings.txt", "r");
	if (bookfile == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}

	// Read bookings from file
	while (fscanf(bookfile, "%s %s %s %[^|]| %[^#]# %s %c %s %lf",
		bookings[num_bookings].booking_id,
		bookings[num_bookings].member_id,
		bookings[num_bookings].train_id,
		bookings[num_bookings].booking_date,
		bookings[num_bookings].passenger_name,
		bookings[num_bookings].seat_number,
		&bookings[num_bookings].coach,
		bookings[num_bookings].payment_info,
		&bookings[num_bookings].amount) == 9) {
		num_bookings++;
	}
	fclose(bookfile);

	//read schedule
	do {
		system("cls");
		printf("=============================================UPDATE BOOKING=========================================\n\n");
		int found = 0;
		printf("\t\t\t Enter BOOKING ID To UPDATE (Exp:B001) : ");
		scanf("%s", bookings[num_bookings].booking_id);

		for (int i = 0; i < num_bookings; i++) {
			if (strcmp(bookings[i].booking_id, bookings[num_bookings].booking_id) == 0) {
				found = 1;

				printf("\t\t\t\t\t----------------------\n");
				printf("\t\t\t\t\t|   Booking ID : %s  |\n", bookings[i].booking_id);
				printf("\t\t\t\t\t----------------------\n\n");

				printf("\t\t\t\t            UPDATE BOOKING \n");
				printf("\t\t\t\t ------------------------------------\n");
				printf("\t\t\t\t    1. TRAIN ID      : %s               \n", bookings[i].train_id);
				printf("\t\t\t\t    2. PASSENGER NAME: %s               \n", bookings[i].passenger_name);
				printf("\t\t\t\t    3. SEAT NUMBER   : %s               \n", bookings[i].seat_number);
				printf("\t\t\t\t    4. COACH         : %c               \n", bookings[i].coach);
				printf("\t\t\t\t    5. PAYMENT INFO  : %s               \n", bookings[i].payment_info);
				printf("\t\t\t\t ------------------------------------\n\n");

				int option;
				printf("\t\t\t\tPlease choose the number to update: ");
				scanf("%d", &option);
				switch (option) {

				case 1:
					fptr2 = fopen("Schedule.dat", "rb");

					if (fptr2 == NULL) {
						printf("Unable To Open The File !");
						exit(-1);
					}

					printf("---------------------------------------------------------------------------------------------------------------------------\n");
					printf("| %-10s | %-20s | %-20s | %-15s | %-15s | %-10s |  %-10s |\n", "Train ID", "Departure Time", "Arrival Time", "Departure From", "Destination", "Date", "Price");
					printf("---------------------------------------------------------------------------------------------------------------------------\n");

					while (fread(&time[sch_i], sizeof(time[sch_i]), 1, fptr2) != 0) {
						printf("| %-10s | %-20.2f | %-20.2f | %-15s | %-15s | %02d-%02d-%04d | %10.2lf  |\n",
							time[sch_i].trainID,
							time[sch_i].deparTime,
							time[sch_i].arrivTime,
							time[sch_i].departure,
							time[sch_i].destination,
							time[sch_i].day,
							time[sch_i].month,
							time[sch_i].year,
							time[sch_i].price);
						sch_i++;
					}

					printf("---------------------------------------------------------------------------------------------------------------------------\n");
					fclose(fptr2);

					do {

						check = 0;
						printf("\n");
						printf("Enter Train ID (eg. T001): ");
						scanf("%s", bookings[i].train_id);


						for (int x = 0; x < sch_i; x++) {
							if (strcmp(time[x].trainID, bookings[i].train_id) == 0) {
								printf("\t\t\t\t----------------------------------------\n");
								printf("\t\t\t\t Train ID = %s\n", time[x].trainID);
								printf("\t\t\t\t Departure Time = %.2f\n", time[x].deparTime);
								printf("\t\t\t\t Arrival Time = %.2f\n", time[x].arrivTime);
								printf("\t\t\t\t Departure From = %s\n", time[x].departure);
								printf("\t\t\t\t Destination = %s\n", time[x].destination);
								printf("\t\t\t\t Train Date = %d-%d-%d\n", time[x].day, time[x].month, time[x].year);
								printf("\t\t\t\t Price = %.2f\n", time[x].price);
								printf("\t\t\t\t----------------------------------------\n");
								check = 1;
								break;
							}
						}
						if (!check) {
							printf("\t\t\t\t NOT RECORD !!!\n");
						}
					} while (!check);
					break;

				case 2:
					printf("\n");
					printf("Enter NEW PASSENGER NAME: ");
					scanf("%s", bookings[i].passenger_name);
					break;

				case 3:
					do {
						printf("\n");
						printf("Enter NEW Seat Number for seat (e.g., 12A or 06D): ");
						scanf("%s", bookings[i].seat_number);

						if (!isValidSeatNumber(bookings[i].seat_number)) {
							printf("==========================================================================================\n");
							printf("Invalid seat number format. Please enter a valid seat number.\n");
							printf("First and Second range from 01 until 12, Third character should be 'A', 'B', 'C', or 'D'\n");
							printf("=========================================================================================\n\n");
						}
						else {
							break;
						}
					} while (1);

					break;

				case 4:
					do {
						printf("\n");
						printf("Enter NEW Coach for seat (A until H): ");
						scanf(" %c", &bookings[i].coach);

						if (bookings[i].coach >= 'A' && bookings[i].coach <= 'H') {
							break;
						}
						else {
							printf("Invalid coach. Please enter a value from A to H.\n");
						}
					} while (1);
					break;

				case 5:
					printf("\n");
					printf("Enter NEW Payment Info (CREDIT , DEBIT , BANKING): ");
					scanf("%s", bookings[i].payment_info);
					break;

				default:
					printf("Invalid option!\n");
					break;
				}
				break;
			}
		}

		if (!found) {
			printf("\t\t\t\t -----------------------------------\n");
			printf("\t\t\t\t        BOOKING ID NOT FOUND ! \n");
			printf("\t\t\t\t -----------------------------------\n");
			system("pause");
			return;
		}

		bookfile = fopen("bookings.txt", "w");
		if (bookfile == NULL) {
			printf("Unable to open file.\n");
			exit(-1);
		}

		for (int j = 0; j < num_bookings; j++) {
			fprintf(bookfile, "%s %s %s  %s| %s# %s %c %s %.2lf\n",
				bookings[j].booking_id,
				bookings[j].member_id,
				bookings[j].train_id,
				bookings[j].booking_date,
				bookings[j].passenger_name,
				bookings[j].seat_number,
				bookings[j].coach,
				bookings[j].payment_info,
				bookings[j].amount);
		}
		fclose(bookfile);
		printf("\t\t\t\t---------------------------------\n");
		printf("\t\t\t\t Booking updated successfully!\n");
		printf("\t\t\t\t---------------------------------\n");

		do {
			printf("\n\nDo you still want continue UPDATE booking anymore ? (y/n): ");
			scanf(" %c", &cont);
		} while (toupper(cont) != 'Y' && toupper(cont) != 'N');

	} while (toupper(cont) == 'Y');
}
void cancelBooking() {
	struct Booking bookings[MAX_BOOKINGS];
	TimeSchedule time[MAX_SCHEDULE];
	int num_bookings = 0;
	int i;
	int check;
	char input[50];

	FILE* bookfile;
	bookfile = fopen("bookings.txt", "r");
	if (bookfile == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}
	while (fscanf(bookfile, "%s %s %s %[^|]| %[^#]# %s %c %s %lf",
		bookings[num_bookings].booking_id,
		bookings[num_bookings].member_id,
		bookings[num_bookings].train_id,
		bookings[num_bookings].booking_date,
		bookings[num_bookings].passenger_name,
		bookings[num_bookings].seat_number,
		&bookings[num_bookings].coach,
		bookings[num_bookings].payment_info,
		&bookings[num_bookings].amount) != EOF) {
		num_bookings++;
	}
	fclose(bookfile);

	system("cls");
	printf("=============================================DELETE BOOKING=========================================\n\n");
	do {
		check = 0;
		printf("\t\t\t Enter BOOKING ID To Delete (Exp:B001) : ");
		rewind(stdin);
		scanf("%s", input);

		printf("\n");

		for (i = 0; i < num_bookings; i++) {
			if (strcmp(bookings[i].booking_id, input) == 0) {
				check = 1;

				printf("\t\t\t\t\t----------------------\n");
				printf("\t\t\t\t\t|   Booking ID : %s  |\n", bookings[i].booking_id);
				printf("\t\t\t\t\t----------------------\n");

				printf("\t\t\t\t ------------------------------------\n");
				printf("\t\t\t\t    MEMBER ID      : %s               \n", bookings[i].member_id);
				printf("\t\t\t\t    TRAIN ID       : %s               \n", bookings[i].train_id);
				printf("\t\t\t\t    BOOKING DATE   : %s               \n", bookings[i].booking_date);
				printf("\t\t\t\t    PASSENGER NAME : %s               \n", bookings[i].passenger_name);
				printf("\t\t\t\t    SEAT NUMBER    : %s               \n", bookings[i].seat_number);
				printf("\t\t\t\t    COACH          : %c               \n", bookings[i].coach);
				printf("\t\t\t\t    PAYMENT INFO   : %s               \n", bookings[i].payment_info);
				printf("\t\t\t\t    AMOUNT         : %.2lf            \n", bookings[i].amount);
				printf("\t\t\t\t -----------------------------------\n");

				break;
			}
		}

		if (check == 0) {
			printf("\t\t\t\t -----------------------------------\n");
			printf("\t\t\t\t        BOOKING ID NOT FOUND ! \n");
			printf("\t\t\t\t -----------------------------------\n");
			system("pause");
			return;
		}
	} while (check == 0);

	char cont;
	do {
		printf("\t\t\t     Do You Confirm To Delete ? ( Y=Yes/N=No ) : ");
		rewind(stdin);
		scanf(" %c", &cont);

		if (toupper(cont) == 'N') {
			printf("\n\t\t\t\t -----------------------------------------\n");
			printf("\t\t\t\t       DELETE BOOKING UNSUCESSFUL !     \n");
			printf("\t\t\t\t -----------------------------------------\n");
			system("pause");
		}
		else if (toupper(cont) == 'Y') {
			printf("\n\n\t\t\t\t -----------------------------------------\n");
			printf("\t\t\t\t  BOOKING ID %s deleted SUCESSFULLY !\n", bookings[i].booking_id);
			printf("\t\t\t\t -----------------------------------------\n");
			system("pause");

			// Shift array elements to overwrite the deleted booking
			for (int j = i; j < num_bookings - 1; j++) {
				strcpy(bookings[j].booking_id, bookings[j + 1].booking_id);
				strcpy(bookings[j].member_id, bookings[j + 1].member_id);
				strcpy(bookings[j].train_id, bookings[j + 1].train_id);
				strcpy(bookings[j].booking_date, bookings[j + 1].booking_date);
				strcpy(bookings[j].passenger_name, bookings[j + 1].passenger_name);
				strcpy(bookings[j].seat_number, bookings[j + 1].seat_number);
				bookings[j].coach = bookings[j + 1].coach;
				strcpy(bookings[j].payment_info, bookings[j + 1].payment_info);
				bookings[j].amount = bookings[j + 1].amount;
			}
			num_bookings--;

			bookfile = fopen("bookings.txt", "w");
			if (bookfile == NULL) {
				printf("Unable to open file.\n");
				exit(-1);
			}
			for (int k = 0; k < num_bookings; k++) {
				fprintf(bookfile, "%s %s %s %s| %s# %s %c %s %.2lf\n",
					bookings[k].booking_id,
					bookings[k].member_id,
					bookings[k].train_id,
					bookings[k].booking_date,
					bookings[k].passenger_name,
					bookings[k].seat_number,
					bookings[k].coach,
					bookings[k].payment_info,
					bookings[k].amount);
			}
			fclose(bookfile);

			break;
		}
		else {
			printf("Invalid input. Please enter 'Y' or 'N'");
		}
	} while (toupper(cont) != 'N' && toupper(cont) != 'Y');
}
void searchBooking() {
	struct Booking bookings[MAX_BOOKINGS];
	int num_bookings = 0;
	int numMembers = 0;
	int x = 0;
	int t_i = 0;
	int a;
	int check;
	char* booking_id = generateBookingID();

	char cont = 'y';
	char input[50];

	FILE* bookfile;
	bookfile = fopen("bookings.txt", "r");
	if (bookfile == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}

	while (!feof(bookfile))
	{
		fscanf(bookfile, "%s %s %s %[^|]| %[^#]# %s %c %s %lf",
			&bookings[num_bookings].booking_id,
			&bookings[num_bookings].member_id,
			&bookings[num_bookings].train_id,
			&bookings[num_bookings].booking_date,
			&bookings[num_bookings].passenger_name,
			&bookings[num_bookings].seat_number,
			&bookings[num_bookings].coach,
			&bookings[num_bookings].payment_info,
			&bookings[num_bookings].amount);
		num_bookings++;
	}
	fclose(bookfile);


	system("cls");
	printf("=============================================SEARCH BOOKING=========================================\n\n");
	do {
		check = 0;
		printf("\t\t\t Enter BOOKING ID To SEARCH (Exp:B001) : ");
		rewind(stdin);
		scanf("%s", &input);

		printf("\n");
		int i;
		for (i = 0; i < num_bookings; i++) {
			if (strcmp(bookings[i].booking_id, input) == 0) {
				check = 1;

				printf("\t\t\t\t\t----------------------\n");
				printf("\t\t\t\t\t|   Booking ID : %s  |\n", bookings[i].booking_id);
				printf("\t\t\t\t\t----------------------\n");

				num_bookings++;
				printf("\t\t\t\t ------------------------------------\n");
				printf("\t\t\t\t    MEMBER ID      : %s               \n", bookings[i].member_id);
				printf("\t\t\t\t    TRAIN ID       : %s               \n", bookings[i].train_id);
				printf("\t\t\t\t    BOOKING DATE   : %s               \n", bookings[i].booking_date);
				printf("\t\t\t\t    PASSENGER NAME : %s               \n", bookings[i].passenger_name);
				printf("\t\t\t\t    SEAT NUMBER    : %s               \n", bookings[i].seat_number);
				printf("\t\t\t\t    COACH          : %c               \n", bookings[i].coach);
				printf("\t\t\t\t    PAYMENT INFO   : %s               \n", bookings[i].payment_info);
				printf("\t\t\t\t    AMOUNT         : %.2lf            \n", bookings[i].amount);
				printf("\t\t\t\t -----------------------------------\n");

			}
		}

		if (check == 0) {
			check = 0;
			printf("\t\t\t\t -----------------------------------\n");
			printf("\t\t\t\t        BOOKING ID NOT FOUND ! \n");
			printf("\t\t\t\t -----------------------------------\n");
			system("pause");
			return;
		}
		do {
			printf("\nDo you want to continue to search? (Y=Yes , N=N0) : ");
			rewind(stdin);
			scanf("%c", &cont);

			if (toupper(cont) == 'Y') {
				system("cls");
				searchBooking();
			}
			else if (toupper(cont) == 'N') {
				system("cls");
				return;
			}
			else {
				printf("Invalid input. Please enter 'Y' or 'N'");
			}
		} while (toupper(cont) != 'N' && toupper(cont) != 'Y');

	} while (check == 0);
}
void reportBooking() {
	struct Booking bookings[MAX_BOOKINGS];
	int num_bookings = 0;

	FILE* bookfile = fopen("bookings.txt", "r");
	if (bookfile == NULL) {
		printf("Unable to open file.\n");
		exit(-1);
	}

	while (fscanf(bookfile, "%s %s %s %[^|]| %[^#]# %s %c %s %lf",
		bookings[num_bookings].booking_id,
		bookings[num_bookings].member_id,
		bookings[num_bookings].train_id,
		bookings[num_bookings].booking_date,
		bookings[num_bookings].passenger_name,
		bookings[num_bookings].seat_number,
		&bookings[num_bookings].coach,
		bookings[num_bookings].payment_info,
		&bookings[num_bookings].amount) == 9) {
		num_bookings++;
	}
	fclose(bookfile);

	int train_counts[MAX_BOOKINGS] = { 0 };
	int member_counts[MAX_BOOKINGS] = { 0 };

	// Count bookings by train ID and member ID
	for (int i = 0; i < num_bookings; i++) {
		// Count how many train IDs have been booked
		for (int j = 0; j < num_bookings; j++) {
			if (strcmp(bookings[i].train_id, bookings[j].train_id) == 0) {
				train_counts[i]++;
			}
		}

		// Count how many bookings each member has made
		for (int j = 0; j < num_bookings; j++) {
			if (strcmp(bookings[i].member_id, bookings[j].member_id) == 0) {
				member_counts[i]++;
			}
		}
	}

	system("cls");
	printf("\n\n");

	printf("\t\t\t\t ================================================================\n");
	printf("\t\t\t\t\t        REPORT OF TOTAL BOOKING OF TICKET  \n");
	printf("\t\t\t\t ----------------------------------------------------------------\n");

	double totalAmount = 0.0;
	for (int i = 0; i < num_bookings; i++) {
		totalAmount += bookings[i].amount;
	}
	for (int i = 0; i < num_bookings; i++) {
		printf("\t\t\t\t  %-13s %-35s RM%.2lf  \n",
			bookings[i].booking_id,
			bookings[i].passenger_name,
			bookings[i].amount);

	}
	printf("\t\t\t\t ----------------------------------------------------------------\n");
	printf("\t\t\t\t %d record(s) booking.\n", num_bookings);
	printf("\t\t\t\t ----------------------------------------------------------------\n");
	printf("\t\t\t\t Total amount of all tickets:\t\t\t    RM%.2lf\n", totalAmount);
	printf("\t\t\t\t ================================================================\n\n");

	printf("\t\t\t\t\t\t============================\n");
	printf("\t\t\t\t\t\t Train ID   |   Bookings\n");
	printf("\t\t\t\t\t\t----------------------------\n");

	int max_train_bookings = 0;
	char hottest_train_id[100];
	for (int i = 0; i < num_bookings; i++) {
		//check duplicate train id 
		int AlreadyDisplay = 0;
		for (int j = 0; j < i; j++) {
			if (strcmp(bookings[i].train_id, bookings[j].train_id) == 0) {
				AlreadyDisplay = 1;
				break;
			}
		}
		//check the hot train id 
		if (!AlreadyDisplay) {
			printf("\t\t\t\t\t\t %s       |   %d\n", bookings[i].train_id, train_counts[i]);
			if (train_counts[i] > max_train_bookings) {
				max_train_bookings = train_counts[i];
				strcpy(hottest_train_id, bookings[i].train_id);
			}
		}
	}

	printf("\t\t\t\t\t\t============================\n");
	printf("\t\t\t\t\t\t Member ID  |   Bookings\n");
	printf("\t\t\t\t\t\t----------------------------\n");

	int max_member_bookings = 0;
	char most_active_member_id[100];
	for (int i = 0; i < num_bookings; i++) {
		//check duplicate id 
		int AlreadyDisplay = 0;
		for (int j = 0; j < i; j++) {
			if (strcmp(bookings[i].member_id, bookings[j].member_id) == 0) {
				AlreadyDisplay = 1;
				break;
			}
		}
		//check the most active member 
		if (!AlreadyDisplay) {
			printf("\t\t\t\t\t\t %s       |   %d\n", bookings[i].member_id, member_counts[i]);
			if (member_counts[i] > max_member_bookings) {
				max_member_bookings = member_counts[i];
				strcpy(most_active_member_id, bookings[i].member_id);
			}
		}
	}
	printf("\t\t\t\t\t\t============================\n\n");
	printf("\t\t\t\t\t  =============================================\n");

	printf("\t\t\t\t\t\t Hottest Booking Train ID    : %s\n", hottest_train_id);
	printf("\t\t\t\t\t\t The Most Booking By member  : %s\n", most_active_member_id);
	printf("\t\t\t\t\t  =============================================\n");

	system("pause");
}
void bookingMENU() {
	int option;

	do {
		system("cls");
		printf("\n\n\t\t\t               Rapidekspres Ticket Booking System\n");
		printf("\t\t\t ==================================================================\n");
		printf("\t\t\t||             1- To ADD booking:                                 ||\n");
		printf("\t\t\t||             2- To UPDATE reserved tickets:                     ||\n");
		printf("\t\t\t||             3- To SEARCH ticket:                               ||\n");
		printf("\t\t\t||             4- To DISPLAY all booking:                         ||\n");
		printf("\t\t\t||             5- To CANCEL the booking:                          ||\n");
		printf("\t\t\t||             6- REPORT ticket:                                  ||\n");
		printf("\t\t\t||             7- MAIN MENU:                                      ||\n");
		printf("\t\t\t ===================================================================\n\n");

		do {
			printf(" Please select your choice(1-7):");
			rewind(stdin);
			scanf("%d", &option);
			if ((option > 7 || option < 1))
			{
				printf(" Invalid Option !!!\n\n");
			}
		} while (option > 7 || option < 1);

		switch (option) {
		case 1:
			addBooking();
			break;
		case 2:
			updateBooking();
			break;
		case 3:
			searchBooking();
			break;
		case 4:
			displayBooking();
			break;
		case 5:
			cancelBooking();
			break;
		case 6:
			reportBooking();
			break;
		}
	} while (option != 7);

	system("pause");
}
////////////////////////////////////////////


//////////////// MEMBER //////////////////
void memberMain() {
	char choice[10];
	system("cls");
	do {
		Member members[MAX_MEMBERS];
		int numMembers = 0;
		int loggedInIndex = -1; // Initialize loggedInIndex to -1

		// Load members from file
		FILE* file = fopen("members.txt", "r");
		if (file != NULL) {
			while (fscanf(file, "%s %[^@]@%s %s %s %s %d\n", members[numMembers].mID, members[numMembers].username, members[numMembers].password, members[numMembers].email, members[numMembers].contactNum, members[numMembers].icNum, &members[numMembers].loyaltyPoints) == 7) {
				numMembers++;
				if (numMembers >= MAX_MEMBERS) {
					printf("Too many members. Increase MAX_MEMBERS.\n");
					break;
				}
			}
			fclose(file);
		}
		else
			printf("File checking failed.\n");


		//START
   /*     printf("Count: %d\n\n",numMembers);
		for (int i = 0; i < numMembers;i++) {
			printf("%s--%s--", members[i].username, members[i].password);
		}*/
		header();
		printf("\n");
		printf("1. Login\n");
		printf("2. Register\n");
		printf("3. Search Member\n");
		printf("4. Display Members Details\n");
		printf("5. Exit\n");
		printf("\n");
		printf("Enter your choice: ");
		rewind(stdin);
		scanf("%s", &choice);


		if (strlen(choice) == 1) {
			switch (choice[0]) {

			case '1':
				if (loggedInIndex == -1) { // If not logged in
					if (login(members, numMembers, &loggedInIndex)) {
						system("cls");
						printf("Login successful.|\n");
						printf("==================\n");
						userpage(members, numMembers, &loggedInIndex); // Pass loggedInIndex to userpage()
					}
					else {
						system("cls");
						printf("\n");
						printf("Login failed. Please try again.\n");

						printf("===============================\n");
					}
				}
				else {
					printf("You are already logged in.\n");
				}
				break;
			case '2':
				system("cls");
				addMember(members, &numMembers);
				break;
			case '3':
				searchMember(members, numMembers, loggedInIndex);
				break;
			case '4':
				displayMember(members, numMembers, loggedInIndex);
				system("cls");
				break;
			case '5':
				printf("Exiting...\n");
				system("pause");
				break;
			default:
				system("cls");
				printf("Invalid choice. Please enter again.\n");
			}
		}
		else {
			printf("Invalid choice. Please enter again.\n");
		}

	} while (choice[0] != '5');

	return 0;
}
int login(Member members[], int numMembers, int* loggedInIndex) {
	char username[MAX_LENGTH];
	char password[MAX_LENGTH];

	system("cls");
	printf("=====================================\n");
	printf("|                                   |\n");
	printf("|           L  O  G  I  N           |\n");
	printf("|                                   |\n");
	printf("=====================================\n");
	printf("Enter username: ");
	rewind(stdin);
	gets(username);

	printf("Enter password: ");
	rewind(stdin);
	scanf("%s", password);


	for (int i = 0; i < numMembers; i++) {
		if (strcmp(members[i].username, username) == 0 && strcmp(members[i].password, password) == 0) {
			*loggedInIndex = i; // Set loggedInIndex to the index of the logged-in user
			return 1; // Login successful
		}
	}
	return 0; // Login failed
}
void changeInfo(Member members[], int numMembers, int* loggedInIndex) {
	char newUsername[MAX_LENGTH];
	char newPassword[MAX_LENGTH];
	char newEmail[MAX_LENGTH];
	char newContact[MAX_LENGTH];
	char newIC[MAX_LENGTH];


	edit();

	printf("Enter new username: ");
	rewind(stdin);
	gets(newUsername);

	// Check if the new username is already taken
	for (int i = 0; i < numMembers; i++) {
		if (i != loggedInIndex && strcmp(members[i].username, newUsername) == 0) {
			system("cls");
			edit();
			printf("Username '%s' is already taken or same.\nPlease choose a different username: ", newUsername);
			rewind(stdin);
			gets(newUsername);
			i = -1; // Reset the loop to check from the beginning
		}
	}
	rewind(stdin);
	printf("Enter new password: ");
	scanf("%s", newPassword);

	// Check if the new password is the same as the existing password
	for (int i = 0; i < numMembers; i++) {
		if (i != loggedInIndex && strcmp(members[i].password, newPassword) == 0) {
			system("cls");
			edit();
			printf("Password cannot be the same as the existing password.\nPlease enter a different password: ");
			rewind(stdin);
			scanf("%s", newPassword);
			i = -1;
		}
	}

	do {
		rewind(stdin);
		printf("Enter new Email: ");
		scanf("%s", newEmail);
		rewind(stdin);

		// Check if the new password is the same as the existing password
		if (strstr(newEmail, "@") == NULL || strstr(newEmail, ".com") == NULL) {
			system("cls");
			edit();
			printf("Invalid email format. Email must contain '@' and end with '.com'.\n");
			newEmail[0] = '\0';
		}
		for (int i = 0; i < numMembers; i++) {


			if (i != loggedInIndex && strcmp(members[i].email, newEmail) == 0) {
				system("cls");
				edit();
				printf("Email cannot be the same as the existing Email.\n");
				newEmail[0] = '\0';
				i = -1;
			}
		}
	} while (newEmail[0] == '\0');
	rewind(stdin);
	printf("Enter new Contact Number: ");
	scanf("%s", newContact);

	// Check if the new contact is the same as the existing contact

	for (int i = 0; i < numMembers; i++) {


		if (i != loggedInIndex && strcmp(members[i].contactNum, newContact) == 0) {
			system("cls");
			edit();
			printf("Contact Number already exists / Same as current.\nPlease enter a different Number: ");
			rewind(stdin);
			scanf("%s", newContact);
			i = -1;
		}
	}


	// Update member information
	strcpy(members[*loggedInIndex].username, newUsername);
	strcpy(members[*loggedInIndex].password, newPassword);
	strcpy(members[*loggedInIndex].email, newEmail);
	strcpy(members[*loggedInIndex].contactNum, newContact);
	strcpy(members[*loggedInIndex].icNum, members[*loggedInIndex].icNum);
	strcpy(members[*loggedInIndex].mID, members[*loggedInIndex].mID);


	printf("Your information have been changed.\n");
	system("pause");
	system("cls");
}
int saveMembers(Member members[], int numMembers) {
	FILE* file = fopen("members.txt", "w"); // Open file for writing (overwrite mode)
	if (file != NULL) {
		for (int i = 0; i < numMembers; i++) {
			fprintf(file, "%s %s@%s %s %s %s %d\n", members[i].mID, members[i].username, members[i].password, members[i].email, members[i].contactNum, members[i].icNum, members[i].loyaltyPoints);
		}
		fclose(file);
	}
	else {
		printf("Error opening file for writing.\n");
	}
}
void addMember(Member members[], int* numMembers) {
	if (*numMembers >= MAX_MEMBERS) {
		printf("Cannot add more members. Maximum limit reached.\n");
		return;
	}
	char username[MAX_LENGTH];
	char password[MAX_LENGTH];
	char email[MAX_LENGTH];
	int loyaltyPoints = 0;
	char contactNum[MAX_LENGTH];
	char icNum[MAX_LENGTH];
	char mID[MAX_LENGTH];
	int count = 0;

	do {
		regis();

		printf("Enter Member ID(M000-M999): ");
		rewind(stdin);
		scanf("%s", mID);
		count = 0;
		for (int i = 0; i < strlen(mID); i++) {
			if (isalpha(mID[i]) != 0)
				count++;
		}
		/* printf("%d %d\n", count,strlen(mID));*/
		if (mID[0] != 'M' || strlen(mID) != 4 || count != 1) {
			system("cls");

			printf("Invalid member ID format. ID must start with 'M' and have three number.\n");
			mID[0] = '\0';
		}
		for (int i = 0; i < *numMembers; i++) {
			if (strcmp(members[i].mID, mID) == 0) {
				system("cls");
				printf("Each ID just for one member. Please choose a different ID.\n");
				mID[0] = '\0';
			}

		}

	} while (mID[0] == '\0'); system("cls");

	do {
		regis();

		printf("Enter username: ");
		rewind(stdin);
		gets(username);

		// Check if the username already exists
		for (int i = 0; i < *numMembers; i++) {
			if (strcmp(members[i].username, username) == 0) {
				system("cls");
				printf("Username already exists. Please choose a different username.\n");

				username[0] = '\0';
			}
		}


	} while (username[0] == '\0'); system("cls");
	do {
		regis();


		printf("Enter password: ");
		rewind(stdin);
		scanf("%s", password);

		// Check if the username and password are the same

		for (int i = 0; i < *numMembers; i++) {
			if (strcmp(members[i].password, password) == 0) {
				system("cls");
				printf("Password already exists. Please choose a different password.\n");
				password[0] = '\0';
			}
		}

	} while (password[0] == '\0'); system("cls");

	do {
		regis();

		printf("Enter email: ");
		rewind(stdin);
		scanf("%s", email);
		if (strstr(email, "@") == NULL || strstr(email, ".com") == NULL) {
			system("cls");
			printf("Invalid email format. Email must contain '@' and end with '.com'.\n");
			email[0] = '\0';
		}
		for (int i = 0; i < *numMembers; i++) {
			if (strcmp(members[i].email, email) == 0) {
				system("cls");
				printf("Each email just for one member. Please choose a different Email.\n");
				email[0] = '\0';
			}

		}

	} while (email[0] == '\0'); system("cls");

	do {
		regis();


		printf("Enter Contact Number(601XXXXXXXX): ");
		rewind(stdin);
		scanf("%s", contactNum);

		// Check if the username and password are the same

		for (int i = 0; i < *numMembers; i++) {
			if (strcmp(members[i].contactNum, contactNum) == 0) {
				system("cls");
				printf("Each contact number just for one member. Please choose a different contact number.\n");
				contactNum[0] = '\0';
			}
		}

	} while (contactNum[0] == '\0'); system("cls");

	do {
		regis();


		printf("Enter IC Number(XXXXXX-XX-XXXX): ");
		rewind(stdin);
		scanf("%s", icNum);

		// Check if the username and password are the same

		for (int i = 0; i < *numMembers; i++) {
			if (strcmp(members[i].icNum, icNum) == 0) {
				system("cls");
				printf("Each IC number just for one member. Please choose a different IC number.\n");
				icNum[0] = '\0';
			}
		}

	} while (icNum[0] == '\0'); system("cls");

	// Add the new member
	//strcpy(members[*numMembers].username, username);
	//strcpy(members[*numMembers].password, password);
	//strcpy(members[*numMembers].email, email);
	//saveMembers(members, *numMembers);
	FILE* fadd;
	fadd = fopen("members.txt", "a");
	if (fadd == NULL) {
		printf("Error");
		exit(-1);
	}
	else {
		(*numMembers)++;
		system("cls");
		fprintf(fadd, "%s %s@%s %s %s %s %d\n", mID, username, password, email, contactNum, icNum, loyaltyPoints);
		printf("------------------------------------\n");
		printf("Member added successfully.\n");
		printf("------------------------------------\n");
		fclose(fadd);
	}
}
int userpage(Member members[], int numMembers, int* loggedInIndex) {
	char selection[10];
	int deleteResult;

	do {
		printf("Welcome! |%s|\n", members[*loggedInIndex]);
		printf("--------------------------------------\n");
		printf("|      1. Your Account Details       |\n");
		printf("|      2. Edit Account Details       |\n");
		printf("|      3. Delete Your Account        |\n");
		printf("|      4. Loyalty Point              |\n");
		printf("|      5. Logout                     |\n");
		printf("--------------------------------------\n");

		printf("Enter your selection: ");


		scanf("%s", &selection);



		if (strlen(selection) == 1) {
			switch (selection[0]) {
				//case '1':
				//    members[*loggedInIndex].loyaltyPoints += 10; // Add 10 loyalty points when booking a ticket
				//    printf("Ticket booked successfully. Loyalty points increased by 10.\n");
				//    saveMembers(members, numMembers);
				//    break;
			case '1':
				system("cls");
				check(members, numMembers, loggedInIndex);
				break;
			case '2':
				system("cls");
				changeInfo(members, numMembers, loggedInIndex); // Pass the index of the logged-in member
				saveMembers(members, numMembers);
				break;
			case '3':
				deleteResult = deleteAccount(members, &numMembers, *loggedInIndex); // Pass loggedInIndex to deleteAccount()
				if (deleteResult) {
					*loggedInIndex = -1;
					system("cls");
					printf("|   Delete Successful!   |\n");
					return 0;


					// Return to the main menu if account is successfully deleted
				}

				break;

			case '4':
				system("cls");
				loyalty(members, numMembers, loggedInIndex);


				break;
			case '5':
				system("cls");
				printf("Logging out...\n");
				*loggedInIndex = -1; // Reset loggedInIndex after logout
				return 0;
			default:
				printf("Invalid choice. Please enter again.\n");
			}
		}
		else { printf("Invalid choice. Please enter again.\n"); }
	} while (selection[0] != '5');

	return 0;
}
int searchMember(Member members[], int numMembers, int* loggedInIndex) {
	////////admin login
	struct staffDetail staff;
	FILE* freadS;
	freadS = fopen("admin.dat", "rb");
	char id[10], password[20];
	int staffInOrOut = 0;
	if (freadS == NULL) {
		printf("File checking failed. (ADMIN)\n");
		system("pause");
		return 0;
	}
	else {
		printf("Login as ANY staff to continue. \n");
		printf("Enter <id> <password> :");
		rewind(stdin);
		scanf("%6s %12s", id, password);
		while (fread(&staff, sizeof(struct staffDetail), 1, freadS) != 0) {
			//printf("%s", staff.department);
			if (strcmp(staff.id, id) == 0 && strcmp(staff.password, password) == 0) {
				writelog("Logged into system - Member", staff.id);
				printf("Logged in successfully as %s.\n", staff.name);
				staffInOrOut = 1;
				break;
			}
		}
		fclose(freadS);
		if (!staffInOrOut) { //LOGIN failed
			printf("Logged In Failed. ");
			system("pause");
			system("cls");
			return -1;
		}
	}
	///////////////
	char searchUsername[MAX_LENGTH];

	printf("Enter the username to search for: ");
	rewind(stdin);
	gets(searchUsername);

	int found = 0;

	// Search for the member with the specified username
	for (int i = 0; i < numMembers; i++) {
		if (strcmp(members[i].username, searchUsername) == 0) {
			system("cls");
			printf("==================================================\n");
			printf("Member ID: %s\n", members[i].mID);
			printf("Username: %s\n", members[i].username);
			printf("Password: %s\n", members[i].password);
			printf("Email: %s\n", members[i].email);
			printf("Contact Number: %s\n", members[i].contactNum);
			printf("IC Number: %s\n", members[i].icNum);
			printf("Loyalty point: %d\n", members[i].loyaltyPoints);
			printf("==================================================\n");

			printf("\n");
			found = 1;
			break;





		}

	}

	if (!found) {
		printf("Member with username '%s' not found.\n", searchUsername);
	}
	system("pause");
	system("cls");
}
//  ^^ADMIN LOGIN done
int deleteAccount(Member members[], int* numMembers, int* loggedInIndex) {
	char username[MAX_LENGTH];
	char password[MAX_LENGTH];

	system("cls");
	printf("=====================================\n");
	printf("|                                   |\n");
	printf("|          D  E  L  E  T  E         |\n");
	printf("|                                   |\n");
	printf("=====================================\n");
	printf("\n");
	printf("Enter your username for confirmation: ");
	rewind(stdin);
	gets(username);
	printf("Enter the password for confirmation: ");
	rewind(stdin);
	scanf("%s", password);

	int indexToDelete = -1;

	// Find the index of the account to delete
	for (int i = 0; i < *numMembers; i++) {
		if (strcmp(members[i].username, username) == 0 && strcmp(members[i].password, password) == 0) {
			indexToDelete = i;
			break;
		}
	}

	// If the account is found, confirm deletion and remove the account
	if (indexToDelete != -1) {
		printf("Are you sure you want to delete the account? (Y/N): ");
		char answer;
		scanf(" %c", &answer);
		if (answer == 'Y' || answer == 'y') {
			// Move the data of the last account to the position of the deleted account
			if (indexToDelete != *numMembers - 1) {
				strcpy(members[indexToDelete].username, members[*numMembers - 1].username);
				strcpy(members[indexToDelete].password, members[*numMembers - 1].password);
				strcpy(members[indexToDelete].email, members[*numMembers - 1].email);
			}
			// Clear the data of the last account
			memset(&members[*numMembers - 1], 0, sizeof(Member));
			// Decrement the number of members
			(*numMembers)--;
			saveMembers(members, *numMembers);
			printf("Account deleted successfully.\n");

			return 1;
			//return 1; // Account successfully deleted
			//*loggedInIndex = -1; // Reset loggedInIndex after deleting account
			//return 0; // After deleting account, return to choice menu

		}
		else {
			system("cls");
			printf("Account deletion cancelled.\n");
			return 0; // Account deletion cancelled
		}
	}
	else {
		system("cls");
		printf("Account not found.\n");
		return 0; // Account not found
	}
}
int displayMember(Member members[], int numMembers, int* loggedInIndex) {
	////////admin login
	struct staffDetail staff;
	FILE* freadS;
	freadS = fopen("admin.dat", "rb");
	char id[10], password[20];
	int staffInOrOut = 0;
	if (freadS == NULL) {
		printf("File checking failed. (ADMIN)\n");
		system("pause");
		return 0;
	}
	else {
		printf("Login as ANY staff to continue. \n");
		printf("Enter <id> <password> :");
		rewind(stdin);
		scanf("%6s %12s", id, password);
		while (fread(&staff, sizeof(struct staffDetail), 1, freadS) != 0) {
			//printf("%s", staff.department);
			if (strcmp(staff.id, id) == 0 && strcmp(staff.password, password) == 0) {
				writelog("Logged into system - Member", staff.id);
				printf("Logged in successfully as %s.\n", staff.name);
				staffInOrOut = 1;
				break;
			}
		}
		fclose(freadS);
		if (!staffInOrOut) { //LOGIN failed
			printf("Logged In Failed. ");
			system("pause");
			system("cls");
			return -1;
		}
	}
	///////////////
	for (int i = 0; i < numMembers; i++) {


		printf("==================================================\n");
		printf("Member ID: %s\n", members[i].mID);
		printf("Username: %s\n", members[i].username);
		printf("Password: %s\n", members[i].password);
		printf("Email: %s\n", members[i].email);
		printf("Contact Number: %s\n", members[i].contactNum);
		printf("IC Number: %s\n", members[i].icNum);
		printf("Loyalty point: %d\n", members[i].loyaltyPoints);
		printf("==================================================\n");

		printf("\n");
	}
	system("pause");
	system("cls");
}
//  ^^ADMIN LOGIN done
int loyalty(Member members[], int numMembers, int* loggedInIndex) {

	printf("=====================================\n");
	printf("|                                   |\n");
	printf("|          R  E  W  A  R  D         |\n");
	printf("|                                   |\n");
	printf("=====================================\n");
	printf("\n");
	printf("Your loyalty points: %d\n", members[*loggedInIndex].loyaltyPoints);
	printf("Please exchange your reward at our train counter/train canteen cabin\n");
	printf("Reward List:\n");
	printf("\n");
	printf("===============================================================\n");
	printf("|Maggi Curry: 100pt\tNasi Lemak: 250pts\tNescafe: 80pts          |\t\n");
	printf("|Milo Ais:    100pt\tMee Mamak:  170pts \tSingapore MeeHun: 280pts|\t\n");
	printf("|Chicken Rice:200pt\tNasi Goreng:350pts\tRM15 Voucher:     580pts|\t\n");
	printf("===============================================================\n");

	system("pause");
	system("cls");
}
int check(Member members[], int numMembers, int* loggedInIndex) {
	printf("=====================================\n");
	printf("|                                   |\n");
	printf("|        D  E  T  A  I  L  S        |\n");
	printf("|                                   |\n");
	printf("=====================================\n");
	printf("\n");
	printf("=============================================\n");
	printf("| Your Member ID: %s\n", members[*loggedInIndex].mID);
	printf("| Your Username: %s\n", members[*loggedInIndex].username);
	printf("| Your Password: HIDDEN\n");
	printf("| Your Email: %s\n", members[*loggedInIndex].email);
	printf("| Your Contact-Num: %s\n", members[*loggedInIndex].contactNum);
	printf("| Your IC-Num: HIDDEN\n");
	printf("| Your loyalty points: %d\n", members[*loggedInIndex].loyaltyPoints);
	printf("=============================================\n");


	system("pause");
	system("cls");
}
void header() {

	printf("=====================================\n");
	printf("|                                   |\n");
	printf("|            M E M B E R            |\n");
	printf("|                                   |\n");
	printf("=====================================\n");
};
void edit() {
	printf("=====================================\n");
	printf("|                                   |\n");
	printf("|              E  D  I  T           |\n");
	printf("|                                   |\n");
	printf("=====================================\n");
	printf("\n");
}
void regis() {
	printf("=====================================\n");
	printf("|                                   |\n");
	printf("|      R  E  G  I  S  T  E  R       |\n");
	printf("|                                   |\n");
	printf("=====================================\n");
}




