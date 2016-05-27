.conflicts.OK <- TRUE
.onLoad <-  function (libname, pkgname) {
    if (.Platform$OS.type == "windows") {
       tryCatch (utils::readRegistry("SOFTWARE\\MeCab", hive="HCU", maxdepth=2), 
           error = function(e){
             browseURL("http://code.google.com/p/mecab/downloads/list") ;
             stop ("MeCab not found. please install it!")
           } )
   } else  if(system("which mecab")) {
      browseURL("http://code.google.com/p/mecab/downloads/list") 
      stop ("MeCab not found. please install it!")
   } else {
      # function (libname, pkgname) library.dynam("RMeCab", pkgname, libname)
  }
}
