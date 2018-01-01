#include "note.h"

Note::Note()
{
        Note::setInstrument(Note::NO_INSTRUMENT);
	Note::resetNote();
}

Note::~Note()
{
        Note::setInstrument(Note::NO_INSTRUMENT);
	Note::resetNote();
}

void Note::resetNote()
{
	Note::setNoteDuration(0);
	Note::setNoteType(Note::NO_NOTE_TYPE);
	Note::setTimeSignature(Note::NO_TIME_SIGN);
        Note::setBeat(0);
        Note::setBeatType(0);
	Note::setMeasureNumber(0);
	
	Note::resetNotePitchStepOctave();
	Note::setStaff(Note::STAFF_NONE);
        Note::setChordStatus(false);
}
//Instrument

void Note::setInstrument(Note::Instrument thisInstrument)
{
    instrument = thisInstrument;

    switch(thisInstrument)
    {
        case Note::NO_INSTRUMENT:{ Note::setMultipleStaffBool(false); break;}
        case Note::PIANO:{ Note::setMultipleStaffBool(true); break;}
        case Note::ELECTRIC_GUITAR:{ Note::setMultipleStaffBool(false); break;}
    }
}

Note::Instrument Note::getInstrument(){return instrument;}

void Note::displayInstrument()
{
    switch(Note::getInstrument())
    {
        case Note::ELECTRIC_GUITAR:{std::cout << "Electric Guitar "; break; }
        case Note::PIANO:{std::cout << "Piano "; break;}
        default:{ std::cout << "Instrument not listed"; break;}
    }
}

//measure number

void Note::setMeasureNumber(int thisNumber){measureNumber = thisNumber;}

int Note::getMeasureNumber(){return measureNumber;}

//duration

void Note::setNoteDuration(int time){duration = time;}

int Note::getNoteDuration(){return duration;}

//Time Signature

void Note::setTimeSignature(Note::TimeSignature timeSign){timeSignature = timeSign;}

void Note::setTimeSignatureFromBeat(int beat, int beatType)
{
	if(beatType == 4)
	{
		switch(beat)
		{
			case 1: { Note::setTimeSignature( Note::ONE_FOUR ); break;}
			case 2: { Note::setTimeSignature( Note::TWO_FOUR ); break;}	
			case 3: { Note::setTimeSignature( Note::THREE_FOUR ); break;}
			case 4: { Note::setTimeSignature( Note::FOUR_FOUR ); break;}
		}
	} 
	else if( beatType == 8)
	{
		switch(beat)
		{
			case 3:{Note::setTimeSignature( Note::THREE_EIGHT ); break;}
			case 6:{Note::setTimeSignature( Note::SIX_EIGHT ); break;}
			case 9:{Note::setTimeSignature( Note::NINE_EIGHT ); break;}
			case 12:{Note::setTimeSignature( Note::TWELVE_EIGHT ); break;}
		}
	}
}

void Note::setTimeSignatureFromBeatPrivate()
{
    if(Note::getBeatType() == 4)
    {
            switch(Note::getBeat())
            {
                    case 1: { Note::setTimeSignature( Note::ONE_FOUR ); break;}
                    case 2: { Note::setTimeSignature( Note::TWO_FOUR ); break;}
                    case 3: { Note::setTimeSignature( Note::THREE_FOUR ); break;}
                    case 4: { Note::setTimeSignature( Note::FOUR_FOUR ); break;}
            }
    }
    else if( Note::getBeatType() == 8)
    {
            switch(Note::getBeat())
            {
                    case 3:{Note::setTimeSignature( Note::THREE_EIGHT ); break;}
                    case 6:{Note::setTimeSignature( Note::SIX_EIGHT ); break;}
                    case 9:{Note::setTimeSignature( Note::NINE_EIGHT ); break;}
                    case 12:{Note::setTimeSignature( Note::TWELVE_EIGHT ); break;}
            }
    }
}

void Note::setBeat(int thisBeat){ beat = thisBeat;}
int Note::getBeat(){ return beat;}

void Note::setBeatType(int thisBeatType){ beatType = thisBeatType;}
int Note::getBeatType(){return beatType;}

Note::TimeSignature Note::getTimeSignature()
{
	return timeSignature;
}

