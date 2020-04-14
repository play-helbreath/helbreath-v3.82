

#define DEF_MAXCRUSADESTRUCTURES		300

#define DEF_MAX_STATUE_LOCATIONS		100



#define DEF_UPPERVERSION		"4"
#define DEF_LOWERVERSION 		"00"

#define DEF_BUILDDATE			1126 // Snoopy, added line to gserver.cfg file

// Those versions are hidden the client version
// they are used to change some MSGID (Anti-hgack)
#define DEF_HIDDEN_UPPERVERSION	4
#define DEF_HIDDEN_LOWERVERSION	96

#define DEF_VERSIONPLUSMODIFIER     1+(DEF_HIDDEN_LOWERVERSION % 7) 
//that can be whatever number you wish, 1 byte-sized numbers will work fine

//NB: The version check is with the MainLog server, not the gserver!
