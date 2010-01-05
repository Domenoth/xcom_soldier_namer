#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <cctype>
#include <math.h>
#include <strings.h>
#include <time.h>
#include <fstream>

#define RANK                0
#define ASSIGNED_BASE       2
#define ASSIGNED_CRAFT      4
#define CRAFT_BEFORE_WOUND  6
#define MISSIONS            8
#define KILLS               10
#define WOUND_RECOVERY      12
#define VALUE               14
#define NAME                16
#define TRANSFER_DEST       41
#define TIME_UNITS_BASE     42
#define HEALTH_BASE         43
#define STAMINA_BASE        44
#define REACTIONS_BASE      45
#define STRENGTH_BASE       46
#define ACCURACY_BASE       47
#define THROWING_BASE       48
#define MELEE_BASE          49
#define PSI_STRENGTH        50
#define PSI_SKILL           51
#define BRAVERY_BASE        52
#define TIME_UNITS_ADDL     53
#define HEALTH_ADDL         54
#define STAMINA_ADDL        55
#define REACTIONS_ADDL      56
#define STRENGTH_ADDL       57
#define ACCURACY_ADDL       58
#define THROWING_ADDL       59
#define MELEE_ADDL          60
#define BRAVERY_ADDL        61
#define ARMOR               62
#define RECENT_PSI_INC      63
#define IN_PSI_TRAINING     64
#define PROMOTION_FLAG      65
#define MALE_OR_FEMALE      66
#define ETHNICITY           67

#define MAX_NAME_LENGTH     25
#define SOLDIER_DAT_SIZE    17000
#define BYTES_PER_SOLDIER   68

using namespace std;

void Recon( unsigned char Rank,
            char *name,
            unsigned short Accuracy,
            unsigned short Time_Units,
            unsigned short Reactions )
{
  if( Rank != 255 )
  {
    name[2] = '%';
    if( Accuracy > 64 )
    {
      if( Time_Units > 59 )
      {
        if( Reactions > 59 )
        {
          name[3] = '/';
        }
        else
        {
          name[3] = '\\';
        }
      }
      else
      {
        name[3] = '^';
      }
    }
  }
}

void Infantry( unsigned char Rank,
            char *name,
            unsigned short Accuracy,
            unsigned short Reactions )
{
  if( Rank != 255 )
  {
    name[2] = 'X';
    if( Accuracy > 64 )
    {
      if( Reactions > 59 )
      {
        if( Accuracy > 69 )
        {
          name[3] = '=';
        }
        else
        {
          name[3] = '(';
        }
      }
      else
      {
        name[3] = '+';
      }
    }
    else
    {
      name[3] = '-';
    }
  }
}

void HeavyWep(  unsigned char Rank,
            char *name,
            unsigned short Strength,
            unsigned short Accuracy,
            unsigned short Reactions )
{
  if( ( Rank != 255 ) && ( Strength > 36 ) )
  {
    name[2] = '#';
    if( Accuracy > 64 )
    {
      if( Reactions > 59 )
      {
        if( Accuracy > 69 )
        {
          name[3] = 'K';
        }
        else
        {
          name[3] = 'i';
        }
      }
      else
      {
        name[3] = ':';
      }
    }
    else
    {
      name[3] = '.';
    }
  }
  else
  {
    Infantry( Rank,name,Accuracy,Reactions );
  }
}

void award_psi_squad( char *name,
                      unsigned char PSI_Strength)
{
    if( PSI_Strength > 60 )
    {
        name[0] = '*';
    }
}

