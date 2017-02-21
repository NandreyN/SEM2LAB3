#include <iostream>
#include <algorithm>
#include <set>
#include <assert.h>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include  <numeric>

using namespace std;

void split(const string& str, vector<string>& target)
{
	istringstream iss(str);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(target));
}

int main()
{
	// First string of an input file contains info on all the species of fishes
	// Other n lines contain info about each fisherman`s catch. Fisherman`s id - number of string in input file by its order

	set<string> allTypes;
	vector<string> auxiliary;
	map<int, vector<string>> fishermanData;

	fstream in("in.txt");
	assert(in.is_open());
	string data;  getline(in, data);

	split(data, auxiliary); // getting vector of all species of fishes
	copy(auxiliary.begin(), auxiliary.end(), inserter(allTypes, allTypes.begin())); // filling set with vect data
	auxiliary.clear();

	for (int id = 1; !in.eof(); id++)
	{
		getline(in, data);
		split(data, auxiliary);
		fishermanData.insert(make_pair(id, auxiliary));
		auxiliary.clear();
	}

	in.close();

	ofstream out; out.open("out.txt", ios::trunc);
	assert(out.is_open());
	// Each fisherman has ...
	for_each(fishermanData.begin(), fishermanData.end(), [&out](pair<int, vector<string>> pair)
	{
		out << "Fisherman" << pair.first << " : "; 
		copy(pair.second.begin(), pair.second.end(), ostream_iterator<string>(out, "  ")); 
		out << endl;
	});

	out.close();
	return 0;
}