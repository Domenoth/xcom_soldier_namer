#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <string>
#include <cctype>
#include <math.h>
#include <strings.h>
#include <time.h>
#include <fstream>

#define UFO_RANK                0
#define UFO_ASSIGNED_BASE       2
#define UFO_ASSIGNED_CRAFT      4
#define UFO_CRAFT_BEFORE_WOUND  6
#define UFO_MISSIONS            8
#define UFO_KILLS               10
#define UFO_WOUND_RECOVERY      12
#define UFO_VALUE               14
#define UFO_NAME                16
#define UFO_TRANSFER_DEST       41
#define UFO_TIME_UNITS_BASE     42
#define UFO_HEALTH_BASE         43
#define UFO_STAMINA_BASE        44
#define UFO_REACTIONS_BASE      45
#define UFO_STRENGTH_BASE       46
#define UFO_ACCURACY_BASE       47
#define UFO_THROWING_BASE       48
#define UFO_MELEE_BASE          49
#define UFO_PSI_STRENGTH        50
#define UFO_PSI_SKILL           51
#define UFO_BRAVERY_BASE        52
#define UFO_TIME_UNITS_ADDL     53
#define UFO_HEALTH_ADDL         54
#define UFO_STAMINA_ADDL        55
#define UFO_REACTIONS_ADDL      56
#define UFO_STRENGTH_ADDL       57
#define UFO_ACCURACY_ADDL       58
#define UFO_THROWING_ADDL       59
#define UFO_MELEE_ADDL          60
#define UFO_BRAVERY_ADDL        61
#define UFO_ARMOR               62
#define UFO_RECENT_PSI_INC      63
#define UFO_IN_PSI_TRAINING     64
#define UFO_PROMOTION_FLAG      65
#define UFO_MALE_OR_FEMALE      66
#define UFO_ETHNICITY           67

#define UFO_MAX_NAME_LENGTH     25
#define UFO_SOLDIER_DAT_SIZE    17000
#define UFO_BYTES_PER_SOLDIER   68

#define TFTD_MC_SKILL_ADDL       0
#define TFTD_TIME_UNITS_ADDL     1
#define TFTD_MC_IMPLANTATION     2
#define TFTD_PROMOTION_FLAG      3
#define TFTD_HEALTH_ADDL         4
#define TFTD_STRENGTH_ADDL       5
#define TFTD_ASSIGNED_BASE       6
#define TFTD_ASSIGNED_CRAFT      8
#define TFTD_RANK                10
#define TFTD_CRAFT_BEFORE_WOUND  12
#define TFTD_KILLS               14
#define TFTD_WOUND_RECOVERY      16
#define TFTD_MISSIONS            18
#define TFTD_VALUE               20
#define TFTD_TRANSFER_DEST       22
#define TFTD_STAMINA_ADDL        23
#define TFTD_REACTIONS_ADDL      24
#define TFTD_ACCURACY_ADDL       25
#define TFTD_TIME_UNITS_BASE     26
#define TFTD_HEALTH_BASE         27
#define TFTD_STAMINA_BASE        28
#define TFTD_THROWING_BASE       29
#define TFTD_ARMOR               30
#define TFTD_MALE_OR_FEMALE      31
#define TFTD_ETHNICITY           32
#define TFTD_ACCURACY_BASE       33
#define TFTD_STRENGTH_BASE       34
#define TFTD_NAME                35
#define TFTD_BRAVERY_ADDL        62
#define TFTD_THROWING_ADDL       63
#define TFTD_BRAVERY_BASE        64
#define TFTD_MC_SKILL_BASE       65
#define TFTD_MELEE_ADDL          66
#define TFTD_MC_STRENGTH         67
#define TFTD_MELEE_BASE          68
#define TFTD_REACTIONS_BASE      69

#define TFTD_MAX_NAME_LENGTH     27
#define TFTD_SOLDIER_DAT_SIZE    17500
#define TFTD_BYTES_PER_SOLDIER   70

#define RECON               '%'
#define RECON_MASTER_SCOUT  '^'
#define RECON_RANGER        '|'
#define RECON_SHARP_SHOOTER '\\'
#define RECON_BASE          '/'

#define INFANTRY            'X'
#define INFANTRY_SNIPER     '='
#define INFANTRY_SPEC_OP    '+'
#define INFANTRY_GRUNT      'r'
#define INFANTRY_BASE       '-'

#define HEAVY               '#'
#define HEAVY_BEHEMOTH      'K'
#define HEAVY_TITAN         'i'
#define HEAVY_GIANT         ':'
#define HEAVY_BASE          '.'

#define PSI_AWARD           '*'

using namespace std;