void ReadDisk()                  //reads a file
{
  int game_number;
  char *filename = new char[80];
  char *bt = NULL;
  int size = 0;
  int i = 0;
  int j = 0;
  int k = 0;
  unsigned char rank;
  char name[MAX_NAME_LENGTH] = {'\0'};
  char *ROOK = "    |";
  char *SQUD = " |  |";
  char *SRGT = "    [";
  char *CAPT = " ]  [";
  char *COLN = "    {";
  char *CMDR = " }  {";
  char *KIA  = " KIA ";
  char *INV  = " INV ";

  cout << "Enter Saved Game Number (1-10):\n";
  cin  >> game_number;
  while( (game_number < 1) || (game_number > 10) )
  {
      cout << "Invalid Selection. Enter 1-10 instead:";
      cin >> game_number;
  }
  cout << "GAME_"
       << game_number
       << "Accepted\n";

  switch( game_number )
  {
      case 1:  filename = "GAME_1\\soldier.dat"; break;
      case 2:  filename = "GAME_2\\soldier.dat"; break;
      case 3:  filename = "GAME_3\\soldier.dat"; break;
      case 4:  filename = "GAME_4\\soldier.dat"; break;
      case 5:  filename = "GAME_5\\soldier.dat"; break;
      case 6:  filename = "GAME_6\\soldier.dat"; break;
      case 7:  filename = "GAME_7\\soldier.dat"; break;
      case 8:  filename = "GAME_8\\soldier.dat"; break;
      case 9:  filename = "GAME_9\\soldier.dat"; break;
      case 10: filename = "GAME_10\\soldier.dat"; break;
      default: cout << "INVALID SAVE GAME!"; exit(1);
  }
//  filename = "soldier.dat";

  ifstream soldatin;
  ofstream soldatout;
  soldatin.open(filename, ifstream::binary ); //| ifstream::ate);

  if ( !soldatin.is_open() )
  {
    cerr << "Failure to open disk file:  " << filename;
    exit(1);
  }

  system("cls");

  size = SOLDIER_DAT_SIZE;//soldatin.tellg();
//  soldatin.seekg( 0, ios::beg );
  bt = new char [size];

  cout << endl << size << endl;

  soldatin.read( bt, size );
  soldatin.close();

  while( i < size )
  {
    cout << i/BYTES_PER_SOLDIER + 1 << "\t";
    rank = ((unsigned char)bt[i+RANK]);// & 0x00FF;
    switch( rank )
    {
      case 0:   memcpy( &name[0], &ROOK[0], 5); break;
      case 1:   memcpy( &name[0], &SQUD[0], 5); break;
      case 2:   memcpy( &name[0], &SRGT[0], 5); break;
      case 3:   memcpy( &name[0], &CAPT[0], 5); break;
      case 4:   memcpy( &name[0], &COLN[0], 5); break;
      case 5:   memcpy( &name[0], &CMDR[0], 5); break;
      case 255: memcpy( &name[0], &KIA[0], 5); break;
      default:  memcpy( &name[0], &INV[0], 5); break;
    }
    unsigned char bravery = 11 - bt[i+BRAVERY_BASE/*52*/] + bt[i+BRAVERY_ADDL/*61*/];
    switch( bravery )
    {
      case 1:  Recon(rank,
                     name,
                     (unsigned short)bt[i+ACCURACY_BASE/*47*/] + (unsigned short)bt[i+ACCURACY_ADDL/*58*/],
                     (unsigned short)bt[i+TIME_UNITS_BASE/*42*/] + (unsigned short)bt[i+TIME_UNITS_ADDL/*53*/],
                     (unsigned short)bt[i+REACTIONS_BASE/*45*/] + (unsigned short)bt[i+56] );
               break;
      case 2:  Recon(rank,
                     name,
                     (unsigned short)bt[i+ACCURACY_BASE/*47*/] + (unsigned short)bt[i+ACCURACY_ADDL/*58*/],
                     (unsigned short)bt[i+TIME_UNITS_BASE/*42*/] + (unsigned short)bt[i+TIME_UNITS_ADDL/*53*/],
                     (unsigned short)bt[i+REACTIONS_BASE/*45*/] + (unsigned short)bt[i+REACTIONS_ADDL/*56*/] );
               break;
      case 3:  Infantry(rank,
                        name,
                        (unsigned short)bt[i+ACCURACY_BASE/*47*/] + (unsigned short)bt[i+ACCURACY_ADDL/*58*/],
                        (unsigned short)bt[i+REACTIONS_BASE/*45*/] + (unsigned short)bt[i+REACTIONS_ADDL/*56*/] );
               break;
      default: HeavyWep(rank,
                        name,
                        (unsigned short)bt[i+STRENGTH_BASE/*46*/],
                        (unsigned short)bt[i+ACCURACY_BASE/*47*/] + (unsigned short)bt[i+ACCURACY_ADDL/*58*/],
                        (unsigned short)bt[i+REACTIONS_BASE/*45*/] + (unsigned short)bt[i+REACTIONS_ADDL/*56*/] );
               break;
    }
    unsigned char psi_skill = bt[i+PSI_SKILL];
    if( psi_skill )
    {
        award_psi_squad(name, bt[i+PSI_STRENGTH]);
    }
    j = NAME;
    if( !isalpha( bt[i+j] ) )
    {
      j = j + 5;
    }
    k = 5;
    while(1)
    {
      if( isalpha( bt[i+j] ) && ( rank != 255 ) )
      {
        name[k] = bt[i+j];
        j++;
        k++;
      }
      else
      {
        break;
      }
    }
    if( bt[i+j] == ' ' )
    {
      name[k] = bt[i+j];
      j++;
      k++;
      while(1)
      {
        if( isalpha( bt[i+j] ) )
        {
          name[k] = bt[i+j];
          j++;
          k++;
        }
        else
        {
          break;
        }
      }
    }
    while( k <= MAX_NAME_LENGTH )
    {
      name[k] = '\0';
      k++;
    }
    cout << name << endl;
    memcpy( &bt[i+NAME], &name[0], MAX_NAME_LENGTH);
    i+=BYTES_PER_SOLDIER;
  }

  soldatout.open(filename, ofstream::binary);

  if ( !soldatout.is_open() )
  {
    cerr << "Failure to open disk file:  " << filename;
    exit(1);
  }

  soldatout.write( bt, size );
  soldatout.close();

  cout << endl;
  system("PAUSE");
}
int main(void)
{
  ReadDisk();
}
