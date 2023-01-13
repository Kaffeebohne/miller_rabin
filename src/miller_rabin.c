#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include "testFunctions.h"

#ifndef true
#define true 1
#define false 0
#endif

typedef char flag;
typedef enum tagECs
  {
  eNoErr,
  eInvalidArgs,
  eFilestreamInvalid,
  eNoMemory,
  } E_Errorcodes;
enum
  {
  eSingle, eMulti, eSet
  };

//extern void checkSingle( FILE *, unsigned long long, unsigned long long *, unsigned int );
//extern void checkMulti( FILE *, unsigned long long, unsigned long long *, unsigned int );
//extern void checkSet( FILE *, unsigned long long, unsigned long long *, unsigned int );

unsigned long long sets[6][12] =
  {
    {2,3}, {31,73}, {2,3,5}, {2,13,23,1662803},
    {2,3,5,7,11}, {2,3,5,7,11,13,17,19,23,29,31,37}
  };
unsigned int lenOfSets[] = { 2, 2, 3, 4, 5, 12 };

void ( *functions[3] )( FILE *, unsigned long long, unsigned long long *, unsigned int )
= { checkSingle, checkMulti, checkSet };

void parseList( char * stream, unsigned long long ** testNumbers, unsigned int * len );
void parseNum( char * stream, int begin, int end, unsigned long long * res );
void die( E_Errorcodes e );

void parseList( char * stream, unsigned long long ** testNumbers, unsigned int * len )
  {
  ( void ) stream;
  ( void ) testNumbers;
  ( void ) len;

  *len = 0;
  unsigned int bucketSize = 8;
  unsigned long long * uls = ( unsigned long long * ) malloc( bucketSize * sizeof( unsigned long long ) );
  char c;
  unsigned int begin = 0, end = 0;
  unsigned long long parsedNum;
  unsigned int i = 0;

  if( uls == NULL )
    die( eNoMemory );

  while( ( c = stream[i] ) != '\0' )
    {
    switch( c )
      {
        case ' ' || '\t':
          parseNum( stream, begin, end, &parsedNum );
          uls[*len] = parsedNum;
          begin = end;
          ++( *len );
          break;
      }
    if( *len == bucketSize )
      {
      bucketSize <<= 1;
      uls = ( unsigned long long * )realloc( uls, bucketSize );
      if( uls == NULL )
        die ( eNoMemory );
      }
    ++i;
    }

  testNumbers = ( unsigned long long ** ) malloc ( sizeof( unsigned long long * ) );
  *testNumbers = ( unsigned long long * ) malloc( *len * sizeof ( unsigned long long * ) );

  for( unsigned int i = 0; i < *len; ++i )
    {
    *testNumbers[i] = uls[i];
    }
  free( uls );
  }
void parseNum( char * stream, int begin, int end, unsigned long long * res )
  {
  char * sub = ( char * ) malloc( end - begin + 1 );
  strncpy( sub, stream + begin, end - begin );
  *( sub + ( end - begin + 1 ) ) = '\0';
  *res = atoll( sub );
  }
void die( E_Errorcodes e )
  {
  exit( e );
  }

int main( int argc, char ** argv )
  {
  int c = 0;
  int exitcode = EXIT_SUCCESS;

  flag verbose = true;
  FILE * output = stdout;
  char * outName;

  unsigned long long candidate = 0;
  unsigned long long wittness = 0;
  unsigned long long * wittnesses = NULL;
  unsigned int nbrOfWittnesses = 0;
  flag setSelect = -1;

  flag testSingle = false;
  flag testMulti = false;
  flag useSet = false;
  flag valid = true;
  flag hasCandidate = false;
  flag useFileStream = false;

  while( valid && ( c = getopt( argc, argv, "vo:t:s:l:S:" ) ) != -1 )
    {
    switch( c )
      {
        case 'v': verbose = true; break;
        case 'o': outName = optarg; useFileStream = true; break;
        case 't': candidate = atoll( optarg ); hasCandidate = true; break;
        case 's': wittness = atoll( optarg ); testSingle = true; break;
        case 'S': setSelect = optarg[0] - '0'; useSet = true; break;
        case 'l': parseList( optarg, &wittnesses, &nbrOfWittnesses ); testMulti = true; break;
        default: valid = false;
      }
    }

  if( !hasCandidate || !valid || ( useSet && ( setSelect < 0 || setSelect > 5 ) )
    || ( testSingle + testMulti + useSet ) != 1 )
    die( eInvalidArgs );

  if( useFileStream )
    {
    FILE * output = fopen( outName, "w" );
    if( output == NULL )
      die ( eFilestreamInvalid );
    }

  if( testSingle )
    functions[eSingle]( output, candidate, &wittness, 1 );
  else if( testMulti )
    {
    functions[eMulti]( output, candidate, wittnesses, nbrOfWittnesses );
    }
  else
    {
    wittnesses = sets[( unsigned int ) setSelect];
    functions[eSet]( output, candidate, wittnesses, lenOfSets[( unsigned int ) setSelect] );
    }

  if( useFileStream )
    fclose( output );

  ( void ) verbose;

  return exitcode;
  }
