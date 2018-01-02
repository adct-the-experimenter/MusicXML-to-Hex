# MusicXML-to-Hex
Currently this program only provides a decimal number which can be converted to hex,binary,octal,etc.

Current Limitations:

-Note Information: 

  - Duration dependent on time signature, 1-8 beats
  - Time Signature 1/4, 2/4, 3/4, 4/4, 3/8, 6/8, 9/8, 12/8
  - Note Pitch (5 octaves)
  
# Required software and Libraries
-Xerces-C++ library

-Recommended any software that exports MusicXML files e.g MuseScore, Finale, Logic Pro, etc.

# How to Install
1. cd directory-where-cloned-git-repository
2. make

# How to use
$ ./musicxml-parse Test.xml

# Help
Music XML Guide:https://wpmedia.musicxml.com/wp-content/uploads/2012/12/musicxml-tutorial.pdf
Binary,Decimal,Hex,Octal Converter:http://coderstoolbox.net/number/
