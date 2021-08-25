#include<bits/stdc++.h>
using namespace std;

int totalLine = 0;

struct scope {
    int startLine;
    int endLine;
    string keyword;
};

vector < string > codeWord[ 100 ];
vector < string > wordType[ 100 ];
vector < scope > scopeInfo;
vector < int > edge[ 100 ];


int strToInt( string str )
{
    int r = 0;
    for( int i = 0; i < str.size(); i++ ) {
        r *= 10;
        r += str[ i ]-'0';
    }
    return r;
}

bool containInScope( int LN )
{
    for ( int i = 0; i < scopeInfo.size(); ++i ) {
        if ( scopeInfo[ i ].startLine == LN )
            return true;
    }
    return false;
}

int idOfScope( int LN )
{
    for ( int i = 0; i < scopeInfo.size(); ++i ) {
        if ( scopeInfo[ i ].startLine == LN )
            return i;
    }
}

int endOfThisIFScope( int LN )
{
    int EL = scopeInfo[ idOfScope( LN ) ].endLine;
    if ( containInScope( EL + 1 ) && scopeInfo[ idOfScope( EL + 1 ) ].keyword == "else" || scopeInfo[ idOfScope( EL + 1 ) ].keyword == "else if" )
        {
                EL = endOfThisIFScope( EL + 1 );
        }

    return EL;
}

void printGraph()
{

    cout<<"\n \t\t\t\t\t\t The control flow graph : \n";

    for ( int i = 1; i <= totalLine; ++i )
      {
        for ( int j = 0; j < edge[ i ].size(); ++j )
        {
            cout <<" \t\t\t\t\t\t\t " << i << " " << edge[ i ][ j ] << "\n";
        }
      }
}

void controlFlowGraphEdgeCreate( int SL, int EL )
{
    int node = SL;
    while ( node <= EL )
      {
        if ( containInScope( node ) )
        {
            int id = idOfScope( node );

            if ( scopeInfo[ id ].keyword == "for" || scopeInfo[ id ].keyword == "while" )
            {
                edge[ node ].push_back( node + 1 );

                edge[ node ].push_back( scopeInfo[ id ].endLine + 1 );

                controlFlowGraphEdgeCreate ( scopeInfo[ id ].startLine + 1, scopeInfo[ id ].endLine - 1 );

                edge[ scopeInfo[ id ].endLine ].push_back( node );

                node = scopeInfo[ id ].endLine + 1;
            }


            else if ( scopeInfo[ id ].keyword == "if" || scopeInfo[ id ].keyword == "else if" || scopeInfo[ id ].keyword == "else" ) {

                int last = endOfThisIFScope( scopeInfo[ id ].startLine ) + 1;

                edge [ node ].push_back( node + 1 );

                edge [ node ].push_back( scopeInfo[ id ].endLine + 1 );

                controlFlowGraphEdgeCreate  ( scopeInfo[ id ].startLine + 1, scopeInfo[ id ].endLine - 1 );

                edge [ scopeInfo[ id ].endLine ].push_back( last );

                node  =  scopeInfo [ id ].endLine + 1;
            }
        }
        else {

            edge[ node ].push_back( node + 1 );
            node++;

        }
    }
}

void  scope_of_control( int startLine, int endLine )
{
    stack < pair < int, string > > ss;
    pair < int, string > lastKeyword;

    for ( int LN = startLine; LN <= endLine; ++LN )
      {
        for ( int CL = 0; CL < codeWord[ LN ].size(); ++CL )
        {
            if ( wordType[ LN ][ CL ] == "keyword" )
            {
                lastKeyword.first = LN;
                lastKeyword.second = codeWord[ LN ][ CL ];
                if ( CL > 0 && codeWord[ LN ][ CL ] == "if" && codeWord[ LN ][ CL - 1 ] == "else" )
                {
                        lastKeyword.second = "else if";
                }
            }

            if ( codeWord[ LN ][ CL ] == "{" )
            {
                   ss.push( lastKeyword );

            }

            if ( codeWord[ LN ][ CL ] == "}" )
                  {
                        scope sc;
                        sc.startLine = ss.top().first;
                        sc.keyword = ss.top().second;
                        sc.endLine = LN;
                        ss.pop();
                        scopeInfo.push_back( sc );
            }
        }
    }
}

int main()
{
    FILE *fp;
    string str, codeText;
    char ch;

    fp = fopen( "tokenized.txt", "r" );

    while ( ( ch = fgetc( fp ) ) != EOF ) codeText = codeText + ch;

    stringstream X( codeText );
    while ( getline( X, str, '\n' ) )
        {
                string strg1, strg2, strg3, strg4;

                stringstream Y( str );
                getline( Y, strg1, '\t' );
                getline( Y, strg2, '\t' );
                getline( Y, strg3, '\t' );
                getline( Y, strg4, '\t' );
                int line = strToInt( strg3 );

                codeWord[ line ].push_back( strg2 );
                wordType[ line ].push_back( strg1 );

                totalLine = max( totalLine, line );
    }

    scope_of_control( 1, totalLine );
    controlFlowGraphEdgeCreate( 1, totalLine );
    printGraph();
}
