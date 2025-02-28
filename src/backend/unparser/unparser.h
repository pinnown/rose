/* unparser.h
 * This header file contains the class declaration for the newest unparser. Six
 * C files include this header file: unparser.C, modified_sage.C, unparse_stmt.C, 
 * unparse_expr.C, unparse_type.C, and unparse_sym.C.
 */

#ifndef UNPARSER_H
#define UNPARSER_H


#include "unparser_opt.h"
#include "unparse_format.h"

// #include <algorithm>
#include "unparseCxx_types.h"
#include "name_qualification_support.h"
// #include "unparseCxx_templates.h"  
#include "unparse_sym.h"
#include "unparse_debug.h"
#include "modified_sage.h"
#include "unparseCxx.h"

#include "unparseFortran.h"
#include "unparseFortran_types.h"
#include "unparseJava.h"
#include "unparsePHP.h"
#include "unparsePython.h"
#include "unparseX10.h"
#include "unparseAda.h"
#include "unparseJovial.h"

// DQ (7/20/2008): New mechanism to permit unparsing of arbitrary strings at IR nodes.
// This is intended to suppport non standard backend compiler annotations.
#include "astUnparseAttribute.h"


#include "includeFileSupport.h"


class Unparser_Nameq;

// Macro used for debugging.  If true it fixes the anonymous typedef and anonymous declaration
// bugs, but causes several other problems.  If false, everything works except the anonymous 
// typedef and anonymous declaration bugs.
#define ANONYMOUS_TYPEDEF_FIX false

// Whether to use Rice's code to wrap long lines in Fortran.
#define USE_RICE_FORTRAN_WRAPPING  0  // 1 if you're Rice, 0 if you want to get through Jenkins

// Maximum line lengths for Fortran fixed source form and free source form, per the F90 specification.
#if USE_RICE_FORTRAN_WRAPPING
  #define MAX_F90_LINE_LEN_FIXED  72
  #define MAX_F90_LINE_LEN_FREE  132
#else
  #define MAX_F90_LINE_LEN      1024
#endif

#define KAI_NONSTD_IOSTREAM 1

// typedef map<int,int,less<int>,allocator<int> > X;
// typedef multimap<int,int,less<int>,allocator<int> > X;
// multimap<int,int,less<int>,allocator<int> > X;
// list<int> Y;
// typedef multimap<int,int,less<int> > X;

#if USE_OLD_MECHANISM_OF_HANDLING_PREPROCESSING_INFO
// I think this is part of the connection to lex support for comments
// extern ROSEAttributesList* getPreprocessorDirectives( char *fileName);
#endif

 /* \if documentDevelopmentVersionUsingDoxygen
          \ingroup backendGenerator
          \brief This function is used by the SgNode object to connect the unparser to the AST.

          This function hides the complexity of generating a string from any subtree 
          of the AST (represented by a SgNode*).

          \internal This function uses the standard stringstream mechanism in C++ to 
                    convert the stream output to a string.
     \endif
  */
// string globalUnparseToString ( SgNode* astNode, SgUnparse_Info* inputUnparseInfoPointer = NULL );

// void printOutComments ( SgLocatedNode* locatedNode );
std::string get_output_filename( SgFile& file);
//! returns the name of type t
std::string get_type_name( SgType* t);

//! Unparse the declaration as a string for use in prototypes within the AST rewrite mechanism prefix mechanism
ROSE_DLL_API std::string unparseDeclarationToString ( SgDeclarationStatement* declaration, bool unparseAsDeclaration = true );

//! Unparse the header of the scope statement (used in the prefix generation to 
//! permit context to be accounted for the in generation of AST fragements from 
//! strings, e.g. for cases in SgSwitchStatement).
std::string unparseScopeStatementWithoutBasicBlockToString ( SgScopeStatement* scope );

//! Unparse header of statements that have bodies (but are not scopes) (e.g. SgDefaultOptionStmt)
std::string unparseStatementWithoutBasicBlockToString      ( SgStatement* statement );



// This is the base class for the support or alternative code generation mechanisms (by Qing Yi)
// and is the basis of the copy based unparsing that unparses the code by copying parts of the
// AST not transformed directly from the source file (character by character, to preserve
// absolutely ALL formatting).  Patch files can then be gnerated from such files, where the
// patches represent only the transformations introduced.
class UnparseDelegate
   {
     public:
     virtual ~UnparseDelegate() {};
       // This class need only support the unparsing of statements since all other IR nodes are 
       // unparsed by the functions that unparse statements.
          virtual bool unparse_statement( SgStatement* stmt, SgUnparse_Info& info, UnparseFormat& out) = 0; 
   };


