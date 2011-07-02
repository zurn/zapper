// a utility function defining a very simple method to indent a line of text

#include "tinyxml.h"
static const char * getIndent( unsigned int numIndents )
{
    static const char * pINDENT = "                                      + ";
    static const unsigned int LENGTH = strlen( pINDENT );

    if ( numIndents > LENGTH ) numIndents = LENGTH;

    return &pINDENT[ LENGTH-numIndents ];
}

static void dump_to_stdout( TiXmlNode * pParent, unsigned int indent = 0 )
{
    if ( !pParent ) return;

    TiXmlText *pText;
    int t = pParent->Type();
    printf( "%s", getIndent( indent));

    switch ( t )
    {
    case TiXmlNode::TINYXML_DOCUMENT:
        printf( "Document" );
        break;

    case TiXmlNode::TINYXML_ELEMENT:
        printf( "Element \"%s\"", pParent->Value() );
        break;

    case TiXmlNode::TINYXML_COMMENT:
        printf( "Comment: \"%s\"", pParent->Value());
        break;

    case TiXmlNode::TINYXML_UNKNOWN:
        printf( "Unknown" );
        break;

    case TiXmlNode::TINYXML_TEXT:
        pText = pParent->ToText();
        printf( "Text: [%s]", pText->Value() );
        break;

    case TiXmlNode::TINYXML_DECLARATION:
        printf( "Declaration" );
        break;
    default:
        break;
    }
    printf( "\n" );

    TiXmlNode * pChild;

    for ( pChild = pParent->FirstChild(); pChild != 0; pChild = pChild->NextSibling())
    {
        dump_to_stdout( pChild, indent+2 );
    }
}

