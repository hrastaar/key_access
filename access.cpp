//ACCESS by Rastaar Haghi
//Started on 12/17/18
//Personal Project

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

/*
FUNCTION OF FILE: 

1. CREATE USERS IN A NETWORK WHO ALL HAVE OWN PERSONAL INFO
AND KEY NUMBER FOR THEIR OWN ACCOUNT ACCESS. 

2. THEY CAN SHARE THAT KEY WITH OTHER USERS BY PROVIDING INFO 
ON THE OTHER USER TO ADD TO THEIR PERSONAL KEY NETWORK. 

3. THERE WILL BE A FUNCTION THAT CLEARS EVERYBODY IN THEIR KEY
ACCESS LIST (PANIC MODE).

4. THERE WILL BE A FUNCTION TO CHANGE THE KEY THEY HAVE FOR A 
NEW ONE. 

5. THEY CAN PRINT THE USERS WHO HAVE ACCESS TO THEIR KEY

6. USERS CAN TRY UNLOCKING A LOCK WITH THEIR KEYS TO SEE IF THEY
HAVE ACCESS TO THAT DOOR, WHICH WILL HOLD A SPECIFIC MESSAGE.

7. THE OWNER OF A KEY CAN CHANGE THEIR KEY'S INFORMATION

8. OWNER OF THE KEY CAN WRITE A LOCK'S MESSAGE INTO A FILE 
THAT THEY SAVE.
*/

/*
HEADER FILE FOR USERS 
*/

struct Key
{
	int key_num;
	string message;
};

class User {
	public:

		User(int i_ID, string i_name, int i_personal_key, string password); //CONSTRUCTOR
		~User(); //DECONSTRUCTOR

		void add_user(int i_ID); //ADD USER WITH THE ID GIVEN
		void delete_user(int i_ID); //REMOVE USER WITH THE ID GIVEN
		void panic_mode(); //DELETE ALL USERS FROM KEY LIST
		void change_key_num(int i_personal_key); //CHANGE KEY NUMBER
		void change_message(string input);

		//RETURN MEMBER VARIABLES FOR EASY ACCESS
		int return_IDnum();
		string return_name();
		vector <int> return_key_shared();
		int key_shared_size();
		int return_keynum();
		string return_keymessage();
		string return_password();

	private:
		int IDnum;
		string password;
		string name;
		Key personal_key; //HAS A NUMBER AND MESSAGE
		vector <int> key_shared;
};

//CREATES A USER
User::User(int i_ID, string i_name, int i_personal_key, string i_password)
{
	IDnum = i_ID;
	name = i_name;
	personal_key.key_num = i_ID;
	personal_key.message = "";
	password = i_password;
}

//DELETES A USER AND HIS KEY
User::~User() 
{
}

//ADD A USER BY PUSHING BACK KEY_SHARED
void User::add_user(int i_ID)
{
	key_shared.push_back(i_ID);
}

//REMOVE A USER BY SEARCHING FOR THE ID
void User::delete_user(int i_ID)
{
	int index_found;
	for(int i = 0; i < key_shared.size(); i++)
	{
		if(key_shared[i] == i_ID)
		{
			index_found = i; //RECORD THE INDEX LOCATION FOUND
		}
	}
	//ERASE THAT INDEX FROM THE KEY_SHARED
	key_shared.erase(key_shared.begin() + index_found);
}



//CLEAR ALL OF THE KEY_SHARED VECTOR IN PANIC MODE
void User::panic_mode()
{
	key_shared.clear();
}

//CHANGE THE KEY NUMBER
void User::change_key_num(int i_personal_key)
{
	personal_key.key_num = i_personal_key;
}

//CHANGE KEY MESSAGE
void User::change_message(string input)
{
	personal_key.message = input;
}

//RETURN MEMBER DATA FUNCTIONS BELOW
/*-----------------------------------------------------------------*/
//RETURN ID
int User::return_IDnum()
{
	return IDnum;
}

//RETURN NAME
string User::return_name()
{
	return name;
}

//RETURN KEY_SHARED VECTOR
vector <int> User::return_key_shared()
{
	return key_shared;
}

//RETURN SIZE OF SHARED VECTOR
int User::key_shared_size()
{
	return key_shared.size();
}

//RETURN PERSONAL KEY
int User::return_keynum()
{
	return personal_key.key_num;
}

//RETURN MESSAGE
string User::return_keymessage()
{
	return personal_key.message;
}

//RETURN PASSWORD
string User::return_password()
{
	return password;
}

/*
END OF THE HEADER FILE FOR USERS 
*/





/*------------------------------------------------------------------*/





/*
HEADER FILE FOR NETWORK OF USERS
*/

class Network {
	public:
		Network();
		~Network();
		void new_user(string input_name, int input_key, string passcode);
		int add_keyshare(string user1, string user2);
		int remove_keyshare(string user1, string user2);

		int getID(string name1);
		User* get_User(int i_index);
	private:
		vector <User*> keynetwork;
};

//INITIALIZE A NETWORK TO ADD USERS
Network::Network()
{
	//DOES NOTHING 
}

//DELETE EACH DYNAMICALLY ALLOCATED USER
Network::~Network()
{
	for(int i = 0; i < keynetwork.size(); i++)
	{
		delete keynetwork[i];
	}
}

void Network::new_user(string input_name, int input_key, string passcode)
{
	int temp_index = keynetwork.size();
	User *temp = new User(temp_index, input_name, input_key, passcode);
	keynetwork.push_back(temp);
}


