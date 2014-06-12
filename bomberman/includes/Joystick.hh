#ifndef _JOYSTICK_
#define _JOYSTICK_

class InputJoystick
{
	public:
	std::map<int, int>					button;
	std::map<int, SDL_Joystick *>		joystick;
    int					nbr_joy;

    InputJoystick();
    ~InputJoystick();
    void		ConnectJoystick();
    void	GetJoystickAxes(int);
    void	GetJoystickButton(int);
    int	Wait_Event(GameEngine &);
};


#endif