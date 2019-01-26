//
// Created by bob on 19-1-15.
//

#ifndef HASHTREE_HASHTREESTATE_H
#define HASHTREE_HASHTREESTATE_H
enum class HashtreeState : unsigned int{
    SUCCESS=0,
    OUT_OF_CAP=2,
    HTBUFFER_OVER_FLOW=11,

    HT_INCOMPLETE=18,

    FILE_OPEN_ERR=21,
    FILE_WRITE_ERR=22,
    FILE_READ_ERR=23,
    FILE_READ_FORMAT_ERR=24,
    //
};
#endif //HASHTREE_HASHTREESTATE_H
