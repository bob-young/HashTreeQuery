//
// Created by bob on 19-1-26.
//

#include "HashTreeQuery.h"
#include "HashtreeFile.h"

HashTreeQuery::HashTreeQuery(const char *fp) {
    std::string path(fp);
    HashtreeFile hf=HashtreeFile();
    hashTree =new Hashtree(FIX_DEPTH);
    hf.File_to_Hashtree(path,*hashTree);
    //owner=hashTree->get_root()->get_owner();
    //current_users=hashTree->get_root()->get_users();
}

HashTreeQuery::HashTreeQuery() {

    hashTree =new Hashtree(FIX_DEPTH);
    //hashTree->show(hashTree->get_root());
}

void getwalk(HashNode* now,size_t hash_value,std::string tablename,HashMem** ret){
    if(now->data.compare(tablename)==0){
        *ret=&(now->hashcode);
        return ;
    } else{
        if(now->get_level()==FIX_DEPTH-1){
            //std::cout<<"[HashQuery]:can not find table: "<< tablename<<std::endl;
            return;
        }else{
            int path=hash_value%now->get_capacity();
            getwalk((HashNode*)(now->sons[path]),hash_value,tablename,ret);
        }

    }
}
HashtreeState HashTreeQuery::get(std::string tablename,HashMem* key) {
    //std::cout<<"not get\n";
    std::hash<std::string> hash_string;
    size_t hash_value=hash_string(tablename);
    int path=hash_value%2;
    HashMem* ret= nullptr;
    getwalk((HashNode*)(hashTree->get_root()->sons[path]),hash_value,tablename,&ret);
    if(ret!=NULL){
        memcpy(key,ret,KEYBYTE);
        return HashtreeState ::SUCCESS;
    } else{

    }

}

void putwalk(HashNode* now,size_t hash_value,std::string tablename){
//    if(){
//
//    }
    std::cout<< now->get_level()<< ":"<<now->occupied<<std::endl;
    if(now->data.compare(tablename)==0){
        return;
    }
    if(now->occupied){//next level
        int path=hash_value%now->get_capacity();
        //std::cout<<"path cap:"<< path<< ":"<<now->get_capacity()<<"::"<<now->get_level()<<std::endl;
        putwalk((HashNode*)(now->sons[path]),hash_value,tablename);
    }else{
        if(now->get_level()==FIX_DEPTH-1){
            std::cout<<"[HashQuery]:reach leaf: "<< tablename<<std::endl;
            return;
        }else{
            now->data=tablename;
            now->occupied=true;
            std::cout<<"[HashQuery]:put ok "<<tablename<<std::endl;
            //now->add_user()
        }
    }
}

HashtreeState HashTreeQuery::put(std::string tablename) {
    std::hash<std::string> hash_string;
    auto hash_value=hash_string(tablename);
    int path=hash_value%2;
    std::cout<<"path:"<< path<< ":"<<hashTree->get_root()->sons.size()<<std::endl;
    putwalk((HashNode*)(hashTree->get_root()->sons[path]),hash_value,tablename);
    return HashtreeState ::SUCCESS;
}

HashtreeState HashTreeQuery::add_user(std::string tablename, std::string username) {

    return HashtreeState::FILE_WRITE_ERR;
}

HashtreeState HashTreeQuery::remove_user(std::string tablename, std::string username) {
    return HashtreeState::FILE_WRITE_ERR;
}

HashtreeState HashTreeQuery::reset(std::string tablename) {
    return HashtreeState::FILE_WRITE_ERR;
}

HashTreeQuery::~HashTreeQuery() {

}

HashtreeState HashTreeQuery::flush() {
    HashtreeFile hf=HashtreeFile();
    hf.Hashtree_to_File(file_path,*hashTree);
    return HashtreeState::SUCCESS;
}
