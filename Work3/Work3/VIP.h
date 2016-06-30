#ifndef VIP_H
#define VIP_H
#include<string>
using namespace std;

class VIP
{
private:
	string name;
	bool IsVIP;
	int points;
public:
	VIP(string name,bool IsVIP);
	string OutName();
	int OutPoints();

	void SetPoints(int points);
};

#endif
