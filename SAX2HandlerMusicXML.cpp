#include "SAX2HandlerMusicXML.hpp"
#include <iostream>

SAX2HandlerMusicXML::SAX2HandlerMusicXML()
{
	notesVectorPtr = nullptr;

        currentNote = &thisNote;

        SAX2HandlerMusicXML::pushElement(SAX2HandlerMusicXML::NO_ELEMENT);
}

SAX2HandlerMusicXML::~SAX2HandlerMusicXML()
{
    notesVectorPtr = nullptr;

    currentNote = nullptr;
}

void SAX2HandlerMusicXML::addPointerToNotes(std::vector<Note> &notesVec){notesVectorPtr = &notesVec;}

void SAX2HandlerMusicXML::freePointerToNotes(){notesVectorPtr = nullptr;}

void SAX2HandlerMusicXML::pushElement(SAX2HandlerMusicXML::Element element){ /*elementStack.push(element);*/ currentElement = element;}

void SAX2HandlerMusicXML::popCurrentElement(){ /*elementStack.pop();*/ currentElement = SAX2HandlerMusicXML::NO_ELEMENT; }

SAX2HandlerMusicXML::Element SAX2HandlerMusicXML::getCurrentElement(){return /*elementStack.top();*/ currentElement;}

/* *** Instrument *** */
void SAX2HandlerMusicXML::setNoteInstrument(Note::Instrument thisInstrument){noteInstrument = thisInstrument;}

Note::Instrument SAX2HandlerMusicXML::getNoteInstrument(){return noteInstrument;}

void SAX2HandlerMusicXML::runPartNameStartElementEvent(char *localname_char)
{
    //if element is part-name
    if( strcmp(localname_char,"part-name") == 0){SAX2HandlerMusicXML::pushElement(SAX2HandlerMusicXML::PART_NAME);}
}

void SAX2HandlerMusicXML::runPartNameCharEvent(char* char_local)
{
        if(strcmp(char_local,"Piano") == 0){ SAX2HandlerMusicXML::setNoteInstrument(Note::PIANO);}
        else if(strcmp(char_local,"Electric Guitar") == 0){ SAX2HandlerMusicXML::setNoteInstrument(Note::ELECTRIC_GUITAR);}

}

void SAX2HandlerMusicXML::runPartNameEndElementEvent(char *localname_char)
{
    //if element is part name
    if( strcmp(localname_char,"part-name") == 0
        && SAX2HandlerMusicXML::getCurrentElement() == SAX2HandlerMusicXML::PART_NAME)
    {
        SAX2HandlerMusicXML::popCurrentElement();
    }
}

/* *** Note Element processes *** */

void SAX2HandlerMusicXML::setNoteState( SAX2HandlerMusicXML::NoteState state){ noteState = state;}
SAX2HandlerMusicXML::NoteState SAX2HandlerMusicXML::getNoteState(){ return noteState;}

void SAX2HandlerMusicXML::runNoteStartElementEvent(char* localname_char,const Attributes& attributes)
{
	//if element is note
	if( strcmp(localname_char,"note") == 0)
	{ 
			// *** NOTE *** skip extra note element by only acting on 
			//every other note element. Done with condition that noteElementCounter is odd number. *** NOTE ***
	
                        //std::cout << "Found element note!" << "Note " << SAX2HandlerMusicXML::getNoteElementCounter() << std::endl;

                        currentNote->setInstrument(SAX2HandlerMusicXML::getNoteInstrument());
			//if no attributes
			if(attributes.getLength() == 0)
			{
				//std::cout << "No attributes. \n";
				//if note type is not defined yet and noteElementCounter is odd

                                SAX2HandlerMusicXML::setNoteState(SAX2HandlerMusicXML::REST_STATE);
                                currentNote->setNoteType(Note::REST);
			}
			else
			{
				//std::cout << "Attributes! Quantity:" << attributes.getLength() << std::endl;
				//if note type is not defined and noteElementCounter is odd				

                            SAX2HandlerMusicXML::setNoteState(SAX2HandlerMusicXML::NOTE_STATE);
                            currentNote->setNoteType(Note::NOTE);
                        }
	}
	
}

