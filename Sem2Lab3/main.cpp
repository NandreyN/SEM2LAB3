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
using namespace std;

void split(const string& str, vector<string>& target)
{
	istringstream iss(str);
	copy(istream_iterator<string>(iss), istream_iterator<string>(), back_inserter(target));
}

ostream& dline(ostream& o)
{
	o << "______________________________________________________________________________________________________________" << endl;
	return o;
}

void getUnion(const vector<set<string>>& setsCollection, set<string>& target)
{
	assert(setsCollection.size() > 0);
	for_each(setsCollection.begin(), setsCollection.end(), [&target](const set<string>& st)
	{
		target.insert(st.begin(), st.end());
	});
}

void getIntersection(const vector<set<string>>& setsCollection, set<string>& target)
{
	set<string> bk;
	assert(setsCollection.size() > 0);
	if (setsCollection.size() == 1) { target = setsCollection[0]; return; }

	set_intersection(setsCollection[0].begin(), setsCollection[0].end(), setsCollection[1].begin(), setsCollection[1].end(), inserter(bk, bk.begin()));
	if (setsCollection.size() == 2) { target = bk; return; }
	for (int i = 2; i < setsCollection.size(); i++)
	{
		target.clear();
		set_intersection(setsCollection[i].begin(), setsCollection[i].end(), bk.begin(), bk.end(), inserter(target, target.begin()));
		bk = target;
	}
	return;
} 

int main()
{
	// First string of an input file contains info on all the species of fishes
	// Other n lines contain info about each fisherman`s catch. Fisherman`s id - number of string in input file by its order

	set<string> allTypes;
	vector<string> auxiliary;
	map<int, set<string>> fishermanData;
	vector<set<string>> fishermanSets;

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

		set<string> st;
		copy(auxiliary.begin(), auxiliary.end(), inserter(st, st.begin()));
		fishermanSets.push_back(st);
		fishermanData.insert(make_pair(id, st));
		auxiliary.clear();
	}
	in.close();

	ofstream out; out.open("out.txt", ios::trunc);
	assert(out.is_open());
	// Each fisherman has ...
	set<string> intersection;  getIntersection(fishermanSets, intersection);
	out << "Intersection : ";
	copy(intersection.begin(), intersection.end(), ostream_iterator<string>(out, " "));

	out << endl << dline;

	set<string> fUnion; getUnion(fishermanSets,fUnion);
	out << "Union : ";
	copy(fUnion.begin(), fUnion.end(), ostream_iterator<string>(out, " "));
	out << endl << dline;

	set<string> diff;
	set_difference(allTypes.begin(), allTypes.end(), fUnion.begin(), fUnion.end(), inserter(diff, diff.begin()));
	out << "Difference : ";
	copy(diff.begin(), diff.end(), ostream_iterator<string>(out, " "));
	out << endl << dline;
	out.close();
	return 0;
}