void Note::displayTimeSignature()
{
	switch(Note::getTimeSignature())
	{
		case Note::ONE_FOUR:{ std::cout << "Time Signature: 1/4 "; break;}
		case Note::TWO_FOUR:{ std::cout << "Time Signature: 2/4 "; break;}
		case Note::THREE_FOUR:{ std::cout << "Time Signature: 3/4 "; break;}
		case Note::FOUR_FOUR:{ std::cout << "Time Signature: 4/4 "; break;}
		case Note::THREE_EIGHT:{ std::cout << "Time Signature: 3/8 "; break;}
		case Note::SIX_EIGHT:{ std::cout << "Time Signature: 6/8 "; break;}
		case Note::NINE_EIGHT:{ std::cout << "Time Signature: 9/8 "; break;}
		case Note::TWELVE_EIGHT:{ std::cout << "Time Signature: 12/8 "; break;}
		default:{ std::cout << "Undefined! ";break;}
	}
}

//Note Type

void Note::setNoteType(Note::NoteType nType){noteType = nType;}

Note::NoteType Note::getNoteType(){return noteType;}

void Note::displayNoteType()
{
	if(Note::getNoteType() == Note::REST){std::cout << "Rest. ";}
        else if(Note::getNoteType() == Note::NOTE && !Note::getChordStatus()){ std::cout << "Note. ";}
        else if(Note::getNoteType() == Note::NOTE && Note::getChordStatus()){std::cout << "Note Chord. ";}
}

//Pitch

void Note::setPitch(Note::Pitch thisPitch){pitch = thisPitch;}

void Note::setPitchStep(char thisStep){pitchStep = thisStep;}
char Note::getPitchStep(){return pitchStep;}

void Note::setPitchOctave(int thisOctave){pitchOctave = thisOctave;}
int Note::getPitchOctave(){return pitchOctave;}

void Note::setPitchFromOctaveStep()
{
	switch(Note::getPitchOctave())
	{
		case 1:
		{
			switch(Note::getPitchStep())
			{
				case 'B':{ Note::setPitch( Note::OCTAVE1_B); break;}
				case 'C':{ Note::setPitch( Note::OCTAVE1_C); break;}
				case 'D':{ Note::setPitch( Note::OCTAVE1_D); break;}
				case 'E':{ Note::setPitch( Note::OCTAVE1_E); break;}
				case 'F':{ Note::setPitch( Note::OCTAVE1_F); break;}
				case 'G':{ Note::setPitch( Note::OCTAVE1_G); break;}
				case 'A':{ Note::setPitch( Note::OCTAVE1_A); break;}
			} 
			break;
		}
		case 2:
		{ 
			switch(Note::getPitchStep())
			{
				case 'B':{ Note::setPitch( Note::OCTAVE2_B); break;}
				case 'C':{ Note::setPitch( Note::OCTAVE2_C); break;}
				case 'D':{ Note::setPitch( Note::OCTAVE2_D); break;}
				case 'E':{ Note::setPitch( Note::OCTAVE2_E); break;}
				case 'F':{ Note::setPitch( Note::OCTAVE2_F); break;}
				case 'G':{ Note::setPitch( Note::OCTAVE2_G); break;}
				case 'A':{ Note::setPitch( Note::OCTAVE2_A); break;}
			}
			break;
		}
		case 3:
		{ 
			switch(Note::getPitchStep())
			{
				case 'B':{ Note::setPitch( Note::OCTAVE3_B); break;}
				case 'C':{ Note::setPitch( Note::OCTAVE3_C); break;}
				case 'D':{ Note::setPitch( Note::OCTAVE3_D); break;}
				case 'E':{ Note::setPitch( Note::OCTAVE3_E); break;}
				case 'F':{ Note::setPitch( Note::OCTAVE3_F); break;}
				case 'G':{ Note::setPitch( Note::OCTAVE3_G); break;}
				case 'A':{ Note::setPitch( Note::OCTAVE3_A); break;}
			}
			break;
		}
		case 4:
		{
 			switch(Note::getPitchStep())
			{
				case 'B':{ Note::setPitch( Note::OCTAVE4_B); break;}
				case 'C':{ Note::setPitch( Note::OCTAVE4_C); break;}
				case 'D':{ Note::setPitch( Note::OCTAVE4_D); break;}
				case 'E':{ Note::setPitch( Note::OCTAVE4_E); break;}
				case 'F':{ Note::setPitch( Note::OCTAVE4_F); break;}
				case 'G':{ Note::setPitch( Note::OCTAVE4_G); break;}
				case 'A':{ Note::setPitch( Note::OCTAVE4_A); break;}
			}
			break;
		}
		case 5:
		{ 
			switch(Note::getPitchStep())
			{
				case 'B':{ Note::setPitch( Note::OCTAVE5_B); break;}
				case 'C':{ Note::setPitch( Note::OCTAVE5_C); break;}
				case 'D':{ Note::setPitch( Note::OCTAVE5_D); break;}
			}
			break;
		}

	}
}

Note::Pitch Note::getPitch()
{
	return pitch;
}

