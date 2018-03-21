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
        //TempBuff.push_back(Linea.substr(0, Linea.find_first_of(Separador)));
        TotalVector = 0;
    }
}

// struct Registro {
//    int vehiculoID;
//    string codigo;
//    int ano;
//    string tipo;
//    string marca;
//    string modelo_raw;
//    string modelo;
//    string version;
//    int pts;
//    int cilindr;
//    string comb;
//    string trans;
//    string equip;
//    int tas_2018;
//    int perm_2018;
// };

int main(){

  mysqlpp::Connection conn(false);
     char db[]     = "SII_2018";
     char server[] = "localhost";
     char user[]   = "r0bert01de";
     char pass[]   = "1709";

     int j = 0, i = 0, k = 0;
     fstream fichero;
     string linea;
     vector<string> TempBuff(0);
     int TotalVector;
     fichero.open("liv2018xls.csv",ios::in);
     getline(fichero,linea);
     while (!fichero.eof()) {
       split(linea, *";", TempBuff, TotalVector);

       if(TempBuff[2]!="MOTO"){
         // llenar BASE DE DATOS
         string res = TempBuff[2];
         i++;
       }else{
         // cout << linea << endl;
         if (TotalVector!=12)
           k++;
         j++;
       }
       getline(fichero,linea);
     // cout << linea << endl;
     }
     cout << TotalVector << endl;
     cout << "motos: " << j << endl;
     cout << "otros: " << i << endl;
     cout << "revisar: " << k << endl;

     if (conn.connect(NULL, server, user, pass)){
        // string consulta = "select * from ins_institutos";
        string consulta="SHOW DATABASES";
        Query query = conn.query(consulta);
        if (StoreQueryResult res = query.store()){
        cout << "Bases de datos encontradas: "<<res.num_rows()<<endl;
          if (res.num_rows() > 0){
            bool flag=false;
            // cout <<res[0]["nombre"] << endl;
            for (StoreQueryResult::iterator it=res.begin(); it!=res.end(); ++it){
              if ((it)->at(0)=="SII_2018"){
                flag=true;
                break;
              }
            }
            if (flag){
                // Miramos los contenidos de la tabla
                cout << "La base de datos se encuentra" << endl;
                query.reset();
                if (conn.select_db("SII_2018")){
                    string sql = "INSERT INTO IDEN_VEHI (vehiculoID,codigo,ano,tipo,marca,modelo_raw,modelo,version,ptas,cilindr,comb,trans,equip,tas_2018,perm_2018) VALUES('"+to_string(i);
                    string sql1 = "','"+TempBuff[0]+"','"+TempBuff[1]+"','"+TempBuff[2]+"','"+TempBuff[3]+"','"+TempBuff[4]+"','"+'0'+"','"+'0'+"','"+TempBuff[5]+"','"+TempBuff[6];
                    string sql2 = "','"+TempBuff[7]+"','"+TempBuff[8]+"','"+TempBuff[9]+"','"+TempBuff[10]+"','"+TempBuff[11]+"')";
                    string registro = sql+sql1+sql2;
                    query = conn.query(registro);
                    if (query.execute()){
                        cout << "OK" << endl;
                    }else{
                        cout << "Fallo al introducir datos" << endl;
                    }
                }else{
                    cout << "Fallo al seleccionar la base de datos" << endl;
                }
            }else{
              // Lo construimos todo
              // cout << "La base de datos no se encuentra, sera creada" << endl;
              // if (conn.create_db("SII_2018")){
              //   cout << "Seleccionando base de datos" << endl;
              //   AQUI HARE UNA LECTURA DEL SQL PARA CREARLA
              //   if (conn.select_db("SII_2018")){
              //     cout << "Creando tabla" << endl;
              //     query.reset();
              //     query=conn.query("CREATE TABLE IF NOT EXISTS `poesiadb`.`test` ("
              //              "`id` bigint(20) NOT NULL AUTO_INCREMENT,"
              //              "`blog` varchar(100) NOT NULL,"
              //              "`url` varchar(255) NOT NULL,"
              //              "PRIMARY KEY (`id`)"
              //              ") ENGINE=MyISAM DEFAULT CHARSET=latin1 AUTO_INCREMENT=1 ;");
              //     if (query.execute()){
              //       query.reset();
              //       string sql = "INSERT INTO IDEN_VEHI (vehiculoID,codigo,ano,tipo,marca,modelo_raw,modelo,version,ptas,cilindr,comb,trans,equip,tas_2018,perm_2018) VALUES('"+to_string(i);
              //       string sql1 = "','"+TempBuff[0]+"','"+TempBuff[1]+"','"+TempBuff[2]+"','"+TempBuff[3]+"','"+TempBuff[4]+"','"+'0'+"','"+'0'+"','"+TempBuff[5]+"','"+TempBuff[6];
              //       string sql2 = "','"+TempBuff[7]+"','"+TempBuff[8]+"','"+TempBuff[9]+"','"+TempBuff[10]+"','"+TempBuff[11]+"')";
              //       string registro = sql+sql1+sql2;
              //       query = conn.query(registro);
              //       if (query.execute()){
              //           cout << "OK" << endl;
              //       }else{
              //           cout << "Fallo al introducir datos" << endl;
              //       }
              //     }else
              //       cout << "Error al crear tabla"<<endl;
              //   }else
              //     cout << "Fallo al seleccionar la base de datos" << endl;
              // }else
              //   cout << "Fallo al crear base de datos" << endl;
            }
          }else
            cout << "Fallo al obtener bases de datos" << endl;
        }
           conn.disconnect();
      }else
        cout <<"Fallo al conectarse a la BD: "<<conn.error()<<endl;
}