void SAX2HandlerMusicXML::runNoteEndElementEvent(char* localname_char)
{
	//if element is note
        if( strcmp(localname_char,"note") == 0)
        {
            //assign measure number to Note object
            currentNote->setMeasureNumber(SAX2HandlerMusicXML::getMeasureNumberCount());

            if(currentNote->getTimeSignature() == Note::NO_TIME_SIGN)
            {
                currentNote->setBeat(SAX2HandlerMusicXML::getBeat());
                currentNote->setBeatType(SAX2HandlerMusicXML::getBeatType());
                currentNote->setTimeSignatureFromBeatPrivate();
            }

            SAX2HandlerMusicXML::checkFinalNote();
            SAX2HandlerMusicXML::setNoteState(SAX2HandlerMusicXML::NO_STATE);
        }
}

void SAX2HandlerMusicXML::runBackUpStartElementEvent(char* localname_char)
{
	//if element is backup
	if( strcmp(localname_char,"backup") == 0){ SAX2HandlerMusicXML::setNoteState(SAX2HandlerMusicXML::BACKUP_STATE);}
}

void SAX2HandlerMusicXML::runBackUpEndElementEvent(char* localname_char)
{
	//if element is backup
	if( strcmp(localname_char,"backup") == 0){ SAX2HandlerMusicXML::setNoteState(SAX2HandlerMusicXML::NO_STATE);}
}

/* *************** Time Signature ********************** */


//Beats and Beat type element processes

void SAX2HandlerMusicXML::runBeatsStartElementEvent(char* localname_char)
{
	//if element is beats
        if( strcmp(localname_char,"beats") == 0){ SAX2HandlerMusicXML::pushElement(SAX2HandlerMusicXML::BEATS);}
}

void SAX2HandlerMusicXML::runBeatsEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"beats") == 0
                && SAX2HandlerMusicXML::getCurrentElement() == SAX2HandlerMusicXML::BEATS)
        {
            currentNote->setBeat(SAX2HandlerMusicXML::getBeat());
            SAX2HandlerMusicXML::popCurrentElement();
        }
}

void SAX2HandlerMusicXML::setBeat(int thisBeat){ beat = thisBeat;}

int SAX2HandlerMusicXML::getBeat(){return beat;}

void SAX2HandlerMusicXML::runBeatTypeStartElementEvent(char* localname_char)
{
	//if element is beat type
        if( strcmp(localname_char,"beat-type") == 0)
        { SAX2HandlerMusicXML::pushElement(SAX2HandlerMusicXML::BEAT_TYPE);}
}

void SAX2HandlerMusicXML::runBeatTypeEndElementEvent(char* localname_char)
{
	//if element is beat type
        if( strcmp(localname_char,"beat-type") == 0
                && SAX2HandlerMusicXML::getCurrentElement() == SAX2HandlerMusicXML::BEAT_TYPE)
        {
                currentNote->setBeatType( SAX2HandlerMusicXML::getBeatType() );
                currentNote->setTimeSignatureFromBeatPrivate();
                SAX2HandlerMusicXML::popCurrentElement();
        }
}

void SAX2HandlerMusicXML::setBeatType(int thisBeatType){ beatType = thisBeatType; }

int SAX2HandlerMusicXML::getBeatType(){return beatType;}

/* *************** Measure Number ****************** */

void SAX2HandlerMusicXML::incrementMeasureNumberCounter() { measureNumberCounter += 1;}

void SAX2HandlerMusicXML::setMeasureNumberCount(int number){ measureNumberCounter = number;}
int SAX2HandlerMusicXML::getMeasureNumberCount(){return measureNumberCounter;}

void SAX2HandlerMusicXML::resetMeasureNumberCounter(){ measureNumberCounter = 0;}

void SAX2HandlerMusicXML::runMeasureStartElementEvent(char* localname_char)
{
	if( strcmp(localname_char,"measure") == 0)
        {
                SAX2HandlerMusicXML::incrementMeasureNumberCounter();
                SAX2HandlerMusicXML::pushElement(SAX2HandlerMusicXML::MEASURE);
	}
}

