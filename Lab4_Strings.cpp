/* Name: Seth John
   Pawprint: scjc68
   ECE 3220 Lab 4
   Date: 03/05/2018
   Monday Lab Section Part 1*/

// Lab4_strings.cpp
// Author: Luis Rivera

// IMPORTANT NOTE: YOU MAY NEED TO COMPILE ADDING THE FOLLOWING FLAG: -std=c++11
//                 OR: -std=c++0x
// Example:  g++ Lab4_strings.cpp -o Lab4_strings -std=c++11
//      or:  g++ Lab4_strings.cpp -o Lab4_strings -std=c++0x
// Some initialization methods and other things are not supported by the old standard. 

#include <iostream>
#include <string>
#include <cctype>
#include <fstream>

using namespace std;

// Complete the assignments stated in the comments.
int main()
{
// ****************************************************************************
// Declare and initialize four or five strings. Use different ways of
// initializing, as shown in Table 7.1 (Lecture 7). 
// Try all the operations in Table 7.2 (Lecture 7) using the strings that
// you declared.
// ****************************************************************************

// -----------------------------------------------------------------------
	
	//Author: Luis Rivera 
	string s1, s2("Hello"), s3 = "World";
	cout << "\nEnter a word:" << endl;
	cin >> s1;
	cin.ignore();	// to consume the '\n' character. Otherwise, you may get issues with
					// the getline() below. Try commenting this out. Any issues?
	
	string s4(s1);
	
	cout << "s1:" << s1 << endl
		 << "s2:" << s2 << endl
		 << "s3:" << s3 << endl
		 << "s4:" << s4 << endl;
	
	s1 = s2 + s3;
	cout << s1 << endl;

	/*string line;
	cout << "\nEnter some text:" << endl;
	getline(cin, line);
	cout << line << endl << endl;*/
	
	//My Code
	cout << endl << "Table 7.2 examples" << endl << endl;

	filebuf fp;
	fp.open("ex_words.txt",std::ios::out);
	ostream os(&fp); //sets output stream variable os to the file
	cout << "writing s3: "<< s3 << " to the file ex_words.txt" << endl;
	os << s3; //writes the string s3 to the file
	fp.close();
	fp.open("ex_words.txt",std::ios::in);
	istream is(&fp); //sets new input stream to the file
	cout << "reading ex_words.txt into s1" << endl;
	is >> s1; //copies what is in the file to string s1;
	fp.close();
	cout << "String s1 is now " << s1 << endl;
	
	fp.open("ex_words.txt",std::ios::in);
	istream is2(&fp); //new input stream
	getline(is2,s2); //using get line to read an entire line
	fp.close();
	cout << endl;
	cout << "copying ex_words.txt into s2 using get line." << endl 
	<< "s2 is now " << s2 << endl;
	
	if(!s1.empty())  //checks to see if s1 is empty and prints a message if not
	{
		cout << endl;
		cout << "s1 is not empty and contains:" << s1 << endl;
	}
	
	cout << endl;
	int i = 0;
	for(i = 0; i<s2.size();i++) //displays each character for the string using string[i] notation
	{
		cout << s2[i];
	}
	
	cout << endl << endl;
	
	string s5("Checking");
	string s6 = "Test";
	
	cout << "s5: " << s5 << " s6: " << s6 << " s5+s6: " << s5+s6 << endl; // using + operator
	
	cout << "setting s5 = s6 .." << endl;
	s5 = s6; // setting strings equal to each other
	cout << "s5: " << s5 << " s6: " << s6 << endl;
	
	
	if(s5==s6) //if the are equal print message
	{
		cout << "s5 and s6 are equal!" << endl;
	}
	
	if(s1!=s5) //if s1 and s5 are not equal print message
	{
		cout << "s1 is not equal to s5" << endl;
	}
	string s7("ABCD");
	string s8("EFGH");
	if(s7>s8) //print message if s7 is bigger than s8 
	{
		cout << s7 << " > " << s8 << endl;
	}
	if(s7<s8) //print message if s7 is less than s8 
	{
		cout << s7 << " < " << s8 << endl;
	}
	if(s7>=s8) //print message if s7 is bigger than or equal s8 
	{
		cout << s7 << " >= " << s8 << endl;
	}
	if(s7<=s8) //print message if s7 is less than or equal s8 
	{
		cout << s7 << " <= " << s8 << endl;
	}


// ****************************************************************************
// Use "Range for" loops (L7_Ex6_Strings.cpp) and operations in table 7.3 to:
// 1) Count the number of letters in your input line above;
// 2) Count the number of digits;
// 3) Count the number of words (may be separated by white spaces, dots, etc.);

// 4) change the case of the letters (upper to lowercase and vice-versa).
// 5) Replace any whitespace with a dot ('.').
// Print the converted text in 4) and 5)
// ****************************************************************************

	//Author: Luis Rivera Part (Modified)
	
	int z=0, v=0, b=0;
	string mystring;
	cout << "\nEnter some text:" << endl;
	getline(cin, mystring);		// Can get a string with whitespaces
	cout << mystring << endl;

	// auto specifier: compiler automatically deduces the type from the initializer
	auto q = mystring.size();
	cout << "Number of characters in the string: " << q << endl
		 << "First character: " << mystring[0] << endl	// one way to access chars.
		 << "First character: " << mystring.at(0) << endl	// another way
		 << "Last character:  " << mystring[q-1] << endl
		 << "Last character:  " << mystring.at(q-1) << endl << endl;

	// "Range for" and some character operations
	for(auto c:mystring)	// "For every char in the string mystring"
	{
		cout << c;	// c is a character in mystring
		if(isalpha(c)) {
			cout << " is a letter. ";
			c = toupper(c);
			cout << "Uppercase: " << c << endl;
		}
		else
			cout << " is not a letter." << endl;
	}
	for(auto c:mystring)	// "For every char in the string mystring"
	{
		if(isalpha(c)) 
		{
			z++;
		}
		if(isdigit(c))
		{
			v++;
		}
		if(isspace(c))
		{
			b++;
		}
	}
	b++;
	cout << endl << "The number of letters in your input line above is " << z << endl;
	cout << "The number of digits in your input line above is " << v << endl;
	cout << "The number of words in your input line above is " << b << endl;
	
	//My part of the code
	
	string anyline;
	cout << "\nEnter some text, and finish it with an &:" << endl;
	getline(cin, anyline, '&');	// the delimiter can be any character
	cout << endl << anyline << endl;
	
	for(auto &c : anyline)
	{
		//loops through each character of the string 
		if(islower(c)) //if lowercase change to upper
		{
			c = toupper(c);
		}
		else if(isupper(c)) //if upper case change to lower
		{
			c = tolower(c); //if 'space' set character to '.'
		}
		if(isspace(c))
		{
			c = '.';
		}
	}
	cout << endl << anyline << endl; //print output new string

	return 0;
}