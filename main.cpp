#include <iostream>
#include <fstream>
#include <regex>
#include <vector>
#include <map>
#include <set>
#include <climits>

#define ll long long
#define pb push_back

#define inf INT_MAX
#define ninf INT_MIN

#define MAXL 100001

#define fo(i,a,b)               	for(int i=a;i<b;i++)
#define foreach(v, c)               for( typeof( (c).begin()) v = (c).begin();  v != (c).end(); ++v)
#define all(a)                      a.begin(), a.end()
#define in(a,b)                     ( (b).find(a) != (b).end())
#define pb                          push_back
#define fill(a,v)                    memset(a, v, sizeof a)
#define sz(a)                       ((int)(a.size()))
#define mp                          make_pair

using namespace std;

const string ops[] = {
	";",
	",",
	
	// data types
	"int",
	"float",
	"string",
	"double",
	"long",
	"long long",

	// control flow
	"if",
	"else",
	"switch",
	"case",
	"do",
	"while",
	"for",

	// encapsulation
	"(",
	"{",
	"[",

	// member access
	".",
	"->",
	
	// arithmetic
	"+",
	"-",
	"*",
	"/",
	"%",
	"=",
	"++",
	"--",

	// logical
	"<",
	">",
	"<=",
	">=",
	"==",
	
	// keywords
	"break",
	"continue",
	"class",
	"struct",
	"default",
	"goto",
	"operator",
	"return"

};

set<string> operators;
map<string, int> operator_counts, operand_counts;

class redundancy_pair
{
	public:
		string f,s;
		int multiplicity;

		redundancy_pair( string a, string b, int multiplicity )
		{
			this->f = a, this->s = b, this->multiplicity = multiplicity;
		}
};

// redundancy pairs are necessary to remove matches that match multiple
// patterns for example c++ matches both '++' and '+', multiplicity is
// required to make adjustments to the count variables 
vector <redundancy_pair> redundancy_pairs;

void _popualate_redundancy_pairs()
{
	for ( set<string>::iterator i = operators.begin(); i != operators.end(); i++)
	{
		for (  set<string>::iterator j = operators.begin(); j != operators.end(); j++ )
		{
			if ( (*i) != (*j) )
			{
				// find num occurences in strings
				int num_occur = 0 , pos = 0;
				while ( (pos = (*i).find(*j, pos)) != string::npos )
				{
					num_occur++;
					pos += (*j).length();
				}
				if ( num_occur > 0 )
					redundancy_pairs.push_back( redundancy_pair( *j , *i , num_occur ) );
			}
		}
	}
}


void _popualate_operators ()
{
	int size = *(&ops + 1) - ops; 
	for ( int i=0 ; i < size; i++ )
		operators.insert( ops[i] );
}

void _adjust_redundancy()
{
	for ( vector<redundancy_pair>::iterator it = redundancy_pairs.begin(); it != redundancy_pairs.end(); it++ )
	{
		// second exists
		if ( operator_counts.find( (*it).s ) != operator_counts.end())
			operator_counts[(*it).f] = operator_counts[(*it).f] - operator_counts[(*it).s]*((*it).multiplicity);
	}

	return;
}

int main()
{

	// fill the operators
	_popualate_operators();
	_popualate_redundancy_pairs();

	for ( vector<redundancy_pair>::iterator it = redundancy_pairs.begin(); it != redundancy_pairs.end(); it++)
		cout << (*it).f << " " << (*it).s << " " << (*it).multiplicity << endl;

	// we now create a regex for identifier
	regex identifier_def( "[A-Za-z][A-Za-z0-9]*" );
	smatch sm;
	
	ifstream file( "code.txt" );
	string input;

	if ( file.is_open() )
	{
		while ( getline( file, input ) )
		{
			// now check for operators in the line
			for ( set<string>::iterator op = operators.begin(); op != operators.end(); op++)
			{	
				int pos = 0;
				// for every operator scan the entire line for multiple matches
				while (( pos = input.find( *op, pos )) != string::npos)
				{
					// found an operator 
					if ( operator_counts.find( *op ) == operator_counts.end() )
						operator_counts.insert({ *op, 1 });
					else
						operator_counts[*op]++;

					pos += (*op).length();
				}
			}
			
			// now lets check for identifiers
			// while( regex_search(  ) )
		}

		_adjust_redundancy();
	}
	
	int N1=0;
	for ( map<string, int>::iterator it=operator_counts.begin(); it != operator_counts.end(); it++ )
	{
		cout << (*it).first << " " << (*it).second << endl;
		N1 += (*it).second;
	}

	cout << N1 << endl;
}


