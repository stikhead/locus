#include <iostream>
#include <sqlite3.h>
#include<string>
using namespace std;

static int callback(void* data, int argc, char** argv, char** azColName)
{
    int i;
    fprintf(stderr, "%s: ", (const char*)data);

    for (i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");
    return 0;
}

int main(int argc, char** argv)
{
     sqlite3* DB;
    int exit = 0;
    exit = sqlite3_open("test.db", &DB);
    string data("CALLBACK FUNCTION");

    string sql("SELECT * FROM VEHICLES;");
    if (exit) {
        std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
        return (-1);
    }
    else
        std::cout << "Opened Database Successfully!" << std::endl;

    int rc = sqlite3_exec(DB, sql.c_str(), callback, (void*)data.c_str(), NULL);

    if (rc != SQLITE_OK)
        cerr << "Error SELECT" << endl;
    else {
        cout << "Operation OK!" << endl;
    }

    sqlite3_close(DB);
    return (0);
}

// #include <iostream>
// #include <sqlite3.h>
// #include <string>

// using namespace std;

// static int callback(void* data, int argc, char** argv, char** azColName)
// {
//     int i;
//     fprintf(stderr, "%s: ", (const char*)data);

//     for (i = 0; i < argc; i++) {
//         printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
//     }

//     printf("\n");
//     return 0;
// }

// int main(int argc, char** argv)
// {
//     sqlite3* DB;
//     char* messaggeError;
//     int exit = sqlite3_open("test.db", &DB);
//     string query = "SELECT * FROM VEHICLES;";

//     cout << "STATE OF TABLE BEFORE INSERT" << endl;

//     sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

//     string sql("INSERT INTO VEHICLES VALUES ('HR02');");//, ('HR04'), ('HR06');");
//     exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
//     if (exit != SQLITE_OK) {
//         std::cerr << "Error Insert" << std::endl;
//         sqlite3_free(messaggeError);
//     }
//     else
//         std::cout << "Records created Successfully!" << std::endl;

//     cout << "STATE OF TABLE AFTER INSERT" << endl;

//     sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

//     sql = "DELETE FROM PERSON WHERE ID = 2;";
//     exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
//     if (exit != SQLITE_OK) {
//         std::cerr << "Error DELETE" << std::endl;
//         sqlite3_free(messaggeError);
//     }
//     else
//         std::cout << "Record deleted Successfully!" << std::endl;

//     cout << "STATE OF TABLE AFTER DELETE OF ELEMENT" << endl;
//     sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

//     sqlite3_close(DB);
//     return (0);
// }
// int main(int argc, char** argv)
// {
//     sqlite3* DB;
//     string sql = "CREATE TABLE VEHICLES("
//                   "ID INT AUTO_INCREMENT PRIMARY KEY,"
//                   "NUMBER_PLATE VARCHAR(50) UNIQUE NOT NULL,"
//                   "PARKED_AT TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
//                 ")";
//     int exit = 0;
//     exit = sqlite3_open("test.db", &DB);
//     char* messaggeError;
//     exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);

//     if (exit != SQLITE_OK) {
//         std::cerr << "Error Create Table" << std::endl;
//         sqlite3_free(messaggeError);
//     }
//     else
//         std::cout << "Table created Successfully" << std::endl;
//     sqlite3_close(DB);
//     return (0);
// }

// int main(int argc, char** argv)
// {
//     sqlite3* DB;
//     int exit = 0;
//     exit = sqlite3_open("test.db", &DB);

//     if (exit) {
//         std::cerr << "Error open DB " << sqlite3_errmsg(DB) << std::endl;
//         return (-1);
//     }
//     else
//         std::cout << "Opened Database Successfully!" << std::endl;
//     sqlite3_close(DB);
//     return (0);
// }


// int main(int argc, char** argv){
//     sqlite3* DB;
//     char* messaggeError;
//     int exit = 0;
//     exit = sqlite3_open("parkingLot.db", &DB);
//     string dropquery = "DROP TABLE VEHICLES";
//     string query = "SELECT * FROM VEHICLES;";
// // //     //  string query = "ALTER TABLE VEHICLES AUTO_INCREMENT=1;";
// // //     //  string query = "ALTER TABLE VEHICLES ADD id INT NOT NULL AUTO_INCREMENT PRIMARY KEY;";
// // //         // string query = "ALTER TABLE VEHICLES MODIFY id INT NOT NULL AUTO_INCREMENT PRIMARY KEY;";
// // // string query = "ALTER TABLE VEHICLES DROP PRIMARY KEY;";
// // // string query2 = "ALTER TABLE VEHICLES MODIFY id INT NOT NULL AUTO_INCREMENT PRIMARY KEY;";

//     cout << "STATE OF TABLE BEFORE INSERT" << endl;

//     sqlite3_exec(DB, dropquery.c_str(), callback, NULL, NULL);
// // // sqlite3_exec(DB, query2.c_str(), callback, NULL, NULL);

//     string sql("INSERT INTO VEHICLES (NUMBER_PLATE) VALUES ('HR02'),('HR04'),('HR06');");

//     exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
//     if (exit != SQLITE_OK) {
//         std::cerr << "Error Insert" << std::endl;
//         sqlite3_free(messaggeError);
//     }
//     else
//         std::cout << "Records created Successfully!" << std::endl;

//     cout << "STATE OF TABLE AFTER INSERT" << endl;

//     sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

//     sql = "DELETE FROM VEHICLES";
//     exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
//     if (exit != SQLITE_OK) {
//         std::cerr << "Error DELETE" << std::endl;
//         sqlite3_free(messaggeError);
//     }
//     else
//         std::cout << "Record deleted Successfully!" << std::endl;

//     cout << "STATE OF TABLE AFTER DELETE OF ELEMENT" << endl;
//     sqlite3_exec(DB, query.c_str(), callback, NULL, NULL);

//     sqlite3_close(DB);
//     return (0);
//     // string sql = "CREATE TABLE VEHICLES("
//     //               "ID INT AUTO_INCREMENT PRIMARY KEY,"
//     //               "NUMBER_PLATE VARCHAR(50) UNIQUE NOT NULL,"
//     //               "PARKED_AT TIMESTAMP DEFAULT CURRENT_TIMESTAMP"
//     //             ")";
//     // char* messaggeError;
//     // exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messaggeError);
//     // exit = sqlite3_open("ParkingLot.db", &DB);
//     // if(exit){
//     //     cout<<"ERROR CREATING DATABSE: "<<sqlite3_errmsg(DB)<<endl;
//     // }
//     // else {
//     //     cout<<"SUCCESSFULLY CREATED DB!"<<endl;
//     // }
//     // sqlite3_close(DB);
//     //  if (exit != SQLITE_OK) {
//     //     std::cerr << "Error Create Table" << std::endl;
//     //     sqlite3_free(messaggeError);
//     // }
//     // else
//     //     std::cout << "Table created Successfully" << std::endl;
//     // sqlite3_close(DB);
//     // return (0);
// }