void Note::displayPitch()
{
		switch(Note::getPitch())
		{
			case OCTAVE1_B:{std::cout << "Pitch: Octave 1 Step B"; break;}
			case OCTAVE1_C:{std::cout << "Pitch: Octave 1 Step C"; break;}
			case OCTAVE1_D:{std::cout << "Pitch: Octave 1 Step D"; break;}
			case OCTAVE1_E:{std::cout << "Pitch: Octave 1 Step E"; break;}
			case OCTAVE1_F:{std::cout << "Pitch: Octave 1 Step F"; break;}
			case OCTAVE1_G:{std::cout << "Pitch: Octave 1 Step G"; break;}
			case OCTAVE1_A:{std::cout << "Pitch: Octave 1 Step A"; break;}
			case OCTAVE2_B:{std::cout << "Pitch: Octave 2 Step B"; break;}
			case OCTAVE2_C:{std::cout << "Pitch: Octave 2 Step C"; break;}
			case OCTAVE2_D:{std::cout << "Pitch: Octave 2 Step D"; break;}
			case OCTAVE2_E:{std::cout << "Pitch: Octave 2 Step E"; break;}
			case OCTAVE2_F:{std::cout << "Pitch: Octave 2 Step F"; break;}
			case OCTAVE2_G:{std::cout << "Pitch: Octave 2 Step G"; break;}
			case OCTAVE2_A:{std::cout << "Pitch: Octave 2 Step A"; break;}
			case OCTAVE3_B:{std::cout << "Pitch: Octave 3 Step B"; break;}
			case OCTAVE3_C:{std::cout << "Pitch: Octave 3 Step C"; break;}
			case OCTAVE3_D:{std::cout << "Pitch: Octave 3 Step D"; break;}
			case OCTAVE3_E:{std::cout << "Pitch: Octave 3 Step E"; break;}
			case OCTAVE3_F:{std::cout << "Pitch: Octave 3 Step F"; break;}
			case OCTAVE3_G:{std::cout << "Pitch: Octave 3 Step G"; break;}
			case OCTAVE3_A:{std::cout << "Pitch: Octave 3 Step A"; break;}
			case OCTAVE4_B:{std::cout << "Pitch: Octave 3 Step B"; break;}
			case OCTAVE4_C:{std::cout << "Pitch: Octave 4 Step C"; break;}
			case OCTAVE4_D:{std::cout << "Pitch: Octave 4 Step D"; break;}
			case OCTAVE4_E:{std::cout << "Pitch: Octave 4 Step E"; break;}
			case OCTAVE4_F:{std::cout << "Pitch: Octave 4 Step F"; break;}
			case OCTAVE4_G:{std::cout << "Pitch: Octave 4 Step G"; break;}
			case OCTAVE4_A:{std::cout << "Pitch: Octave 4 Step A"; break;}
			case OCTAVE5_B:{std::cout << "Pitch: Octave 5 Step B"; break;}
			case OCTAVE5_C:{std::cout << "Pitch: Octave 5 Step C"; break;}
			case OCTAVE5_D:{std::cout << "Pitch: Octave 5 Step D"; break;}
                        default: { break;}
		}
}

void Note::displayPitchStepOctave()
{
	std::cout << "Octave: " << Note::getPitchOctave() << std::endl;
	std::cout << "Step: " << Note::getPitchStep() << std::endl; 
}

void Note::resetNotePitchStepOctave()
{ 
	Note::setPitch(Note::NO_PITCH);
	Note::setPitchOctave(0);
	Note::setPitchStep(0);
}

// *** Staff ***

void Note::setMultipleStaffBool(bool state){hasMultipleStaff = state;}

bool Note::getMultipleStaffBool(){return hasMultipleStaff;}

void Note::setStaff(Note::Staff thisStaff){ staff = thisStaff;}

void Note::setStaffFromInt(int thisStaff)
{
    switch(thisStaff)
    {
            case 1:{Note::setStaff(Note::STAFF_1); break;}
            case 2:{Note::setStaff(Note::STAFF_2); break;}
            default: {Note::setStaff(Note::STAFF_NONE); break;}
    }
}
Note::Staff Note::getStaff(){ return staff;}

void Note::displayStaff()
{	
    if(Note::getMultipleStaffBool())
    {
	switch(Note::getStaff())
	{
		case Note::STAFF_NONE: { std::cout << " \n No Staff! "; break;}
		case Note::STAFF_1:{ std::cout << "\n Staff 1"; break;}
		case Note::STAFF_2:{ std::cout << "\n Staff 2"; break;}
        }
    }
}

//chord

void Note::setChordStatus(bool state){isChord = state;}
bool Note::getChordStatus(){return isChord;}


