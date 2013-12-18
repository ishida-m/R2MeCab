#include "setMap.h"

int setMap (map<string, int> & lmap, const string word) {
  
  // 要素を出力する
  map <string, int>::iterator pa = lmap.begin();

  pa = lmap.find(word);
  //出てきた形態素原型は既にマップにあるか？
  if(pa != lmap.end()){
    pa->second =  pa->second + 1;
    //二つ目の数値を加算
  }					
  else{// マップにないなら，新規にマップに追加
    //					  Rprintf("add map \n");
    lmap.insert(make_pair(word, 1));// 1 は 1個目と言う意味
  }

  return 0;
  
  // while( it != names.end() )
  //   {
  //     cout << (*pa).first << ":" << (*pa).second << endl;
  //     ++pa;
  //   }
  
}

