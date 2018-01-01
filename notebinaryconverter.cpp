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
            case 4:{ thisNote |= (1<<14); break;} // 100
            case 5:{ thisNote |= ( (1<<13) | (1<<12) ); break;} // 011
            case 6:{ thisNote |= ( (1<<14) | (1<<12) ); break;} // 101
            case 7:{ thisNote |= ( (1<<14) | (1<<13)); break;} // 110
            case 8:{ thisNote |= ( (1<<14) | (1<<13) | (1<<12) ); break;} // 111
            default:{ break;}
        }

        //0000xxx00000000
        //Note Time Signature
        switch(notesVectorPtr->at(i).getTimeSignature())
        {
            case Note::ONE_FOUR:{ thisNote |= (0<<9); break;} // 000
            case Note::TWO_FOUR:{ thisNote |= (1<<9); break;} // 001
            case Note::THREE_FOUR:{ thisNote |= (1<<10); break;} // 010
            case Note::FOUR_FOUR:{ thisNote |= (1<<11); break;} // 100
            case Note::THREE_EIGHT:{ thisNote |= ( (1<<10) | (1<<9) ); break;} // 011
            case Note::SIX_EIGHT:{ thisNote |= ( (1<<11) | (1<<9) ); break;} // 101
            case Note::NINE_EIGHT:{ thisNote |= ( (1<<11) | (1<<10)); break;} // 110
            case Note::TWELVE_EIGHT:{ thisNote |= ( (1<<11) | (1<<10) | (1<<9) ); break;} // 111
            default:{ std::cout << "Undefined! "; break;}
        }

        //0000000xxxxxxxxx
        //Note pitch
        switch(notesVectorPtr->at(i).getPitch())
        {
            case Note::OCTAVE1_B:{thisNote |= (1<<0); break;}// 000000001
            case Note::OCTAVE1_C:{thisNote |= (1<<1); break;}// 000000010
            case Note::OCTAVE1_D:{thisNote |= (1<<2); break;}// 000000100
            case Note::OCTAVE1_E:{thisNote |= (1<<3); break;}// 000001000
            case Note::OCTAVE1_F:{thisNote |= (1<<4); break;}// 000010000
            case Note::OCTAVE1_G:{thisNote |= (1<<5); break;}// 000100000
            case Note::OCTAVE1_A:{thisNote |= (1<<6); break;}// 001000000
            case Note::OCTAVE2_B:{thisNote |= (1<<7) ; break;}// 100000000
            case Note::OCTAVE2_C:{thisNote |= ( (1<<8) | (1<<0) ); break;}// 100000001
            case Note::OCTAVE2_D:{thisNote |= ( (1<<8) | (1<<1) ); break;}// 100000010
            case Note::OCTAVE2_E:{thisNote |= ( (1<<8) | (1<<2) ); break;}// 100000100
            case Note::OCTAVE2_F:{thisNote |= ( (1<<8) | (1<<3) ); break;}// 100001000
            case Note::OCTAVE2_G:{thisNote |= ( (1<<8) | (1<<4) ); break;}// 100010000
            case Note::OCTAVE2_A:{thisNote |= ( (1<<8) | (1<<5) ); break;}// 100100000
            case Note::OCTAVE3_B:{thisNote |= ( (1<<8) | (1<<7) ); break;}// 110000000
            case Note::OCTAVE3_C:{thisNote |= ( (1<<8) | (1<<7) | (1<<0)); break;}// 110000001
            case Note::OCTAVE3_D:{thisNote |= ( (1<<8) | (1<<7) | (1<<1)); break;}// 110000010
            case Note::OCTAVE3_E:{thisNote |= ( (1<<8) | (1<<7) | (1<<2)); break;}// 1100000100
            case Note::OCTAVE3_F:{thisNote |= ( (1<<8) | (1<<7) | (1<<3)); break;}// 110001000
            case Note::OCTAVE3_G:{thisNote |= ( (1<<8) | (1<<7) | (1<<4)); break;}// 110010000
            case Note::OCTAVE3_A:{thisNote |= ( (1<<8) | (1<<7) | (1<<5)); break;}// 110100000
            case Note::OCTAVE4_B:{thisNote |= ( (1<<7) | (1<<6)); break;}// 011000000
            case Note::OCTAVE4_C:{thisNote |= ( (1<<7) | (1<<6) | (1<<0)); break;}// 011000001
            case Note::OCTAVE4_D:{thisNote |= ( (1<<7) | (1<<6) | (1<<1)); break;}// 011000010
            case Note::OCTAVE4_E:{thisNote |= ( (1<<7) | (1<<6) | (1<<2)); break;}// 011000100
            case Note::OCTAVE4_F:{thisNote |= ( (1<<7) | (1<<6) | (1<<3)); break;}// 011001000
            case Note::OCTAVE4_G:{thisNote |= ( (1<<7) | (1<<6) | (1<<4)); break;}// 011010000
            case Note::OCTAVE4_A:{thisNote |= ( (1<<7) | (1<<6) | (1<<5)); break;}// 011100000
            case Note::OCTAVE5_B:{thisNote |= ( (1<<6) | (1<<5) | (1<<0)); break;}// 001100001
            case Note::OCTAVE5_C:{thisNote |= ( (1<<6) | (1<<5) | (1<<1)); break;}// 001100010
            case Note::OCTAVE5_D:{thisNote |= ( (1<<6) | (1<<5) | (1<<2)); break;}// 011000100
            default: { break;}
        }

        //push binary number into notes binary vector
        binaryNotesVectorPtr->push_back(thisNote);
    }

}