void SAX2HandlerMusicXML::runMeasureEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"measure") == 0
                && SAX2HandlerMusicXML::getCurrentElement() == SAX2HandlerMusicXML::MEASURE)
        {
            SAX2HandlerMusicXML::popCurrentElement();
        }
}



/*  ******************* Duration ******************** */

void SAX2HandlerMusicXML::runDurationStartElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"duration") == 0)
        {
            if(currentNote->getNoteType() == Note::REST
                    || currentNote->getNoteType() == Note::NOTE)
            {
                SAX2HandlerMusicXML::pushElement(SAX2HandlerMusicXML::DURATION);
            }
        }
}

void SAX2HandlerMusicXML::runDurationEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"duration") == 0
                && SAX2HandlerMusicXML::getCurrentElement() == SAX2HandlerMusicXML::DURATION )
        {
            //assign duration to current note
            currentNote->setNoteDuration(SAX2HandlerMusicXML::getDuration());
            SAX2HandlerMusicXML::popCurrentElement();
        }
}

void SAX2HandlerMusicXML::setDuration(int thisDuration){ duration = thisDuration;}

int SAX2HandlerMusicXML::getDuration(){return duration;}




/*  ************************* Pitch ************************ */

void SAX2HandlerMusicXML::runStepStartElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"step") == 0)
        {SAX2HandlerMusicXML::pushElement(SAX2HandlerMusicXML::STEP);}
}

void SAX2HandlerMusicXML::runStepEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"step") == 0
                && SAX2HandlerMusicXML::getCurrentElement() == SAX2HandlerMusicXML::STEP)
        {
            currentNote->setPitchStep(SAX2HandlerMusicXML::getStep());
            SAX2HandlerMusicXML::popCurrentElement();
        }
}

void SAX2HandlerMusicXML::setStep(char thisStep){step = thisStep;}
char SAX2HandlerMusicXML::getStep(){return step;}

void SAX2HandlerMusicXML::runOctaveStartElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"octave") == 0){SAX2HandlerMusicXML::pushElement(SAX2HandlerMusicXML::OCTAVE);}
}

void SAX2HandlerMusicXML::runOctaveEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"octave") == 0
                && SAX2HandlerMusicXML::getCurrentElement() == SAX2HandlerMusicXML::OCTAVE)
        {
            currentNote->setPitchOctave(SAX2HandlerMusicXML::getOctave());
            //setup pitch from octave step members assigned
            currentNote->setPitchFromOctaveStep();
            SAX2HandlerMusicXML::popCurrentElement();
        }
}

void SAX2HandlerMusicXML::setOctave(int thisOctave){ octave = thisOctave;}
int SAX2HandlerMusicXML::getOctave(){return octave;}

/* ********* Staff ************ */

void SAX2HandlerMusicXML::runStaffStartElementEvent(char* localname_char)
{
	if( strcmp(localname_char,"staff") == 0)
        {
               if(!currentNote->getMultipleStaffBool()){currentNote->setMultipleStaffBool(true);}
               SAX2HandlerMusicXML::pushElement(SAX2HandlerMusicXML::STAFF);
        }
}

void SAX2HandlerMusicXML::runStaffEndElementEvent(char* localname_char)
{
        if( strcmp(localname_char,"staff") == 0
                && SAX2HandlerMusicXML::getCurrentElement() == SAX2HandlerMusicXML::STAFF)
        {
            //assign staff to note
            currentNote->setStaffFromInt(SAX2HandlerMusicXML::getNoteStaff());
            SAX2HandlerMusicXML::popCurrentElement();
        }
}

void SAX2HandlerMusicXML::setNoteStaff(int thisStaff){ noteStaff = thisStaff;}
int SAX2HandlerMusicXML::getNoteStaff(){return noteStaff;}


/* ********* Chord ********** */

void SAX2HandlerMusicXML::runChordStartElementEvent(char* localname_char)
{
        if( strcmp(localname_char, "chord") == 0 ){currentNote->setChordStatus(true);}
}


