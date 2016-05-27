#undef USE_ICONV
#ifdef USE_ICONV
  #include <iconv.h>
#else
  #include <unicode/ucnv.h>
#endif
#include <unicode/unistr.h>
#include <unicode/uchar.h>
#include <unicode/schriter.h>
#include <unicode/normlzr.h>
#include <vector>
#include "setMap.h"

int setMap (map<string, int> & lmap, const string word) {

 // utf-8 からUnicodeに変換
  icu::UnicodeString src(word.c_str(), "utf-8");
// NFKC正規化
  icu::UnicodeString dest;
  UErrorCode status;
  icu::Normalizer::normalize(src, UNORM_NFKC, 0, dest, status);
  // 失敗した場合．
  if (U_FAILURE(status)) {
    return 1;
  }
  // 再びUTF-8に戻す
  // char buf[16];
  std::vector<char> buf (dest.length() + 1);
  int32_t length = dest.extract(0, dest.length(), &buf[0], sizeof(buf), "utf-8");
  
  // 要素を出力する
  map <string, int>::iterator pa = lmap.begin();

  pa = lmap.find(&buf[0]);
  //出てきた形態素原型は既にマップにあるか？
  if(pa != lmap.end()){
    pa->second =  pa->second + 1;
    //二つ目の数値を加算
  }					
  else{// マップにないなら，新規にマップに追加
    //					  Rprintf("add map \n");
    lmap.insert(make_pair(&buf[0], 1));// 1 は 1個目と言う意味
  }

  return 0;
  
  // while( it != names.end() )
  //   {
  //     cout << (*pa).first << ":" << (*pa).second << endl;
  //     ++pa;
  //   }
  
}

