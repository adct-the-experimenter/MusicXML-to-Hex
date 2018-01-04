#include "notebinaryconverter.h"

NoteBinaryConverter::NoteBinaryConverter(std::vector <Note> *ptrToNotes,
                                         std::vector <uint16_t> *ptrToBinaryNotes)
{
    notesVectorPtr = ptrToNotes;
    binaryNotesVectorPtr = ptrToBinaryNotes;
}

NoteBinaryConverter::~NoteBinaryConverter()
{
    notesVectorPtr = nullptr;
    binaryNotesVectorPtr = nullptr;
}

void NoteBinaryConverter::runNoteToBinaryConversion()
{
    for(size_t i=0; i < (*notesVectorPtr).size(); ++i)
    {
        uint16_t thisNote = 0;

        //x000000000000000
        //Note or Rest Bool
        switch ( notesVectorPtr->at(i).getNoteType())
        {
            case Note::NOTE:{thisNote |= (1<<15); break;}
            case Note::REST:{thisNote |= (0<<15); break;}
            default:{break;}
        }

        //0xxx00000000000
        //Note duration
        switch( notesVectorPtr->at(i).getNoteDuration())
        {
            case 1:{ thisNote |= (0<<12); break;} // 000
            case 2:{ thisNote |= (1<<12); break;} // 001
            case 3:{ thisNote |= (1<<13); break;} // 010
            case 4:{ thisNote |= ( (1<<13) | (1<<12) ); break;} // 011
            case 5:{ thisNote |= (1<<14); break;} // 100
            case 6:{ thisNote |= ( (1<<14) | (1<<12) ); break;} // 101
            case 7:{ thisNote |= ( (1<<14) | (1<<13) ); break;} // 110
            case 8:{ thisNote |= ( (1<<14) | (1<<13) | (1<<12) ); break;} // 111
            default:{ std::cout << "Undefined! \n"; break;}
        }

        //0000xxx000000000
        //Note Time Signature
        switch(notesVectorPtr->at(i).getTimeSignature())
        {
            case Note::ONE_FOUR:{ thisNote |= (0<<9); break;} // 000
            case Note::TWO_FOUR:{ thisNote |= (1<<9); break;} // 001
            case Note::THREE_FOUR:{ thisNote |= (1<<10); break;} // 010
            case Note::FOUR_FOUR:{ thisNote |= ( (1<<10) | (1<<9) ); break;} // 011
            case Note::THREE_EIGHT:{ thisNote |=  (1<<11); break;} // 100
            case Note::SIX_EIGHT:{ thisNote |= ( (1<<11) | (1<<9) ); break;} // 101
            case Note::NINE_EIGHT:{ thisNote |= ( (1<<11) | (1<<10)); break;} // 110
            case Note::TWELVE_EIGHT:{ thisNote |= ( (1<<11) | (1<<10) | (1<<9) ); break;} // 111
            default:{ std::cout << "Undefined! "; break;}
        }

        //0000000xxxxxxxxx
        //Note pitch
        switch(notesVectorPtr->at(i).getPitch())
        {
            case Note::OCTAVE1_B:{thisNote |= 0x01; break;}// 000000001
            case Note::OCTAVE1_C:{thisNote |= 0x02; break;}// 000000010
            case Note::OCTAVE1_D:{thisNote |= 0x03; break;}// 000000011
            case Note::OCTAVE1_E:{thisNote |= 0x04; break;}// 000000100
            case Note::OCTAVE1_F:{thisNote |= 0x05; break;}// 000000101
            case Note::OCTAVE1_G:{thisNote |= 0x06; break;}// 000000110
            case Note::OCTAVE1_A:{thisNote |= 0x07; break;}// 000000111
            case Note::OCTAVE2_B:{thisNote |= 0x08 ; break;}// 000001000
            case Note::OCTAVE2_C:{thisNote |= 0x09; break;}// 000001001
            case Note::OCTAVE2_D:{thisNote |= 0x0A; break;}// 000001010
            case Note::OCTAVE2_E:{thisNote |= 0x0B; break;}// 000001011
            case Note::OCTAVE2_F:{thisNote |= 0x0C; break;}// 000001100
            case Note::OCTAVE2_G:{thisNote |= 0x0D; break;}// 000001101
            case Note::OCTAVE2_A:{thisNote |= 0x0E; break;}// 000001110
            case Note::OCTAVE3_B:{thisNote |= 0x0F; break;}// 000001111
            case Note::OCTAVE3_C:{thisNote |= 0x10; break;}// 000010000
            case Note::OCTAVE3_D:{thisNote |= 0x11; break;}// 000010001
            case Note::OCTAVE3_E:{thisNote |= 0x12; break;}// 0000010010
            case Note::OCTAVE3_F:{thisNote |= 0x13; break;}// 000010011
            case Note::OCTAVE3_G:{thisNote |= 0x14; break;}// 000010100
            case Note::OCTAVE3_A:{thisNote |= 0x15; break;}// 000010101
            case Note::OCTAVE4_B:{thisNote |= 0x16; break;}// 000010110
            case Note::OCTAVE4_C:{thisNote |= 0x17; break;}// 000010111
            case Note::OCTAVE4_D:{thisNote |= 0x18; break;}// 000011000
            case Note::OCTAVE4_E:{thisNote |= 0x19; break;}// 000011001
            case Note::OCTAVE4_F:{thisNote |= 0x1A; break;}// 000011010
            case Note::OCTAVE4_G:{thisNote |= 0x1B; break;}// 000011011
            case Note::OCTAVE4_A:{thisNote |= 0x1C; break;}// 000011100
            case Note::OCTAVE5_B:{thisNote |= 0x1D; break;}// 000011101
            case Note::OCTAVE5_C:{thisNote |= 0x1E; break;}// 000011110
            case Note::OCTAVE5_D:{thisNote |= 0x1F; break;}// 000011111
            default: { break;}
        }

        //push binary number into notes binary vector
        binaryNotesVectorPtr->push_back(thisNote);
    }

}
