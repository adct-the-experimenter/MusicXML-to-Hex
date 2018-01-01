#ifndef NOTE_H
#define NOTE_H

#include <iostream>

class Note 
{
	public:
	
		Note();
		~Note();

                enum Instrument{NO_INSTRUMENT,PIANO,ELECTRIC_GUITAR};
                void displayInstrument();

		//function to return duration of note
		int getNoteDuration();

		//note or rest  
                enum NoteType {NO_NOTE_TYPE = 0, NOTE,REST};
		
		//function to return note type 		
		Note::NoteType getNoteType();

		//function to display note type
		void displayNoteType();

		//pitch
		enum Pitch {NO_PITCH = 0,OCTAVE1_B,OCTAVE1_C,OCTAVE1_D,OCTAVE1_E,OCTAVE1_F,OCTAVE1_G,OCTAVE1_A,
					OCTAVE2_B,OCTAVE2_C,OCTAVE2_D,OCTAVE2_E,OCTAVE2_F,OCTAVE2_G,OCTAVE2_A,
					OCTAVE3_B,OCTAVE3_C,OCTAVE3_D,OCTAVE3_E,OCTAVE3_F,OCTAVE3_G,OCTAVE3_A,
					OCTAVE4_B,OCTAVE4_C,OCTAVE4_D,OCTAVE4_E,OCTAVE4_F,OCTAVE4_G,OCTAVE4_A,
					OCTAVE5_B,OCTAVE5_C,OCTAVE5_D};
		
		//function to return pitch type
		Note::Pitch getPitch();		
		
		char getPitchStep();
		int getPitchOctave();

		void displayPitch();

		void displayPitchStepOctave();

		//staff number
		enum Staff {STAFF_NONE = 0, STAFF_1, STAFF_2};

		void displayStaff();
		
		//enum Clef {ALTO = 0, BASS, TENOR, TREBLE};

		//time signature
		enum TimeSignature { NO_TIME_SIGN = 0, ONE_FOUR,TWO_FOUR,THREE_FOUR,FOUR_FOUR,
							THREE_EIGHT,SIX_EIGHT,NINE_EIGHT,TWELVE_EIGHT};
		
		//function to return time signature
		Note::TimeSignature getTimeSignature();

		void displayTimeSignature();
	
		//measure number

		//function to return the measure number that note is in
		int getMeasureNumber();


		friend class SAX2HandlerMusicXML;

	private:
                //Instrument
                Note::Instrument instrument;
                void setInstrument(Note::Instrument thisInstrument);
                Note::Instrument getInstrument();

                //how long note lasts
		int duration; 
		//function to set duration
		void setNoteDuration(int time);

		//time signature
		Note::TimeSignature timeSignature;
		//function to set time signature
		void setTimeSignature(Note::TimeSignature timeSign);
		void setTimeSignatureFromBeat(int beat, int beatType);

                void setTimeSignatureFromBeatPrivate();
                int beat;
                void setBeat(int thisBeat);
                int getBeat();

                int beatType;
                int getBeatType();

                void setBeatType(int thisBeatType);

		
		//musical note or rest		
		Note::NoteType noteType;
		//function to set note type
		void setNoteType(Note::NoteType nType);

		//pitch of note
		Note::Pitch pitch;
		//function to set pitch
		void setPitch(Note::Pitch thisPitch);
		//function to set pitch from step and octave
		void setPitchFromOctaveStep();
		
		// octave for pitch
		int pitchOctave;
		void setPitchOctave(int thisOctave);
		
		// step for pitch
		char pitchStep;
		void setPitchStep(char thisStep);
		
		void resetNotePitchStepOctave();		

		//measure number
		int measureNumber;
		void setMeasureNumber(int thisNumber);

		//staff
                bool hasMultipleStaff;
                void setMultipleStaffBool(bool state);
                bool getMultipleStaffBool();

		Note::Staff staff;
		void setStaff(Note::Staff thisStaff);
		void setStaffFromInt(int thisStaff);
		Note::Staff getStaff();

                //chord
                bool isChord;
                void setChordStatus(bool state);
                bool getChordStatus();


		//function to reset note
		void resetNote();
};

#endif
