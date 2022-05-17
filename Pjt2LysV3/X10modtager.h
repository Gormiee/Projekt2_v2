#pragma once

class X10modtager
{
	public:
	X10modtager(); //måske setpoint
	int listenUseCase(int antalBits, int & modtaget);
	void setCurrentUseCase(int useCase);
	int getCurrentUseCase();
	void setReceivedUseCase(int useCase);
	int getReceivedUseCase();
	static const int startBits_ = 0b1110;
	static const int stopBits_ = 0b000000;
	static const int lysOgLys_ = 0b010110;
	static const int kunLys_ = 0b011001;
	static const int kunLyd_ = 0b011010;
	static const int kunAlarm_ = 0b100101;
	static const int stopSim_ = 0b101001;
	static const int LysiGogK = 0b100110;
	protected:
	int currentUseCase_;
	int reveivedUseCase_;
	private:

};

