namespace pb {

    enum BlobElementDataType {
        NULL_VALUE,
        OBJECT,
        ARRAY,
        BOOLEAN,
        STRING,
        UNSIGNED_INTEGER,
        INTEGER,
        FLOAT,
        DATE,
        BINARY
    };

    class Blob {
        public:
            Blob() = default;
            ~Blob() = default;

            // Add methods to serialize and deserialize to/from JSON, CSV, etc.
            // Add methods to handle memory mapping if needed.

        private:
            // Add private members to store metadata and data.
            void* metadata_ = nullptr; // Pointer to metadata structure
            void* data_ = nullptr;     // Pointer to the actual data
    };

} // namespace pb