class BaseSoldier {
  public:
    int name, max_name_length;
    void set_soldier_data( char *data ) {
      soldier_data = data;
    }
    unsigned char accuracy() {
      return soldier_data[accuracy_base_loc] + soldier_data[accuracy_addl_loc];
    }
    unsigned char bravery() {
      return 11 - soldier_data[bravery_base_loc] + soldier_data[bravery_addl_loc];
    }
    unsigned char psi_skill() {
      return soldier_data[psi_skill_loc];
    }
    unsigned char psi_strength() {
      return soldier_data[psi_strength_loc];
    }
    unsigned char rank() {
      return soldier_data[rank_loc];
    }
    unsigned char reactions() {
      return soldier_data[reactions_base_loc] + soldier_data[reactions_addl_loc];
    }
    unsigned char strength() {
      return soldier_data[strength_base_loc] + soldier_data[strength_addl_loc];
    }
    unsigned char strength_base() {
      return soldier_data[strength_base_loc];
    }
    unsigned char time_units() {
      return soldier_data[time_units_base_loc] + soldier_data[time_units_addl_loc];
    }
  protected:
    int accuracy_base_loc, accuracy_addl_loc, bravery_base_loc, bravery_addl_loc, psi_skill_loc, psi_strength_loc, rank_loc, reactions_base_loc, reactions_addl_loc, strength_base_loc, strength_addl_loc, time_units_base_loc, time_units_addl_loc;
  char *soldier_data;
};

class UfoDefenseSoldier: public BaseSoldier {
  public:
    UfoDefenseSoldier( int = UFO_NAME, int = UFO_MAX_NAME_LENGTH, int = UFO_ACCURACY_BASE, int = UFO_ACCURACY_ADDL, int = UFO_BRAVERY_BASE, int = UFO_BRAVERY_ADDL, int = UFO_PSI_SKILL, int = UFO_PSI_STRENGTH, int = UFO_RANK, int = UFO_REACTIONS_BASE, int = UFO_REACTIONS_ADDL, int = UFO_STRENGTH_BASE, int = UFO_STRENGTH_ADDL, int = UFO_TIME_UNITS_BASE, int = UFO_TIME_UNITS_ADDL );
    ~UfoDefenseSoldier() {
      delete soldier_data;
    }
};

UfoDefenseSoldier::UfoDefenseSoldier( int name_loc, int max_name, int acc_b, int acc_a, int brv_b, int brv_a, int p_skl, int p_str, int rnk, int rea_b, int rea_a, int str_b, int str_a, int tus_b, int tus_a )
{
  name = name_loc;
  max_name_length = max_name;
  accuracy_base_loc = acc_b;
  accuracy_addl_loc = acc_a;
  bravery_base_loc = brv_b;
  bravery_addl_loc = brv_a;
  psi_skill_loc = p_skl;
  psi_strength_loc = p_str;
  rank_loc = rnk;
  reactions_base_loc = rea_b;
  reactions_addl_loc = rea_a;
  strength_base_loc = str_b;
  strength_addl_loc = str_a;
  time_units_base_loc = tus_b;
  time_units_addl_loc = tus_a;
}

class TerrorFromTheDeepSoldier: public BaseSoldier {
  public:
    TerrorFromTheDeepSoldier( int = TFTD_NAME, int = TFTD_MAX_NAME_LENGTH, int = TFTD_ACCURACY_BASE, int = TFTD_ACCURACY_ADDL, int = TFTD_BRAVERY_BASE, int = TFTD_BRAVERY_ADDL, int = TFTD_MC_SKILL_BASE + TFTD_MC_SKILL_ADDL, int = TFTD_MC_STRENGTH, int = TFTD_RANK, int = TFTD_REACTIONS_BASE, int = TFTD_REACTIONS_ADDL, int = TFTD_STRENGTH_BASE, int = TFTD_STRENGTH_ADDL, int = TFTD_TIME_UNITS_BASE, int = TFTD_TIME_UNITS_ADDL );
    ~TerrorFromTheDeepSoldier() {
      delete soldier_data;
    }
};

TerrorFromTheDeepSoldier::TerrorFromTheDeepSoldier( int name_loc, int max_name, int acc_b, int acc_a, int brv_b, int brv_a, int p_skl, int p_str, int rnk, int rea_b, int rea_a, int str_b, int str_a, int tus_b, int tus_a )
{
  name = name_loc;
  max_name_length = max_name;
  accuracy_base_loc = acc_b;
  accuracy_addl_loc = acc_a;
  bravery_base_loc = brv_b;
  bravery_addl_loc = brv_a;
  psi_skill_loc = p_skl;
  psi_strength_loc = p_str;
  rank_loc = rnk;
  reactions_base_loc = rea_b;
  reactions_addl_loc = rea_a;
  strength_base_loc = str_b;
  strength_addl_loc = str_a;
  time_units_base_loc = tus_b;
  time_units_addl_loc = tus_a;
}