// This is the class representing all the code generation support for C and C++.  It is separated from
// being a part of the AST IR so that it can be more easily developed as a separate modular piece of ROSE.
class Unparser
   {
     public:
       // DQ (8/13/2007): This was added by Thomas and will be commented later.
          Unparse_Type* u_type;
          Unparser_Nameq* u_name;
       // Unparse_Support* u_support;
          Unparse_Sym* u_sym;
          Unparse_Debug* u_debug;
          Unparse_MOD_SAGE* u_sage;
          Unparse_ExprStmt* u_exprStmt;

       // DQ (8/14/2007): I have added this here to be consistant, but I question if this is a good design!
          UnparseFortran_type* u_fortran_type;
          FortranCodeGeneration_locatedNode* u_fortran_locatedNode;

     private:


       // CI (03/06/2007): Changed private to protected, to enable user-derivated classes to access these variables, especially to access cur to output
  // private:
     public:

      //! Used to support unparsing of doubles and long double as x.0 instead of just x if they are whole number values.
       // bool zeroRemainder( long double doubleValue );

      //! holds all desired options for this unparser
          Unparser_Opt opt;

      //! used to index the preprocessor list
          int cur_index;

      //! The previous directive was a CPP statment (otherwise it was a comment)
          bool prevdir_was_cppDeclaration;

#if 0
      // These have been removed from use (it was a ackard mechanism).
      //! the line number of the statement/directive to be unparsed note that 0 means unparse ALL lines
       // int line_to_unparse;
          int ltu;
#endif

       // DQ (8/19/2007): Added simple access to the SgFile so that options specified there are easily available.
       // Using this data member a number of mechanism in the unparser could be simplified to be more efficient 
       // (they currently search bacj through the AST to get the SgFile).
          SgFile* currentFile;

      //! This is a cursor mechanism which is not encapsulated into the curprint() member function.
     public:
          UnparseFormat cur;

     public:
      //! delegate unparser that can be used to replace the output of this unparser
          UnparseDelegate *repl;

#if USE_OLD_MECHANISM_OF_HANDLING_PREPROCESSING_INFO

#error "Dead Code!"

      /*! \brief Old approach to handling comments separately from the AST, it 
                 is included for compatability while it is evaluated.
          \depricated This approach is currently not used (will be removed soon).
       */
          ROSEAttributesListContainer directiveListContainer;
#endif

      // DQ (10/23/2006): Moved to be private after Thomas noticed this was incorrectly marked 
      // public in this program vizualization.
      //! compiler generated code statements are pushed into a temporary queue so that they can 
      //! be output after any statements attached to the next statements and before the next statement
          std::list<SgStatement*> compilerGeneratedStatementQueue;

   // DQ (5/8/2010): Switched this to be private.
      private:
       // DQ (12/5/2006): Output information that can be used to colorize properties of generated code (useful for debugging).
          int embedColorCodesInGeneratedCode;

       // DQ (12/5/2006): Output separate file containing source position information for highlighting (useful for debugging).
          int generateSourcePositionCodes;

       // DQ (5/8/2010): Added support to force unparser to reset the source positon in the AST (this is the only side-effect in unparsing).
          bool p_resetSourcePosition;

     public:
#if 0
       // DQ (12/6/2014): This type permits specification of what bounds to use in the specifiation of token stream subsequence boundaries.
          enum token_sequence_position_enum_type
             {
               e_leading_whitespace_start,
               e_leading_whitespace_end,
               e_token_subsequence_start,
               e_token_subsequence_end,
               e_trailing_whitespace_start,
               e_trailing_whitespace_end
             };
#endif

       // DQ (8/19/2007): I have removed the "int lineNumberToUnparse" function parameter (see code for details).
       // Unparser( std::ostream* localStream, std::string filename, Unparser_Opt info, int lineNumberToUnparse, UnparseFormatHelp *h = NULL, UnparseDelegate* repl = NULL);
      //! constructor
          Unparser( std::ostream* localStream, std::string filename, Unparser_Opt info, UnparseFormatHelp *h = NULL, UnparseDelegate* repl = NULL);

      //! destructor
          virtual ~Unparser();

       // DQ (9/11/2011): Added copy constructor.
          Unparser(const Unparser & X);

       // DQ (9/11/2011): Added operator==() to fix issue detected in static analysis.
          Unparser & operator=(const Unparser & X);

      //! get the output stream wrapper
          UnparseFormat& get_output_stream(); 

      //! true if SgLocatedNode is part of a transformation on the AST
          bool isPartOfTransformation( SgLocatedNode *n);

      //! true if SgLocatedNode is part of a compiler generated part of the AST (e.g template instatiation)
          bool isCompilerGenerated( SgLocatedNode *n);

      //! counts the number of lines in one directive
          int line_count(char*);
  
      //! Used to decide which include files (most often header files) will be unparsed
          bool containsLanguageStatements (char* fileName);

      //! special case of extern "C" { \n\#include "foo.h" }
          bool includeFileIsSurroundedByExternCBraces ( char* tempFilename );

      //! incomplete-documentation
          bool isASecondaryFile ( SgStatement* stmt );

      //! friend string globalUnparseToString ( SgNode* astNode );

       // void unparseProject ( SgProject* project, SgUnparse_Info& info );
       // void unparseFile       ( SgFile* file, SgUnparse_Info& info );
          void unparseFile ( SgSourceFile* file, SgUnparse_Info& info, SgScopeStatement* unparseScope = NULL );
          void unparseFile ( SgBinaryComposite*, SgUnparse_Info& info );

       // Unparses a single physical file
          void unparseAsmFile ( SgAsmGenericFile* asmFile, SgUnparse_Info & info );

      //! remove unneccessary white space to build a condensed string
          static std::string removeUnwantedWhiteSpace ( const std::string & X );

      //! friend string globalUnparseToString ( SgNode* astNode );
      //  void unparseProject ( SgProject* project, SgUnparse_Info& info );
      //  void unparseFile    ( SgFile* file, SgUnparse_Info& info );

       // DQ (12/5/2006): Output separate file containing source position information for highlighting (useful for debugging).
          int get_embedColorCodesInGeneratedCode();
          int get_generateSourcePositionCodes();
          void set_embedColorCodesInGeneratedCode( int x );
          void set_generateSourcePositionCodes( int x );

       // DQ (5/8/2010): Added support to force unparser to reset the source positon in the AST (this is the only side-effect in unparsing).
          void set_resetSourcePosition(bool x);
          bool get_resetSourcePosition();

       // DQ (5/8/2010): Added support to force unparser to reset the source positon in the AST (this is the only side-effect in unparsing).
      //! Reset the Sg_File_Info to reference the unparsed (generated) source code.
          void resetSourcePosition (SgStatement* stmt);

       // DQ (9/30/2013): Unparse the file using the token stream (stored in the SgFile).
          void unparseFileUsingTokenStream ( SgSourceFile* file );

       // DQ (9/30/2013): Supporting function for evaluating token source position information.
       // int getNumberOfLines( std::string s ) const;
       // int getColumnNumberOfEndOfString( std::string s ) const;
          static int getNumberOfLines( std::string s );
          static int getColumnNumberOfEndOfString( std::string s );

       // DQ (8/7/2018): Refactored code for name qualification (so that we can call it once before all files 
       // are unparsed (where we unparse multiple files because fo the use of header file unparsing)).
          static void computeNameQualification ( SgSourceFile* file );
   };


