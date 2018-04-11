#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <mysql++/mysql++.h>

using namespace std;
using namespace mysqlpp;

int Cuenta(string s, const char Separadorr, int &TotalChars) {
    for (int i = 0; i < s.size(); i++)
        if (s[i] == Separadorr) TotalChars++;
}
void split(string Linea, char Separador, vector<string> &TempBuff, int &TotalVector) {
    TempBuff.resize(0);
    TotalVector = 0;
    int Nums = -1;
    int NumPos = -1;
    int ValorNum = 0;
    int TotalChars = 0;
    int TotalEspacios = Linea.length();
    string Valor;
    Cuenta(Linea, Separador, TotalChars);
    if (TotalChars != 0){
        while (Nums < TotalChars){
            Nums++;
            ValorNum = Linea.find(Separador, NumPos + 1);
            Valor = Linea.substr(NumPos + 1,ValorNum);
            Valor = Valor.substr(0, Valor.find_first_of(Separador));
            TempBuff.push_back(Valor);
            NumPos = ValorNum;
            TotalEspacios++;
        }
        TotalVector = TempBuff.size();
    }else{
        TotalVector = 0;
    }
}
int main(){

  mysqlpp::Connection conn(false);
      char db[]     = "SII_2018";
      char server[] = "localhost";
      char user[]   = "r0bert01de";
      char pass[]   = "1709";

  int j = 0, i = 0, k = 0,TotalVector;
  fstream fichero;
  string linea;
  vector<string> TempBuff(0);
  fichero.open("liv2018xls.csv",ios::in);
  getline(fichero,linea);
  while (!fichero.eof()) {
    split(linea, *";", TempBuff, TotalVector);
      if(TempBuff[2]!="MOTO"){
        if (conn.connect(NULL, server, user, pass)){
          string consulta="USE SII_2010";
          Query query = conn.query(consulta);
            if (conn.select_db("SII_2018")){
              // cout << "La base de datos se encuentra" << endl;
              query.reset();
              string sql = "INSERT INTO IDEN_VEHI (vehiculoID,codigo,ano,tipo,marca,modelo_raw,modelo,version,ptas,cilindr,comb,trans,equip,tas_2018,perm_2018) VALUES('"+to_string(i);
              string sql1 = "','"+TempBuff[0]+"','"+TempBuff[1]+"','"+TempBuff[2]+"','"+TempBuff[3]+"','"+TempBuff[4]+"','"+'0'+"','"+'0'+"','"+TempBuff[5]+"','"+TempBuff[6];
              string sql2 = "','"+TempBuff[7]+"','"+TempBuff[8]+"','"+TempBuff[9]+"','"+TempBuff[10]+"','"+TempBuff[11]+"')";
              string registro = sql+sql1+sql2;
              query = conn.query(registro);
              if (query.execute()){
                //cout << "OK" << endl;
                i++;
              }else{
                cout << "Fallo al introducir datos" << endl;
                break;
              }
            }else{
              cout << "Fallo al seleccionar la base de datos" << endl;
              break;
            }
          conn.disconnect();
        }
      }else{
        if (TotalVector!=12)
          k++;
        j++;
      }
    getline(fichero,linea);
  }
  cout << TotalVector << endl;
  cout << "motos: " << j << endl;
  cout << "otros: " << i << endl;
  cout << "revisar: " << k << endl;
}
