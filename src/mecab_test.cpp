
/* put following Makevars in same directory
   
PKG_CXXFLAGS=$(shell Rscript -e "Rcpp:::CxxFlags()")
PKG_LIBS=$(shell Rscript -e "Rcpp:::LdFlags()") -lmecab
CLINK_CPPFLAGS=$(shell Rscript -e "Rcpp:::Cxx0xFlags()")
*/

/* usage: 
 $  R CMD SHLIB RcppMeCab.cpp util.cpp 
 $
 $ R
R> dyn.load ("RcppMeCab.so")
R> x <- .Call ("mecab_test", "すもももももももものうち")
R> x
R> dyn.unload ("RcppMeCab.so")
*/


#include <Rcpp.h>
#include "setMap.h"
// #include <string>
// #include "makeDataFrame.h"

#include "mecab_test.h"
#include <list>
// #include <vector>
#include "mecab.h"
#include "util.h"

//     using namespace std;

/*
#define CHECK(eval) if (! eval) { \
   const char *e = tagger ? tagger->what() : MeCab::getTaggerError(); \
   delete tagger; \
   return (SEXP) -1; }
*/



//#define CHECK(eval) if (! eval) { \
//    fprintf (stderr, "Exception:%s\n", mecab_strerror (mecab)); \
//    mecab_destroy(mecab); \
//    return R_NilValue ; }
///////////////////////////////////////////////////////////////return R_NilValue;} (SEXP) -1;


SEXP mecab_test (SEXP str){
  //   using namespace Rcpp;

  
  string input = Rcpp::as<string> (str);

  mecab_t * mecab;// MeCab::Tagger *tagger = MeCab::createTagger("");
  mecab = mecab_new2("");
  if (!mecab) {return R_NilValue ;}else { // ; CHECK(mecab); // CHECK(tagger);
  // Gets Node object.
    const mecab_node_t * node = mecab_sparse_tonode(mecab, input.c_str());// // const MeCab::Node* node = tagger->parseToNode(input.c_str());
    if (!node) {
      if (mecab) {
	mecab = NULL;
	free(mecab);
      }
      return R_NilValue ;
    } // 	CHECK(node);
    

  list <string> strL, strL2;
  // char * buf1;
  vector <string> feat; 
  map <string, int> m;
 
  
  for (; node; node = node->next){

    if (node->stat == MECAB_BOS_NODE) Rprintf ("\n");
    else if (node->stat == MECAB_EOS_NODE) ("\n");
    else {
      /*  <old>
      char * buf1 = (char *)malloc( node->length * MB_CUR_MAX+ 1);
      strncpy(buf1, node->surface, node->length) ;
      buf1[node->length] = '\0';// NULL-Terminateしておく //
      // </old>
      or
      */
      std::string buf1 (node->surface, node->length) ;
      if (buf1.size () > 0){
        // Rcpp::Rcout << buf1 << endl;
         
         feat = tmpsplit (string (node->feature), ",");
         strL.push_back (buf1);
         strL2.push_back(feat[0]);
         buf1  = buf1 + "-" + feat[0];
         setMap (m, buf1);
      }else {
         continue;
      }
      // <old> free (buf1); // if using char * buf1; // </old>
    }
    
  }
 
  mecab_destroy (mecab); // if (mecab != NULL) {free(mecab);}
 
  if (m.size () > 0){
    Rcpp::DataFrame res = Rcpp::DataFrame::create(Rcpp::_["word"] = m); 
  //  res.attr ("class") = "data.frame";
    return res;
  }else{
    return R_NilValue;
  }
  }//else 
}