void Recon( BaseSoldier *soldier, char *name )
{
  if( soldier->rank() != 255 )
  {
    name[2] = RECON;
    if( soldier->accuracy() > 64 )
    {
      if( soldier->time_units() > 59 )
      {
        if( soldier->reactions() > 59 )
        {
          name[3] = RECON_MASTER_SCOUT;
        }
        else
        {
          name[3] = RECON_RANGER;
        }
      }
      else
      {
        name[3] = RECON_SHARP_SHOOTER;
      }
    }
    else
    {
      name[3] = RECON_BASE;
    }
  }
}

void Infantry( BaseSoldier *soldier, char *name )
{
  if( soldier->rank() != 255 )
  {
    name[2] = INFANTRY;
    if( soldier->accuracy() > 64 )
    {
      if( soldier->reactions() > 59 )
      {
        if( soldier->accuracy() > 69 )
        {
          name[3] = INFANTRY_SNIPER;
        }
        else
        {
          name[3] = INFANTRY_SPEC_OP;
        }
      }
      else
      {
        name[3] = INFANTRY_GRUNT;
      }
    }
    else
    {
      name[3] = INFANTRY_BASE;
    }
  }
}

void HeavyWep( BaseSoldier *soldier, char *name )
{
  if( ( soldier->rank() != 255 ) && ( soldier->strength_base() > 36 ) )
  {
    name[2] = HEAVY;
    if( soldier->accuracy() > 64 )
    {
      if( soldier->reactions() > 59 )
      {
        if( soldier->accuracy() > 69 )
        {
          name[3] = HEAVY_BEHEMOTH;
        }
        else
        {
          name[3] = HEAVY_TITAN;
        }
      }
      else
      {
        name[3] = HEAVY_GIANT;
      }
    }
    else
    {
      name[3] = HEAVY_BASE;
    }
  }
  else
  {
    Infantry( soldier, name );
  }
}

void award_psi_squad( BaseSoldier *soldier, char *name )
{
    if( soldier->psi_strength() > 60 )
    {
        name[0] = PSI_AWARD;
    }
}

void ReadDisk()                  //reads a file
{
  int game_number;
  char *filename = new char[80];
  char *bt = NULL;
  int size = 0;
  int bytes_per_soldier;
  string soldier_type;
  int i = 0;
  int j = 0;
  int k = 0;
  char name[30] = {'\0'};
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

  ifstream soldatin;
  ofstream soldatout;
  soldatin.open(filename, ifstream::binary );

  if ( !soldatin.is_open() )
  {
    cerr << "Failure to open disk file:  " << filename;
    exit(1);
  }

  system("cls");

  soldatin.seekg( 0, ios::end );
  size = soldatin.tellg();
  soldatin.seekg( 0, ios::beg );
  if ( size == UFO_SOLDIER_DAT_SIZE )
  {
    bytes_per_soldier = UFO_BYTES_PER_SOLDIER;
    soldier_type = "ufo";
  }
  else
  {
    bytes_per_soldier = TFTD_BYTES_PER_SOLDIER;
    soldier_type = "tftd";
  }
  bt = new char [size];

  cout << endl << size << endl << soldier_type << endl << bytes_per_soldier << endl;

  soldatin.read( bt, size );
  soldatin.close();

  while( i < size )
  {
    cout << i/bytes_per_soldier + 1 << "\t";
    char data[bytes_per_soldier];
    memcpy( &data[0], &bt[i], bytes_per_soldier );
    UfoDefenseSoldier ufo_soldier;
    TerrorFromTheDeepSoldier tftd_soldier;
    BaseSoldier *soldier;
    if ( soldier_type == "ufo" )
    {
      soldier = &ufo_soldier;
    }
    else
    {
      soldier = &tftd_soldier;
    }
    soldier->set_soldier_data( data );
    switch( soldier->rank() )
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
    switch( soldier->bravery() )
    {
      case 1:  Recon(soldier, name ); break;
      case 2:  Recon(soldier, name ); break;
      case 3:  Infantry(soldier, name ); break;
      default: Infantry(soldier, name ); break;
    }
    if( soldier->psi_skill() )
    {
        award_psi_squad( soldier, name );
    }
    j = soldier->name;
    if( !isalpha( bt[i+j] ) )
    {
      j = j + 5;
    }
    k = 5;
    while(1)
    {
      if( isalpha( bt[i+j] ) && ( soldier->rank() != 255 ) )
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
    while( k <= soldier->max_name_length )
    {
      name[k] = '\0';
      k++;
    }
    cout << name << endl;
    memcpy( &bt[i+soldier->name], &name[0], soldier->max_name_length );
    i+=bytes_per_soldier;
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
