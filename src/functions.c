#include "testFunctions.h"

// PROTOTYPEN
static unsigned long long calculatePower( unsigned long long n );
static unsigned long long squareAndMultiply( unsigned long long n, unsigned long long a, unsigned long long d );

// PUBLIC METHODEN
void checkSingle( FILE * stream, unsigned long long n, unsigned long long * a, unsigned int len )
  {
  ( void ) len;
  unsigned long long d = calculatePower( n );
  fprintf( stream, "R: %llu\n", squareAndMultiply( n, *a, d ) );
  }
void checkMulti( FILE * stream, unsigned long long n, unsigned long long * a, unsigned int len )
  {
  ( void ) stream;
  ( void ) n;
  ( void ) a;
  ( void ) len;
  }
void checkSet( FILE * stream, unsigned long long n, unsigned long long * a, unsigned int len )
  {
  ( void ) stream;
  ( void ) n;
  ( void ) a;
  ( void ) len;
  }

// PRIVATE METHODEN
static unsigned long long calculatePower( unsigned long long n )
  {
  unsigned int m = 0;
  --n;

  while( ( n & 1 ) == 0 )
    {
    n >>= 1;
    ++m;
    }

  return n;
  }

static unsigned long long squareAndMultiply( unsigned long long n, unsigned long long a, unsigned long long d )
  {
  unsigned long long remainder = a;
  unsigned long long mask = 0x8000000000000000;
  while( ( mask & d ) == 0 )
    mask >>= 1;

  do
    {
    mask >>= 1;
    remainder = ( remainder * remainder ) % n; //square always
    if( ( mask & d ) != 0 )
      {
      remainder = ( remainder * a ) % n;
      }
    } while( mask != 1 );

    return remainder;
  }