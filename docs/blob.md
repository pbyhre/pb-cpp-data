### Blob
The idea of this class is to create a memory structure that can story any type of data in any structure.  Given that JSON does this, if we can serialize to and from JSON, it should work for CSV or anything else.  

This should work whether the whole blob is in memory or if it is backed by a memory mapped file.

Structure 
Metadata - Initial metadata will provide info about the data and it's structure.  
- JSON - Should note that the structure is JSON and maybe provide the JSON Schema
- CSV - Store that it is CSV, what the delimiter is, number of columns and the column definitions.  Number of rows.