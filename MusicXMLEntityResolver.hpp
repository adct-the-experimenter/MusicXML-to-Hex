#ifndef MUSICXML_ENTITYRESOLVER_H
#define MUSICXML_ENTITYRESOLVER_H

#include <xercesc/sax/EntityResolver.hpp>
#include <xercesc/framework/LocalFileInputSource.hpp>
#include <xercesc/util/XMLString.hpp>

using namespace xercesc;

class MusicXMLEntityResolver : public EntityResolver 
{
	public:
		
            /** Default Constructor */
            //MusicXMLEntityResolver();



            /** Destructor */
           // ~MusicXMLEntityResolver();



            virtual InputSource* resolveEntity
	    (
	        const   XMLCh* const    publicId
	        , const XMLCh* const    systemId
	    );

	

};

#endif
