/* 
* LogicSignal.h
*
* Created: 2/8/2016 3:15:41 PM
* Author: kmo
*/


#ifndef __LOGICSIGNAL_H__
#define __LOGICSIGNAL_H__


class LogicSignal
{
//===variables=================================================================
public:
	enum class State
	{
		Start,
		One,
		OneAgain,
		Zero,
		ZeroAgain,
	};
	
protected:
private:
	bool _signal;
	bool _nflanc = 0;
	bool _pflanc = 0;
	bool _ntoggle= 0;
	bool _ptoggle= 0;
	
	State _state;

//===functions=================================================================
public:
	__attribute__((noinline))
	LogicSignal()
	{
		_state=State::Start; 
	}
	
	bool NegativeFlanc() { return _nflanc; }
	bool NegativeToggle() { return _ntoggle; }
	bool PositiveFlanc() { return _pflanc; }
	bool PositiveToggle() { return _ptoggle; }
	bool Signal() { return _signal; }
	bool Flanc() { return _pflanc || _nflanc; }
	bool Toggle() { return _ptoggle ^ _ntoggle; }
	
	void Run(int signal )
	{
		_signal = signal;
		
		switch(_state)
		{
			case State::Start:
				_state = signal==0 ? _state=State::Zero : _state=State::One;
				_signal=signal;
				break;
				
			case State::One:
			_pflanc = 0;
			if ( _signal == 0 )
			{
				_state = State::Zero;
				_nflanc = 1;
				_ntoggle=!_ntoggle;
			}
			else
			{
				_state = State::OneAgain;
			}
			break;
			
			case State::OneAgain:
			if ( _signal == 0 )
			{
				_state = State::Zero;
				
				_nflanc = 1;
				_ntoggle=!_ntoggle;
			}
			break;
			
			case State::Zero:
			_nflanc = 0;
			if ( _signal == 1 )
			{
				_state = State::One;
				_pflanc = 1;
				_ptoggle=!_ptoggle;
			}
			else
			{
				_state = State::ZeroAgain;
			}
			break;
			
			case State::ZeroAgain:
			if ( _signal == 1 )
			{
				_state = State::One;
				
				_pflanc = 1;
				_ptoggle=!_ptoggle;
			}
			break;
		}
	}
	
	~LogicSignal();
protected:
private:
	LogicSignal( const LogicSignal &c );
	LogicSignal& operator=( const LogicSignal &c );

}; //LogicSignal

#endif //__LOGICSIGNAL_H__
