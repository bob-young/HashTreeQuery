//
// Created by bob on 19-1-15.
//

#include "HashtreeFile.h"

void split(std::string string,const std::string flag,std::vector<std::string>& v){
    std::string::size_type p1,p2;
    size_t len=string.length();
    p2=string.find(flag);
    p1=0;
    while (std::string::npos!=p2){
        v.emplace_back(string.substr(p1,p2-p1));
        p1=p2+flag.size();
        p2=string.find(flag,p1);
    }
    if(p1!=len){
        v.emplace_back(string.substr(p1));
    }
}

HashtreeState HashtreeFile::Hashnode_to_Buffer(HashNode &hashNode, HTBuffer &htBuffer) {
    int buffer_count=0;
    //table name
    sprintf((char*)htBuffer.data,"{table_name:%s\0}\n",hashNode.data.c_str());
    buffer_count+=hashNode.data.size()+15;
    //prev hash
    htBuffer.data[buffer_count++]='{';
    for (int i = 0; i < KEYBYTE; ++i) {
        htBuffer.data[buffer_count++]=*((char*)&hashNode.prevHashcode+i);
    }
    htBuffer.data[buffer_count++]='}';
    //users
    htBuffer.data[buffer_count++]='{';
    for (int i = 0; i < hashNode.users.size(); ++i) {
        sprintf((char*)htBuffer.data+i,"%s\0,",hashNode.users[i].c_str());
        buffer_count+=hashNode.users[i].size()+2;
    }
    htBuffer.data[buffer_count++]='}';
    if(buffer_count>=1024){
        return HashtreeState::HTBUFFER_OVER_FLOW;
    }
    return HashtreeState::SUCCESS;
}

HashtreeState HashtreeFile::Buffer_to_Hashnode(HashNode &hashNode, HTBuffer &htBuffer) {
    return HashtreeState ::SUCCESS;
}

HashtreeState HashtreeFile::File_to_Hashtree(std::string& input_path, Hashtree &hashtree) {
    std::cout<<"loading...\n";
    std::ifstream input(input_path,std::ios_base::in |std::ios_base::binary);

    if(input.fail()){
        return HashtreeState ::FILE_OPEN_ERR;
    }
    if(input.bad()){
        return HashtreeState ::FILE_READ_ERR;
    }
//------------------
    char getstr[BUFSIZE];
    char newstr[BUFSIZE];
    input.getline(getstr,BUFSIZE);
    sscanf(getstr,"<<%d>>",&(hashtree.id));

    memset(getstr,'\0',BUFSIZE);
    input.getline(getstr,BUFSIZE);
    sscanf(getstr,"<<%s>>",newstr);
    hashtree.name=std::string(newstr);

    memset(getstr,'\0',BUFSIZE);
    input.getline(getstr,BUFSIZE);
    sscanf(getstr,"<<%d>>",&(hashtree.depth));

//---------------------------

    build_FiletoHash(input,hashtree.get_root(),hashtree.get_depth()-1);
    input.close();
    return HashtreeState ::SUCCESS;
}

HashtreeState HashtreeFile::Hashtree_to_File(std::string& output_path, Hashtree &hashtree) {
    std::cout<<"dumping...\n";
    std::ofstream output(output_path,std::ios_base::out| std::ios::trunc|std::ios_base::binary);
    //write basic hashtree data
    //name
    output<<"<<"<<hashtree.id<<">>\n";
    output<<"<<"<<hashtree.name<<">>\n";
    output<<"<<"<<hashtree.depth<<">>\n";
    output.close();
    build_HashtoFile(output_path,hashtree.get_root(),hashtree.get_depth()-1);
    return HashtreeState ::SUCCESS;
}

HashtreeState HashtreeFile::build_HashtoFile(std::string& output_path,HashNode* now ,int target){
    if(now->get_level()==target){
        Hashnode_to_File(output_path,*now);
        return HashtreeState ::SUCCESS;
    }else{
        //std::cout<<"++"<<now->get_capacity()<<std::endl;
        if(now->sons.size()!=now->get_capacity()){
            std::cout<<"incomplete hash tree\n";
            return HashtreeState ::HT_INCOMPLETE;
        }
        for(int i=0;i<now->sons.size();i++){
            //std::cout<<"__"<<now->get_level()<<std::endl;
            if(build_HashtoFile(output_path,(HashNode*)(now->sons[i]),target)== HashtreeState ::SUCCESS){
                continue;
            } else{
                std::cout<<"fail to dump"<<std::endl;
                exit(0);
            }
        }
        Hashnode_to_File(output_path,*now);
        return HashtreeState ::SUCCESS;
    };
}


