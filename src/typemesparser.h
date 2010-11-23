#include <string>
class AQueue;
using namespace std;
class QueTypeParser
{
private:
	int count_que;
	int max_count_que;
	string** prefix;
        AQueue** que;
public:

	QueTypeParser(int);
	~QueTypeParser();
	void AddPair(string*,AQueue*);
	AQueue* TypeParse(string&);
};
