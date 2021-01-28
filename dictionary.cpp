#include <bits/stdc++.h>
using namespace std;

// CONSTANTS
const int KEY_SIZE = 10;
const int WEEK_DAYS = 7;

// STRUCTURE 
struct Dictionary {
	char key[KEY_SIZE];
	int value;
};

string days[WEEK_DAYS] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
void input (vector<Dictionary> &D, int n);
void output (vector<Dictionary> &D);
string deduce_day (int year, int month, int day);
vector<Dictionary> solution (const vector<Dictionary> &D, int n);

int main()  {
	int number_of_entries;
	
	try {
		cout << "Enter the numbers of entries in Dictonary: ";
		cin >> number_of_entries;
		
		if (number_of_entries <= 0 || number_of_entries > 1e6) {
			throw 0;
		}
	}
	catch (...) {
		cout << "\nINVALID NUMBER_OF_ENTRIES\n";
		return 0;
	}
	
	vector<Dictionary> dictionary(number_of_entries);
	 
	// INPUT  
	input (dictionary, number_of_entries);
	
	// PROCESS
	vector<Dictionary> ans = solution (dictionary, number_of_entries);
	
	// OUTPUT
	output (ans);
	
	return 0;
}

void input (vector<Dictionary> &D, int n) {
	for (int indx = 0; indx < n; indx++) {
		for (int str_indx = 0; str_indx < KEY_SIZE; str_indx++) {
			cin >> D[indx].key[str_indx];
		}
		cin >> D[indx].value;
	}
}

void output (vector<Dictionary> &D) {
	cout << "{";
	for (int indx = 0; indx < WEEK_DAYS; indx++) {
		cout << "\'" << D[indx].key << "\': " << D[indx].value << ", ";
	}
	cout << "\b\b}";
}

string deduce_day (int year, int month, int day) {
	// CAN VALIDATE DATE USING TRY CATCH BLOCK
	try {
		if (year < 1970 || year > 2100) {
			throw 0;
		}
		if (month > 12 || month < 1) {
			throw 1;
		}
		if (day > 31 || day < 1) {
			throw 2;
		}
	}
	catch (int i) {
		cout << "\nINVALID DATE EXCEPTION\n";
		if (i == 0) {
			cout << "INVALID YEAR";
		}
		else if (i == 1) {
			cout << "INVALID MONTH";
		}
		else {
			cout << "INVALID DAY";
		}
		exit(0);
	}
	
	int lookUp[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};  
    year -= (month < 3);  
    
    int day_indx = (year + (year / 4) - (year / 100) +  (year / 400) + lookUp[month - 1] + day) % 7;  
	day_indx = (day_indx == 0? 7: day_indx);

    return days[day_indx - 1];
}

vector<Dictionary> solution (const vector<Dictionary> &D, int n) {
	vector<Dictionary> ans(WEEK_DAYS);
	map <string, int> hash;
	
	for (int indx = 0; indx < n; indx++) {
		int year, month, day;
	
		// KEY FORMAT - YYYY-MM-DD
		year = (D[indx].key[0] -'0') * 1000 + (D[indx].key[1] -'0') * 100 + (D[indx].key[2] -'0') * 10 + (D[indx].key[3] -'0');
		month = (D[indx].key[5] -'0') * 10 + (D[indx].key[6] -'0');
		day = (D[indx].key[8] -'0') * 10 + (D[indx].key[9] -'0');
				
		string str = deduce_day (year, month, day);
		hash[str] += D[indx].value;
	}
	
	
	for (int indx = 0; indx < WEEK_DAYS; indx++) {
		for (int str_indx = 0; days[indx][str_indx] != '\0'; str_indx++) {
			ans[indx].key[str_indx] = days[indx][str_indx];
		}
		
		// IF PRESENT
		if (hash.find (days[indx]) != hash.end()) {
			ans[indx].value += hash[days[indx]];
		}
		// ELSE TAKE MEAN OF PREV & NEXT DAY
		else {
			// PREV & NEXT
			if (hash.find(days[indx - 1]) != hash.end() && hash.find(days[indx + 1]) != hash.end()) {
				ans[indx].value = (hash[days[indx - 1]] + hash[days[indx + 1]]) / 2;
			}
			// PREV & PREV_PREV
			else if (hash.find(days[indx - 1]) != hash.end() && hash.find(days[indx - 2]) != hash.end()) {
				ans[indx].value = 2 * hash[days[indx - 1]] -  hash[days[indx - 2]];
			}
			// NEXT & NEXT_NEXT
			else if (hash.find(days[indx + 1]) != hash.end() && hash.find(days[indx + 2]) != hash.end()) {
				ans[indx].value = (2 * hash[days[indx + 1]]) -  hash[days[indx + 2]];
			}
			// Nth TERM OF AP 
			else {
				int f = hash["Mon"];
				int l = hash["Sun"];
				int d = (l - f) / 6;
				int term = f +((indx + 1) * d);
				ans[indx].value = term;
			}
		}
	}
		
	return ans;
}
