
#include	<cstdlib>
#include <unistd.h>
#include	"GameEngine.hpp"


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
    void	InitMap();
    int	Wait_Event(GameEngine 		&engine);
};

InputJoystick::InputJoystick(){}

InputJoystick::~InputJoystick(){}

void		InputJoystick::InitMap()
{
	button[0] = 0; 
	button[1] = 0; 
	button[2] = 0; 
	button[3] = 0; 
	button[4] = 0; 
	button[5] = 0; 
	button[6] = 0; 
	button[7] = 0; 
	button[8] = 0; 
	button[9] = 0; 
	button[10] = 0; 
	button[11] = 0; 
	button[12] = 0;
	button[13] = 0;
	button[14] = 0;
	button[15] = 0;
	button[16] = 0;
	button[17] = 0;
	button[18] = 0;
	button[19] = 0;
}

void		InputJoystick::ConnectJoystick()
{
	int		i;

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) == -1 )
	{
		fprintf(stderr,"Error SDL\n");
		return;
	}
	i = 0;
	for (nbr_joy = SDL_NumJoysticks();  i < nbr_joy; i++)
	{
		joystick[i] = SDL_JoystickOpen(i);
		printf("Name : %s\n",SDL_JoystickName(0));
		printf("nbre d' : %d\n",SDL_JoystickNumAxes(joystick[i]));
		printf("nbre de chapeaux : %d\n",SDL_JoystickNumHats(joystick[i]));
		printf("nbre de trackballs : %d\n",SDL_JoystickNumBalls(joystick[i]));
		printf("Nombre de boutons : %d\n",SDL_JoystickNumButtons(joystick[i]));
		printf("i = %d nbr_joy = %d\n", i, nbr_joy);
		if (joystick[i] == NULL || SDL_JoystickNumButtons(joystick[i]) != 19)
		{
			fprintf(stderr,"Error joystick[i]\n");
			return;
		}
	}

}

void	InputJoystick::GetJoystickAxes(int player)
{
	int		i;

	for (i = 0; i < SDL_JoystickNumAxes(joystick[player]); i++)
	{
		printf("Player[%d] Axe %d, valeur %d\n",player, i,SDL_JoystickGetAxis(joystick[player],i));
		button[i] = SDL_JoystickGetAxis(joystick[player],i);
	}
}

void	InputJoystick::GetJoystickButton(int player)
{
	int		i;

	for ( i = 0 ; i < SDL_JoystickNumButtons(joystick[player]) ; i++ )
	{
		if ( SDL_JoystickGetButton(joystick[player],i) )
		{
			printf("Player[%d] Bouton %d : appuyé\n",player, i);
		}
		else
		{
			printf("Player[%d] Bouton %d n'est pas appuyé\n",player, i);
		}
	}
}

int		InputJoystick::Wait_Event(GameEngine 		&engine)
{
	int	i;

	if (engine.initialize() == false)
		return (EXIT_FAILURE);
	while (engine.update() == true)
	{
		engine.draw();
		SDL_JoystickUpdate();
		for (i = 0; i < 2; i++)
		{
			GetJoystickAxes(i);
			GetJoystickButton(i);
		}
	}
	return 1;
}
