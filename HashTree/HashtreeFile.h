//
// Created by bob on 19-1-15.
//

#ifndef HASHTREE_HASHTREEFILE_H
#define HASHTREE_HASHTREEFILE_H

#include <string>
#include "Hashtree.h"

#include <fstream>
#define BUFSIZE 1024

typedef struct HashtreeBuffer{

    unsigned char data[BUFSIZE];
} HTBuffer;



class HashtreeFile {
private:
    HashtreeState Hashnode_to_Buffer(HashNode& hashNode,HTBuffer& htBuffer);
    HashtreeState Buffer_to_Hashnode(HashNode& hashNode,HTBuffer& htBuffer);

    HashtreeState Hashnode_to_File(std::string& output_path,HashNode& hashNode);
    HashtreeState File_to_Hashnode(std::ifstream& output_path,HashNode& hashNode);
    HashtreeState build_HashtoFile(std::string& output_path,HashNode *now, int target);
    HashtreeState build_FiletoHash(std::ifstream& output_path,HashNode *now, int target);
public:
    HashtreeState File_to_Hashtree(std::string& input_path,Hashtree& hashtree);
    HashtreeState Hashtree_to_File(std::string& output_path,Hashtree& hashtree);


};


#endif //HASHTREE_HASHTREEFILE_H
