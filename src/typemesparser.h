#include <string>
class AQueue;
using namespace std;

struct QuePref
{
	string* prefix;
        AQueue* que;
};

class QueTypeParser
{
private:
	int count_que;
	int max_count_que;
	QuePref* queue;
public:

	QueTypeParser(int);
	~QueTypeParser();
	void AddPair(string*,AQueue*);
	AQueue* TypeParse(string&);
};