// DQ (5/8/2010): Refactored code to generate the Unparser object.
void resetSourcePositionToGeneratedCode( SgFile* file, UnparseFormatHelp *unparseHelp );

// DQ (10/11/2007): I think this is redundant with the Unparser::unparseProject() member function
// DQ (3/18/2006): Modified to include UnparseFormatHelp in the interface.  These function can be 
// called by the user if backend compilation using the vendor compiler is not required.

//! User callable function available if compilation using the backend compiler is not required.
ROSE_DLL_API void unparseFile   ( SgFile*    file,    UnparseFormatHelp* unparseHelp = NULL, UnparseDelegate *repl  = NULL, SgScopeStatement* unparseScope = NULL );

//! User callable function available if compilation using the backend compiler is not required.
ROSE_DLL_API void unparseIncludedFiles( SgProject* project, UnparseFormatHelp* unparseHelp = NULL, UnparseDelegate *repl  = NULL );

//! User callable function available if compilation using the backend compiler is not required.
ROSE_DLL_API void unparseProject( SgProject* project, UnparseFormatHelp* unparseHelp = NULL, UnparseDelegate *repl  = NULL );

//! Support for handling directories of files in ROSE (useful for code generation).
void unparseDirectory   ( SgDirectory* directory, UnparseFormatHelp* unparseHelp = NULL, UnparseDelegate *repl  = NULL );

// DQ (1/19/2010): Added support for refactored handling directories of files.
//! Support for refactored handling directories of files.
void unparseFileList ( SgFileList* fileList, UnparseFormatHelp *unparseFormatHelp = NULL, UnparseDelegate* unparseDelegate = NULL);

#endif