//ADD A USER TO THE KEYSHARE
int Network::add_keyshare(string user1, string user2)
{
	if(user1 == user2)
	{
		return -1;
	}
	//GET THEIR ID NUMBERS
	int user1_ID = getID(user1);
	int user2_ID = getID(user2);

	//ADD USER2 TO USER1 KEY CHAIN
	keynetwork[user1_ID]->add_user(user2_ID);
	return 0;

}
int Network::remove_keyshare(string user1, string user2)
{
	if(user1 == user2)
	{
		return -1;
	}
	//GET THEIR ID NUMBERS
	int user1_ID = getID(user1);
	int user2_ID = getID(user2);

	keynetwork[user1_ID]->delete_user(user2_ID);
	return 0;
}
/*------------------------------------------------------*/
//ACCESS MEMBER VARIABLES
User* Network::get_User(int i_index)
{
	return keynetwork[i_index];
}
int Network::getID(string i_name)
{
	for(int i = 0; i < keynetwork.size(); i++)
	{
		if(i_name == keynetwork[i]->return_name())
			return keynetwork[i]->return_IDnum();
	}
	//IF NOT FOUND 
	return -1;
}
/*
END OF THE HEADER FILE FOR NETWORK OF USERS
*/





/*------------------------------------------------------*/





/*
START OF THE MAIN FUNCTION 
*/

int main()
{
	Network running_network;
	cout << "Welcome to the Key Manager" << endl;
	cout << "Option 1: Add a User to Network" << endl;
	cout << "Option 2: Log In Attempt" << endl;

	int userinput;
	do{
		cin >> userinput;

		//ADD A USER TO THE KEY NETWORK
		if(userinput == 1)
		{
			int temp_id;
			string temp_name1, temp_name2;
			int temp_key = rand() % 10000;
			string temp_pass;

			cout << "Please enter ID" << endl;
			cin >> temp_id;
			cout << "Please enter your name" << endl;
			cin >> temp_name1 >> temp_name2;
			cout << "Please enter your password" << endl;
			cin >> temp_pass;
			string temp_name_compressed = temp_name1 + " " + temp_name2;
			running_network.new_user(temp_name_compressed, temp_key, temp_pass);

			cout << "Successfully added " << temp_name_compressed << " to the Key Network!" << endl;
		}
		else if(userinput == 2)
		{
			string name1, name2;
			string samplepassword;

			cout << "Log into your account" << endl;
			cout << "Username: " << endl;
			cin >> name1 >> name2;
			cout << "Enter Password: " << endl;
			cin >> samplepassword;

			int checkon = running_network.getID(name1 + " " + name2);
			string correctpass = running_network.get_User(checkon)->return_password();

			//BAD LOGIN
			if(samplepassword != correctpass)
			{
				cout << "Wrong Password" << endl;
			}
			//SUCCESSFUL LOGIN
			else
			{
				cout << "Logged in Successfully" << endl;
				cout << endl;
				cout << "What would you like to do?" << endl;

				cout << "Option 1: Share Key with a User" << endl;
				cout << "Option 2: Remove a User from Key Network" << endl;
				cout << "Option 3: Check Users who have access to Key" << endl;
				int access_input;
				do{
					cout << "Option 1: Share Key with a User" << endl;
					cout << "Option 2: Remove a User from Key Network" << endl;
					cout << "Option 3: Check Users who have access to Key" << endl;

					cin >> access_input;

					//GIVE KEY ACCESS
					if(access_input == 1)
					{
						string firstname1, firstname2, lastname1, lastname2;
						cout << "Who's key would you like to share? (first name, then last name)" << endl;
						cin >> firstname1 >> lastname1;
						string completename1 = firstname1 + " " + lastname1;
						cout << "Who would you like to add? (first name, then last name)" << endl;
						cin >> firstname2 >> lastname2;
						string completename2 = firstname2 + " " + lastname2;
//NEED TO MAKE SURE USER EXISTS OR ELSE SEGMENTATION FAULT
						running_network.add_keyshare(completename1, completename2);
					}

					//REMOVE KEY ACCESS
					else if(access_input == 2)
					{
						string firstname1, firstname2, lastname1, lastname2;
						cout << "Who's key would you like to affect? (first name, then last name)" << endl;
						cin >> firstname1 >> lastname1;
						string completename1 = firstname1 + " " + lastname1;
						cout << "Who would you like to remove access from? (first name, then last name)" << endl;
						cin >> firstname2 >> lastname2;
						string completename2 = firstname2 + " " + lastname2;
//NEED TO CHECK IF USER EXISTS ON LIST OR ELSE SEGMENTATION FAULT
						running_network.remove_keyshare(completename1, completename2);
					}

					//PRINT KEY LIST
					else if(access_input == 3)
					{
						string firstname1, lastname1;
						cout << "Who's key would you like to check? (first name, then last name)" << endl;
						cin >> firstname1 >> lastname1;
						string completename1 = firstname1 + " " + lastname1;
						int checkon = running_network.getID(completename1);
						if(checkon == -1)
						{
							cout << "User Not Found" << endl;
						}
						else
						{
							vector <int> tempvec = running_network.get_User(checkon)->return_key_shared();
							for(int i = 0; i < tempvec.size(); i++)
							{
								cout << "List of Members:" << endl;
								cout << "User " << (i+1) << ": " << tempvec[i] << endl;
							}
							cout << "List Size: " << tempvec.size() << endl;
						}
					}
				} while((access_input > 0 && access_input < 4) && !cin.fail()); //ENDS LOGIN WHILE LOOP
			} //ENDS LOGGED IN LOOP
		} //ENDS USERINPUT == 2 IF STATEMENT
	} while((userinput > 0 && userinput < 10) && !cin.fail()); //ENDS BIG WHILE LOOP
	return 0;
}

/*
END OF THE MAIN FUNCTION
*/

/*------------------------------------------------------*/