void SAX2HandlerMusicXML::checkFinalNote()
{
		//if current note is note type NOTE
                if(currentNote->getNoteType() == Note::NOTE)
		{
			//if current note has time signature
			// is in a measure
			// has duration
			// and has pitch
                        if( currentNote->getTimeSignature() != Note::NO_TIME_SIGN
                                && currentNote->getMeasureNumber() != 0
                                && currentNote->getNoteDuration() != 0
                                && currentNote->getPitch() != Note::NO_PITCH
                                 )
                        {
                                if(currentNote->getMultipleStaffBool()
                                           && currentNote->getStaff() != Note::STAFF_NONE)
                                {
                                    //add current note to element in notes vector
                                    notesVectorPtr->push_back(*currentNote);
                                    //reset note
                                    currentNote->resetNote();
                                }
                                else if(!currentNote->getMultipleStaffBool())
                                {
                                    //add current note to element in notes vector
                                    notesVectorPtr->push_back(*currentNote);
                                    //reset note
                                    currentNote->resetNote();
                                }

                        }
		}
		//else if current note note type REST
		else if(currentNote->getNoteType() == Note::REST)
		{
			//if current note has time signature and is in a measure
                        if( currentNote->getTimeSignature() != Note::NO_TIME_SIGN
                                && currentNote->getMeasureNumber() != 0
                                && currentNote->getNoteDuration() != 0
                                 )
                        {
                            if(currentNote->getMultipleStaffBool()
                                       && currentNote->getStaff() != Note::STAFF_NONE)
                            {
                                //add current note to element in notes vector
                                notesVectorPtr->push_back(*currentNote);
                                //reset note
                                currentNote->resetNote();
                            }
                            else if(!currentNote->getMultipleStaffBool())
                            {
                                //add current note to element in notes vector
                                notesVectorPtr->push_back(*currentNote);
                                //reset note
                                currentNote->resetNote();
                            }
                        }
		}

}


void SAX2HandlerMusicXML::startElementRoutine(char* localname_char, const Attributes& attributes)
{
        //function to run if part name element found
        SAX2HandlerMusicXML::runPartNameStartElementEvent(localname_char);

	//function to run if measure number element found
	SAX2HandlerMusicXML::runMeasureStartElementEvent(localname_char);
		
        //functions to run if beats and beat-type element found
	SAX2HandlerMusicXML::runBeatsStartElementEvent(localname_char);
	SAX2HandlerMusicXML::runBeatTypeStartElementEvent(localname_char);

	//function to run if note element found
	SAX2HandlerMusicXML::runNoteStartElementEvent(localname_char,attributes);

	//function to run if backup element found
	SAX2HandlerMusicXML::runBackUpStartElementEvent(localname_char);

	//function to run if chord element found
	SAX2HandlerMusicXML::runChordStartElementEvent(localname_char);

	//function to run if step element found
	SAX2HandlerMusicXML::runStepStartElementEvent(localname_char);

	//function to run if octave element found
	SAX2HandlerMusicXML::runOctaveStartElementEvent(localname_char);

	//function to run if duration element found
	SAX2HandlerMusicXML::runDurationStartElementEvent(localname_char);

	//function to run if staff element found
	SAX2HandlerMusicXML::runStaffStartElementEvent(localname_char);
}

void SAX2HandlerMusicXML::charactersRoutine(char* chars_local)
{
        //std::stringstream charBuffer;

        switch(SAX2HandlerMusicXML::getCurrentElement())
        {
            case SAX2HandlerMusicXML::PART_NAME:
            {
                SAX2HandlerMusicXML::runPartNameCharEvent(chars_local);
            }

            case SAX2HandlerMusicXML::BEATS :
            {
               // charBuffer << chars_local;
                //int beats;
                //charBuffer >> beats;
                SAX2HandlerMusicXML::setBeat( atoi(chars_local) );
                break;
            }
            case SAX2HandlerMusicXML::BEAT_TYPE :
            {
                //charBuffer << chars_local;
                //int beatType;
                //charBuffer >> beatType;
                SAX2HandlerMusicXML::setBeatType( atoi(chars_local) );
                break;
            }
            case SAX2HandlerMusicXML::DURATION :
            {
                //charBuffer << chars_local;
                //int duration;
                //charBuffer >> duration;
                SAX2HandlerMusicXML::setDuration( atoi(chars_local) );
                break;
            }
            case SAX2HandlerMusicXML::STEP :
            {
                //charBuffer << chars_local;
                //char step;
                //charBuffer >> step;
                SAX2HandlerMusicXML::setStep(*chars_local);
                break;
            }
            case SAX2HandlerMusicXML::OCTAVE :
            {

                //charBuffer << chars_local;
                //int octave;
                //charBuffer >> octave;
                SAX2HandlerMusicXML::setOctave( atoi(chars_local) );
                break;
            }
            case SAX2HandlerMusicXML::STAFF :
            {
              //  charBuffer << chars_local;
            //    int staff;
          //      charBuffer >> staff;
                SAX2HandlerMusicXML::setNoteStaff(atoi(chars_local));
                break;
            }
        }
}

