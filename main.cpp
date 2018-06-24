#include <QCoreApplication>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <QVector>
using namespace std;

bool identical(string,string);

int main(int argc, char *argv[])
{
    map<string,string> identical_files;
    QVector <string> files;
    DIR *dfd;
    struct dirent *dp;
    char filename[NAME_MAX];

    if ( argc < 2 )
        strcpy(filename, "./files");
    else
        strcpy(filename, argv[1]);

    //printf("%s\n\n", filename);
    dfd=opendir(filename);

    while( (dp=readdir(dfd)) != NULL )
       {
        if (!(strcmp(dp->d_name,".")) || !(strcmp(dp->d_name, ".."))){}
            else
        files.push_back(dp->d_name);}

    closedir(dfd);

    for (int i = 0; i < files.size()-1; ++i) {
        for (int j = i+1; j < files.size(); ++j){
            if (i!=j){
                if (identical(files.at(i).c_str(),files.at(j).c_str())) {
                    identical_files.insert(pair<string,string>
                                           (files.at(i).c_str(),files.at(j).c_str()));
                    break;
                }
            }
        }
    }

    for ( auto it = identical_files.begin(); it != identical_files.end(); ++it)
            {
                cout << (*it).first << " : " << (*it).second << endl;
            }
    return 0;
}

bool identical(string filename1,string filename2){

    ifstream file1(("./files/"+filename1).c_str());
    ifstream file2(("./files/"+filename2).c_str());
    string line;
    vector<string>  text1,text2;
    if (file1.is_open() )
    {
        while (! file1.eof() )
        {
        getline (file1,line );

            text1.push_back(line);
        }
   }
    file1.close();


    if (file2.is_open() )
    {
        while (! file2.eof() )
        {
            getline (file2,line);

           text2.push_back(line);
        }

    }
    file2.close();


    if (text1==text2) return 1;
    else return 0;
}

