// ewood

#include "clavier.hpp"

TClavier::TClavier(void) : timeoutMs(100)
    {
    reconfigureTerminal();
    }

TClavier::~TClavier()
    {
    restaureTerminal();
    }

int16_t TClavier::kbhit(void)
    {
    int16_t retour;
    fd_set setRead;
    struct timeval tv;

    tv.tv_sec = 0;
    tv.tv_usec = (timeoutMs * 1000);
    FD_ZERO(&setRead);
    FD_SET(fileno(stdin),&setRead);
    select(FD_SETSIZE,&setRead,NULL,NULL,&tv);
    if(FD_ISSET(fileno(stdin),&setRead))
      retour = 1;
    else
      retour = 0;

    return retour;
    }

int16_t TClavier::getch(void)
    {
    return getchar();
    }

int16_t TClavier::reconfigureTerminal(void)
    {
    int16_t retour = 0;
    struct termios newTermios;

    if(tcgetattr(fileno(stdin),&oldTermios) == -1)
      {
      perror("tcgetattr");
      retour = -1;
      }

    newTermios = oldTermios;
    newTermios.c_lflag &= ~ICANON;
    newTermios.c_lflag &= ~ECHO;

    newTermios.c_cc[VMIN]  = 1;

    if(tcsetattr(fileno(stdin),TCSANOW,&newTermios) == -1)
      {
      perror("tcsetattr");
      retour = -1;
      }

    return retour;
    }

int16_t TClavier::restaureTerminal(void)
    {
    return tcsetattr(fileno(stdin),TCSANOW,&oldTermios);
    }
