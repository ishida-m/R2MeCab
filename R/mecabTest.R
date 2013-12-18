
mecabTest  <- function(str){
  if ((!is.character(str)) || nchar(str) < 1){
    stop ("arg must be characters")
  }else{
    .Call( "mecab_test", str, PACKAGE = "R2MeCab" )
  }
}

