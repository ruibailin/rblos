#define BYTE unsigned byte
#define WORD unsigned int

extern  WORD far GetSSSP(void);
static  WORD aaa[0x6fff];
int main()
{
  WORD ii;
  for(;;)
  {
    ii=GetSSSP();
    if(ii > 0x6fff)
    {
      ii=0;
      aaa[ii]=0;
    }
  }
  return 0;
}

