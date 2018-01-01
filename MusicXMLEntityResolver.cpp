#include "MusicXMLEntityResolver.hpp"

//constructor
//MusicXMLEntityResolver::MusicXMLEntityResolver(){}

//destructor
//MusicXMLEntityResolver::~MusicXMLEntityResolver(){}


InputSource* MusicXMLEntityResolver::resolveEntity
	    (
			const   XMLCh* const    publicId
	        , const XMLCh* const    systemId
	    )
{
        char* system_id_local = XMLString::transcode(systemId);

        if(XMLString::compareString(system_id_local,"musicxml.xsd") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/musicxml.xsd");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"http://www.musicxml.org/xsd/xml.xsd") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/xml.xsd");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"http://www.musicxml.org/xsd/xlink.xsd") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/xlink.xsd");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"http://www.musicxml.org/dtds/partwise.dtd") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/partwise.dtd");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"common.mod") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/common.mod");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"isolat1.ent") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/isolat1.ent");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"isolat2.ent") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/isolat2.ent");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"layout.mod") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/layout.mod");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"identity.mod") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/identity.mod");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"attributes.mod") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/attributes.mod");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"link.mod") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/link.mod");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"note.mod") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/note.mod");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"barline.mod") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/barline.mod");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"direction.mod") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/direction.mod");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else if(XMLString::compareString(system_id_local,"score.mod") == 0)
        {
            // return input source with  file path "MusicXML_Resources/..."
            XMLCh* path = XMLString::transcode("MusicXML_Resources/score.mod");
            return new LocalFileInputSource(path);
            XMLString::release(&path);
        }
        else{return nullptr;}
	
	//free xml strings	
        XMLString::release(&system_id_local);
}
