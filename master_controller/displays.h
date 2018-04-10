typedef struct
{
  char first [8];  // first four chars (with decimals)
  char last  [8];  // last four chars (with decimals)
} display_pair;

typedef struct
{
  display_pair x;
  display_pair z;
  display_pair w;
  display_pair c;
} displays;

display_pair dp_from_float(float);
