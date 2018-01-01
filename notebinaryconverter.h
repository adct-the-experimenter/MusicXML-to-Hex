#ifndef NOTEBINARYCONVERTER_H
#define NOTEBINARYCONVERTER_H

#include "note.h"
#include <vector>
#include <cstdint>

class NoteBinaryConverter
{
public:
    NoteBinaryConverter(std::vector <Note> *ptrToNotes,
                        std::vector <uint16_t> *ptrToBinaryNotes);

    ~NoteBinaryConverter();

    //function to run conversion process
    void runNoteToBinaryConversion();


private:
    std::vector <Note> *notesVectorPtr;
    std::vector <uint16_t> *binaryNotesVectorPtr;
};

#endif // NOTEBINARYCONVERTER_H