HashtreeState HashtreeFile::Hashnode_to_File(std::string &output_path, HashNode &hashNode) {

    std::ofstream output(output_path,std::ios_base::app|std::ios_base::binary);
    if(output.fail()){
        return HashtreeState ::FILE_OPEN_ERR;
    }
    if(output.bad()){
        return HashtreeState ::FILE_WRITE_ERR;
    }
    //colname
    output<<"{"<<hashNode.data<<"}\n";
    //prev hash
    output<<"{";
    for (int i = 0; i < KEYBYTE; ++i) {
        output<<*((char*)&(hashNode.prevHashcode)+i);
    }
    output<<"}\n";
    //users
    output<<"{";
    for (int j = 0; j < hashNode.users.size(); ++j) {
        output<<hashNode.users[j]<<",";
    }
    output<<"}\n";
    output.close();
    return HashtreeState ::SUCCESS;
}

HashtreeState HashtreeFile::File_to_Hashnode(std::ifstream& input, HashNode &hashNode) {

    if(input.fail()){
        return HashtreeState ::FILE_OPEN_ERR;
    }
    if(input.bad()){
        return HashtreeState ::FILE_READ_ERR;
    }
    //colname
    //output<<"{"<<hashNode.data<<"}\n";
    char getstr[BUFSIZE];
    char newstr[BUFSIZE];
    input.getline(getstr,BUFSIZE);
    sscanf(getstr ,"{%s", newstr);


    hashNode.data = std::string(newstr);
    hashNode.data.pop_back();
    //prev hash
    /*
    output<<"{";
    for (int i = 0; i < KEYBYTE; ++i) {
        output<<*((char*)&(hashNode.prevHashcode)+i);
    }
    output<<"}\n";
    */
     //----------------
    char tmpchar;
    input.get(tmpchar);
    if(tmpchar=='{'){
        for(int i=0;i< KEYBYTE;i++){
            input.get(tmpchar);
            *((char*)&(hashNode.prevHashcode)+i)=tmpchar;
        }
    } else{
        return HashtreeState::FILE_READ_FORMAT_ERR;
    }
    input.get(tmpchar);
    if(tmpchar!='}'){
        return HashtreeState ::FILE_READ_FORMAT_ERR;
    }
    input.get(tmpchar);//get "\n"
    //users
    /*
    output<<"{";
    for (int j = 0; j < hashNode.users.size(); ++j) {
        output<<hashNode.users[j]<<",";
    }
    output<<"}\n";*/
    memset(getstr,'\0',BUFSIZE);
    memset(newstr,'\0',BUFSIZE);
    input.getline(getstr,BUFSIZE);
    sscanf(getstr,"{%s}",newstr);

    std::string str=std::string(newstr);
    str.pop_back();
    //std::cout<<str<<std::endl;
    std::vector<std::string> users;

    split(str,std::string(","),users);

    for (int j = 0; j < users.size(); ++j) {
        hashNode.users.push_back(users[j]);
    }

    return HashtreeState ::SUCCESS;
}

HashtreeState HashtreeFile::build_FiletoHash(std::ifstream& input, HashNode *now, int target) {
    if(now->get_level()==target){
        File_to_Hashnode(input,*now);
        (*now).showNode();
        return HashtreeState ::SUCCESS;
    }else{
        //std::cout<<"++"<<now->get_capacity()<<std::endl;
        if(now->sons.size()!=now->get_capacity()){
            std::cout<<"incomplete hash tree\n";
            return HashtreeState ::HT_INCOMPLETE;
        }
        for(int i=0;i<now->sons.size();i++){
            //std::cout<<"__"<<now->get_level()<<std::endl;
            if(build_FiletoHash(input,(HashNode*)(now->sons[i]),target)== HashtreeState ::SUCCESS){
                continue;
            } else{
                std::cout<<"fail to load"<<std::endl;
                exit(0);
            }
        }
        File_to_Hashnode(input,*now);
        (*now).showNode();
        return HashtreeState ::SUCCESS;
    };
}