void SAX2HandlerMusicXML::endElementRoutine(char* localname_char)
{
        //function to run if part name element found
        SAX2HandlerMusicXML::runPartNameEndElementEvent(localname_char);

	//function to run if measure element found
	SAX2HandlerMusicXML::runMeasureEndElementEvent(localname_char);

	//function to run if note element found
	SAX2HandlerMusicXML::runNoteEndElementEvent(localname_char);

	//function to run if backup element found
	SAX2HandlerMusicXML::runBackUpEndElementEvent(localname_char);

	//functions to run if beats and beat-type element found 
	SAX2HandlerMusicXML::runBeatsEndElementEvent(localname_char);
	SAX2HandlerMusicXML::runBeatTypeEndElementEvent(localname_char);
	
	//function to run if step element found
	SAX2HandlerMusicXML::runStepEndElementEvent(localname_char);

	//function to run if octave element found
	SAX2HandlerMusicXML::runOctaveEndElementEvent(localname_char);

	//function to run if duration element found
	SAX2HandlerMusicXML::runDurationEndElementEvent(localname_char);

	//function to run if staff element found
	SAX2HandlerMusicXML::runStaffEndElementEvent(localname_char);
}

//SAX2 Content Handler functions

void SAX2HandlerMusicXML::startElement(const   XMLCh* const    uri,
                            const   XMLCh* const    localname,
                            const   XMLCh* const    qname,
                            const   Attributes&     attrs)
{
	//save localname to local char var.
    char* message_localname = XMLString::transcode(localname);
	
	//run start element processes
	SAX2HandlerMusicXML::startElementRoutine(message_localname,attrs);

	//release local char variable for localname 		
    XMLString::release(&message_localname);
}


void SAX2HandlerMusicXML::fatalError(const SAXParseException& exception)
{
    char* message = XMLString::transcode(exception.getMessage());
    std::cout << "Fatal Error: " << message
         << " at line: " << exception.getLineNumber()
         << std::endl;
}

void SAX2HandlerMusicXML::characters
(
        const   XMLCh* const    chars
        , const XMLSize_t       length
) 
{
    //save chars to local char var.
    char* message_chars = XMLString::transcode(chars);
	
    SAX2HandlerMusicXML::charactersRoutine(message_chars);

    //release local char var containing chars
    XMLString::release(&message_chars);
}

void SAX2HandlerMusicXML::endDocument () {}

void SAX2HandlerMusicXML::endElement
	(
		const XMLCh* const uri,
		const XMLCh* const localname,
		const XMLCh* const qname
	) 
{
	//save localname to local char var.
	char* message_localname = XMLString::transcode(localname);

	SAX2HandlerMusicXML::endElementRoutine(message_localname);

        XMLString::release(&message_localname);
}

void SAX2HandlerMusicXML::ignorableWhitespace
    (
        const   XMLCh* const    chars
        , const XMLSize_t       length
    ) {}

void SAX2HandlerMusicXML::processingInstruction
    (
        const   XMLCh* const    target
        , const XMLCh* const    data
    ) {}

void SAX2HandlerMusicXML::setDocumentLocator(const Locator* const locator) {}

void SAX2HandlerMusicXML::startDocument() {}

	
void SAX2HandlerMusicXML::startPrefixMapping
	(
		const	XMLCh* const	prefix,
		const	XMLCh* const	uri
	){}

void SAX2HandlerMusicXML::endPrefixMapping
	(
		const	XMLCh* const	prefix
	){}

void SAX2HandlerMusicXML::skippedEntity
(
	const	XMLCh* const	name
){}
