#include "crypt.h"

crypting::crypting(QObject *parent) :
    QObject(parent)
{
}
QString crypting::dsCrypt(QString input,bool decrypt) {
    int x=13; // squares width (of symbols)
    int y=10; // squares height (of symbols)
    QChar s1[x][y]; // Arrays for: Output, Square1, Square2
    QChar s2[x][y];
    // формируем базовый массив с набором символов
    QString basea="1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZабвгдежзийклмнопрстуфхцчшщъыьэюяАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ _,.";    // base symbol set // first square
    QString baseb="а мХНй8ABПwZТ,.12опЖЗzцxEYИЙшtfghijК6БВЛк_рхэWюяpqrKлжДЕP9QVcнвгXщN0бУзиф7eсC34РГъыOЦyШЩЪЫЬЧЭЮЯIJDФАsFОuчklmnoST5ьМabvСUтудеLMRdGH";    // base symbol set // second square
    // filling squares
    for(int i=0;i<y;i++) { // create Squares
        for(int j=0;j<x;j++) {
            s1[j][i] = basea[i*x+j];
            s2[j][i] = baseb[i*x+j];
        }
    }

    int m = (int)floor(input.count()/2)*2; // !strlen%2
    QChar symbl;  // last symbol (unpaired)
    if (m==input.count()){
        symbl=NULL;
    } else {
        symbl=input[input.count()-1];
    }

    // crypting/uncrypting pairs of symbols
    QString o;
    int al[2];
    for (int ii=0; ii<m; ii+=2) {
        QChar symb1;
        QChar symb2;
        QChar symbn1;
        QChar symbn2;
        symb1 = symbn1 = input[ii];
        symb2 = symbn2 = input[ii+1];
        int a1[2];
        int a2[2];

        for(int i=0;i<y;i++) { // search symbols in Squares
            for(int j=0;j<x;j++) {
                if (decrypt) {
                    if (symb1==s2[j][i] ) { a1[0]=j; a1[1]=i; }
                    if (symb2==s1[j][i] ) { a2[0]=j; a2[1]=i; }
                    if (!symbl.isNull() && symbl==s2[j][i]) { al[0]=j; al[1]=i; }
                }
                else {
                    if (symb1==s1[j][i] ) { a1[0]=j; a1[1]=i; }
                    if (symb2==s2[j][i] ) { a2[0]=j; a2[1]=i; }
                    if (!symbl.isNull() && symbl==s1[j][i]) { al[0]=j; al[1]=i; }
                }
            }
        }

        if (sizeof(a1) && sizeof(a2)) {
            if (decrypt==true){
                symbn1=s1[a1[0]][a2[1]];
                symbn2=s2[a2[0]][a1[1]];
            } else {
                symbn1=s2[a1[0]][a2[1]];
                symbn2=s1[a2[0]][a1[1]];
            }
        }
        o += symbn1;
        o += symbn2;
    }
    if (!symbl.isNull() && sizeof(al)) // last symbol
        o+= decrypt ? s1[al[1]][al[0]] : s2[al[1]][al[0]];
   return o;
}
QString crypting::encrypt(QString input){
    return this->dsCrypt(input);
}
QString crypting::decrypt(QString input){
    return this->dsCrypt(input,true);
}
