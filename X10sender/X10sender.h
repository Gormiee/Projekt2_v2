#pragma once

class X10sender
{
	public:
	X10sender();
	void sendBit(int bit);
	const int startBits_ = 1110;
	const int stopBits_ = 000000;
	const int lysOgLys_ = 010110;
	const int kunLys_ = 011001;
	const int kunLyd_ = 011010;
	const int kunAlarm_ = 100101;
	const int stopSim_ = 101001;
	const int LysiGogK = 100110;
	private:
	int UC_;
	
};

