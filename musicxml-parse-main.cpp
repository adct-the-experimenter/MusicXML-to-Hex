#include "SAX2HandlerMusicXML.hpp" //for custom implementation of content handler. Used to read elements in Musix XML file.  
#include "MusicXMLEntityResolver.hpp" //for custom implementation of entity resolver. Used to point to local copies of URL files in MusicXML Schema.
#include <xercesc/sax2/SAX2XMLReader.hpp> //for xml reader use
#include <xercesc/sax2/XMLReaderFactory.hpp> //for creating xml reader
#include <xercesc/sax2/DefaultHandler.hpp> //for content/error handler
#include <xercesc/util/XMLString.hpp> //for xml strings

#include <iostream>

#include "notebinaryconverter.h" // for converting note elements into binary numbers

using namespace xercesc;

int main (int argc, char* args[]) 
{
	/*  
		*********************************
		*** Xerces-C++ initialization *** 
		********************************* 
	*/
	
	//std::cout << "argc:" << argc << std::endl;

	//for(int i = 2; i < argc + 1; i++)
	//{
	//	std::cout << args[1] << "";
	//}

	//xml file extension check
	bool xmlFileCheckPassBool;
	if(argc > 0 && argc <= 2)
	{
		char* xmlFileCheck;
		xmlFileCheck = strstr(args[1],".xml");
		if( strcmp(xmlFileCheck,".xml") != 0 )
		{ 
			xmlFileCheckPassBool = false;
			std::cout << "Input an XML file! \n";
		}
		else if(strcmp(xmlFileCheck,".xml") == 0) 
		{
			xmlFileCheckPassBool = true;
			std::cout << "XML file " << args[1] << " received \n";
		}
	}	
	else 
	{
		std::cout << "Input an XML file! \n";
		xmlFileCheckPassBool = false;
	}

if(xmlFileCheckPassBool == true)
{
	try 
	{
	    XMLPlatformUtils::Initialize();
	}
    catch (const XMLException& toCatch) 
	{
        char* message = XMLString::transcode(toCatch.getMessage());
        std::cout << "Error during initialization! :\n";
        std::cout << "Exception message is: \n"
             << message << "\n";
        XMLString::release(&message);
        return 1;
    }

	/* File Paths */

	//pointer to xml file path
	const char* xmlFile = args[1];
	
	
	//pointer to xml schema file path 
	XMLCh* schemaFilePath = XMLString::transcode("musicxml.xsd");
	ArrayJanitor<XMLCh> janValue(schemaFilePath);

	/*	
		*************************************************** 
		*** Setup Parser,Parser Features and Properties ***
		*************************************************** 
	*/

	//create xml parser for reading xml file
	SAX2XMLReader* parser = XMLReaderFactory::createXMLReader();

	//setup parser features and properties     
	parser->setFeature(XMLUni::fgSAX2CoreValidation,true); // reports validation errors 
	parser->setFeature(XMLUni::fgSAX2CoreNameSpaces,true); // optional,  allows use of namespace
	parser->setFeature(XMLUni::fgXercesSchema,true); //Enable parser's schema support
	parser->setFeature(XMLUni::fgXercesLoadSchema,true); //load schema set to true
	parser->setProperty(XMLUni::fgXercesSchemaExternalNoNameSpaceSchemaLocation, schemaFilePath); //specifying schema grammar without namespace	
	parser->setFeature(XMLUni::fgXercesSchemaFullChecking, true); 
	parser->setFeature(XMLUni::fgXercesDynamic, false);

	//setup custom handler for content handler
	SAX2HandlerMusicXML* customContentHandler = new SAX2HandlerMusicXML(); //content handler
	parser->setContentHandler(customContentHandler);

	//setup default handler for error handler
	DefaultHandler* defaultHandler = new DefaultHandler(); //error handler    
	parser->setErrorHandler(defaultHandler);
	
	
	//setup custom handler for entity resolver
	MusicXMLEntityResolver* customEntityResolver = new MusicXMLEntityResolver;
	parser->setEntityResolver(customEntityResolver);

	//create vector of note objects and pass to custom content handler
	std::vector<Note> notes;	
	customContentHandler->addPointerToNotes(notes);	

	/*  
		****************************************
		*** Preprocessing and Caching Schema *** 
		****************************************
	*/	

	std::cout << "preprocessing musicxml schema... \n";
	//Preprocess the XML Schema and cache it.
	parser->loadGrammar(schemaFilePath, Grammar::SchemaGrammarType, true);

	//make parser use cached schema when processing XML file
	parser->setFeature(XMLUni::fgXercesUseCachedGrammarInParse,true); 

	/*	
		*************** 
		*** Parsing *** 
		***************
	*/

	//parse file
	try
	{
		std::cout << "parsing xml file with cached schema... \n";
		parser->parse(xmlFile);
	}

	/*  
		**********************
		*** Error Checking *** 
		**********************
	*/

	//if Xerces xml system error
	catch (const XMLException& toCatch)
	{
            char* message = XMLString::transcode(toCatch.getMessage());
            std::cout << "Xerces XML system error! \n";
            std::cout << "Exception message is: \n"
             << message << "\n";
            XMLString::release(&message);
            return -1;
	}
	//if SAX parser error
	catch (const SAXParseException& toCatch)
	{
		char* message = XMLString::transcode(toCatch.getMessage());
		std::cout << "SAX Parser error! \n";
		std::cout << "Exception message is: \n"
		 << message << "\n";
		XMLString::release(&message);
		return -1;
	}
	//if unexpected error
    catch (...)
	{
		std::cout << "Unexpected Exception \n" ;
		return -1;
	}
	
	/*
		*******************
		*** Note Output ***
		*******************
	*/

	//for every note
	for(size_t i=0; i < notes.size(); ++i)
	{
		if(i == 0)
		{
			std::cout << std::endl;
			//display instrument
			notes[i].displayInstrument();
			std::cout << " \nNumber of Notes: " << notes.size() << std::endl;
			std::cout << std::endl;
		}

		std::cout << i << std::endl;

		//display note type
		notes[i].displayNoteType();
		
		//display Time Signature
		notes[i].displayTimeSignature();
		
		//display measure number
		std::cout << " Measure Number: " << notes[i].getMeasureNumber();

		//display note duration
		std::cout << " Duration: " << notes[i].getNoteDuration() << std::endl;

		//display pitch
		notes[i].displayPitch();
		
		//display staff
		notes[i].displayStaff();

		//new line
		std::cout << "\n";
	}

	std::vector <uint16_t> binaryNotes;

	NoteBinaryConverter converter_note_binary(&notes,&binaryNotes);

	converter_note_binary.runNoteToBinaryConversion();

	std::cout << "\n Binary Notes \n";

	for(size_t i=0; i < binaryNotes.size(); ++i)
	{
		std::cout << binaryNotes[i] << std::endl;
	}

	/*
		****************
		*** Clean Up ***
		**************** 
	*/

	customContentHandler->freePointerToNotes();

	delete parser;
   	delete customContentHandler;
	delete customEntityResolver;
	delete defaultHandler;
	return 0;
}
else{return 2;}

    
}
 
