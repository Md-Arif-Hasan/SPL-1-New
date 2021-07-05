#include <bits/stdc++.h>
using namespace std;


struct singleLine {
      int lineNum;
      string codeTxt;
};

singleLine LINE[ 100 ];

string keywords[ 32 ] = { "auto", "break", "case", "char", "const",
                              "continue","default", "do", "double", "else",
                                "enum", "extern","float", "for", "goto", "if",
                                    "int", "long", "register","return", "short",
                                    "signed","sizeof", "static", "struct","switch",
                                     "typedef", "union", "unsigned", "void", "volatile", "while" };
int lineCount = 0;
string codeWord;
ofstream file( "tokenized.txt" );


bool isOperator_or_Not( char ch )
{
      if (  ch == '?' || ch == '.' || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '&' ||ch ==  '|' || ch == '!' || ch == '=' || ch == '<' || ch == '>' || ch == ',' || ch == '{' || ch == '}' || ch == '[' || ch == ']' || ch == '(' || ch == ')' || ch == '#' || ch == ';' || ch == ':' )
            {
               return true;
            }
      else
      {
          return false;
      }
}


void keyword_identifier_check( int l, int col )
{
      if ( codeWord.size() == 0 )
      {
            return;
      }

      int flag = 0;

      for ( int k = 0; k < 32; k++ )
      {
            if ( codeWord.compare( keywords[ k ] ) == 0 )
            {
                  flag = 1;
                  break;
            }
      }
      if ( flag == 1 )
           {
                 file << "keyword\t" << codeWord << "\t" << LINE[ l ].lineNum << "\t" << col - ( codeWord.size() ) + 1 << "\n";
           }
      else
      {
          file << "identifier\t" << codeWord << "\t" << LINE[ l ].lineNum << "\t" << col - ( codeWord.size() ) + 1 << "\n";

      }

      codeWord = "";
}




bool isDigit_or_Not( char ch )
{
      if ( ch >= '0' && ch <= '9' )
      {
           return true;
      }
      else
      {
          return false;
      }

}


bool isArithmatic_operator(char ch)
{
      if ( ch == '+' || ch == '-' || ch == '&' || ch == '|' || ch == '=' || ch == '>' || ch == '<' )
            return true;
      else
            return false;
}


void Analyzing_Raw_Code()
{
      for ( int i = 0; i < lineCount; i++ )
            {

                  int lenPerLine = LINE[ i ].codeTxt.size();

                  for ( int j = 0; j < lenPerLine; )
                        {

                              if ( isOperator_or_Not( LINE[ i ].codeTxt[ j ] ) && isArithmatic_operator( LINE[ i ].codeTxt[ j + 1 ] ) )
                                    {
                                          keyword_identifier_check( i, j );
                                          file << "operator\t" << LINE[ i ].codeTxt[ j ] << LINE[ i ].codeTxt[ j + 1 ] << "\t" << LINE[ i ].lineNum << "\t" << j + 1 << "\n";
                                          j += 2;
                                    }

                              else if ( isOperator_or_Not( LINE[ i ].codeTxt[ j ] ) )
                                    {
                                          keyword_identifier_check( i, j );
                                          file << "operator\t" << LINE[ i ].codeTxt[ j ] << "\t" << LINE[ i ].lineNum << "\t" << j + 1 << "\n";
                                          j += 1;
                                    }

                              else if ( LINE[ i ].codeTxt[ j ] == '\\' )
                                    {
                                          keyword_identifier_check( i, j );
                                          file << "character\t" << LINE[ i ].codeTxt[ j ] << LINE[ i ].codeTxt[ j + 1 ] << "\t" << LINE[ i ].lineNum << "\t" << j + 1 << "\n";//check which character
                                          j += 2;
                                    }

                              else if ( isDigit_or_Not(LINE[ i ].codeTxt[ j ] ) )
                                    {
                                          keyword_identifier_check( i, j );
                                          int f = 0, a = LINE[ i ].codeTxt[ j ] - '0';
                                          j++;
                                          int temp = j;
                                          while ( isDigit_or_Not( LINE[ i ].codeTxt[ j ] ) || LINE[ i ].codeTxt[ j ] == '.' )
                                                {
                                                      if ( LINE[ i ].codeTxt[ j ] == '.' )
                                                            {
                                                                  f = 1;
                                                                  file << "float\t" << a << ".";
                                                                  a = 0;
                                                            }
                                                      else
                                                            {
                                                                  a = a * 10 + ( LINE[ i ].codeTxt[ j ] - '0' );
                                                            }

                                                      j++;
                                                }

                                          if( f == 0 )
                                                {
                                                      file << "integer\t" << a << "\t" << LINE[ i ].lineNum << "\t" << temp << "\n";
                                                }

                                          else
                                                {
                                                      file << a << "\t" << LINE[ i ].lineNum << "\t" << temp << "\n";
                                                }

                                    }

                              else if ( LINE[ i ].codeTxt[ j ] == '"' )

                                    {
                                          keyword_identifier_check( i, j );
                                          j++;
                                          int temp = j;
                                          string strg;

                                          while ( LINE[ i ].codeTxt[ j ] != '"' )
                                                {
                                                      strg = strg + LINE[ i ].codeTxt[ j ];
                                                      j++;
                                                }

                                                j++;
                                                file << "string\t" << strg  << "\t" << LINE[ i ].lineNum << "\t" << temp + 1 << "\n"; //char check in string
                                    }

                              else if ( LINE[ i ].codeTxt[ j ] == ' ' || LINE[ i ].codeTxt[ j ] == '\n' )
                                    {
                                          keyword_identifier_check( i, j );
                                          j++;
                                    }

                              else
                                    {
                                          codeWord = codeWord + LINE[ i ].codeTxt[ j++ ];
                                    }
                        }
            }
}


void execution()
{
      int value;
      cout << " \n\t\t\t\t\t\t Do you want to analyze input code ?"<< endl;
      cout  << "\t\t\t\t\t\t If YES, press 1: " <<endl;
      cout  << " \t\t\t\t\t\t If NO, press 2: " <<endl;
      cout<<" \t\t\t\t\t\t Your choice : ";
      cin>> value;

      if(value == 1)
      {
            Analyzing_Raw_Code();
            cout<<"\t\t\t\t\t\t Analyzing successfully done !" <<endl;
      }
      else if( value==2)
      {
           cout<<"\t\t\t\t\t\t Analyzing failed !" <<endl;
      }
}

int main()
{
      FILE *filePointer;
      string s, inputCodes;
      char chr;

      filePointer = fopen( "raw.cpp", "r" );

      if ( filePointer == NULL )
      {
            printf( "Can not open\n" );
            exit( 0 );
      }

      while ( ( chr = fgetc( filePointer ) ) != EOF )
      {
            inputCodes = inputCodes + chr;
      }

      stringstream X( inputCodes );

      while ( getline( X, s, '\n' ) )
      {
            LINE[ lineCount ].codeTxt = s + " ";
            LINE[ lineCount++ ].lineNum = lineCount;
      }

      execution();
      //Analyzing_Raw_Code();

      return 0;
}
